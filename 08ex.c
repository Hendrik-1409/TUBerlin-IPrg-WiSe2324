/*
Zur Abgabe einen branch `iprg-b08` erstellen und pushen, in dem als einzige Datei die `08ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Ein Array zusammen mit seiner Länge. */
typedef struct ArrayWithLength_ {
    uint16_t *arr;
    size_t len;
} ArrayWithLength;

/*
Bei merge sort werden häufiger mal *zwei* vorsortierte Arrays kombiniert. Auf diesem Blatt
kombinieren wir effizient *beliebig viele* vorsortierte Arrays mit einem divide-and-conquer Algorithmus.
*/

/*
Aufgabe 1a:

Gegeben ein absteigend sortiertes Array, geben Sie ein absteigend sortiertes Array
mit den gleichen Elementen zurück.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.

Tipp: Ja, es ist wirklich so banal wie es klingt. Das haben base-cases bei divide-and-conquer
Algorithmen häufig so an sich.
*/
ArrayWithLength base_case(ArrayWithLength arr) {
    ArrayWithLength ret;

    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * arr.len);
    ret.len = arr.len;
    for (size_t i = 0; i < arr.len; i++)
    {
        ret.arr[i] = arr.arr[i];
    }
    return ret;
}

/*
Aufgabe 1b:

Gegeben zwei absteigend sortierte Arrays der Längen len1 und len2,
geben Sie ein absteigend sortiertes Array zurück,
welches die Elemente beider Eingabearrays enthält. Die Funktion soll in O(len1 + len2) laufen.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength combine(ArrayWithLength arr1, ArrayWithLength arr2) {
    ArrayWithLength ret;
    ret.len = arr1.len + arr2.len;
    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * ret.len);
    
    size_t arr1count = 0;
    size_t arr2count = 0;
    for (size_t i = 0; i < ret.len; i++)
    {
        if (arr2count >= arr2.len)
        {
            ret.arr[i] = arr1.arr[arr1count];
            arr1count++;
        }        
        else if (arr1count < arr1.len && arr1.arr[arr1count] > arr2.arr[arr2count])
        {
            ret.arr[i] = arr1.arr[arr1count];
            arr1count++;
        }
        else
        {
            ret.arr[i] = arr2.arr[arr2count];
            arr2count++;
        }        
    }
    
    return ret;
}

/*
Aufgabe 1c:

Gegeben ein nichtleeres Array `arrs` aus `count` vielen absteigend sortierten Arrays, geben Sie ein absteigend sortiertes Array
zurück, welches die Elemente aller Eingabearrays enthält. Ihre Lösung soll in O(n * log(count)) laufen, wobei `n` die
Gesamtzahl an Elementen in allen Arrays ist. Dazu müssen sie clever dive-and-conquern.

Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength merge_k(ArrayWithLength *arrs, size_t count) {
    ArrayWithLength ret;
    
    size_t n = 0;

    for (size_t b = 0; b < count; b++)
    {
        n = n + arrs[b].len;
    }

    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * n);
    ret.len = n;

    size_t* countArr = (size_t *) calloc(1, sizeof(size_t) * count);
    size_t* tmpArr = (size_t *) calloc(1, sizeof(size_t) * count);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t a = 0; a < count; a++)
        {
            if (arrs[a].len > countArr[a])
            {
                tmpArr[a] = arrs[a].arr[countArr[a]];
            }
            else
            {
                tmpArr[a] = 0;
            }                        
        }
        size_t tmp = 0;
        size_t tmpPos = 0;
        for (size_t x = 0; x < count; x++)
        {
            if (tmp < tmpArr[x])
            {
                tmp = tmpArr[x];
                tmpPos = x;
            }            
        }
        countArr[tmpPos]++;
        ret.arr[i] = tmp;
    }
    
    free(countArr);
    free(tmpArr);

    return ret;
}
