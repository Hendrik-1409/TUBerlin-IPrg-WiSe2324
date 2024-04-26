/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Gegeben ein Array `arr`, geben Sie zurück, ob der zugehörige linksvollständige Binärbaum
die max-heap Eigenschaft erfüllt.
*/

bool is_max_heap_helper(Array arr, int32_t pos) {
    bool first = true;
    if (arr.len > 2 * pos + 1)
    {
        if (arr.arr[2*pos+1] <= arr.arr[pos])
        {
            first = is_max_heap_helper(arr, 2*pos+1);
        }
        else
        {
            return false;
        }        
    }
    if (arr.len > 2 * pos + 2)
    {
        if (arr.arr[2*pos+2] <= arr.arr[pos] && first)
        {
            return is_max_heap_helper(arr, 2*pos+2);
        }
        return false;
    }
    else if (first)
    {
        return true;
    }    
    if (arr.len <= 2 * pos + 2 && arr.len <= 2 * pos + 1)
    {
        return true;
    }    
    return false;
}

bool is_max_heap(Array arr) {
    return is_max_heap_helper(arr, 0);
}

/*
Aufgabe 2:

Gegeben ein linksvollständiger Binärbaum, tragen Sie im Array `arr` dessen Arrayrepräsentation ein.

Tipp 1: Wie so häufig bei Bäumen, bietet sich hier eine rekursive Lösung an.
Tipp 2: Diese Funktion selbst ist allerdings nur so mäßig gut für rekursive Aufrufe geeignet, eventuell sollten Sie sich eine (rekursive) Hilfsfunktion schreiben.
Tipp 3: Die Position eines Knotens im Array lässt sich relativ leicht bestimmen, wenn man die Position vom Elternknoten weiß, und, ob es sich um ein linkes oder ein rechtes Kind handelt.
Tipp 4: Ja, das sind also sinnvolle Argumente für die Hilfsfunktion.
Tipp 5: Regelmäßig zähneputzen und genug bewegen.
*/

void tree_decode(TreeNode *t, Array arr, int32_t pos) {
    arr.arr[pos] = t->item;
    if (2*pos+1 < arr.len)
    {
        tree_decode(t->left, arr, 2*pos+1);
    }
    if (2*pos+2 < arr.len)
    {
        tree_decode(t->right, arr, 2*pos+2);
    }
}

void tree_to_array(TreeNode *t, Array arr) {
    if (0 < arr.len)
    {
        tree_decode(t, arr, 0);
    }    
}