#include <json.h>

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

JsonParser::Json::Json(std::map<std::string, JsonParser::Json> obj_sp)
{
    this->m_type = json_object;
    this->m_value = obj_sp;
}
