#include <json.h>

using namespace std;
JsonParser::Json::Json()
{
    this->m_type = json_null;
    this->m_value = 0;
}

JsonParser::Json::Json(int num)
{
    this->m_type = json_int;
    this->m_value = num;
}

JsonParser::Json::Json(double num)
{
    this->m_type = json_double;
    this->m_value = num;
}

JsonParser::Json::Json(bool log)
{
    this->m_type = json_bool;
    this->m_value = log;
}

JsonParser::Json::Json(std::shared_ptr<std::string> str_sp)
{
    this->m_type = json_string;
    this->m_value = str_sp;
}

JsonParser::Json::Json(std::shared_ptr<std::vector<JsonParser::Json>> vector_sp)
{
    this->m_type = json_vector;
    this->m_value = vector_sp;
}

JsonParser::Json::Json(std::shared_ptr<std::map<string, JsonParser::Json>> obj_sp)
{
    this->m_type = json_object;
    this->m_value = obj_sp;
}

std::string JsonParser::Json::str()
{
    if (this->m_type == json_int) {
        return to_string(get<int>(m_value));
    } else if (this->m_type == json_bool) {
        return to_string(get<bool>(m_value));
    } else if (this->m_type == json_null) {
        return 0;
    } else if (this->m_type == json_double) {
        return to_string(get<double>(m_value));
    } else if (this->m_type == json_object) {
        string res;
        res += '{';
        shared_ptr<map<string, Json>> m_object = get<shared_ptr<map<string, Json>>>(m_value);
        for (auto itr = m_object->begin(); itr != m_object->end(); itr++) {
            if (itr != m_object->begin()) {
                res += ',';
            }
            res += itr->first;
            res += ':';
            res += itr->second.str();
        }
        res += '}';
        return res;

    } else if (this->m_type == json_string) {
        string res;
        res += '"';
        res += *(get<shared_ptr<string>>(m_value));
        res += '"';
        return res;
    } else if (this->m_type == json_vector) {
        string res;
        res += '[';
        shared_ptr<vector<Json>> m_v = get<shared_ptr<vector<Json>>>(m_value);
        for (auto itr = m_v->begin(); itr != m_v->end(); itr++) {
            if (itr != m_v->begin()) {
                res += ',';
            }
            res += itr->str();
        }
        res += ']';
        return res;
    }
    return 0;
}
