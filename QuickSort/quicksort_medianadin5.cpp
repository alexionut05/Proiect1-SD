#include <vector>
#include <fstream>
#include <algorithm>
double median(std::vector<double>& arr) {
    std::sort(arr.begin(), arr.end());
    return arr[arr.size() / 2];
}

double medianadincinci(double a, double b, double c, double d, double e) {
    std::vector<double> arr = {a, b, c, d, e};
    return median(arr);
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
        double second = arr[arr.size() / 4];
        double fourth = arr[arr.size() / 4 * 3];
        pivot = medianadincinci(first, middle, last, second, fourth); // Alegerea pivotului folosind mediana din 5
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

    for (unsigned long long i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";            ///afisare
    }

    fin.close();
    fout.close();

    return 0;
}
