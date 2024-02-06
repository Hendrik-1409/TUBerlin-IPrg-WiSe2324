/*
Zur Abgabe einen branch `iprg-b11` erstellen und pushen, in dem als einzige Datei die `11ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && ./11ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./11ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Implementieren Sie folgenden Algorithmus, um ein Array zu partitionieren:

- die `pivot_position` ist initial die letzte Stelle im Array
- der Wert an der `pivot_position` ist das `pivot` Element
- solange es links der `pivot_position` Elemente gibt, die größer oder gleich `pivot` sind:
    - sei `i` die Position des linkesten solchen Elements
    - rotiere die Werte an den Positionen `i`, `pivot_position - 1` und `pivot_position` nach links (siehe Testoutput)
    - dekrementiere die `pivot_position`

Nutzen Sie die `visualizer_append_array` Funktion (siehe `array_visualizer.h` bzw das sechste Semesteraufgabenblatt 06) um den Algorithmus zu visualisieren. Und nutzen Sie die vom Testrunner erstellten Bilder zum Debuggen, und falls Ihnen das zu erwartende Verhalten unklar ist.

Imaginäre Bonuspunkte, wenn Ihre Implementierung in linearzeit läuft.

Tipp: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void visualize_partition(Visualizer *v, uint8_t *arr, size_t len) {
    visualizer_append_array(v, arr);
    int pivotPosition = len - 1;
    while (pivotPosition > 0)
    {
        size_t i = 0;
        while (i < pivotPosition)
        {
            if (arr[i] >= arr[pivotPosition])
            {
                break;
            }
            i++;
        }
        if (i < pivotPosition)
        {
            uint8_t tmp = arr[i];
            arr[i] = arr[pivotPosition - 1];
            arr[pivotPosition - 1] = arr[pivotPosition];
            arr[pivotPosition] = tmp;
            pivotPosition--;
            visualizer_append_array(v, arr);
        }
        else
        {
            break;
        }        
    }
    
    return;
}

/*
Aufgabe 2:
Implementieren Sie Quicksort rekursiv, und visualisieren Sie den Algorithmus wie von den Tests verlangt.

Wählen Sie als Pivotelement stets das letzte Element eines Teilarrays, und partitionieren Sie mit dem in Aufgabe 1 beschriebenen Algorithmus.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Visualisieren Sie außerdem das Array immer nachdem Sie ein Teilarray der Größe mindestens zwei partitioniert haben.
Tipp 3: Diese Funktion selbst lässt sich nicht sinnvoll rekursiv aufrufen. Schreiben Sie eine geeignete Funktion, und rufen Sie sie in `sort_quickly` auf.
*/

size_t partition(uint8_t *arr, size_t len, size_t startpoint) {
    int pivotPosition = len - 1;
    while (pivotPosition > startpoint)
    {
        size_t i = startpoint;
        while (i < pivotPosition)
        {
            if (arr[i] >= arr[pivotPosition])
            {
                break;
            }
            i++;
        }
        if (i < pivotPosition)
        {
            uint8_t tmp = arr[i];
            arr[i] = arr[pivotPosition - 1];
            arr[pivotPosition - 1] = arr[pivotPosition];
            arr[pivotPosition] = tmp;
            pivotPosition--;
        }
        else
        {
            return i;
        }        
    }    
    return startpoint;
}

void assist(Visualizer *v, uint8_t *arr, size_t len, size_t pivot, size_t startpoint) {
    printf("%lu bei len %lu\n",pivot, len);
    visualizer_append_array(v, arr);
    if (pivot > startpoint + 1) // linkseitig
    {
        size_t i = partition(arr, pivot, startpoint);
        assist(v, arr, pivot, i, startpoint);
    }
    if (len - pivot > 2) // rechtsseitig
    {
        size_t i = partition(arr, len, pivot + 1);
        assist(v, arr, len, i, pivot + 1);
    }
    visualizer_append_array(v, arr);
    return;
}

void sort_quickly(Visualizer *v, uint8_t *arr, size_t len) {
    printf("\n\nTask starting \n");
    visualizer_append_array(v, arr);
    size_t i = partition(arr, len, 0);
    assist(v, arr, len, i, 0);
    visualizer_append_array(v, arr);
    return;
}
