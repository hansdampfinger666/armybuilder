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
// requries from and to to be in bounds
{
    for(size_t idx = from; idx < to; idx++)
    {
        if(vec[idx] == what)
        {
            return idx;
        }
    }
    return {};
}

template<typename T>
bool exists(const vector<T>& vec, const T& what)
{
    for(auto elem : vec)
    {
        if(elem == what)
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
    size_t idx_last_non_initial = vec.size();

    while(idx_last_non_initial > -1)
    {
        if(vec[idx_last_non_initial] != initial)
        {
            break;
        }
        idx_last_non_initial--;
    }
    if(idx_last_non_initial > 0)
    {
        uint64 number_initial = 0;

        for(size_t i = 0; i < idx_last_non_initial; i++)
        {
            if(vec[i] == initial)
            {
                number_initial++;
            }
        }
        return number_initial / idx_last_non_initial;
    }
    return 1;
}

template<typename T>
vector<T> defrag(const vector<T>& vec_i)
{
    // TODO: make this variadic and swap all values in all vectors at once
    // making copying the result into a brand new vector to
    // have a diff for the other vectors obsolete

    vector<T> result(vec_i.size());
    T initial = {};
    size_t idxa = 0;
    size_t idxb = vec_i.size() - 1;

    while(idxb > idxa)
    {
        if(vec_i[idxa] != initial)
        {
            result[idxa] = vec_i[idxa];
            idxa++;
            continue;
        }

        if(vec_i[idxb] == initial)
        {
            idxb--;
            continue;
        }
        result[idxa++] = vec_i[idxb--];
    }
    return result;
}

template<typename T>
vector<size_t> index_all(const vector<T>& vec)
{
    vector<size_t> result;
    result.reserve(vec.size());

    for(size_t index = 0; index < vec.size(); index++)
    {
        result.push_back(index);
    }
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


void sort_vec_with_idx_diff(const vector<size_t>& idx_mapping,
                            Range auto& vec)
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


template<typename U, typename... Ts>
requires std::is_default_constructible<U>::value
void erase_where_initial(vector<U>& ref_vec, Ts&... vecs)
{

}





