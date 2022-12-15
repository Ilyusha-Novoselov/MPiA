#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

#include "tsp.h"
const int N = 11;

int main(int argc, char* argv[]) {
    setlocale(0, "");
    srand(time(0));
    for (int n = 7; n <= N; n++)
    {
        Graph g;
        g.random_graph(n);
        int start_vertex = rand() % n;
        cout << "Для N = " << n << endl;
        auto t1 = std::chrono::high_resolution_clock::now();
        auto a = tsp_native(g, start_vertex);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Наивная реализация: " << time << " Длина пути: " << Length(g, a) << endl;
        
        t1 = std::chrono::high_resolution_clock::now();
        a = tsp_bnb(g, start_vertex);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Метод ветвей и границ: " << time << " Длина пути: " << Length(g, a) << endl;

        t1 = std::chrono::high_resolution_clock::now();
        a = tsp_greedy(g, start_vertex);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Жадный алгоритм: " << time << " Длина пути: " << Length(g, a) << endl;

        t1 = std::chrono::high_resolution_clock::now();
        a = tsp(g, start_vertex);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Метод локального поиска: " << time << " Длина пути: " << Length(g, a) << endl;
        cout << endl;
    }


    int result = Catch::Session().run(argc, argv);
    return result;
}
