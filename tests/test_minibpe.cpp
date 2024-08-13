#include "minibpe.h"

#include <benchmark/benchmark.h>

//using stat_type = std::map<std::pair<int, int>, int>;
//
//static void BM_BPE_BENCHMARK(benchmark::State &state) {
//    int round = 10;
//    auto tokens = tokens_generate();
//    int new_token = 1000;
//    for (auto _: state) {
//        for (int k = 0; k < round; ++k) {
//            // calculate stats
//            stat_type stats_map;
//            for (size_t i = 0; i < tokens.size() - 1; ++i)
//                stats_map.insert_or_assign({tokens[i], tokens[i + 1]}, stats_map[{tokens[i], tokens[i + 1]}] + 1);
//
//            // find the most frequent pair in this round
//            auto max_it = std::max_element(stats_map.begin(), stats_map.end(), [](auto const &a, auto const &b) {
//                return a.second < b.second;
//            });
//            std::cout << "Most frequent pair of round #" << (k + 1) << ": " << max_it->first.first << " "
//                      << max_it->first.second << " " << max_it->second << "\n";
//
//            // merge the most frequent pair
//            tokens.find_assign_shrink({max_it->first.first, max_it->first.second}, new_token);
//
//            ++new_token;
//        }
//        benchmark::DoNotOptimize(state.iterations());
//    }
//}
//BENCHMARK(BM_BPE_BENCHMARK);


static void BM_BPE_BENCHMARK2(benchmark::State &state) {
    int round = 100;
    auto tokens = tokens_generate();
    int new_token = 1000;
    for (auto _: state) {
        for (int k = 0; k < round; ++k) {
            // find the most frequent pair in this round
            auto max_it = std::max_element(tokens.g_stats_map.begin(), tokens.g_stats_map.end(),
                                           [](auto const &a, auto const &b) {
                                               return a.second < b.second;
                                           });

//            if (max_it->second == 1) break;

            std::cout << "Most frequent pair of round #" << (k + 1) << ": " << max_it->first.first << " "
                      << max_it->first.second << " " << max_it->second << "\n";

            // merge the most frequent pair
            tokens.find_assign_shrink({max_it->first.first, max_it->first.second}, new_token);

            ++new_token;
        }
        benchmark::DoNotOptimize(state.iterations());
    }
}
BENCHMARK(BM_BPE_BENCHMARK2);


BENCHMARK_MAIN();