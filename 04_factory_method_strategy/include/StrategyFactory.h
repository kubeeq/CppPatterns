#ifndef STRATEGY_FACTORY_H
#define STRATEGY_FACTORY_H

#include <memory>
#include <stdexcept>
#include "MultiplicationStrategy.h"

// Фабрика стратегий
class StrategyFactory {
public:
    enum StrategyType {
        LOOP = 1,
        POINTERS = 2,
        STL = 3
    };

    static std::unique_ptr<MultiplicationStrategy> create(StrategyType type);
    static void printAvailableStrategies();
};

#endif // STRATEGY_FACTORY_H
