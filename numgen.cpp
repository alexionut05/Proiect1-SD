#include <iostream>
#include <fstream>

int main() {
    std::cout << "Number of numbers to generate: ";
    int n;
    std::cin >> n;

    if(n < 1) {
        std::cout << "Invalid input\n";
        return 1;
    }

    std::cout << "Range:                         ";
    long long a, b;
    std::cin >> a >> b;

    if(a > b) {
        std::cout << "Invalid input\n";
        return 1;
    }

    std::cout << "Generate floats? (y/n):        ";
    char c;
    std::cin >> c;

    std::cout << "Name of file to save to:       ";
    std::string file;

    std::cin >> file;
    std::cout << "Generating " << n << " numbers in the range " << a << " to " << b << " to " << file << "...\n";

    std::ofstream fout(file);

    clock_t t;
    t = clock();

    if(c == 'y') {
        fout << n << '\n';
        for(int i = 0; i < n; i++) {
            fout << static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (b - a) + a << '\n';
        }
    } else if (c == 'n'){
        fout << n << '\n';
        for(int i = 0; i < n; i++) {
            fout << rand() % (b - a + 1) + a << '\n';
        }
    } else {
        std::cout << "Invalid input\n";
        return 1;
    }

    t = clock() - t;
    std::cout << "Time taken: " << (float)t / CLOCKS_PER_SEC << " seconds\n";

    fout.close();

    return 0;
}