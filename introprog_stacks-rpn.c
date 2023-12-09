#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_stacks-rpn.h"
#include "introprog_input_stacks-rpn.h"

/* 
 * Füge Element am Anfang des Stacks ein
 *
 * char* - Ein Pointer auf den Stack.
 * float - Zahl, die als neues Element auf den Stack gelegt
 *         werden soll.
 */
void stack_push(stack* thisStack, float newNumber)
{
    /* HIER implementieren */
    stack_element *newElement = (stack_element *)calloc(1, sizeof(stack_element));
    newElement->value = newNumber;
    if (thisStack->top != NULL)
    {
        newElement->next = thisStack->top;
    }
    thisStack->top = newElement;
    return;
}

/* 
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * stack* - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* thisStack)
{
    /* HIER implementieren */
    float Number = NAN;
    stack_element *Element;
    if (thisStack->top != NULL)
    {
        Number = thisStack->top->value;
        Element = thisStack->top;
        thisStack->top = thisStack->top->next;
        free(Element);
    }
    return Number;
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * stack*  - Ein Pointer auf den Stack
 * char*  - Eine Zeichenkette
 */
void process(stack* thisStack, char* Input)
{
    /* HIER implementieren */
    int posLastBlank = 0;
    for (size_t i = 0; i < strlen(Input); i++)
    {
        if (Input[i] == " ")
        {
            char* tmpStr[strlen(Input)];
            int counterTmpStr = 0;
            for (size_t a = posLastBlank; a < i; a++)
            {
                tmpStr[counterTmpStr] = Input[a];
                counterTmpStr++;
            }
            tmpStr[counterTmpStr + 1] = '\0';
            if (is_number(tmpStr))
            {
                stack_push(thisStack, atof(tmpStr));
            }
            if (is_add(tmpStr))
            {
                stack_push(thisStack, stack_pop(thisStack) + stack_pop(thisStack));
            }
            if (is_sub(tmpStr))
            {
                float secondNumber = stack_pop(thisStack);
                stack_push(thisStack, stack_pop(thisStack) - secondNumber);
            }
            if (is_mult(tmpStr))
            {
                stack_push(thisStack, stack_pop(thisStack) * stack_pop(thisStack));
            }
            posLastBlank = i;
        }        
    }
    return;
    /* Du kannst zur Erkennung der Token folgende Hilfsfunktionen
     * benutzen:
     *
     * Funktion          Rückgabewert von 1 bedeutet
     * ---------------------------------------------
     * is_add(token)     Token ist ein Pluszeichen
     * is_sub(token)     Token ist ein Minuszeichen
     * is_mult(token)    Token ist ein Multiplikationszeichen
     * is_number(token)  Token ist eine Zahl
     */
}

/* 
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
    /* HIER implementieren */
    stack *newStack = (stack *)calloc(1, sizeof(stack));
    return newStack;
}