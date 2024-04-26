/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include "sphinx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array mit n absteigend sortierten Zahlen überlegt (Zahlen
können mehrfach vorkommen). Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet) vielen
Positionen fragen. Und wenn du mir danach nicht sagen kannst, ob das Array die Zahl 12345
enthält, dann fresse ich dich.".

Geben Sie zurück, ob das Array der Sphinx die Zahl 12345 enthält. Um den Wert an Position `i`
zu erfragen, rufen Sie `sphinx_ask(s, i)` auf. Aber Achtung: Wenn Sie diese Funktion mehr als
1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm fehlerhaft ab.
*/
bool descending_sphinx(Sphinx *s, size_t n) {
    printf("n: %lu\n", n);
    if (n == 0)
    {
        printf("false\n\n");
        return false;
    }
    if (n == 1)
    {
        if (sphinx_ask(s, 0) == 12345)
        {
            printf("true\n\n");
            return true;
        }
        else
        {
            printf("false\n\n");
            return false;
        }
        
    }    
    size_t devider = n / 2;
    size_t newPos = n / 2;
    while (true)
    {
        if (newPos > n)
        {
            printf("false\n\n");
            return false; 
        }        
        size_t test = sphinx_ask(s, newPos);
        printf("%lu at %lu\n", test, newPos);
        if (test == 12345)
        {
            printf("true\n\n");
            return true;
        }
        if (devider == 0)
        {
            printf("false\n\n");
            return false;       
        }

               
        size_t newDevider = devider / 2;
        size_t testDevider = (devider - 1) / 2;
        if (newDevider == testDevider && devider != 1)
        {
            devider = devider / 2 + 1;
        }
        else
        {
            devider = devider / 2;
        }
        printf("devider: %lu\n", devider);        
        if (test > 12345)
        {
            newPos = newPos + devider;            
        }
        else
        {
            newPos = newPos - devider;
        }
    }
}