#pragma once

#include <QStringList>

#include <generic/types.h>


template<typename T>
QString qt_conv(const T& input)
{
    return QString::fromStdString(input);
}

template<typename T>
requires std::is_integral<T>::value
QString qt_conv(const T& input)
{
    return QString::number(input);
}

template<typename T>
QStringList qt_conv(const vector<T>& vec)
{
    QStringList qlist;

    for(const auto& val : vec)
    {
        qlist << qt_conv(val);
    }
    return qlist;
}
