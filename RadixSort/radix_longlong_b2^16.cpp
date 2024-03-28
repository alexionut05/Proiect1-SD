// nu cumva sa ii dati numere rationale, 'cause  it's not built for that :)

#include <fstream>
#include <vector>
#include <cmath>
#define b16 65536

std::ifstream fin("date.in");
std::ofstream fout("date.out");

int n;
std::vector<long long> v;

void Afisare(int n, std::vector<long long> &v) {
    for(int i = 0; i < n; ++i) {
        fout << v[i] << " ";
    }
    fout.close();
}

// stim ca pentru fiecare cifra in parte vom face counting sort, deci trebuie sa stim numarul maxim de cifre
long long Nr_maxim_cifre(int n, std::vector<long long> &v) {
    // voi returna modulul valorii cu un numar maxim de cifre
    long long max_cifre = std::abs(v[0]);
    for(int i = 1; i < n; ++i) {
        if(std::abs(v[i]) > max_cifre) {
            max_cifre = std::abs(v[i]);
        }
    }
    return max_cifre;
}

void Counting_Sort(int n, std::vector<long long>& v, int pow_base) {
    long long auxiliar[n]; // in el construiesc, ulterior copiez in vectorul v
    int count[2 * b16]; // count[i] = frecventa cifrei i la pasul curent (la primul apel ne intereseaza de
    // cate ori apare cifra i la unitati, apoi de cate ori apare la zeci...)
    for(int i = 0; i < 2 * b16 - 1; ++i) { // initializez
        count[i] = 0;
    }

    /**
     * De ce are count dimensiunea 2 * base? (stiu ca puteam sa pun 2*base - 2)
     * ..........................................
     * In input putem aveam si numere intregi, deci in momentul in care ne dorim sa accesam cifra
     * de la pasul curent aceasta poate avea valori din intervalul [-base + 1, base - 1]
     * Pentru ca nu putem avea indici negativi in count (nu exista count[-2]), normalizam indicii
     * adaugand la fiecare cifra pe care o obtinem (base - 1).
     * Astfel, in count, indicii(valorile normalizate ale cifrelor) vor lua valori in intervalul [0, 2*base - 2]
    */

   for(int i = 0; i < n; ++i) {
    int digit = v[i] / pow_base % b16; // preluam cifra care ne intereseaza
    count[digit + b16 - 1]++; // o normalizam si ii incrementam frecventa
   }

   /**
    * !!! Urmeaza sa schimbam semnificatia lui count !!!
    * ...................................................
    * In momentul de fata, count[i] indica de cate ori a aparut cifra i
    * (Eu vreau ca in vectorul v sa am prima data numerele a caror cifra accesata a fost 0,
    * apoi numerele cu cifra = 1 si tot asa )
    * Imi propun ca (ignorati cacofonia) count[i] - 1 sa reprezinte ultima pozitie unde o sa am un numar cu cifra i
    *
    * ex: count[0] = 3, count[1] = 4
    * Prima data o sa pun numerele cu 0 de la pozitia 0 la pozitia 2 (= count[0] - 1)
    * Dupa pun numerele cu 1 de la pozitia 3 la pozitia 6 (= count[0] + count[1] - 1)
   */

    for(int i = 1; i <= 2 * b16 - 2; ++i) {
        count[i] += count[i - 1];
    }

    /**
     * Stiu ce va ganditi: chiar daca cifra 2 * base - 2 nu ar aparea deloc, acum o sa am count-ul ei ca fiind
     * suma tuturor count-urilor. Nu o sa ne afecteze, pentru ca o sa accesam count doar pentru acele cifre care apar!
    */

   /**
    * !!! E foarte important sa le luam de la dreapta la stanga (4 ore am facut debugging din cauza asta)
    * Pentru ca asa se asigura stabilitatea metodei (trebuie investigat mai mult)
   */
    for(int i = n - 1; i >= 0; --i) {
        int digit = v[i] / pow_base % b16;
        digit += b16 - 1;
        auxiliar[count[digit] - 1]  = v[i]; // pun valoarea mea pe ultima pozitie unde are voie sa fie
        // s-a ocupat pozitia count[digit] - 1, deci acum am voie sa pun mai la stanga
        count[digit]--;
    }
    // rasturnam dintr un vector in celalalt
    for(int i = 0; i < n; ++i) {
        v[i] = auxiliar[i];
    }

}

int Nr_Cifre(long long n) {
    if(n == 0) return 1;
    int ct_cifre = 0;
    while(n) {
        n /= b16;
        ct_cifre++;
    }
    return ct_cifre;
}

void Radix_Sort(int n, std::vector<long long> &v) {
    long long max_cifre = Nr_maxim_cifre(n, v);
    int pow_base = 1; // vom tine puteri ale bazei pentru a putea accesa pe rand cifrele
    int nr_iteratii = Nr_Cifre(max_cifre); // calculam numarul maxim de cifre
    for(int i = 0; i < nr_iteratii; ++i) { // pt fiecare cifra, fac counting sort
        Counting_Sort(n, v, pow_base);  // (cifra curenta se acceseaza cu v[pos] / pow_base % base)
        pow_base *= b16;
    }
}

bool Sortat(int n, std::vector<long long> &v) {
    for(int i = 1; i < n; ++i) {
        if(v[i] < v[i - 1]) {
            return 0;
        }
    }
    return 1;
}


void Citire(int &n, std::vector<long long> &v) {
    fin >> n;
    long long val;
    for(int i = 0; i < n; ++i) {
        fin >> val;
        v.push_back(val);
    }
    fin.close();

}

int main() {

    Citire(n, v);
    if(!Sortat(n, v)) {
        Radix_Sort(n, v);
    }

    try {
        Afisare(n, v);
    } catch(std::exception& e) {
        return -1;
    }

    return 0;
}
