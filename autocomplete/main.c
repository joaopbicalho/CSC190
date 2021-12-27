#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"


int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    int x = lowest_match(terms, nterms, "Tor");
    //printf("%d \n", x);
    int y = highest_match(terms, nterms, "Tor");
    //printf("%d \n" , y);
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice
    printf("%s", answer->term);
    return 0;
}
