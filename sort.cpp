#include <iostream>
#include <vector>


template <typename T>
void print_arr(const std::vector<T> arr) {
    std::cout << "{ ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "}" << std::endl;
}





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


/*
     Макс кол-во рекурсий log(n)
*/

template<typename T>
void heapify(std::vector<T>& arr, int64_t i, int64_t n) {
    
    int64_t left_i = 2*i + 1;
    int64_t right_i = 2*i + 2;
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
void heap_sort(std::vector<T>& arr) {
    
    //Строим кучу (самый большой элемент станет корнем i = 0)
    // (0.5 * n) * log(n)
    int64_t n = arr.size();
    for (int64_t i = (n / 2) - 1; i >= 0; i--)
        heapify(arr, i, n);

    
    // n * log(n)
    for (int64_t i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]); //перемещаем корень
        heapify(arr, 0, i); // Преобразуем уменьшенную кучу
    }

    // Общая сложность O (1.5 * n * log(n)) ~ O (n*log(n))

}

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


int main()
{
    std::setlocale(LC_ALL, "RU");
    srand(std::time(0));
    std::vector<int> v ;

    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
    }
    for (int i = 0; i < 20; ++i) {
        std::swap(v[i], v[rand() % (v.size() - 1)]);
    }
    std::cout << "До сортировки" << std::endl;
    print_arr(v);
    //heap_sort(v);
    
    merge_sort(v);

    std::cout << "После сортировки" << std::endl;
    print_arr(v);

}
