#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono>


int int_input()		//проверка на ввод.
{
    int input;
    while (!(std::cin >> input) //соответсвие введенного значения типу переменной
        || std::cin.peek() != '\n')  //проверка на конец ввода
    {
        std::cin.clear();	//"лечим" поток. +состояние good
        while (std::cin.get() != '\n');
        std::cout << "Некорректный ввод. Повторите снова. " << std::endl;
    }
    return input;
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Перемещаем элементы arr[0..i-1], которые больше key, на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // Левый дочерний элемент
    int right = 2 * i + 2; // Правый дочерний элемент

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Если правый дочерний элемент больше текущего наибольшего
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Если наибольший элемент не корень
    if (largest != i) {
        std::swap(arr[i], arr[largest]); // Меняем местами

        // Рекурсивно "просеиваем" затронутое поддерево
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); // Перемещаем текущий корень в конец
        heapify(arr, i, 0); // Вызываем heapify на уменьшенной куче
    }
}

void printArray(std::vector<int>& arr)
{
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

std::vector<int> createRandomArray(int n) {
    std::vector<int> newVector;
    for (int i = 0; i < n; i++) {
        newVector.push_back(round(rand() % 100));
    }
    return newVector;
}

std::vector<int> createAlmostRandomArray(int n) {
    std::vector<int> newVector;
    for (int i = 0; i < n; i++) {
        newVector.push_back(round(rand() % 100) * (i+1));
    }
    return newVector;
}

std::vector<int> createManualArray(int n) {
    std::vector<int> newVector;
    for (int i = 0; i < n; i++) {
        std::cout << "Введите " << i << " элемент массива: ";
        newVector.push_back(int_input());
    }
    return newVector;
}


int main() {
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned int>(time(0)));
    int n;
    std::cout << "Введите размер массива: ";
    n = int_input();
    std::cout << std::endl;

    std::vector<int> sortArr = createRandomArray(n);
    std::vector<int> piramidArr = sortArr;
    std::vector<int> insertArr = sortArr;

    // Выводим исходный массив
    std::cout << "Исходный массив: ";
    printArray(piramidArr);

    auto start = std::chrono::high_resolution_clock::now(); // Начало отсчета времени
    insertionSort(insertArr);
    auto end = std::chrono::high_resolution_clock::now(); // Конец отсчета времени
    std::chrono::duration<double> insert_arr_duration = end - start;

    std::cout << "Сортировка вставками: ";
    printArray(insertArr);

    start = std::chrono::high_resolution_clock::now(); // Начало отсчета времени
    heapSort(piramidArr);
    end = std::chrono::high_resolution_clock::now(); // Конец отсчета времени
    std::chrono::duration<double> piramid_arr_duration = end - start;
    
    std::cout << "Пирамидальная сортировка: ";
    printArray(piramidArr);
    
    start = std::chrono::high_resolution_clock::now(); // Начало отсчета времени
    std::sort(sortArr.begin(), sortArr.end());
    end = std::chrono::high_resolution_clock::now(); // Конец отсчета времени
    std::chrono::duration<double> std_sort_duration = end - start;

    std::cout << "Стандартная сортировка: ";
    printArray(sortArr);


    std::cout << "\nВремя выполнения стандартной сортировки: " << std_sort_duration.count() << " секунд.";
    std::cout << "\nВремя выполнения сортировки вставками: " << insert_arr_duration.count() << " секунд.";
    std::cout << "\nВремя выполнения пирамидальной сортировки: " << piramid_arr_duration.count() << " секунд." << std::endl;

    std::cout << "\nУскорение стандартной сортировки по сравнению с сортировкой вставками: " << insert_arr_duration.count() / std_sort_duration.count();
    std::cout << "\nУскорение стандартной сортировки по сравнению с пирамидальной сортировкой: " << piramid_arr_duration.count() / std_sort_duration.count() << std::endl;
    

    piramidArr.clear();
    insertArr.clear();
    sortArr.clear();
}