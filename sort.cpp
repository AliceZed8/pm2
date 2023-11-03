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

template <typename T>
void combSort( std::vector <T>& arr) {
    size_t n = arr.size();
    size_t step = n;
    bool swp = true;

    while (step != 1 || swp) {
        step /= 1.247;
        if (step < 1) step = 1;

        swp = false;

        for (int i = 0; i + step < n; ++i) {
            if (arr[i] > arr[i + step]) {
                std::swap(arr[i], arr[i + step]);
                swp = true;
            }
        }
    }
}

template <typename T>
void insertionSort(std::vector<T> & arr) {
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

template <typename T>
void selectionSort(std::vector<T> & arr) {
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

        std::copy(out, out + arr.size(), arr.begin());
    }

    delete[] out;

}

template <typename T>
void merge(std::vector<T> & arr, size_t left, size_t middle, size_t right) {
    size_t n1 = middle - left + 1;
    size_t n2 = right - middle;


    T* L = new T[n1];
    T* R = new T[n2];
    
    std::memcpy(L, arr.data() + left, sizeof(T) * n1);
    std::memcpy(R, arr.data() + middle + 1, sizeof(T) * n2);

    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L, R;
}

template <typename T>
void mergeSort(std::vector<T> & arr, size_t left, size_t right) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}






int main()
{
    std::setlocale(LC_ALL, "RU");
    srand(std::time(0));
    std::vector<int> v ;
    std::vector<int> vv = {
        9, 2, 5, 1, 6, 8, 1
    };
    for (int i = 0; i < 20; ++i) {
        v.push_back(rand() % 1000);
    }
    std::cout << "До сортировки" << std::endl;
    print_arr(v);
    //combSort(v);
    //insertionSort(v);
    //selectionSort(v);
    //radixSort(vv);
    mergeSort(v, 0, v.size() - 1);

    std::cout << "После сортировки" << std::endl;
    print_arr(v);

}
