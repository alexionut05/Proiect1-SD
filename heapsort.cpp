#include <iostream>
#include <vector>


/**
Mica introducere:
    - cititi asta
    - un arbore binar se poate tine in memorie folosind un array unde, daca arr[i] e radacina,
      fiul stang al radacinii e arr[2 * i + 1], iar fiul drept al radacinii e arr[2 * i + 2]

      ex: radacina arborelui mare e pe pozitia 0. fiul stang se afla pe pozitia 1, cel drept pe pozitia 2.
          la randul sau, arr[1] e radacina pentru subarborele stang si se continua rationamentul

    - un arbore binar complet este un arbore binar care are toate nivelurile complete, mai putin ultimul (si ultimul poate
      fi complet, dar nu e obligatoriu). de regula, nodurile de pe ultimul nivel sunt grupate in partea stanga

    - un max-heap este un arbore binar cu proprietatea ca radacina din orice subarbore este mai mare decat fii sai
     (deci arr[i] > arr[2 * i + 1] si arr[i] > arr[2 * i + 2])

     - un arbore binar se pooate transforma intr-un max-heap folosind "operatia" heapify
     - intr-un arbore binar complet cu n noduri, n/2 noduri sunt neterminale (nu sunt frunze)

-----------------------------------------------------------------------------------------------

    heapify(arr, n, i) = primeste ca argumente un arbore binar tinut in arr, unde n este numarul de noduri
                         si transforma in max-heap subarborele cu radacina arr[i]

*/

std::vector<int> v;
int n;

void citire() {
    std::cin >> n;
    int x;
    for(int i = 0; i < n; ++i) {
        std::cin >> x;
        v.push_back(x);
    }

}


void heapify(std::vector<int> &v, int n, int root_pos) {
    // calculam indici celor 2 fii
    int left = 2 * root_pos + 1;
    int right = 2 * root_pos + 2;

    // calculam pozitia maximului
    int max_pos = root_pos;
    if(left < n && v[left] > v[max_pos]) {
        max_pos = left;
    }
    if(right < n && v[right] > v[max_pos]) {
        max_pos = right;
    }

    if(root_pos != max_pos) // daca radacina nu e deja mai mare decat cei doi fii
    {
        std::swap(v[root_pos], v[max_pos]); // am coborat radacina in adancime
        // valoarea radacinii se afla acum la max_pos
        // vad daca trebuie sa o mai scufund in continuare
        heapify(v, n, max_pos);
    }
}

void heapsort(std::vector<int> &v, int n) {
    // transformam arborele binar intr-un max-heap
    // pornesc de la radacina fiecarui subarbore si tot urc in inaltime
    for(int i = n / 2 - 1; i >= 0; --i) {
        heapify(v, n, i);
    }

    // in momentul asta eu am maximul din vector in varf
    for(int i = n - 1; i >= 0; --i) {
        // v[0] e maxim, asa ca il iau si il duc pe pozitia lui finala in vectorul sortat
        std::swap(v[0], v[i]);
        // rastabilesc ordinea in max-heap
        heapify(v, i, 0);
    }

}


void afisare(std::vector<int> v, int n) {
    for(int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }

}

int main()
{
    citire();
    heapsort(v, n);
    afisare(v, n);
    return 0;
}
