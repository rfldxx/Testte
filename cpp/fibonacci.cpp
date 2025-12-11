#include <emscripten.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
int fibonacci(int n) {
    if (n <= 1) return n;
    
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

EMSCRIPTEN_KEEPALIVE
int* fibonacci_sequence(int n) {
    int* result = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; i++) {
        if (i <= 1) {
            result[i] = i;
        } else {
            result[i] = result[i-1] + result[i-2];
        }
    }
    
    return result;
}

EMSCRIPTEN_KEEPALIVE
void free_memory(int* ptr) {
    free(ptr);
}

}
