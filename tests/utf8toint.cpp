#include <iostream>
#include <string>
#include <vector>

std::vector<int> utf8StringToIntList(const std::u8string& utf8String) {
    std::vector<int> intList;
    for (unsigned char c : utf8String) {
        intList.push_back(static_cast<int>(c));
    }
    return intList;
}

int main() {
    std::u8string s = u8"你好";
    std::vector<int> intList = utf8StringToIntList(s);

    for (int i : intList) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}