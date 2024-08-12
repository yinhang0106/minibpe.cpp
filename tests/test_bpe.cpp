#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <map>
#include <format>

auto tokens_generate() {
    // auto seed = std::random_device{}();
    auto seed = 24;
    auto rng = std::mt19937(seed);
    std::uniform_int_distribution<int> dist(0, 25);
    std::vector<int> data(1000);
    std::ranges::generate(data, [&](){ return dist(rng); });
    return data;
}

template <typename T>
void print(std::vector<T> const& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << std::format("{: <4d}", v[i]);
        if ((i + 1) % 20 == 0)
            std::cout << "\n";
        else
            std::cout << " ";
    }
    std::cout << "\n";
}

template <class T1, class T2>
requires std::same_as<T1, std::pair<int, int>>
void print(std::map<T1, T2> const& m) {
    for (auto const& [k, v] : m)
        std::cout << std::format("{: <4d} {: <4d} {: <4d}\n", k.first, k.second, v);
}

using stat_type = std::map<std::pair<int, int>, int>;

stat_type stats(auto const& v) {
    stat_type stats_map;
    for (int i = 0; i < v.size() - 1; i++)
        stats_map.insert_or_assign({v[i], v[i + 1]}, stats_map[{v[i], v[i + 1]}] + 1);
    return stats_map;
}

std::vector<int> merge(std::vector<int> const& tokens, auto const& key, int new_token) {
    std::vector<int> new_tokens;
    for (int i = 0; i < tokens.size() - 1; ) {
        if (tokens[i] == key.first && tokens[i + 1] == key.second) {
            new_tokens.push_back(new_token);
            i += 2;
        } else {
            new_tokens.push_back(tokens[i++]);
        }
    }
    return new_tokens;
}

auto bytes_pair_encode(std::vector<int>& tokens, int round) {
}

int main () {
    auto tokens = tokens_generate();
    print(tokens);
    auto stats_map = stats(tokens);
    print(stats_map);
    auto max_it = std::max_element(stats_map.begin(), stats_map.end(), [] (auto const& a, auto const& b) { return a.second < b.second; });
    auto key = max_it->first;
    std::cout << std::format("Most common pair: {} {}\n", key.first, key.second);
    auto new_tokens = merge(tokens, key, 26);
    print(new_tokens);
}
