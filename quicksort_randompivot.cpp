#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
std::ifstream fin("date.in");
std::ofstream fout("date.out");

int pivotrandom(std::vector<int>& arr, int left, int right) {
    srand(time(0));
    return arr[rand() % (right - left + 1) + left];
}

std::vector<int> quicksort(std::vector<int>& arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }
    else
    {
        int pivot = pivotrandom(arr,0,arr.size()-1);  ///am ales un pivot random, o sa schimbam asta sau facem mai multe teste cu asta
        std::vector<int> left;
        std::vector<int> right;
        for (int i = 1; i < arr.size(); i++)    ///impart vectorul initial in doua astfel incat elementele din left sa fie mai mici decat pivotul si din right mai mare decat pivotul
        {
            if (arr[i] < pivot)
            {
                left.push_back(arr[i]);
            }
            else
            {
                right.push_back(arr[i]);
            }
        }
        left = quicksort(left);     ///apelez recursiv functia pentru a sorta cele doua subsiruri
        right = quicksort(right);
        left.push_back(pivot);
        left.insert(left.end(), right.begin(), right.end());    ///reconstruiesc vectorul pentru a il afisa
        return left;
    }
}

int main()
{
    std::vector<int> v;
    int num;
    while (fin >> num)
    {
        v.push_back(num);   ///input
    }
    //auto start = std::chrono::high_resolution_clock::now();
    //std::cout<<pivotrandom(v,0,v.size())<<std::endl;
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> duration = end - start;
    //std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    v = quicksort(v);   ///sortare

    for (int i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";            ///afisare
    }
    return 0;
}
