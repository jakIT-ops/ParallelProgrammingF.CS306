#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <future>


/*
    Promises, Futures хэрэглэх арга 
    - Асинхрон ажиллагааны шинж чанарыг хангасан c++ -ын буцаах утгын механизм
    - s = (p, f) Харилцан холбоотой хослолыг тодорхойлно.
        -   p: promise, зөвхөн мэдээлэл солилцох шатанд 1 удаа утга олгоно
        -   f: future promise-оор мэдээлэл солилцсоны дараа хандана
    - Мастер thread болон хуулбар thread хоёрын хооронд сонхрончлох механизм болгон хэрэглэх p,f-ын хамааралыг байгуулна.
    - promise хэзээ ч ажиллахгүй бол future - ийг унших гэж оролсоноор түгжрэл (deadlock) үүсэх боломжтой
    
*/

template <
    typename value_t,
    typename index_t>
void fibo(
    value_t n,
    std::promise<value_t> && result) {

    value_t a_0 = 0;
    value_t a_1 = 1;

    for (index_t index = 0; index < n; index++) {
        const value_t tmp = a_0; 
        a_0 = a_1; 
        a_1 += tmp;
    }

    result.set_value(a_0);
}

int main(int argc, char * argv[]) {

    const uint64_t num_threads = 32;

    std::vector<std::thread> threads;
    std::vector<std::future<uint64_t>> results;

    for (uint64_t id = 0; id < num_threads; id++) {
        std::promise<uint64_t> promise;
        results.emplace_back(promise.get_future());

        threads.emplace_back(
            std::thread(
                fibo<uint64_t, uint64_t>, id, std::move(promise)
            )
        );
    }

    for (auto& result: results)
        std::cout << result.get() << std::endl;

    for (auto& thread: threads)
        thread.detach();

}
