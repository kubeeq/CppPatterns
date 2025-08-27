#include <iostream>
#include <vector>
#include <stdexcept>

// Версия с обычным циклом
void multiplyArray(std::vector<int>& arr, int k) {
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] *= k;
    }
}

// Версия с указателями
void multiplyArrayWithPointers(std::vector<int>& arr, int k) {
    int* ptr = arr.data(); // Получаем указатель на первый элемент
    for (size_t i = 0; i < arr.size(); i++) {
        *(ptr + i) *= k; // Изменяем значение через указатель
    }
}

// Альтернативная версия с указателями (более идиоматичная)
void multiplyArrayWithPointersAlt(std::vector<int>& arr, int k) {
    int* ptr = arr.data();
    int* end = ptr + arr.size();
    
    while (ptr < end) {
        *ptr *= k;
        ptr++;
    }
}

int main() {
    try {
        int n;
        std::cout << "Введите размер массива (n): ";
        std::cin >> n;
        
        // Проверка на корректность n
        if (n <= 0) {
            throw std::invalid_argument("n должно быть больше 0");
        }
        
        std::vector<int> arr(n);
        
        // Ввод элементов массива
        std::cout << "Введите " << n << " элементов массива:" << std::endl;
        for (int i = 0; i < n; i++) {
            if (!(std::cin >> arr[i])) {
                throw std::runtime_error("Ошибка ввода данных");
            }
        }
        
        int k;
        std::cout << "Введите множитель k: ";
        if (!(std::cin >> k)) {
            throw std::runtime_error("Ошибка ввода множителя");
        }
        
        // Сохраняем копию для второго умножения
        std::vector<int> arrCopy = arr;
        
        // Вывод исходного массива
        std::cout << "Исходный массив: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
        // Умножение через обычный цикл
        multiplyArray(arr, k);
        std::cout << "После умножения (обычный цикл): ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
        // Умножение через указатели
        multiplyArrayWithPointersAlt(arrCopy, k);
        std::cout << "После умножения (указатели): ";
        for (int num : arrCopy) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}