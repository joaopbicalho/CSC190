#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

int compare_str(const void *pa,const void *pb){
    return strcmp(((struct term *)pa)->term , (((struct term *)pb)->term));
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){

    char line[200];
    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    *pnterms = atof(line);

    *terms = (struct term *)malloc((*pnterms) * (sizeof(struct term)));

    for(int i = 0; i < *pnterms; i++){
        

        fgets(line, sizeof(line), fp); 
        
        int j = 0;
        double num = 0;            
     
        while( ! isdigit(line[j]))
        {
            j++;
        }
        for(; isdigit(line[j]); j++){
            num = num*10 + (line[j] - '0');
        }
        (*terms+i)->weight = num;

        int k = 0;
        char str[200];
        for(int k = 0; line[k] != '\n' && line[k] != '\r' && (line[k]); k++){
    
            str[k] = line[k+15];
            if (str[k] == '\n'){
                str[k] = '\0';
            }
        }
        
        strncpy((*terms+i)->term, str ,200);
        //strncpy(str,line,sizeof();
        //strtok(\t)
    }
    size_t size = sizeof(struct term);
    qsort(*terms, *pnterms, size, compare_str);
    fclose(fp);
    //printf("%s", (*terms)[0].weight);

}


int lowest_match(struct term *terms, int nterms, char *substr)
{
   
    int i = 0;
    int j = 0;
    int k = 0;
    int size = strlen(substr);
    int start_index = 0;
    int end_index = nterms-1;
    while (start_index <= end_index){
        int mid = (end_index + start_index )/2;
        if ((strncmp((terms+mid)->term, substr, size)) == 0){
            while((strncmp((terms+mid-i)->term, substr, size)) == 0){
                i++;
            }
            return mid-i;      
        }
        
        if ((strncmp((terms+mid)->term, substr, size)) < 0)
            start_index = mid + 1;
        else
            end_index = mid - 1;
    }
    return -1;
}


int highest_match(struct term *terms, int nterms, char *substr)
{
       
    int i = 0;
    int j = 0;
    int k = 0;
    int size = strlen(substr);
    int start_index = 0;
    int end_index = nterms -1;
    while (start_index <= end_index ){
        int mid = (end_index+ start_index )/2;
        if ((strncmp((terms+mid)->term, substr, size)) == 0){
            while((strncmp((terms+mid+i)->term, substr, size)) == 0){
                i++;
            }
            return mid+i;      
        }
        
        if ((strncmp((terms+mid)->term, substr, size)) < 0)
            start_index = mid + 1;
        else
            end_index = mid - 1;
    }
    return -1;
}

int compare_weight(const void *pa,const void *pb){
    return (((struct term *)pb)->weight - (((struct term *)pa)->weight));
}
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{
    int start = lowest_match(terms, nterms, substr);
    //printf("%d", start);
    int end = highest_match(terms, nterms, substr);
    //printf("%d", end);
     if (end < 0 || start < 0)
    {
        *n_answer = 0;
        *answer = NULL;
        return;
    }
    *n_answer = (end-start+1);
    //printf("%d \n", *n_answer);
    
    *answer = (struct term*)malloc((*n_answer) * (sizeof(struct term)));
    for (int i = 0; i < *n_answer; i++){
        //printf("%s", terms[start+i].term);
        (*answer)[i] = terms[start+i];
        //printf("%s\t%lf", (*answer)[i].term, (*answer)[i].weight);
    }
    size_t size = sizeof(struct term);
    
    qsort(*answer, *n_answer, size, compare_weight);
    //printf("%s", (*answer)[0].term);
    // for (int i = 0; i < *n_answer; i++){
    //     //printf("%s", terms[start+i].term);
    //     printf("\n%lf %s", (*answer)[i].weight, (*answer)[i].term);
    // }
} 
