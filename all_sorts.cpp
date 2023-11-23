#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <queue>

template <typename T>
void print_arr(const std::vector<T> arr) {
    std::cout << "{ ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "}" << std::endl;
}

// СОРТИРОВКА ВСТАВКАМИ
template <typename T>
void insertionSort(std::vector<T>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        size_t key = arr[i];
        size_t j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// СОРТИРОВКА ВЫБОРОМ
template <typename T>
void selectionSort(std::vector<T>& arr) {
    size_t n = arr.size();

    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIndex = i;

        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }

        if (minIndex != i)
            std::swap(arr[i], arr[minIndex]);
    }
}

// СОРТИРОВКА ШЕЛЛА
template <typename T>
void shell_sort(std::vector<T>& arr)
{
    for (int d = arr.size() / 2; d > 0; d /= 2)
    {
        for (int i = d; i < arr.size(); ++i)
        {
            for (int j = i - d; j >= 0 && arr[j] > arr[j + d]; j -= d)
            {
                std::swap(arr[j], arr[j + d]);
            }
        }
    }
};

// ПОРАЗРЯДНАЯ СОРТИРОВКА
template <typename T>
void radixSort(std::vector<T>& arr) {
    // O(кол-во разрядов * (n + 10)) 
    T Max = arr[0];
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > Max) Max = arr[i];
    }

    size_t n = arr.size();
    T* out = new T[n]; //mem  O(n+k) ~ O(n)
    for (int del = 1; Max / del > 0; del *= 10) {
        int count[10] = { 0 };
        for (int i = 0; i < n; i++)
            count[(arr[i] / del) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            out[count[(arr[i] / del) % 10] - 1] = arr[i];
            count[(arr[i] / del) % 10]--;
        }


        std::memcpy(arr.begin(), out, arr.size() * sizeof(T));
    }

    delete[] out;

}









// ПИРАМИДАЛЬНАЯ СОРТИРОВКА

/*
    arr = {10, 5, 9, 1, 3, 2, 11, 9, 4, 1, 8}
    Куча
                         10 [0]
              5 [1]                    9 [2]
       1 [3]         3 [4]       2 [5]     11 [6]
  9 [7]   4 [8]  1 [9]   8 [10]

  Если i-ый элемент корень кучи (или "под-кучи") то:
  Левый дочерний элемент - с индексом 2i + 1
  Правый дочерний элемент - с индексом 2i + 2

  n/2 - 1 = 4
  1) arr = {10, 5, 9, 1, *3, 2, 11, 9, 4, _1, _8}
  2) arr = {10, 5, 9, *1, 8, 2, 11, _9, _4, 1, 3}
  3) arr = {10, 5, *9, 9, 8, _2, _11, 1, 4, 1, 3}
  4) arr = {10, *5, 11, _9, _8, 2, 9, 1, 4, 1, 3}
  5) arr = {10, 9, 11, *5, 8, 2, 9, _1, _4, 1, 3}
  6) arr = {*10, _9, _11, 5, 8, 2, 9, 1, 4, 1, 3}
  7) arr = {11, 9, *10, 5, 8, _2, _9, 1, 4, 1, 3}

*/

template<typename T>
void heapify(T* arr, int64_t i, int64_t n) {

    int64_t left_i = 2 * i + 1;
    int64_t right_i = 2 * i + 2;
    int64_t largest_i = i;

    if ((left_i < n) && (arr[left_i] > arr[largest_i]))
        largest_i = left_i;

    if ((right_i < n) && (arr[right_i] > arr[largest_i]))
        largest_i = right_i;

    if (largest_i != i) {
        std::swap(arr[i], arr[largest_i]);
        heapify(arr, largest_i, n);
    }

}


template<typename T>
void heap_sort(T* arr, int64_t n) {

    //Строим кучу (самый большой элемент станет корнем i = 0)
    // (0.5 * n) * log(n)
    for (int64_t i = (n / 2) - 1; i >= 0; i--)
        heapify(arr, i, n);


    // n * log(n)
    for (int64_t i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]); //перемещаем корень
        heapify(arr, 0, i); // Преобразуем уменьшенную кучу
    }

    // Общая сложность O (1.5 * n * log(n)) ~ O (n*log(n))

}




// СОРТИРОВКА СЛИЯНИЕМ
template <typename T>
void MergeSort1(std::vector<T>& arr, std::vector<T>& buffer, uint64_t l, uint64_t r) {
    if (r - l < 1) return;
    if (r - l == 1) {
        if (arr[l] > arr[l + 1]) std::swap(arr[l], arr[l + 1]);
        return;
    }

    uint64_t m = (l + r) / 2;
    MergeSort1(arr, buffer, l, m);
    MergeSort1(arr, buffer, m + 1, r);

    uint64_t k = l;
    for (uint64_t i = l, j = m + 1; i <= m || j <= r; ) {
        if (j > r || (i <= m && arr[i] < arr[j])) {
            buffer[k] = arr[i];
            ++i;
        }
        else {
            buffer[k] = arr[j];
            ++j;
        }

        ++k;
    }

    std::memcpy(arr.data() + l, buffer.data() + l, (r - l + 1) * sizeof(T));
}

template <typename T>
void merge_sort(std::vector<T>& arr) {
    if (!arr.empty()) {
        std::vector<T> buffer(arr.size());
        MergeSort1(arr, buffer, 0, arr.size() - 1);
    }
}





// БЫСТРАЯ СОРТИРОВКА

/*
    Дан массив arr = [4, 9, 7, 6, 2, 3, 8]
    Пусть p опорный элемент

    p = arr[ (r + l) / 2 ]

    i                 j
    4, 9, 7, 6, 2, 3, 8
    l        ^        r

    Инкрементируем i пока не найдем элемент больше опорного.
    Декрементируем j пока не найдем элемент меньше опорного.

       i           j
    4, 9, 7, 6, 2, 3, 8                 Плохой случай
    l        ^        r             
                                    i                  j
          i     j                   4, 9, 7, 50, 2, 3, 30
    4, 3, 7, 6, 2, 9, 8             l        ^         r
    l        ^        r             
                                              i        j
                                    4, 9, 7, 50, 2, 3, 30
             j                      l                  r
             i                                   i  j
    4, 3, 2, 6, 7, 9, 8             4, 9, 7, 30, 2, 3, 50
    l        ^        r             l                  r
                                                    j   i 
                                    4, 9, 7, 30, 2, 3, 50
                                    l                  r
             
          j     i
    4, 3, 2, 6, 7, 9, 8                        Пусть длина N
    l        ^        r          
                                                     N
    i     j       i     j                     N/2         N/2
    4, 3, 2       7, 9, 8                 N/4     N/4  N/4   N/4
    l  ^  r       l  ^  r
                                            Уровней log(N). 
                                    На каждом уровне располагаем элементы меньше опорного 
    j  p  i          i  j           в левой части, а элементы больше опорного в правой.
    2, 3, 4       7, 9, 8           За O(N)
    l     r       l     r
                    
                     j  i
                  7, 8, 9

*/

template <typename T>
void qq_sort(std::vector<T>& arr, int l, int r) {
    if (l >= r) return;

    int i = l, j = r;
    T middle = arr[(l + r) / 2];


    while (i <= j) {
        while (arr[i] < middle) i++;
        while (middle < arr[j]) j--;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++; j--;
        }
    }


    qq_sort(arr, l, j);
    qq_sort(arr, i, r);

}

template <typename T>
void q_sort(std::vector<T>& arr) {
    qq_sort(arr, 0, arr.size() - 1);
}



void create_input(const std::string& file_path, size_t numbers_count) {
    std::ofstream f;
    f.open(file_path);
    if (f.is_open()) {
        for (long long i = 0; i < numbers_count; i++) {
            f << rand() << std::endl;
        }

        std::cout << "created input file: " << file_path << std::endl;
    }
    f.close();
}


/*
    params
    :input_file_path: путь к входному файлу
    :max_alloc_mem: 
*/

void polyphasemerge_sort(
    const std::string& input_file_path,
    const std::string& out_file_path,
    size_t max_alloc_mem
) {


    int chunk_size = max_alloc_mem / sizeof(int); //Размер чанка
    int* arr = new int[chunk_size];
    
    std::cout << "Start sorting: " << input_file_path << std::endl;
    std::cout << "Chunk size: " << chunk_size << std::endl;
    std::filesystem::create_directory("tmp/");

    std::ifstream input;
    std::ofstream temp;

    input.open(input_file_path); 
    if (!input.is_open()) throw std::exception("Failed to open input file");



    // ДЕЛИМ ВХОДНОЙ ФАЙЛ НА ЧАНКИ
    int i = 0;
    int chunks_count = 0; //кол-во чанков
    size_t N = 0;
    while (!input.eof()) {
        N++;
        //Прочитаем chunk_size элементов
        input >> arr[i++];
        if (i == chunk_size) {

            //Отсортируем
            heap_sort(arr, i);


            //запишем во временный файл
            temp.open("tmp/temp" + std::to_string(chunks_count) + ".txt");
            for (int64_t j = 0; j < i; j++) {
                temp << arr[j] << std::endl;
            }

            chunks_count++;
            i = 0;
            temp.close();
        }
    }

    //K - длина чанка
    //Сложность O( N/K * K * Klog(K) ) ~ O(N * K * log(K))


    std::cout << "N: " << N << std::endl;

    input.close();
    //Остатки
    if (i != 0) {
        //printf("Sorting and writing chunk_%d\n", chunks_count);

        //Отсортируем
        heap_sort(arr, i);

        //запишем остатки во временный файл
        temp.open("tmp/temp" + std::to_string(chunks_count) + ".txt");
        for (int j = 0; j < i; j++) {
            temp << arr[j] << std::endl;
        }
        chunks_count++;
        i = 0;
        temp.close();
    }

    delete[] arr;
 
    std::cout << "Chunks count: " << chunks_count << std::endl;

    //Создаем очередь с приоритетом.
    auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first > b.first;
    };

    std::priority_queue <
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        decltype(cmp)> p_queue(cmp);
    
    //открываем все серии (отсортированные последовательности)
    //и закидываем в очередь первые элементы
    std::ifstream* temp_files = new std::ifstream[chunks_count];
    


    // O(N/K)
    for (int i = 0; i < chunks_count; i++) {
        temp_files[i].open("tmp/temp" + std::to_string(i) + ".txt");
        
        if (temp_files[i].is_open() && !temp_files[i].eof()) {
            int first_val;
            temp_files[i] >> first_val;
            p_queue.push({ first_val, i });
        }
    }

    //Выходной файл
    std::ofstream output;
    output.open(out_file_path);
    if (!output.is_open()) return;

    //N*log(K)
    while (!p_queue.empty()) {
        //Вытаскивам минимальный элемент и записываем в результат
        auto min_pair = p_queue.top();
        p_queue.pop();

        output << min_pair.first << std::endl;
        output.flush();

        //Обновляем очередь
        if (!temp_files[min_pair.second].eof()) {
            int next_val;
            temp_files[min_pair.second] >> next_val;
            p_queue.push({ next_val, min_pair.second });
        }
    }


    /*
        Общая сложность: N*K*log(K) ~ N*log(N);
        Память O(K)
     */


    output.close();
    for (int i = 0; i < chunks_count; i++) {
        temp_files[i].close();
    }
    std::cout << "Sorting is finished: " << out_file_path << std::endl;
    delete[] temp_files;
    

}


int main()
{
    std::setlocale(LC_ALL, "RU");
    srand(std::time(0));

    create_input("input.txt", 500'000);

    polyphasemerge_sort("input.txt", "out.txt", 8192);

}
