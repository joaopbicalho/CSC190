#include <stdio.h>

void g(int *b, int size){
    int temp = 0;
    for(int i = 1; i < size; i++){
        temp = b[i];
        for(int j = i - 1; j > -1; j--){
            if (temp < b[j])
            {
                b[j+1] = b[j];
                b[j] = temp;
            }
            else{break;}
        }
    }
}

 
int main(void){
     
    int b[5] = {3, 6, 2, 5, 4};
    g(b, 5);
    int i = 0;
    for(i = 0; i < 5; i++){
       printf("%d\n", b[i]);
    
    }
    return 0;
}   
