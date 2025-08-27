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

// Конкретная стратегия: умножение через STL transform
class TransformMultiplication : public MultiplicationStrategy {
public:
    void multiply(std::vector<int>& arr, int k) override;
    std::string getName() const override;
};

// Конкретная стратегия: умножение через range-based for
class RangeMultiplication : public MultiplicationStrategy {
public:
    void multiply(std::vector<int>& arr, int k) override;
    std::string getName() const override;
};

#endif // MULTIPLICATION_STRATEGY_H
