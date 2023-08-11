#include <parse.h>

using namespace JsonParser;
using namespace std;

pair<Json, int> parse(string_view str)
{
    // 如果第一个字符是"，说明这是个字符串
    if (str[0] == '"') {
        shared_ptr<string> res = make_shared<string>();
        // 从第一个下标开始往后看
        size_t index;
        for (index = 1; index < str.size(); index++) {
            // 如果不是最后一个字符的字符，则加入res中
            if (str[index] != '"') {
                res->push_back(str[index]);
            }
            // 指向"的下一个字符
            else {
                return { Json(res), index + 1 };
            }
        }
        return { Json(), 0 };
    } else if (size_t off = str.find_first_not_of(" \n\t\a\b,"); off != 0 && off < str.size()) {
        auto [obj, eaten] = parse(str.substr(off));
        return { move(obj), off + eaten };
    }
    // 如果第一个字符是0-9或者是+或者-，那么说明是数字
    else if ((str[0] >= '0' && str[0] <= '9') || str[0] == '+' || str[0] == '-') {
        // 正则表达式识别科学计数法
        regex pattern { "[+-]?[0-9]+(\\.[0-9]*)?([eE][+-]?[0-9]+)?" };
        cmatch match;
        // 用正则表达式将数字识别，放入match中
        // 如果成功
        if (regex_search(str.begin(), str.begin() + str.size(), match, pattern)) {
            // 如果match里面是int，如果是int，转换为int类型的Json；如果是double，转换成double类型的Json
            if (auto res = convert_to_num<int>(match.str()); res.has_value()) {
                return { Json(res.value()), match.size() + 1 };
            } else {
                return { Json(convert_to_num<double>(match.str()).value()), match.size() + 1 };
            }
        }
        return { Json(), 0 };
    }

    // 如果第一个字符是[，则说明是含有多个Json对象的向量
    else if (str[0] == '[') {
        shared_ptr<vector<Json>> res = make_shared<vector<Json>>();
        size_t i;
        // 遍历加入res
        for (i = 1; i < str.size();) {
            if (str[i] == ']') {
                i++;
                break;
            }
            // 判断这个Json占据了多少个字符
            auto [obj, eaten] = parse(str.substr(i));
            if (eaten == 0) {
                i = 0;
                break;
            }
            i += eaten;
            res->push_back(move(obj));
            if (str[i] == ',') {
                i++;
            }
        }
        return { Json(res), i + 1 };
    }

    else if (str[0] == '{') {
        shared_ptr<map<string, Json>> res = make_shared<map<string, Json>>();
        size_t i;
        for (i = 1; i < str.size();) {
            if (str[i] == '}') {
                i++;
                break;
            }
            // 计算key
            auto [key_obj, key_eaten] = parse(str.substr(i));

            //            cout << key_obj.str() << endl;
            if (key_eaten == 0) {
                i = 0;
                break;
            }

            i += key_eaten;
            // 防止':'之前有杂的字符
            size_t off = str.substr(i).find_first_not_of(" \n\t\a\b,");
            i += off;
            // 跳过':'
            if (str[i] == ':') {
                i++;
            }
            // 计算value
            auto [value_obj, value_eaten] = parse(str.substr(i));

            //            cout << value_obj.str() << endl;
            if (value_eaten == 0) {
                i = 0;
                break;
            }

            i += value_eaten;

            // 加入结果中
            res->insert({ key_obj.str(), value_obj });

            if (str[i] == ',') {
                i++;
            }

            size_t off2 = str.substr(i).find_first_not_of(" \n\t\a\b,");
            i += off2;
        }

        return { Json(res), i + 1 };
    }

    return { Json(), 0 };
}
