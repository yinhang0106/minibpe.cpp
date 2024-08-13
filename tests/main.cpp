#include "minibpe.h"

#include <fstream>


int main() {

    // 读取file.txt文件内容, 并打印到控制台
    std::ifstream in;
    in.open("./file.txt", std::ios::in);
    if (!in.is_open()) {
        std::cerr << "Error: open file failed." << std::endl;
        return 1;
    }

    std::string line;
    while (getline(in, line)) {
        std::cout << line << std::endl;
    }

//    int round = 100;
//    auto tokens = tokens_generate(0, 125, 1000);
//    int new_token = 1000;
//    bytes_pair_encode(tokens, round, new_token);

    return 0;
}