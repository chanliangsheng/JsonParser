#pragma once
#include <json.h>
#include <regex>

std::pair<JsonParser::Json, int> parse(std::string_view str);

// 把string转换为数字，根据不同情况转换为int和double
template <typename T>
std::optional<T> convert_to_num(std::string_view ss)
{
    T value;
    std::istringstream iss(ss.data());
    if (iss >> value && iss.eof()) {
        return value;
    }
    return std::nullopt;
}
