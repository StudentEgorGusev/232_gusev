#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>
int main() {
    std::size_t n;
    if (!(std::cin >> n) || n < 16) return 0;
    std::vector<int> a(n);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 999);
    for (auto &v : a) v = dist(rng);
    std::size_t base= n/4;
    std::size_t rem  = n%4;
    long long sum = 0;
    std::mutex m;
    auto worker = [&](std::size_t l, std::size_t r) {
        long long local = 0;
        for (std::size_t i = l; i < r; ++i) local += a[i];
        std::lock_guard<std::mutex> g(m);
        sum += local;
    };
    std::vector<std::thread> th;
    std::size_t pos = 0;
    for (int i = 0; i < 4; ++i) {
        std::size_t len = base + (i < static_cast<int>(rem) ? 1u : 0u);
        th.emplace_back(worker, pos, pos + len);
        pos += len;
    }
    for (auto &t : th) t.join();
    std::cout << "Array:";
    for (int v : a) std::cout << ' ' << v;
    std::cout << '\n';
    std::cout << "Total sum: " << sum << '\n';
    return 0;
}
