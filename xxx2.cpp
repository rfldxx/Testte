// emcc filename.cpp -o calc.wasm -O3 -s WASM=1 -s EXPORTED_FUNCTIONS='["_createCalc","_calcF","_calcG","_freeString","_deleteCalc"]'   --no-entry -s ALLOW_MEMORY_GROWTH=1

#include <emscripten.h>
#include <string>
#include <cstring>

class Calc {
private:
    int x;
    std::string message;
public:
    Calc(int xx = 0) : x(xx), message("Hello!") {}
    
    int f(int y) { 
        return x * y; 
    }
    
    std::string g() { 
        return message; 
    }
};

// Функции для работы с классом через C-интерфейс
extern "C" {
    
    // Создание нового экземпляра Calc
    EMSCRIPTEN_KEEPALIVE
    Calc* createCalc(int x) {
        return new Calc(x);
    }
    
    // Вызов метода f
    EMSCRIPTEN_KEEPALIVE
    int calcF(Calc* calc, int y) {
        return calc->f(y);
    }
    
    // Вызов метода g (возвращает строку)
    // Внимание: выделяем память для строки, нужно освобождать в JS!
    EMSCRIPTEN_KEEPALIVE
    char* calcG(Calc* calc) {
        std::string result = calc->g();
        char* buffer = new char[result.length() + 1];
        std::strcpy(buffer, result.c_str());
        return buffer;
    }
    
    // Освобождение памяти строки
    EMSCRIPTEN_KEEPALIVE
    void freeString(char* str) {
        delete[] str;
    }
    
    // Удаление экземпляра Calc
    EMSCRIPTEN_KEEPALIVE
    void deleteCalc(Calc* calc) {
        delete calc;
    }
}
// ТУПОСТЬ, требуется python 3.10 который фиг пойми как устанавливать... (ужас, че так всё противно сделано, зачем столько мороки, зачем им этот match понадобился, ради чего??? какой смысл, чтобы написать на одну строчку короче, но зато надо запомнитьь новое бесполезное название функцииии???? вот c c++ молодцы, а это фу)
// ./emsdk install  latest
// ./emsdk activate latest


// ЭТО проходит с python 3.8
// ./emsdk install  3.1.14
// ./emsdk activate 3.1.14

// source ./emsdk_env.sh