#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <deque>
#include "MultiplicationStrategy.h"
#include "StrategyFactory.h"
#include "OperationHistory.h"

// Реализация OperationHistory
OperationHistory::OperationHistory(const std::string& name, int k, const std::vector<int>& state)
    : strategyName(name), multiplier(k), previousState(state) {}

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

// Реализация TransformMultiplication
void TransformMultiplication::multiply(std::vector<int>& arr, int k) {
    std::transform(arr.begin(), arr.end(), arr.begin(),
                  [k](int x) { return x * k; });
}

std::string TransformMultiplication::getName() const {
    return "Умножение через std::transform";
}

// Реализация RangeMultiplication
void RangeMultiplication::multiply(std::vector<int>& arr, int k) {
    for (auto& element : arr) {
        element *= k;
    }
}

std::string RangeMultiplication::getName() const {
    return "Умножение через range-based for";
}

// Реализация StrategyFactory
std::unique_ptr<MultiplicationStrategy> StrategyFactory::create(StrategyType type) {
    switch (type) {
        case LOOP:
            return std::make_unique<LoopMultiplication>();
        case POINTERS:
            return std::make_unique<PointerMultiplication>();
        case TRANSFORM:
            return std::make_unique<TransformMultiplication>();
        case RANGE:
            return std::make_unique<RangeMultiplication>();
        default:
            throw std::invalid_argument("Неизвестный тип стратегии");
    }
}

void StrategyFactory::printAvailableStrategies() {
    std::cout << "\n=== ДОСТУПНЫЕ СТРАТЕГИИ ===" << std::endl;
    std::cout << "1 - Умножение через цикл" << std::endl;
    std::cout << "2 - Умножение через указатели" << std::endl;
    std::cout << "3 - Умножение через std::transform" << std::endl;
    std::cout << "4 - Умножение через range-based for" << std::endl;
    std::cout << "=== КОМАНДЫ ===" << std::endl;
    std::cout << "undo - Отменить последнюю операцию" << std::endl;
    std::cout << "history - Показать историю операций" << std::endl;
    std::cout << "exit - Выход из программы" << std::endl;
}

// Контекст, который использует стратегию
class ArrayMultiplier {
private:
    std::unique_ptr<MultiplicationStrategy> strategy;
    std::deque<OperationHistory> history;
    const size_t MAX_HISTORY = 10;
    
public:
    void setStrategy(std::unique_ptr<MultiplicationStrategy> newStrategy) {
        strategy = std::move(newStrategy);
        if (strategy) {
            std::cout << "✓ Применена стратегия: " << strategy->getName() << std::endl;
        }
    }
    
    void multiplyArray(std::vector<int>& arr, int k) {
        if (strategy) {
            saveHistory(arr, k);
            int oldSum = sumArrayWithPointers(arr);
            strategy->multiply(arr, k);
            int newSum = sumArrayWithPointers(arr);
            std::cout << "Сумма до: " << oldSum << " → Сумма после: " << newSum << std::endl;
        } else {
            throw std::runtime_error("Стратегия не установлена!");
        }
    }
    
    void saveHistory(const std::vector<int>& arr, int k) {
        if (history.size() >= MAX_HISTORY) {
            history.pop_front();
        }
        history.emplace_back(strategy->getName(), k, arr);
    }
    
    bool undo(std::vector<int>& arr) {
        if (history.empty()) {
            std::cout << "❌ Нет операций для отмены" << std::endl;
            return false;
        }
        
        const auto& lastOp = history.back();
        arr = lastOp.previousState;
        std::cout << "✓ Отменена операция: " << lastOp.strategyName 
                  << " с множителем " << lastOp.multiplier << std::endl;
        history.pop_back();
        return true;
    }
    
    void printHistory() const {
        if (history.empty()) {
            std::cout << "История операций пуста" << std::endl;
            return;
        }
        
        std::cout << "\n=== ИСТОРИЯ ОПЕРАЦИЙ ===" << std::endl;
        for (size_t i = 0; i < history.size(); i++) {
            const auto& op = history[i];
            std::cout << i + 1 << ". " << op.strategyName 
                      << " (k=" << op.multiplier << ")" << std::endl;
        }
    }
    
    bool hasStrategy() const {
        return strategy != nullptr;
    }
    
    size_t getHistorySize() const {
        return history.size();
    }
};

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

void printArray(const std::vector<int>& arr, const std::string& label = "Массив") {
    std::cout << label << ": [ ";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << " ";
    }
    std::cout << " ]" << std::endl;
}

std::vector<int> inputArray() {
    int n;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> n;
    
    if (n <= 0) {
        throw std::invalid_argument("Размер массива должен быть больше 0");
    }
    
    std::vector<int> arr(n);
    std::cout << "Введите " << n << " элементов массива:" << std::endl;
    
    for (int i = 0; i < n; i++) {
        std::cout << "Элемент " << i + 1 << ": ";
        std::cin >> arr[i];
    }
    
    return arr;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int main() {
    try {
        std::cout << "=== ДИНАМИЧЕСКАЯ СИСТЕМА УМНОЖЕНИЯ МАССИВОВ ===" << std::endl;
        
        std::vector<int> arr = inputArray();
        ArrayMultiplier multiplier;
        
        while (true) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            printArray(arr, "Текущий массив");
            std::cout << "Сумма элементов: " << sumArrayWithPointers(arr) << std::endl;
            std::cout << "Операций в истории: " << multiplier.getHistorySize() << std::endl;
            
            StrategyFactory::printAvailableStrategies();
            
            std::cout << "\nВведите команду: ";
            std::string input;
            std::cin >> input;
            
            if (input == "exit") {
                std::cout << "Завершение работы..." << std::endl;
                break;
            }
            else if (input == "undo") {
                multiplier.undo(arr);
                clearInputBuffer();
                continue;
            }
            else if (input == "history") {
                multiplier.printHistory();
                clearInputBuffer();
                continue;
            }
            
            try {
                int choice = std::stoi(input);
                auto strategy = StrategyFactory::create(static_cast<StrategyFactory::StrategyType>(choice));
                multiplier.setStrategy(std::move(strategy));
                
                int k;
                std::cout << "Введите множитель k: ";
                std::cin >> k;
                
                multiplier.multiplyArray(arr, k);
                
            } catch (const std::invalid_argument&) {
                std::cout << "❌ Ошибка: неверная команда! Попробуйте снова." << std::endl;
            } catch (const std::out_of_range&) {
                std::cout << "❌ Ошибка: неверный номер стратегии!" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "❌ Ошибка: " << e.what() << std::endl;
            }
            
            clearInputBuffer();
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
