#pragma once

#include <generic/types.h>
#include <generic/print.h>
#include <optional>
#include <algorithm>
#include <ranges>

#include <iostream>

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
        if(left >= right)
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

// TODO: swtich idx_mapping to struct, that only holds the diff
// between two vectors in the form of two vectors<size_t>

struct index_diff
{
    vector<size_t> old_idx, new_idx;
};

template<typename T>
index_diff map_vector_index_dif(const vector<T>& vec_old,
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
void sort_vec_with_idx_diff(const vector<size_t>& idx_mapping,
                            vector<T> vec)
{
    auto vec_old = vec;

    for(size_t old_idx = 0; const auto new_idx : idx_mapping)
    {
        vec[new_idx] = vec_old[old_idx++];
    }
}

void sort_vecs(Range auto& ref_vec, Range auto&... vecs)
{
    // generate mapping table for sorting result by comparing unsorted
    // and sorted vector; mapping is old_idx --> new_idx with:
    // vector_index --> idx_mapping[vector_index]

    auto vec_old = ref_vec;
    std::ranges::sort(ref_vec);
    vector<size_t> idx_mapping;
    idx_mapping.reserve(ref_vec.size());

    for(const auto& val : vec_old)
    {
        size_t pos_in_sorted = 0;
        std::optional<size_t> new_index = {};

        do
        {
            auto new_index_tmp = index(
                        ref_vec, val, pos_in_sorted, ref_vec.size());

            if(new_index_tmp)
            {
                new_index = new_index_tmp;
            }
        }
        while(pos_in_sorted++ < ref_vec.size() &&
              new_index &&
              exists(idx_mapping, new_index.value()));

        idx_mapping.push_back(new_index.value());
    }
    (sort_vec_with_idx_diff(idx_mapping, vecs), ...);
}

template<typename U, typename...Ts>
void erase(const vector<size_t>& idx_mapping,
           vector<U> vec, Ts... vecs)
{
    for(const auto idx : idx_mapping)
    {

    }
}


template<typename U, typename... Ts>
requires std::is_default_constructible<U>::value
void erase_where_initial(vector<U>& ref_vec, Ts&... vecs)
{
    auto where_initial = WHERE(ref_vec, return val == U{}; );

}





