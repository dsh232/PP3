#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono>

int int_input() {
    int input;
    while (!(std::cin >> input) || std::cin.peek() != '\n') {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Некорректный ввод. Повторите снова. " << std::endl;
    }
    return input;
}

char char_input()
{
    char input;
    while (!(std::cin >> input) || std::cin.peek() != '\n')
    {
        std::cin.clear();
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

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void heapIfY(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapIfY(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapIfY(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapIfY(arr, i, 0);
    }
}

void printArray(const std::vector<int>& arr) {
    int arr_size = arr.size();
    if (arr_size > 23) {
        std::cout << "\nПервые 10 элементов: ";
        for (int i = 0; i < 10; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
        std::cout << "Последние 10 элементов: ";
        for (int i = arr_size - 10; i < arr_size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
    else {
        for (int i = 0; i < arr_size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<int> createRandomArray(int n) {
    std::vector<int> newVector;
    for (int i = 0; i < n; i++) {
        newVector.push_back(rand() % 100); // Генерация случайных чисел от 0 до 99
    }
    return newVector;
}

std::vector<int> createAlmostRandomArray(int n) {
    std::vector<int> newVector;
    for (int i = 0; i < n; i++) {
        newVector.push_back(rand() % 100 * (i + 1)); // Почти отсортированные данные
    }
    return newVector;
}

std::vector<int> createManualArray(int n) {
    std::vector<int> newVector;
    for (int i = 0; i < n; i++) {
        std::cout << "Введите " << i + 1 << " элемент массива: "; 
        newVector.push_back(int_input());
    }
    return newVector;
}

void howCreateArray(std::vector<int>& vec, int arr_size) {
    int answer;
    std::cout << "Как бы вы хотели заполнить данные в вектор? \n1 - ручной ввод,\n2 - случайные данные,\n3 - 'почти отсортированные' случайные данные." << std::endl;

    answer = int_input();
    std::cout << std::endl;

    if (answer == 1) {
        vec = createManualArray(arr_size); // Сохраняем результат
    }
    else if (answer == 2) {
        vec = createRandomArray(arr_size); // Сохраняем результат
    }
    else if (answer == 3) {
        vec = createAlmostRandomArray(arr_size); // Сохраняем результат
    }
    else {
        std::cout << "Некорректный ввод. Введите цифры 1 или 2 или 3\n";
        howCreateArray(vec, arr_size); // Повторный вызов для корректного ввода
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    bool is_need_next_run = false; //создание флага для повторного запуска программы
    while (is_need_next_run == false) {     

        int arr_size;

        std::cout << "Введите размер массива: ";
        arr_size = int_input();

        std::vector<int> sortArr; // Инициализация вектора для хранения данных
        howCreateArray(sortArr, arr_size); // Заполнение вектора

        // Выводим исходный массив
        std::cout << "Исходный массив: ";
        printArray(sortArr);

        // Копируем массив для различных сортировок
        auto insertArr = sortArr;
        auto piramidArr = sortArr;

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

        // Вывод времени выполнения
        std::cout << "\nВремя выполнения стандартной сортировки: " << std_sort_duration.count() << " секунд.";
        std::cout << "\nВремя выполнения сортировки вставками: " << insert_arr_duration.count() << " секунд.";
        std::cout << "\nВремя выполнения пирамидальной сортировки: " << piramid_arr_duration.count() << " секунд." << std::endl;

        // Ускорение стандартной сортировки по сравнению с другими методами
        if (insert_arr_duration.count() > 0)
            std::cout << "\nУскорение стандартной сортировки по сравнению с сортировкой вставками: "
            << insert_arr_duration.count() / std_sort_duration.count();

        if (piramid_arr_duration.count() > 0)
            std::cout << "\nУскорение стандартной сортировки по сравнению с пирамидальной сортировкой: "
            << piramid_arr_duration.count() / std_sort_duration.count() << std::endl;

        
        bool is_need_processed = false;
        do {
            std::cout << "Хотите продолжить? (Y/N):  ";
            char answer = char_input();
            if (answer == 'N') {
                std::cout << "Пока!" << std::endl;
                is_need_next_run = true;
                is_need_processed = true;
            }
            else if (answer == 'Y') {
                std::cout << "Продолжить? конечно!" << std::endl;
                is_need_processed = true;
            }

        } while (is_need_processed == false);
    }
}