#pragma once

#include <generic/types.h>

#include <iostream>
#include <numeric>

// TODO: bugfix: this call leads to endless loop,
// presumably because table name is too long for table width
// print_table print("Indices where val == 1", result);

struct print_table
{
    vector<uint64> column_widths_ = {};
    uint32 table_width_ = 0;
    const string field_name_header_ = "Field name";
    uint32 field_name_width_ = field_name_header_.length();
    vector<string> field_names_ = {};
    int64 current_row_ = -1;

    template<typename... Ts>
    print_table(const string&& table_name,
                const vector<string>&& field_names,
                const vector<Ts>&... vecs):
        field_names_(field_names)
    {
        prepare_field_name_data(vecs...);
        (calculate_column_width(vecs), ...);
        table_width_ = calculate_table_width();
        print_hor_line();
        print_header(table_name);
        print_hor_line();
        print_column_indices();
        print_hor_line();
        (print_table_row(vecs), ...);
        print_hor_line();
        delete this;
    }

    template<typename... Ts>
    print_table(const string&& table_name,
                const vector<Ts>&... vecs)
    {
        prepare_field_name_data(vecs...);
        (calculate_column_width(vecs), ...);
        table_width_ = calculate_table_width();
        print_hor_line();
        print_header(table_name);
        print_hor_line();
        print_column_indices();
        print_hor_line();
        (print_table_row(vecs), ...);
        print_hor_line();
        delete this;
    }

    template<typename... Ts>
    print_table(const vector<Ts>&... vecs)
    {
        prepare_field_name_data(vecs...);
        (calculate_column_width(vecs), ...);
        table_width_ = calculate_table_width();
        print_hor_line();
        print_header("");
        print_hor_line();
        print_column_indices();
        print_hor_line();
        (print_table_row(vecs), ...);
        print_hor_line();
        delete this;
    }

    template<typename... Ts>
    void prepare_field_name_data(const vector<Ts>&... vecs)
    {
        if(field_names_.size() < sizeof...(vecs))
        {
            for(size_t i = field_names_.size(); i < sizeof...(vecs); i++)
            {
                field_names_.emplace_back("field" + stringify(i));
            }
        }
        for(const auto &field_name : field_names_)
        {
            if(field_name.length() > field_name_width_)
            {
                field_name_width_ = field_name.length();
            }
        }
    }

    template<typename T>
    void calculate_column_width(const vector<T>& vec)
    {
        //TODO: f32 wants to output 8 characters, even if 0; fix this
        if(column_widths_.size() < vec.size())
        {
            column_widths_.resize(vec.size(), 3);
        }
        for(size_t i = 0; const auto& val : vec)
        {
            auto len = stringify(val).length() > (stringify(i).length() + 2) ?
                        stringify(val).length() : stringify(i).length() + 2;

            if(len > column_widths_[i])
            {
                column_widths_[i] = len;
            }
            i++;
        }
    }

    template<typename T>
    string stringify(const T& input)
    {
        return input;
    }

    template<typename T>
    requires std::is_integral<T>::value || std::is_floating_point<T>::value
    string stringify(const T& input)
    {
        return std::to_string(input);
    }

    uint32 calculate_table_width()
    {
        return 1 +
                field_name_width_ + 1 +
                column_widths_.size() +
                std::accumulate(
                    column_widths_.begin(), column_widths_.end(), 0);
    }

    void print_hor_line()
    {
        for(uint32 i = 1; i <= table_width_; i++)
        {
            std::cout << "-";
        }
        nl();
    }

    void print_header(const string& table_name)
    {
        string name = table_name == "" ? "Table" : table_name;
        print_line(name);
    }

    void print_line(const string& str)
    {
        std::cout << "|" << str;

        for(uint32 i = 0; i < table_width_ - str.length() - 2; i++)
        {
            std::cout << " ";
        }
        std::cout << "|"; nl();
    }

    void print_column_indices()
    {
        if(current_row_ == -1)
        {
            std::cout << "|";

            for(uint64 padding = 1;
                (padding <= field_name_width_ - field_name_header_.length());
                 padding++)
            {
                std::cout << " ";
            }
            std::cout << field_name_header_;
            current_row_++;
        }

        std::cout << "|";

        for(uint64 i = 0; const auto width : column_widths_)
        {
            for(uint64 padding = 1;
                padding <= (width - 2 - stringify(i).length()); padding++)
            {
                std::cout << " ";
            }
            std::cout << "[" << i << "]|";
            i++;
        }
        nl();
    }

    template<typename T>
    void print_table_row(const vector<T>& vec)
    {
        std::cout << "|";

        for(uint64 padding = 1;
            padding <= (field_name_width_ - field_names_[current_row_].length());
            padding++)
        {
            std::cout << " ";
        }
        std::cout << field_names_[current_row_];
        current_row_++;

        std::cout << "|";

        for(uint64 i = 0; const auto& val : vec)
        {
            for(uint64 padding = 1;
                padding <= (column_widths_[i] - stringify(val).length());
                padding++)
            {
                std::cout << " ";
            }
            std::cout << stringify(val) << "|";
            i++;
        }
        nl();
    }

    void nl()
    {
        std::cout << "\n";
    }
};


template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}
