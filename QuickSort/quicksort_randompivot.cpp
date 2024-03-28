#include <vector>
#include <fstream>
#include <random>

double pivotrandom(double a,double b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(a, b);
    return dis(gen);
}

std::vector<double> quicksort(std::vector<double>& arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }
    else
    {
        double pivot = pivotrandom(0,arr.size()-1);  ///am ales un pivot random, o sa schimbam asta sau facem mai multe teste cu asta
        std::vector<double> left;
        std::vector<double> right;
        for (unsigned long long i = 0; i < arr.size(); i++)    ///impart vectorul initial in doua astfel incat elementele din left sa fie mai mici decat pivotul si din right mai mare decat pivotul
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

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    int n;
    fin>>n;
    std::vector<double> v;
    long long num;
    while (fin >> num)
    {
        v.push_back(num);   ///input
    }
    //auto start = std::chrono::high_resolution_clock::now();
    //std::cout<<pivotrandom(v,0,v.size())<<std::endl;
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> duration = end - start;
    //std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    try {
        v = quicksort(v);
    } catch (const std::exception& e) {
        return -1;
    }

    for (unsigned long long i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";            ///afisare
    }

    fin.close();
    fout.close();
    return 0;
}
