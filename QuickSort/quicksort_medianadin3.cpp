
#include <vector>
#include <fstream>
#include <random>
std::ifstream fin("date.in");
std::ofstream fout("date.out");

long long  medianadintrei(std::vector<double>& arr, long long low, long long high) {
    long long mid = low + (high - low) / 2;

    //gasesc mijlocul dintre cele 3 valori
    if (arr[low] > arr[mid])
        std::swap(arr[low], arr[mid]);
    if (arr[mid] > arr[high])
        std::swap(arr[mid], arr[high]);
    if (arr[low] > arr[mid])
        std::swap(arr[low], arr[mid]);

    return mid;
}
long long partition(std::vector<double>& arr, long long low, long long high) {
    long long pivotindex = medianadintrei(arr, low, high);
    double pivot = arr[pivotindex];  //alegere pivot
    long long i = low - 1;

    for (long long j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;  // Incrementez indexul daca elementul e mai mic decat pivotul
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[pivotindex]);

    return i + 1;  // returnez unde fac partitionarea
}

void quicksort(std::vector<double>& arr, long long low, long long high) {
    if (low < high) {
        long long part = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quicksort(arr, low, part - 1);
        quicksort(arr, part + 1, high);
    }
}

int main() {
    std::vector<double> arr;
    double num;
    while(fin >> num)
        arr.push_back(num);

    quicksort(arr, 0, arr.size() - 1);

    for (double x : arr) {
        fout << x << " ";
    }

    return 0;
}
