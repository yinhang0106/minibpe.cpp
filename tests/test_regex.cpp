#include <regex>
#include <iostream>
#include <string>

#include "boost/regex.hpp"

int main() {
    // Define the regular expression pattern
    boost::regex re(R"('s|'t|'re|'ve|'m|'ll|'d| ?\p{L}+| ?[0-9]+| ?[^\s\p{L}\p{N}]+)", boost::regex::icase);
    std::regex re2(R"('s|'t|'re|'ve|'m|'ll|'d| ?[a-z]+| ?[0-9]+| ?[^\s\p{L}\p{N}]+)", std::regex::icase); // Matches a pattern like 123-45-6789

    // String to match
    std::string str = "123-45-6789";
    std::string text = "Hello, world how are you 3.4";

    std::regex_token_iterator<std::string::iterator> it{text.begin(), text.end(), re2};
    std::regex_token_iterator<std::string::iterator> end;
    while (it != end)
        std::cout << *it++ << '\n';
    return 0;
}