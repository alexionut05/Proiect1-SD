#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>   //librarie pt masurarea timpului

std::ifstream fin("date.in");
std::ofstream fout("date.out");

void merge(std::vector<int>& v, int l, int m, int r) { //l si r sunt marginile, iar m e mijlocul
    int n1 = m - l + 1;
    int n2 = r - m;         //am impartit la mijloc vectorul de sortat
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = v[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = v[m + 1 + j];
    }                           //am construit doi vectori (L-left si R-right) pe care ii voi sorta)
    //algoritm de interclasare:
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];        //daca elementul la care am ajuns in stanga e mai mic decat cel din dreapta, il voi pune in vecotrul final pe cel din stanga
            i++;
        } else {
            v[k] = R[j];        //daca elementul la care am ajuns in stanga e mai mare decat cel din dreapta, il voi pune in vecotrul final pe cel din dreapta
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;                //daca au mai ramas elemente in stanga, le adaug (ele fiind sortate deja)
    }
    while (j < n2) {        //daca au mai ramas elemente in dreapta, le adaug (ele fiind sortate deja)
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(std::vector<int>& v, int l, int r) { //functia ce sorteaza propriu-zis
    if (l < r) {    //conditie de valabilitate (daca nu e asa, n-am ce sa sortez)
        int m = (r + l) / 2;    //creez mijlocul
        mergesort(v, l, m); //sortez jumatatea din stanga a vectorului
        mergesort(v, m + 1, r); //sortez jumatatea din dreapta a vectorului
        merge(v, l, m, r);  //combin cele doua subsiruri cu ajutorul interclasarii pentru a obtine vectorul sortat, caruia ii dau si output
    }
}

int main() {
    std::vector<int> v;
    int num;
    while (fin >> num) {
        v.push_back(num);
    } //construiesc vectorul de sortat

    auto start = std::chrono::high_resolution_clock::now(); // start timing
    mergesort(v, 0, v.size() - 1); //apelez functia si incep sa cronometrez
    auto end = std::chrono::high_resolution_clock::now(); // sfarsit timing
    std::chrono::duration<double> duration = end - start; //timpul total

    for (int i = 0; i < v.size(); i++) {
        fout << v[i] << " ";
    } //afisare

    std::cout << duration.count() << " seconds" << std::endl; //in cat timp a sortat

    return 0;
}
