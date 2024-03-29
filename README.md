# Proiect1-SD

In acest minunat proiect realizat de Roxana Asavei, Teodor Lepadatu si Alex Tincu am implementat urmatorii algoritmi, unii dintre ei cu mai multe versiuni, (in paranteza versiunea folosita si recomandata):

* Radix Sort (radix_longlong.cpp - baza folosita va fi ultima valoare din input)
* Merge Sort (mergesort.cpp)
* Shell Sort (shellsort_ci225o.cpp)
* Heap Sort (heapsort.cpp)
* Quick Sort (quicksort_medianadin5.cpp)
* Bucket Sort (bucketsort_logn_buckets.cpp)

Recomandam compilarea astfel:
```
g++ -O3 -o file file.cpp
```

Fiecare executabil va folosi argumente din comanda de linie drept input si output, spre exemplu:
```
./file input.txt output.txt
```

Fisierul numgen.cpp va genera numerele, utliziarea lui este documentat in cod.

Am generat ~2000 fisiere de input, pe care le-am folosit pe cei 6 algoritmi (la radix, pe ambele variante), dar si pe sortarile native din C si C++.

Spreadsheet-ul cu testele: https://shorturl.at/jsCKO

Din constrangeri de spatiu, nu am putut sa includem si testele, dar recomandam generarea astfel, in paritate cu datele din spreadsheet (se va modifica tipul de distributie si range-ul):

Sheet-ul 1:
```
./numgen 100000 0 [low] [high] [uni, ..., alm] input.txt
```

Sheet-ul 2:
```
./numgen 10000000 0 [low] [high] [uni, ..., alm] input.txt
```

Sheet-ul 3:
```
./numgen 1000000000 0 [low] [high] [uni, ..., alm] input.txt
```

Prezentarea: https://shorturl.at/htMR1