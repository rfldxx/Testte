let wasmModule = null;

// Инициализация WebAssembly
async function initWasm() {
    try {
        // Загружаем WebAssembly модуль
        const response = await fetch('fibonacci.wasm');
        const buffer = await response.arrayBuffer();
        
        // Компилируем и инстанцируем модуль
        const module = await WebAssembly.compile(buffer);
        const instance = await WebAssembly.instantiate(module, {
            env: {
                memoryBase: 0,
                tableBase: 0,
                memory: new WebAssembly.Memory({ initial: 256 }),
                table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
            }
        });
        
        wasmModule = instance.exports;
        console.log('✅ WebAssembly модуль загружен');
    } catch (error) {
        console.error('❌ Ошибка загрузки WebAssembly:', error);
        document.getElementById('result').innerHTML = 
            '<span style="color: red;">Ошибка загрузки WebAssembly модуля</span>';
    }
}

// Вычислить одно число Фибоначчи
function calculateSingle() {
    if (!wasmModule) {
        alert('WebAssembly модуль ещё не загружен');
        return;
    }
    
    const input = document.getElementById('fibInput');
    const n = parseInt(input.value);
    
    if (isNaN(n) || n < 0) {
        alert('Пожалуйста, введите положительное число');
        return;
    }
    
    const startTime = performance.now();
    const result = wasmModule.fibonacci(n);
    const endTime = performance.now();
    
    const timeTaken = (endTime - startTime).toFixed(4);
    
    document.getElementById('result').innerHTML = `
        <strong>Число Фибоначчи F(${n}) = ${result}</strong><br>
        ⏱ Время вычисления: ${timeTaken} мс<br>
        🚀 Выполнено в WebAssembly (C++)
    `;
}

// Вычислить последовательность чисел Фибоначчи
function calculateSequence() {
    if (!wasmModule) {
        alert('WebAssembly модуль ещё не загружен');
        return;
    }
    
    const input = document.getElementById('fibInput');
    const n = parseInt(input.value);
    
    if (isNaN(n) || n < 0) {
        alert('Пожалуйста, введите положительное число');
        return;
    }
    
    const startTime = performance.now();
    
    // Вызываем C++ функцию, которая возвращает указатель на массив
    const ptr = wasmModule.fibonacci_sequence(n);
    
    // Читаем массив из памяти WebAssembly
    const sequence = [];
    for (let i = 0; i <= n; i++) {
        // Читаем 4-байтовое целое число (int)
        const value = new Int32Array(wasmModule.memory.buffer, ptr + i * 4, 1)[0];
        sequence.push(value);
    }
    
    // Освобождаем память, выделенную в C++
    wasmModule.free_memory(ptr);
    
    const endTime = performance.now();
    const timeTaken = (endTime - startTime).toFixed(4);
    
    document.getElementById('result').innerHTML = `
        <strong>Последовательность Фибоначчи до F(${n}):</strong><br>
        ${sequence.join(', ')}<br><br>
        ⏱ Время вычисления: ${timeTaken} мс<br>
        🚀 Выполнено в WebAssembly (C++)<br>
        📊 Всего чисел: ${sequence.length}
    `;
}

// Загружаем WebAssembly при загрузке страницы
window.onload = initWasm;
