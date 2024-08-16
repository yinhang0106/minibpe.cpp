#include "minibpe.h"

#include <fstream>


int main() {

    // 读取file.txt文件内容, 并打印到控制台
    std::ifstream ifs;
    ifs.open("./file.txt", std::ios::in);
    if (!ifs.is_open()) {
        std::cerr << "Error: open file failed." << std::endl;
        return 1;
    }

    std::string line;
    while (getline(ifs, line)) {
        std::cout << line << std::endl;
        break;
    }
    ifs.close();

    std::cout << line << std::endl;

    std::vector<unsigned char> vec;
    for (unsigned char c : line)
        vec.emplace_back(c);

    for (auto const &val : vec)
        std::cout << (int)val << " ";
    std::cout << std::endl;

    JumpVector<int> tokens = JumpVector<int>(vec.begin(), vec.end());

//    auto tokens = tokens_generate(0, 125, 1000);
    int round = 100;
    int new_token = 1000;
    bytes_pair_encode(tokens, round, new_token);

    return 0;
}