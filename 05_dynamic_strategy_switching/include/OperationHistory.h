#ifndef OPERATION_HISTORY_H
#define OPERATION_HISTORY_H

#include <vector>
#include <string>
#include <deque>

// Структура для хранения истории операций
struct OperationHistory {
    std::string strategyName;
    int multiplier;
    std::vector<int> previousState;
    
    OperationHistory(const std::string& name, int k, const std::vector<int>& state);
};

#endif // OPERATION_HISTORY_H
