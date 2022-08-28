#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <functional>
#include <future>


/*
    Уламжилалт арга:
    Бүх thread санах ойг multithreading сценараар дундаа ашигладаг
        - Заагчийг үр дүнгийн утганд холбох
        - Тооцоолсон утгыг холбогдох санах ойд бичих
    Thread боломжит чөлөөлөгдсөн санах ойд ажиллах тул сегментчлэлийн алдаа үүсэх боломжтой 
    Race condition - д орохгүйн тулд thread ажиллах явцад үр дүнгийн утгуудыг мастер thread-тэй холбоотой байлгах шаардлагатай.
*/


template <
    typename value_t,
    typename index_t>
void fibo(
    value_t n,
    value_t * result) {

    value_t a_0 = 0;
    value_t a_1 = 1;

    for (index_t index = 0; index < n; index++) {
        const value_t tmp = a_0; a_0 = a_1; a_1 += tmp;
    }

    *result = a_0;
}

int main(int argc, char * argv[]) {

    const uint64_t num_threads = 32;

    std::vector<std::thread> threads;
    std::vector<uint64_t> results(num_threads);

    for (uint64_t id = 0; id < num_threads; id++) {

        threads.emplace_back(
            std::thread(
                fibo<uint64_t, uint64_t>, id, &(results[id])
            )
        );
    }

    for (auto& thread: threads)
        thread.join();

    for (auto& result: results)
        std::cout << result << std::endl;
}
