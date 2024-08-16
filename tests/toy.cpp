#include <fstream>
#include <vector>
#include <string>

#include <iostream>

#include "minibpe.h"


int main() {
    std::ifstream ifs("file.txt");
    if (!ifs.is_open())
        std::cerr << "Error: file is not open!";

    std::string str;
    getline(ifs, str);
    std::cout << str << std::endl;

    std::vector<int> tokens;
    for (auto & c : str)
        tokens.emplace_back((unsigned char)(c));

    std::cout << "length of context is " << tokens.size() << "\n";
    for (auto const& val : tokens)
        std::cout << val << " ";
    std::cout << "\n";

    Tokenizer<int> tokenizer{tokens.begin(), tokens.end()};

    tokenizer.print_stats();


}