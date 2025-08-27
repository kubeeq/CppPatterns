#ifndef MULTIPLICATION_STRATEGY_H
#define MULTIPLICATION_STRATEGY_H

#include <vector>
#include <memory>
#include <string>

// Базовый интерфейс стратегии
class MultiplicationStrategy {
public:
    virtual ~MultiplicationStrategy() = default;
    virtual void multiply(std::vector<int>& arr, int k) = 0;
    virtual std::string getName() const = 0;
};

// Конкретная стратегия: умножение через обычный цикл
class LoopMultiplication : public MultiplicationStrategy {
public:
    void multiply(std::vector<int>& arr, int k) override;
    std::string getName() const override;
};

// Конкретная стратегия: умножение через указатели
class PointerMultiplication : public MultiplicationStrategy {
public:
    void multiply(std::vector<int>& arr, int k) override;
    std::string getName() const override;
};

// Конкретная стратегия: умножение через STL
class STLMultiplication : public MultiplicationStrategy {
public:
    void multiply(std::vector<int>& arr, int k) override;
    std::string getName() const override;
};

// Контекст, который использует стратегию
class ArrayMultiplier {
private:
    std::unique_ptr<MultiplicationStrategy> strategy;
    
public:
    void setStrategy(std::unique_ptr<MultiplicationStrategy> newStrategy);
    void multiplyArray(std::vector<int>& arr, int k);
    bool hasStrategy() const;
};

// Вспомогательные функции
int sumArrayWithPointers(const std::vector<int>& arr);
void printArray(const std::vector<int>& arr, const std::string& label = "Массив");

#endif // MULTIPLICATION_STRATEGY_H
