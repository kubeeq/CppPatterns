#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "MultiplicationStrategy.h"
#include "StrategyFactory.h"

// Реализация LoopMultiplication
void LoopMultiplication::multiply(std::vector<int>& arr, int k) {
    std::cout << "Применяется стратегия: " << getName() << std::endl;
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] *= k;
    }
}

std::string LoopMultiplication::getName() const {
    return "Умножение через цикл";
}

// Реализация PointerMultiplication
void PointerMultiplication::multiply(std::vector<int>& arr, int k) {
    std::cout << "Применяется стратегия: " << getName() << std::endl;
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

// Реализация STLMultiplication
void STLMultiplication::multiply(std::vector<int>& arr, int k) {
    std::cout << "Применяется стратегия: " << getName() << std::endl;
    for (auto& element : arr) {
        element *= k;
    }
}

std::string STLMultiplication::getName() const {
    return "Умножение через STL range-based for";
}

// Реализация ArrayMultiplier
void ArrayMultiplier::setStrategy(std::unique_ptr<MultiplicationStrategy> newStrategy) {
    strategy = std::move(newStrategy);
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

// Реализация StrategyFactory
std::unique_ptr<MultiplicationStrategy> StrategyFactory::create(StrategyType type) {
    switch (type) {
        case LOOP:
            return std::make_unique<LoopMultiplication>();
        case POINTERS:
            return std::make_unique<PointerMultiplication>();
        case STL:
            return std::make_unique<STLMultiplication>();
        default:
            throw std::invalid_argument("Неизвестный тип стратегии");
    }
}

void StrategyFactory::printAvailableStrategies() {
    std::cout << "\nДоступные стратегии:" << std::endl;
    std::cout << "1 - Умножение через цикл" << std::endl;
    std::cout << "2 - Умножение через указатели" << std::endl;
    std::cout << "3 - Умножение через STL" << std::endl;
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
        
        // Выбор стратегии через фабрику
        StrategyFactory::printAvailableStrategies();
        
        int choice;
        std::cout << "\nВыберите способ умножения: ";
        if (!(std::cin >> choice)) {
            throw std::runtime_error("Ошибка выбора стратегии");
        }
        
        // Создание стратегии через фабрику
        auto strategy = StrategyFactory::create(static_cast<StrategyFactory::StrategyType>(choice));
        
        ArrayMultiplier multiplier;
        multiplier.setStrategy(std::move(strategy));
        
        // Вывод исходного массива и суммы
        std::cout << "\n";
        printArray(arr, "Исходный массив");
        std::cout << "Сумма элементов (через указатели): " << sumArrayWithPointers(arr) << std::endl;
        
        // Применение выбранной стратегии
        multiplier.multiplyArray(arr, k);
        
        // Вывод результатов
        printArray(arr, "Результат");
        std::cout << "Новая сумма элементов: " << sumArrayWithPointers(arr) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
