
#include <vector>
#include <fstream>

std::ifstream fin("date.in");
std::ofstream fout("date.out");

long long medianadincinci(std::vector<long long>& arr, long long low, long long high) {
    long long n = high - low + 1;
    long long mid = low + n / 2;

    // Indices for the five elements
    long long a = low, b = low + 1, c = mid, d = high - 1, e = high;

    // Sort the five elements
    if (arr[a] > arr[b]) std::swap(arr[a], arr[b]);
    if (arr[c] > arr[d]) std::swap(arr[c], arr[d]);
    if (arr[a] > arr[c]) std::swap(arr[a], arr[c]);
    if (arr[b] > arr[d]) std::swap(arr[b], arr[d]);
    if (arr[b] > arr[c]) std::swap(arr[b], arr[c]);

    return c; // Return the index of the median
}
long long partition(std::vector<long long>& arr, long long low, long long high) {
    long long pivotindex = medianadincinci(arr, low, high);
    long long pivot = arr[pivotindex];  //alegere pivot
    std::swap(arr[pivotindex], arr[high]);  //l am mutat ultimul ca altfel nush
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

        quicksort(arr, low, part-1);
        quicksort(arr, part+1, high);
    }
}

int main() {
    std::vector<long long> arr;
    long long num;
    while(fin >> num)
        arr.push_back(num);
    quicksort(arr, 0, arr.size() - 1);
    for (long long i=0;i<arr.size();i++) {
        fout << arr[i]<<" ";
    }
    return 0;
}
