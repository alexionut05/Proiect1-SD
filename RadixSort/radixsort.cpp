// nu cumva sa ii dati numere rationale, 'cause  it's not built for that :)

#include <fstream>
#include <vector>
#include <cmath>

int n, base;
std::vector<int> v;

void Afisare(int n, std::vector<int> v, char *filename) {
    std::ofstream fout(filename);
    for(int i = 0; i < n; ++i) {
        fout << v[i] << " ";
    }
    fout.close();
}

// stim ca pentru fiecare cifra in parte vom face counting sort, deci trebuie sa stim numarul maxim de cifre
int Nr_maxim_cifre(int n, std::vector<int> v) {
    // voi returna modulul valorii cu un numar maxim de cifre
    int max_cifre = std::abs(v[0]);
    for(int i = 1; i < n; ++i) {
        if(std::abs(v[i]) > max_cifre) {
            max_cifre = std::abs(v[i]);
        }
    }
    return max_cifre;
}

void Counting_Sort(int n, std::vector<int>& v, int base, int pow_base) {
    int auxiliar[n]; // in el construiesc, ulterior copiez in vectorul v
    int count[2 * base]; // count[i] = frecventa cifrei i la pasul curent (la primul apel ne intereseaza de 
    // cate ori apare cifra i la unitati, apoi de cate ori apare la zeci...)
    for(int i = 0; i < 2 * base - 1; ++i) { // initializez
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
    int digit = v[i] / pow_base % base; // preluam cifra care ne intereseaza
    count[digit + base - 1]++; // o normalizam si ii incrementam frecventa
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

    for(int i = 1; i <= 2 * base - 2; ++i) {
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
        int digit = v[i] / pow_base % base;
        digit += base - 1;
        auxiliar[count[digit] - 1]  = v[i]; // pun valoarea mea pe ultima pozitie unde are voie sa fie
        // s-a ocupat pozitia count[digit] - 1, deci acum am voie sa pun mai la stanga
        count[digit]--;
    }
    // rasturnam dintr un vector in celalalt
    for(int i = 0; i < n; ++i) {
        v[i] = auxiliar[i];
    }

}

int Nr_Cifre(int n, int base) {
    if(n == 0) return 1;
    int ct_cifre = 0;
    while(n) {
        n /= base;
        ct_cifre++;
    }
    return ct_cifre;
}

void Radix_Sort(int n, std::vector<int>& v, int base) {
    int max_cifre = Nr_maxim_cifre(n, v);
    int pow_base = 1; // vom tine puteri ale bazei pentru a putea accesa pe rand cifrele
    int nr_iteratii = Nr_Cifre(max_cifre, base); // calculam numarul maxim de cifre
    for(int i = 0; i < nr_iteratii; ++i) { // pt fiecare cifra, fac counting sort
        Counting_Sort(n, v, base, pow_base);  // (cifra curenta se acceseaza cu v[pos] / pow_base % base)
        pow_base *= base;
    }
}

bool Sortat(int n, std::vector<int> v) {
    for(int i = 1; i < n; ++i) {
        if(v[i] < v[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        return 1;
    }

    std::ifstream fin(argv[1]);
    fin >> n >> base;
    int val;
    for(int i = 0; i < n; ++i) {
        fin >> val;
        v.push_back(val);
    }
    if(!Sortat(n, v)) {
        Radix_Sort(n, v, base);
    }

    try {
        Afisare(n, v, argv[2]);
    } catch(std::exception& e) {
        return -1;
    }

    fin.close();
    return 0;
}
