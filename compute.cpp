// emcc xxx2.cpp -o calc.js -O3 -s MODULARIZE=1 -s EXPORT_NAME='createModule' -s EXPORTED_FUNCTIONS='["_createCalc","_deleteCalc","_calcF","_calcG","_allocateMemory","_freeMemory"]' -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","UTF8ToString","allocate","ALLOC_NORMAL"]' -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s ENVIRONMENT='web'

// Компиляция C++ в WASM 

// calc.cpp
#include <emscripten.h>
#include <string>
#include <cstring>
#include <cstdlib>

// Простой класс Calc
class Calc {
private:
    int x;
    
public:
    Calc(int xx = 0) : x(xx) {}
    
    int f(int y) { 
        return x * y; 
    }
    
    const char* g() {
        // Используем статический буфер для простоты
        static char buffer[100];
        std::string result = "Hello! x = " + std::to_string(x);
        strcpy(buffer, result.c_str());
        return buffer;
    }
};

// C-стиль функции для работы с классом из JavaScript
extern "C" {
    // Создание экземпляра класса
    EMSCRIPTEN_KEEPALIVE
    Calc* createCalc(int x) {
        return new Calc(x);
    }
    
    // Удаление экземпляра класса
    EMSCRIPTEN_KEEPALIVE
    void deleteCalc(Calc* calc) {
        delete calc;
    }
    
    // Вызов метода f
    EMSCRIPTEN_KEEPALIVE
    int calcF(Calc* calc, int y) {
        if (!calc) return 0;
        return calc->f(y);
    }
    
    // Вызов метода g - возвращаем строку
    // Внимание: для простоты используем статический буфер
    EMSCRIPTEN_KEEPALIVE
    const char* calcG(Calc* calc) {
        if (!calc) return "Error: null pointer";
        return calc->g();
    }
    
    // Вспомогательная функция для выделения памяти в WASM
    EMSCRIPTEN_KEEPALIVE
    void* allocateMemory(int size) {
        return malloc(size);
    }
    
    // Вспомогательная функция для освобождения памяти
    EMSCRIPTEN_KEEPALIVE
    void freeMemory(void* ptr) {
        free(ptr);
    }
}



// ТУПОСТЬ, требуется python 3.10 который фиг пойми как устанавливать... (ужас, че так всё противно сделано, зачем столько мороки, зачем им этот match понадобился, ради чего??? какой смысл, чтобы написать на одну строчку короче, но зато надо запомнитьь новое бесполезное название функцииии???? вот c c++ молодцы, а это фу)
// ./emsdk install  latest
// ./emsdk activate latest


// ЭТО проходит с python 3.8
// ./emsdk install  3.1.14
// ./emsdk activate 3.1.14

// source ./emsdk_env.sh
