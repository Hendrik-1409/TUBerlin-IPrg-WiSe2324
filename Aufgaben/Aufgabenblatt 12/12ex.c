/*
Zur Abgabe einen branch `iprg-b12` erstellen und pushen, in dem als einzige Datei die `12ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 12ex_test.c -o 12ex_test.o -lm && ./12ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 12ex_test.c -o 12ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./12ex_test.o
*/

#include "height_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t height_or_zero(HeightTreeNode *t) {
    if (t == NULL) {
        return 0;
    } else {
        return t->height;
    }
}

/*
Aufgabe 1a:

Führen Sie eine Rechtsrotation auf dem gegebenen Baum durch, und geben Sie einen Pointer auf
die Wurzel des neuen Baumes zurück.
Der Baum ist nichtleer, und die Wurzel hat einen nichtleeren linken Teilbaum.

Denken Sie daran, auch die Höhen und die Elternpointer anzupassen.

Die Baumausgabe im Terminal enthält in jedem Knoten erst das Item, dann die Höhe, und zuletzt
das Item des Elternkotens (oder NULL für die Wurzel).

Die Baumausgabe nimmt den zurückgegebenen Knoten als Wurzel. Sollte die Baumausgabe komplett
überraschend aussehen, könnte das gut an einer falsch zurückgegebenen Wurzel liegen.
*/
HeightTreeNode *rotate_right(HeightTreeNode *t) {
    HeightTreeNode *newright = calloc(1, sizeof(HeightTreeNode));
    newright->item = t->item;
    newright->parent = t;
    if (t->right != NULL)
    {
        t->right->parent = newright;
        newright->right = t->right;
        newright->height = t->right->height +1;
        t->height++;
    }
    else
    {
        newright->height = 1;
    }
    t->right = newright;
    if (t->left->right != NULL)
    {
        newright->left = t->left->right;
        t->left->right->parent = newright;
        newright->height = newright->height + newright->left->height;
        t->height = t->height + newright->left->height;
    }
    t->item = t->left->item;    
    if (t->left->left != NULL)
    {
        HeightTreeNode *oldleft = t->left;
        t->left->left->parent = t;
        t->left = t->left->left;
        free(oldleft);
        t->height--;
    }
    else
    {
        free(t->left);
        t->left = NULL;
    }
    return t;
}

/*
Die vier möglichen Sequenzen von Rotationen, um einen Beinahe-AVL-Baum in einen AVL-Baum zu überführen.
*/
typedef enum Rotations_ {
    Left, /* eine Linksrotation */
    Right, /* eine Rechtsrotation */
    DoubleRotationLeftRight, /* Doppelrotation: erst Linksrotation, dann Rechtsrotation */
    DoubleRotationRightLeft, /* Doppelrotation: erst Rechtsrotation, dann Linksrotation */
} Rotations;

/*
Aufgabe 2:

Gegeben ein Beinahe-AVL-Baum mit korrekten Höhenwerten, geben Sie zurück, welche Rotationen ihn zu einem AVL-Baum machen.
*/
Rotations determine_rotations(HeightTreeNode *t) {
    int left_height = t->left ? t->left->height : 0;
    int right_height = t->right ? t->right->height : 0;

    int balance_factor = left_height - right_height;

    if (balance_factor > 1) 
    {
        if (t->left && t->left->left && t->left->left->height >= (t->left->right ? t->left->right->height : 0))
        {
            // Left-Left case
            return Right;
        } 
        else 
        {
            // Left-Right case
            return DoubleRotationLeftRight;
        }
    } 
    else if (balance_factor < -1) 
    {
        if (t->right && t->right->right && t->right->right->height >= (t->right->left ? t->right->left->height : 0)) 
        {
            // Right-Right case
            return Left;
        }
        else
        {
            // Right-Left case
            return DoubleRotationRightLeft;
        }
    }
    return Left;
}