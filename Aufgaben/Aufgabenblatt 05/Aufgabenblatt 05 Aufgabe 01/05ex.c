/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige
Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den
folgenden Befehl aus: cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o
-lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so
testen wir auch auf dem Server: cc -std=c11 -g -Wall -Werror 05ex_test.c -o
05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all
--track-origins=yes ./05ex_test.o
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "search_tree.h"

/*
Aufgabe 1:

Fügen Sie den Wert `x` als Blatt so in den nicht-leeren Suchbaum `t` ein, dass
`t` hinterher wieder ein Suchbaum ist. Falls `x` bereits in `t` vorkam, soll `t`
stattdessen unverändert bleiben. Geben Sie zurück, ob der Baum modifiziert
wurde.

Nutzen Sie `malloc`, um das neue Blatt zu erstellen. Der Testrunner wird das
Blatt wieder `free`n, darum brauchen Sie sich nicht zu kümmern.
*/
bool search_tree_insert(TreeNode *t, uint16_t x) {
    if (t->item < x) {
        if (t->right == NULL) {
            TreeNode *new = (TreeNode *)calloc(1, sizeof(TreeNode));
            new->item = x;
            t->right = new;
            return true;
        }
        else {
            return search_tree_insert(t->right, x);
        }
    }
    else if (t->item > x) {
        if (t->left == NULL) {
            TreeNode *new = (TreeNode *)calloc(1, sizeof(TreeNode));
            new->item = x;
            t->left = new;
            return true;
        }
        else {
            return search_tree_insert(t->left, x);
        }
    }
    return false;
}

/*
Aufgabe 2:
Geben Sie die kleinste Zahl im Suchbaum `t` zurück, welche echt größer als `x`
ist. Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die
Laufzeit Ihrer Lösung soll proportional zur Höhe des Baumes sein, aber
unabhängig von der Gesamtzahl an Knoten.
*/
uint16_t search_tree_get_greater_than(TreeNode *t, uint16_t x) {
    if (t != NULL && t->item <= x)
    {
        if (t->right == NULL)
        {
            return x;
        }
        return search_tree_get_greater_than(t->right, x);
    }
    if (t != NULL && t->item > x)
    {
        if (t->left == NULL)
        {
            return t->item;
        }
        uint16_t newNumber = search_tree_get_greater_than(t->left, x);
        if (newNumber < t->item && newNumber != x)
        {
            return newNumber;
        }
        else
        {
            return t->item;
        }
    }
    return x;
}
