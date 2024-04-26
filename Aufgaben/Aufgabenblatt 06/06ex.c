/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./06ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Machen Sie sich in dieser Aufgabe mit dem `Visualizer` (siehe array_visualizer.h) vertraut.
Nutzen Sie die `visualizer_append_array` Funktion damit die Tests durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void warmup(Visualizer *v, uint8_t *arr, size_t len) {
    for (size_t i = 0; i < len; i++)
    {
        visualizer_append_array(v, arr);
        u_int8_t tmp = arr[0];
        for (size_t a = 0; a < len - 1; a++)
        {
            arr[a] = arr[a+1];
        }
        arr[len-1] = tmp;
    }
}

/*
Aufgabe 2:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Es handelt sich um eine Abwandlung von iterativem Mergesort.
Tipp 3: `len` ist immer eine Dreierpotenz, damit Sie sich nicht mit Rundungsdetails herumschlagen brauchen.
*/
void sort_it(Visualizer *v, uint8_t *arr, size_t len) {
    visualizer_append_array(v, arr);
    int devider = len;
    /*for (size_t i = 0; i < len; i = i + 3)
    {
            int tmp = 0;
            if (arr[i] > arr[i + 1])
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
            if (arr[i + 1] > arr[i + 2])
            {
                tmp = arr[i + 1];
                arr[i + 1] = arr[i + 2];
                arr[i + 2] = tmp;
            }
            if (arr[i] > arr[i + 1])
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
        visualizer_append_array(v, arr);
    }*/
    while (devider > 1)
    {
        for (size_t a = 0; a < devider / 3; a++)
        {
            int elementspBlock = len / devider;
            int posBBlock = a * elementspBlock * 3;
            int posB1 = 0;
            int posB2 = 0;
            int posB3 = 0;
            uint8_t arrTmp1[elementspBlock];
            uint8_t arrTmp2[elementspBlock];
            uint8_t arrTmp3[elementspBlock];
            for (size_t b = 0; b < elementspBlock; b++)
            {
                arrTmp1[b] = arr[posBBlock + b];
                arrTmp2[b] = arr[posBBlock + b + elementspBlock];
                arrTmp3[b] = arr[elementspBlock * 2 + b + posBBlock];
            }
            for (size_t i = 0; i < elementspBlock * 3; i++)
            {
                int smallfirst = 256;
                int block = 0;
                if (posB1 < elementspBlock && posB2 < elementspBlock)
                {
                    if (arrTmp1[posB1] < arrTmp2[posB2])
                    {
                        smallfirst = arrTmp1[posB1];
                        block = 1;
                    }
                    else
                    {
                        smallfirst = arrTmp2[posB2];
                        block = 2;
                    }                    
                }
                else
                {
                    if (posB1 < elementspBlock)
                    {
                        smallfirst = arrTmp1[posB1];
                        block = 1;
                    }
                    else if (posB2 < elementspBlock)
                    {
                        smallfirst = arrTmp2[posB2];
                        block = 2;
                    }                    
                }

                if (posB3 >= elementspBlock || smallfirst < arrTmp3[posB3])
                {
                    if (block == 1)
                    {
                        arr[posBBlock + i] = arrTmp1[posB1];
                        posB1++;
                    }
                    else
                    {
                        arr[posBBlock + i] = arrTmp2[posB2];
                        posB2++;
                    }                    
                }
                else
                {
                    arr[posBBlock + i] = arrTmp3[posB3];
                    posB3++;
                }
                
            }
            visualizer_append_array(v, arr);
        }       
    devider = devider / 3;
    }    
}
