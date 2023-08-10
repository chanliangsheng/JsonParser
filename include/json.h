#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace JsonParser {
class Json {

public:
    // 标注这个Json是什么类型
    enum Type {
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_vector,
        json_object
    };

public:
    // Json可以是bool,int,double,string,vector,map(or unorder_map)
    std::variant<int, double, bool, std::shared_ptr<std::string>, std::shared_ptr<std::vector<Json>>, std::shared_ptr<std::map<std::string, Json>>> m_value;
    Type m_type;

    // 构造函数
public:
    Json();
    Json(int num);
    Json(double num);
    Json(bool log);
    Json(std::shared_ptr<std::string> str_sp);
    Json(std::shared_ptr<std::vector<Json>> vector_sp);
    Json(std::shared_ptr<std::map<std::string, Json>> obj_sp);

public:
    std::string str();
};
};
