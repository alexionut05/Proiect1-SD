#include <vector>
#include <fstream>
double medianadintrei(double a, double b, double c) {
    if ((a < b && b < c) || (c < b && b < a))
        return b;
    else if ((b < a && a < c) || (c < a && a < b))
        return a;
    else
        return c;
}
std::vector<double> quicksort(std::vector<double>& arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }
    else
    {
        double pivot;
        double first = arr[0];
        double middle = arr[arr.size() / 2];
        double last = arr[arr.size() - 1];
        pivot = medianadintrei(first, middle, last);  ///am ales un pivot random, o sa schimbam asta sau facem mai multe teste cu asta
        std::vector<double> left;
        std::vector<double> right;
        for (long long i = 0; i < arr.size(); i++)    ///impart vectorul initial in doua astfel incat elementele din left sa fie mai mici decat pivotul si din right mai mare decat pivotul
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

    std::vector<double> v;
    double num;
    double temp;
    fin >> temp;

    while (fin >> num)
    {
        v.push_back(num);   ///input
    }

    try {
        v = quicksort(v);   ///sortare
    } catch (std::exception& e) {
        return -1;
    }

    for (long long i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";            ///afisare
    }

    fin.close();
    fout.close();

    return 0;
}
