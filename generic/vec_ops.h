#pragma once

#include <generic/types.h>
#include <algorithm>
#include <ranges>

/*
 * Definitions
*/

#define WHERE(vec, cond) where<decltype(vec)::value_type>( \
    vec, [](const auto& val){ cond; });

struct index_diff
{
    // this index_diff is the result of a calculation of difference
    // between two vectors v1 and v2
    // it describes all move operations that have to take place within
    // v1 to get v2 as a result:
    // move_operation[n...] --> v1[new_idx[n...]] = v1[old_idx[n...]]
    // so that at the end: v1 == v2
    vector<size_t> old_idx, new_idx;
};

template<typename T>
struct value_groups
{
    vector<T> group_values;
    vector<size_t> group_index_from, group_index_to;
};

template<typename T>
concept Range = std::ranges::range<T>;


template<typename T>
std::optional<size_t> index(const vector<T>& vec, const T& what)
{
    for(size_t idx = 0; auto elem : vec)
    {
        if(elem == what)
        {
            return idx;
        }
        idx++;
    }
    return {};
}

template<typename T>
std::optional<size_t> index(const vector<T>& vec, const T& what,
                            const size_t from, const size_t to)
{
    for(size_t index = from; index < to; index++)
    {
        if(vec[index] == what)
        {
            return index;
        }
    }
    return {};
}

template<typename T>
vector<size_t> where(const vector<T>& vec, bool(*cond)(const T& val))
{
    vector<size_t> result;

    for(size_t i = 0; const auto& val : vec)
    {
        if(cond(val))
        {
            result.push_back(i);
        }
        i++;
    }
    return result;
}

template<typename T>
bool exists(const vector<T>& vec, const T& what)
{
    for(const auto& elem : vec)
    {
        if(elem == what)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
bool exists(const vector<T>& vec, const T& what,
            const size_t from, const size_t to)
{
    static_assert(to <= vec.size());

    for(size_t index = from; index < to; index++)
    {
        if(vec[index] == what)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
f32 calc_frag(const vector<T>& vec)
{
    T initial = {};
    size_t right = vec.size() - 1;

    for(; right > 0;  right--)
    {
        if(vec[right] != initial)
        {
            break;
        }
    }
    uint64 number_initial = 0;

    for(size_t left = 0; left < right; left++)
    {
        if(vec[left] == initial)
        {
            number_initial++;
        }
    }
    if((f32)right == 0.f || (f32)number_initial == 0.f)
    {
        return 0.f;
    }
    return (f32)number_initial / (f32)right;
}

template<typename U, typename ...Ts>
requires std::is_default_constructible<U>::value
void defrag(vector<U>& vec, Ts... vecs)
{
    U initial = {};
    size_t left = 0;
    size_t right = vec.size() - 1;

    while(true)
    {
        while(vec[left] != initial)
        {
            left++;
        }
        while(vec[right] == initial)
        {
            right--;
        }
        if(left > right)
        {
            break;
        }
        std::swap(vec[left], vec[right]);
        (std::swap(vecs[left], vec[right]), ...);
        left++;
        right--;
    }
}

template<typename T>
vector<size_t> index_all(const vector<T>& vec)
{
    vector<size_t> result(vec.size());
    size_t index = 0;
    std::ranges::generate(result, [&index]() mutable { return index++; });
    return result;
}

template<typename T>
requires std::is_default_constructible<T>::value
vector<size_t> index_where_not_initial(const vector<T>& vec)
{
    T initial = {};
    vector<size_t> result;
    result.reserve(vec.size());

    for(size_t index = 0; auto& entry : vec)
    {
        if(entry != initial)
        {
            result.push_back(index);
        }
        index++;
    }
    return result;
}

template<typename T>
vector<T> get_values(const vector<T>& vec,
                     const vector<size_t>& vec_indexes)
{
    if(vec_indexes.size() > vec.size())
    {
        return vector<T>{};
    }
    vector<T> values;
    values.reserve(vec_indexes.size());

    for(size_t values_index = 0; const auto index : vec_indexes)
    {
        values[values_index++] = vec[index];
    }
    return values;
}

template<typename T>
vector<T*> get_value_ptrs(const vector<T>& vec,
                         const vector<size_t>& vec_indexes)
{
    if(vec_indexes.size() > vec.size())
    {
        return vector<T*>{};
    }
    vector<T*> value_refs;
    value_refs.reserve(vec_indexes.size());

    for(size_t value_refs_index = 0; const auto index : vec_indexes)
    {
        value_refs[value_refs_index++] = &(vec[index]);
    }
    return value_refs;
}

template<typename T>
index_diff get_vector_index_diff(const vector<T>& vec_old,
                                 const vector<T>& vec_new)
{
    index_diff result {&vec_old, &vec_new};

    for(size_t pos_in_old = 0; pos_in_old < vec_old.size(); pos_in_old++)
    {
        if(vec_new[pos_in_old] == vec_old[pos_in_old])
        {
            continue;
        }
        size_t pos_in_new = 0;
        std::optional<size_t> new_index = {};

        do
        {
            auto new_index_tmp = index(
                        vec_new, vec_old[pos_in_old],
                        pos_in_new, vec_old.size());

            if(new_index_tmp)
            {
                new_index = new_index_tmp;
                pos_in_new = new_index.value() + 1;
            }
        }
        while(pos_in_new < vec_old.size() &&
              new_index &&
             (vec_old[pos_in_new - 1] == vec_new[pos_in_new - 1] ||
              exists(result.new_idx, new_index.value())));

        if(!new_index)
        {
            continue;
        }
        result.old_idx.push_back(pos_in_old);
        result.new_idx.push_back(new_index.value());
    }
    return result;
}

template<typename T>
int partition(vector<T>& vec, const int begin_index, const int end_index,
              Range auto&... vecs)
{
    const auto pivot = &vec[end_index];
    int swap = begin_index - 1;

    for(int comp = begin_index; comp <= end_index; comp++)
    {
        if(vec[comp] < *pivot)
        {
            swap++;
            std::swap(vec[swap], vec[comp]);
            (std::swap(vecs[swap], vecs[comp]), ...);
        }
    }
    std::swap(vec[swap + 1], vec[end_index]);
    (std::swap(vecs[swap + 1], vecs[end_index]), ...);
    return swap + 1;
}

template<typename T>
void quick_sort_impl(vector<T>& vec, const int64 begin_index, const int64 end_index,
                     Range auto&... vecs)
{
    if(begin_index < end_index)
    {
        auto partition_index = partition(vec, begin_index, end_index, vecs...);
        quick_sort_impl(vec, begin_index, partition_index - 1, vecs...);
        quick_sort_impl(vec, partition_index + 1, end_index, vecs...);
    }
}

template<typename T>
bool quick_sort(vector<T>& vec, Range auto&... vecs)
{
    if(vec.size() == 1)
    {
        return true;
    }
    bool sizes_illegal = false;

    auto size_illegal = [&](const auto& vec, const auto& vec_comp){
        sizes_illegal = vec_comp.size() < vec.size() ? true : false;
    };
    (size_illegal(vec, vecs), ...);

    if(sizes_illegal)
    {
        return false;
    }
    uint64 begin_index = 0;
    uint64 end_index = vec.size() - 1;
    quick_sort_impl(vec, begin_index, end_index, vecs...);
    return true;
}

template<typename T>
bool quick_sort(vector<T>& vec, const int64 begin_index, const int64 end_index,
                Range auto&... vecs)
{
    if(vec.size() == 1)
    {
        return true;
    }
    if(begin_index < 0 || end_index > vec.size() - 1)
    {
        return false;
    }
    bool sizes_illegal = false;

    auto size_illegal = [&](const auto& vec, const auto& vec_comp){
        sizes_illegal = vec_comp.size() < vec.size() ? true : false;
    };
    (size_illegal(vec, vecs), ...);

    if(sizes_illegal)
    {
        return false;
    }
    quick_sort_impl(vec, begin_index, end_index, vecs...);
    return true;
}


template<typename T>
value_groups<T> get_value_groups(vector<T>& vec)
{
    if(vec.size() == 0)
    {
        return {};
    }
    value_groups<T> value_groups;
    T* last_val = nullptr;

    for(size_t index = 0; const auto& val : vec)
    {
        if(!last_val)
        {
            value_groups.group_values.push_back(val);
            value_groups.group_index_from.push_back(index);
            last_val = &vec[index];
            index++;
            continue;
        }
        if(val != *last_val)
        {
            value_groups.group_index_to.push_back(index - 1);
            value_groups.group_values.push_back(val);
            value_groups.group_index_from.push_back(index);
            last_val = &vec[index];
            index++;
            continue;
        }
        last_val = &vec[index];
        index++;
    }
    value_groups.group_index_to.push_back(vec.size() - 1);
    return value_groups;
}


template<typename T>
bool quick_sort_by_value_groups(vector<T>& vec, value_groups<T>& value_groups,
                                Range auto&... vecs)
{
    for(size_t i = 0; i < value_groups.group_index_from.size(); i++)
    {
        (quick_sort_impl(vec, value_groups.group_index_from,
                         value_groups.group_index_to, vecs), ...);
    }
}
