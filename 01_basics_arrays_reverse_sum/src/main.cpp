#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>

// Функция для создания вектора с числами от 1 до n (с проверкой)
std::vector<int> createArray(int n) {
    if (n <= 0) {
        throw std::invalid_argument("n должно быть положительным!");
    }
    std::vector<int> arr;
    arr.reserve(n);
    for (int i = 1; i <= n; ++i) {
        arr.push_back(i);
    }
    return arr;
}

// Функция для подсчёта суммы элементов вектора
int calculateSum(const std::vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

// Форматированный вывод чисел
void printFormatted(const std::string& message, const std::vector<int>& arr) {
    std::cout << message;
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

// Вывод в обратном порядке через reverse-итераторы
void printReverse(const std::vector<int>& arr) {
    std::cout << "Обратный порядок (через итераторы): ";
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Вывод в обратном порядке через стек
void printReverseStack(const std::vector<int>& arr) {
    std::cout << "Обратный порядок (через стек): ";
    std::stack<int> numStack;
    for (int num : arr) {
        numStack.push(num);
    }
    while (!numStack.empty()) {
        std::cout << numStack.top() << " ";
        numStack.pop();
    }
    std::cout << std::endl;
}

// Обратный вывод через указатели + изменение элементов
void printAndModifyViaPointers(std::vector<int>& arr) {
    std::cout << "Обратный порядок (через указатели + модификация): ";
    if (arr.empty()) return;

    int* ptr = arr.data() + arr.size() - 1;
    while (ptr >= arr.data()) {
        std::cout << *ptr << " ";
        *ptr *= 2;
        --ptr;
    }
    std::cout << "\nМассив после модификации: ";
    printFormatted("", arr);
}

int main() {
    try {
        int n;
        std::cout << "Введите число n: ";
        std::cin >> n;

        if (!std::cin || n <= 0) {
            throw std::invalid_argument("Ошибка: n должно быть положительным числом!");
        }

        std::vector<int> numbers = createArray(n);
        printFormatted("Исходный массив: ", numbers);

        printReverse(numbers);
        printReverseStack(numbers);
        printAndModifyViaPointers(numbers);

        int sum = calculateSum(numbers);
        std::cout << "Сумма всех чисел: " << sum << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "⚠️ Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
