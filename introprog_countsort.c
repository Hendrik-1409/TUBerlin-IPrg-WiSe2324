#include <stdio.h>
#include <string.h>
#include "introprog_countsort.h"
#include "arrayio.h"

/* Ab hier Funktion count_sort_calculate_counts implementieren */

void count_sort_calculate_counts(int input_array[], int len, int count_array[])
{
    for (size_t i = 0; i < len; i++)
    {
        count_array[input_array[i]]++;
    }
}

/* Ab hier Funktion count_sort_write_output_array implementieren */

void count_sort_write_output_array(int output_array[], int count_array[], SortDirection order)
{
    int outCounter = 0;
    if (order == ASCENDING)
    {
        for (int i = 0; i <= MAX_VALUE; i++)
        {
            for (size_t j = 0; j < count_array[i]; j++)
            {
                output_array[outCounter] = i;
                outCounter++;
            } 
        }
    }
    else
    {
        for (int i = MAX_VALUE; i >= 0; i--)
        {
            for (size_t j = 0; j < count_array[i]; j++)
            {
                output_array[outCounter] = i;
                outCounter++;
            } 
        }
    }
}

/* Ab hier Funktion extract_order_direction implementieren */

SortDirection extract_order_direction (char *order)
{
    SortDirection sDirection = NOTDEFINED;
    if (strcmp(order, "asc") == 0)
    {
        sDirection = ASCENDING;
    }
    else if (strcmp(order, "desc") == 0)
    {
        sDirection = DESCENDING;
    }
    return sDirection;
}

/* Ab hier Funktion count_sort implementieren und entsprechende Funktionsaufrufe einfügen */

void count_sort(int input_array[], int len, int output_array[], SortDirection order)
{
    int count[MAX_VALUE];
    count_sort_calculate_counts(input_array, len, count);
    count_sort_write_output_array(output_array, count, order);
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Aufruf: %s <Dateiname> asc|desc\n", argv[0]);
        printf("Beispiel: %s zahlen.txt asc\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    /*
     * Hier die Sortierrichtung einlesen und einer Variablen
     * des Datentypes SortDirection (siehe h-Datei) verwenden.
     * 
     * Beenden des Programmes mit derselben Ausgabe der Hilfe 
     * (siehe Anfang main-Funktion)
     * 
     * Implementieren Sie zur Umwandlung die Funktion 
     * extract_order_direction und verwenden Sie, wenn kein 
     * gültiger Parameter gefunden wurde, NOTDEFINED.
     * 
     * Hinweis: Die extract_order_direction soll auch mit dieser
     * SortDirection auch ein Standardverhalten implementieren, 
     * die nicht mit einem Fehler terminiert.
     * 
     * Das Hauptprogramm main hingegen, darf auf unkorrekte Eingaben
     * reagieren und auch entsprechend Ausgaben erzeugen oder mit Fehler
     * beenden.
     */

    SortDirection sDirection = extract_order_direction(argv[2]);
    if (sDirection == NOTDEFINED)
    {
        printf("failed to detect sorting order!\n");
        printf("Aufruf: %s <Dateiname> asc|desc\n", argv[0]);
        printf("Beispiel: %s zahlen.txt asc\n", argv[0]);
        return 2;
    }
    

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier count_sort aufrufen und alle nötigen Deklarationen einfügen!
     */

    int output_array[MAX_LAENGE];
    count_sort(input_array, len, output_array, sDirection);

    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    print_array(output_array, len);

    return 0;
}
