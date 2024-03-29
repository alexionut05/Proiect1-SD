#include <vector>
#include <fstream>

std::ifstream fin("date.in");
std::ofstream fout("date.out");

long long partition(std::vector<long long>& arr, long long low, long long high) {
    long long pivot = arr[high];  //pivot ca ultimul element
    long long i = low - 1;

    for (long long j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;  // Incrementez indexul daca elementul e mai mic decat pivotul
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);

    return i + 1;  // returnez unde fac partitionarea
}

void quicksort(std::vector<long long>& arr, long long low, long long high) {
    if (low < high) {
        long long part = partition(arr, low, high);

        quicksort(arr, low, part - 1);
        quicksort(arr, part + 1, high);
    }
}

int main() {
    std::vector<long long> arr;
    long long num;
    while(fin >> num)
        arr.push_back(num);

    quicksort(arr, 0, arr.size() - 1);

    for (long long x : arr) {
        fout << x << " ";
    }

    return 0;
}

