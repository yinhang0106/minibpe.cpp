#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <utf8.h>


int main() {
    std::string const s = "你好";
    std::cout << std::format("句子的长度是 {}。", s.size()) << std::endl;

    std::u32string const u32s = U"你好";
    std::cout << std::format("句子的长度是 {}。", u32s.size()) << std::endl;

    std::vector<std::string> slogan = {
            "小彭老师公开课万岁", "全世界程序员大团结万岁",
    };
    std::string joined;
    for (auto const &str: slogan) {
        joined += str; // 只是拼接而已，UTF-8 没问题
    }
    std::cout << joined << std::endl;

    std::u32string s2 = U"你好";
    for (auto const &c: s2) {
        std::cout << std::format("{:d} ", static_cast<unsigned char>(c));
    }
    std::cout << std::endl;

    // convert utf32 string to utf8 string
    for (auto h = utf8::utf32to8(s2); auto const &c: h) {
        printf("%d ", static_cast<unsigned char>(c));
    }

}