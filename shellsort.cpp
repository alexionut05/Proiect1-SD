/* SHELL SORT
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 * Stable: No
 * In-place: Yes
 * 
 * Shell sort e un insertion sort imbunatait. Foarte pe scurt, spre deosebire de insertion sort, shell sort
 * compara elemente care sunt la o distanta [gap] una de cealalta, nu elemente consecutive. Dupa ce compara
 * elementele la distanta [gap], shell sort reduce [gap] si repeta procesul pana cand [gap] devine 1, caz in
 * care shell sort devine un insertion sort.
 * 
 * Diversi matematicieni au incercat sa gaseasca o formula pentru [gap] care sa duca la un timp de executie
 * optim. In prezent, nu exista o formula care sa duca la un timp de executie optim in toate cazurile, dar
 * exista cateva formule care dau rezultate bune in majoritatea cazurilor.
 * 
 * SHELL'S ORGINIAL SEQUENCE:   gap = n / (2^k).                                Worst case: O(n^2)
 * KNUTH'S SEQUENCE:            gap = (3^k - 1) / 2.                            Worst case: O(n^(3/2))
 * SEDGEWICK'S SEQUENCE:        gap = 4^k + 3 * 2^(k - 1) + 1.                  Worst case: O(n^(4/3)
 * CIURA'S SEQUENCE:            gap = 1, 4, 10, 23, 57, 132, 301, 701, 1750.    Worst case: O(n^(4/3)) (unknown)
 *      (nota: se opreste la 1750, dar vom folosi diversi multiplieri pentru a prelungi secventa,
 *       aici incepe alta discutie fara raspuns, dar niste numere populare sunt 2.25, 2.35, 2.20)
 * 
 * Ne vom opri aici, pentru ca sunt secvente cate-n luna si in stele, dintre care unele mai complicate pe care nu am
 * chef sa le implementez.
 * 
 * Algoritmul se va specifica astfel: la executia algoritmului, vom adauga in comanda numele secventei dorite, astfel:
 *      0 / SH = SHELL'S ORGINIAL SEQUENCE (va fi default daca nu e specificat)
 *      1 / KN = KNUTH'S SEQUENCE
 *      2 / SW = SEDGEWICK'S SEQUENCE
 *      3 / CI220 = CIURA'S SEQUENCE (2.20 multiplier)
 *      4 / CI225 = CIURA'S SEQUENCE (2.25 multiplier)
 *      5 / CI225O = CIURA'S SEQUENCE (2.25 multiplier, forced odd)
 *      6 / CI235 = CIURA'S SEQUENCE (2.35 multiplier)
 *      
 *     Exemplu: ./shellsort 3 < input.txt SAU ./shellsort CI220 < input.txt
*/

#include <iostream>
#include <vector>
#include <algorithm>

void generate_gaps(std::string option, long long n, std::vector<long long> &gaps) {
    std::vector<long long> Ciura = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    
    long long gap;
    if (option == "SH" || option == "0") {
        gap = n / 2;
        while (gap > 0) {
            gaps.push_back(gap);
            gap /= 2;
        }
    } else if (option == "KN" || option == "1") {
        gap = 1;
        while (gap < n) {
            gaps.push_back(gap);
            gap = 3 * gap + 1;
        }

        std::reverse(gaps.begin(), gaps.end());
    } else if (option == "SW" || option == "2") {
        gap = 1;
        while (gap < n) {
            gaps.push_back(gap);
            gap = 4 * gap + 3;
        }

        std::reverse(gaps.begin(), gaps.end());
    } else if (option == "CI220" || option == "3") {
        for(size_t i = 0; i < Ciura.size(); i++) {
            if(Ciura[i] < n) {
                gaps.push_back(Ciura[i]);
            }
        }

        gap = 2.20 * Ciura[Ciura.size() - 1];
        while (gap < n) {
            gaps.push_back(gap);
            gap = 2.20 * gap;
        }

        std::reverse(gaps.begin(), gaps.end());
    } else if (option == "CI225" || option == "4") {
        for(size_t i = 0; i < Ciura.size(); i++) {
            if(Ciura[i] < n) {
                gaps.push_back(Ciura[i]);
            }
        }

        gap = 2.25 * Ciura[Ciura.size() - 1];
        while (gap < n) {
            gaps.push_back(gap);
            gap = 2.25 * gap;
        }

        std::reverse(gaps.begin(), gaps.end());
    } else if (option == "CI225O" || option == "5") {
        for(size_t i = 0; i < Ciura.size(); i++) {
            if(Ciura[i] < n) {
                gaps.push_back(Ciura[i]);
            }
        }

        gap = 2.25 * Ciura[Ciura.size() - 1];
        gap = (gap % 2 == 0) ? gap + 1 : gap;
        while (gap < n) {
            gaps.push_back(gap);
            gap = 2.25 * gap;
        }

        std::reverse(gaps.begin(), gaps.end());
    } else if (option == "CI235" || option == "6") {
        for(size_t i = 0; i < Ciura.size(); i++) {
            if(Ciura[i] < n) {
                gaps.push_back(Ciura[i]);
            }
        }

        gap = 2.35 * Ciura[Ciura.size() - 1];
        while (gap < n) {
            gaps.push_back(gap);
            gap = 2.35 * gap;
        }

        std::reverse(gaps.begin(), gaps.end());
    } else {
        std::cout << "Invalid argument" << std::endl;
        exit(1);
    }
}

void shell_sort(float *a, long long n, std::vector<long long> gaps) {
    for (size_t i = 0; i < gaps.size(); i++) {
        long long gap = gaps[i];
        for (size_t j = gap; j < n; j++) {
            float temp = a[j];
            long long k;
            for (k = j; k >= gap && a[k - gap] > temp; k -= gap) {
                a[k] = a[k - gap];
            }
            a[k] = temp;
        }
    }
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    std::cin >> n;
    float *a = new float[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<long long> gaps;

    if(argc < 2) {
        generate_gaps("SH", n, gaps);
    }
    else {
        std::string option = argv[1];
        generate_gaps(option, n, gaps);
    }

    clock_t start = clock();
    shell_sort(a, n, gaps);
    clock_t end = clock();

    double time = (double) (end - start) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << time << "s" << std::endl;
    std::cout << "Checking..." << std::endl;

    for (size_t i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            std::cout << "Wrong answer!" << std::endl;
            return 1;
        }
    }

    std::cout << "OK" << std::endl;
    
    delete[] a;
    return 0;
}