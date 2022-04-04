#pragma once

#include <generic/types.h>
#include <algorithm>
#include <ranges>

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
        std::swap(vec[left++], vec[right--]);
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
vector<T*> get_value_ptr(const vector<T>& vec,
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

#define WHERE(vec, cond) where<decltype(vec)::value_type>( \
    vec, [](const auto& val){ cond; });

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
index_diff get_vector_index_diff(const vector<T>& vec_old,
                                 const vector<T>& vec_new)
{
    index_diff result;

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
void sort_vec_with_idx_diff(const index_diff& idx_diff,
                            vector<T>& vec)
{
    // start to read the idx_diff table: read first move operation:
    // move val from idx_old to idx_new; rememeber val at the moved
    // to idx; at the next iteration move remembered value from the
    // previously moved to idx and so on

    size_t move_tab_idx = 0;
    std::optional<size_t> new_move_tab_idx = {};
    T moved_to_value = vec[idx_diff.old_idx[move_tab_idx]];

    for(size_t n = 0; n < idx_diff.old_idx.size(); n++)
    {
        move_tab_idx = new_move_tab_idx ? new_move_tab_idx.value() : 0;
        auto tmp = vec[idx_diff.new_idx[move_tab_idx]];
        vec[idx_diff.new_idx[move_tab_idx]] = moved_to_value;
        moved_to_value = std::move(tmp);
        new_move_tab_idx = index(idx_diff.old_idx,
                                 idx_diff.new_idx[move_tab_idx]);
    }
}

void sort_vecs(Range auto& ref_vec, Range auto&... vecs)
{
    auto vec_old = ref_vec;
    std::ranges::sort(ref_vec);
    auto idx_diff = get_vector_index_diff(vec_old, ref_vec);
    (sort_vec_with_idx_diff(idx_diff, vecs), ...);
}





