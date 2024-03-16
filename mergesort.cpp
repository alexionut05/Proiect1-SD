#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
void merge(std::vector<int>& v, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = v[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = v[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(std::vector<int>& v, int l, int r) {
    if (l < r) {
        int m = (r + l) / 2;
        mergesort(v, l, m);
        mergesort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

int main() {
    std::vector<int> v;
    int num;
    while (fin >> num) {
        v.push_back(num);
    }
    mergesort(v, 0, v.size() - 1);
    for (int i = 0; i < v.size(); i++) {
        fout << v[i] << " ";
    }
    return 0;
}


