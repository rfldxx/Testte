#include <cstdint>

extern "C" {
    // Формат входной строки: "a+b", где a и b - цифры '0'..'9', s[3] == '\0'
    int compute(const char* s) {
        if (!s) return -1;
        // Проверка формата: digit '+' digit '\0'
        if (s[1] != '+') return -1;
        if (s[0] < '0' || s[0] > '9') return -1;
        if (s[2] < '0' || s[2] > '9') return -1;
        if (s[3] != '\0') return -1;

        int a = s[0] - '0';
        int b = s[2] - '0';
        return a + b;
    }
}
