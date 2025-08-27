#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "MultiplicationStrategy.h"

// Реализация LoopMultiplication
void LoopMultiplication::multiply(std::vector<int>& arr, int k) {
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] *= k;
    }
}

std::string LoopMultiplication::getName() const {
    return "Умножение через цикл";
}

// Реализация PointerMultiplication
void PointerMultiplication::multiply(std::vector<int>& arr, int k) {
    int* ptr = arr.data();
    int* end = ptr + arr.size();
    
    while (ptr < end) {
        *ptr *= k;
        ptr++;
    }
}

std::string PointerMultiplication::getName() const {
    return "Умножение через указатели";
}

// Реализация ArrayMultiplier
void ArrayMultiplier::setStrategy(std::unique_ptr<MultiplicationStrategy> newStrategy) {
    strategy = std::move(newStrategy);
    if (strategy) {
        std::cout << "✓ Применена стратегия: " << strategy->getName() << std::endl;
    }
}

void ArrayMultiplier::multiplyArray(std::vector<int>& arr, int k) {
    if (strategy) {
        strategy->multiply(arr, k);
    } else {
        throw std::runtime_error("Стратегия не установлена!");
    }
}

bool ArrayMultiplier::hasStrategy() const {
    return strategy != nullptr;
}

// Вспомогательные функции
int sumArrayWithPointers(const std::vector<int>& arr) {
    const int* ptr = arr.data();
    const int* end = ptr + arr.size();
    int sum = 0;
    
    while (ptr < end) {
        sum += *ptr;
        ptr++;
    }
    
    return sum;
}

void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": ";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
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
        
        // Выбор стратегии
        int choice;
        std::cout << "Выберите способ умножения (1 = цикл, 2 = указатели): ";
        if (!(std::cin >> choice)) {
            throw std::runtime_error("Ошибка выбора стратегии");
        }
        
        ArrayMultiplier multiplier;
        
        switch (choice) {
            case 1:
                multiplier.setStrategy(std::make_unique<LoopMultiplication>());
                break;
            case 2:
                multiplier.setStrategy(std::make_unique<PointerMultiplication>());
                break;
            default:
                std::cout << "Неверный выбор, используется стратегия по умолчанию (цикл)" << std::endl;
                multiplier.setStrategy(std::make_unique<LoopMultiplication>());
                break;
        }
        
        // Вывод исходного массива и суммы
        std::cout << "\n";
        printArray(arr, "Исходный массив");
        std::cout << "Сумма элементов (через указатели): " << sumArrayWithPointers(arr) << std::endl;
        
        // Применение выбранной стратегии
        multiplier.multiplyArray(arr, k);
        
        // Вывод результатов
        printArray(arr, "После умножения");
        std::cout << "Новая сумма элементов: " << sumArrayWithPointers(arr) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}