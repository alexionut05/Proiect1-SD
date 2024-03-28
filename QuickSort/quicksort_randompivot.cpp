#include <vector>
#include <fstream>
#include <random>
std::ifstream fin("date.in");
std::ofstream fout("date.out");

long long pivotrandom(long long a,long long b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(a, b);
    return dis(gen);
}
long long partition(std::vector<double>& arr, long long low, long long high) {
    double pivot = arr[pivotrandom(low, high)];  //alegere pivot random
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

