#include <fstream>
#include <iostream>
#include <json.h>
#include <parse.h>
#include <sstream>
using namespace std;

int main()
{
    std::ifstream file("D:/qt_project/JsonParser/json_test.txt"); // 打开文件

    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf(); // 将文件内容读入缓冲区

        auto res = parse(move(buffer.str()));

        std::cout << res.first.str() << std::endl;

        file.close(); // 关闭文件
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
    return 0;
}
