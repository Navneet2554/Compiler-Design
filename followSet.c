//#include <stdlib.h> follow.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 10
void findFollow(char symbol, char followSet[], int *index);
void addToResultSet(char symbol, char followSet[], int *index);
int isInResultSet(char symbol, char followSet[], int index);
void computeAllFollowSets();
int numOfProductions;
char productionSet[MAX][MAX];
char nonTerminals[MAX];
int nonTerminalCount = 0;
int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &numOfProductions);
    printf("Enter the productions :\n");
    for (int i = 0; i < numOfProductions; i++){
        scanf("%s", productionSet[i]);
    }
    for (int i = 0; i < numOfProductions; i++){
        if (isInResultSet(productionSet[i][0], nonTerminals, nonTerminalCount) == 0){
            nonTerminals[nonTerminalCount++] = productionSet[i][0];
        }
    }
    printf("\nFOLLOW Sets:\n");
    computeAllFollowSets();
    return 0;
}
void computeAllFollowSets() {
    for (int i = 0; i < nonTerminalCount; i++){
             char followSet[MAX] = {0};
             int followSetIndex = 0;
             findFollow(nonTerminals[i], followSet, &followSetIndex);

             printf("%c\t\t{ ", nonTerminals[i]);
             for (int j = 0; j < followSetIndex; j++){
                 printf("%c ", followSet[j]);
             }
             printf("}\n");
         }
 }

void findFollow(char symbol, char followSet[], int *index){
    if (symbol == productionSet[0][0]){
             addToResultSet('$', followSet, index);
         }

         for (int i = 0; i < numOfProductions; i++){
             for (int j = 3; j < strlen(productionSet[i]); j++){
                 if (productionSet[i][j] == symbol){
                     if (productionSet[i][j + 1] != '\0'){
                         char nextSymbol = productionSet[i][j + 1];
                         if (islower(nextSymbol)){
                             addToResultSet(nextSymbol, followSet, index);
                         }
                         else{
                             char firstSet[MAX] = {0};
                             int firstSetIndex = 0;
                             for (int k = 0; k < numOfProductions; k++){
                                 if (productionSet[k][0] == nextSymbol){
                                     char *prod = strtok(&productionSet[k][3], "|");
                                     while (prod != NULL){
                                         if (islower(prod[0])){
                                             addToResultSet(prod[0], followSet, index);
                                             break;
                                         }
                                         else if (prod[0] == '#'){
                                             addToResultSet('#', followSet, index);
                                             break;
                                         }
                                         else{
                                             findFollow(prod[0], followSet, index);
                                             for (int m = 0; m < *index; m++){
                                                 if (followSet[m] != '#'){
                                                     addToResultSet(followSet[m], followSet, index);
                                                 }
                                             }
                                             if (isInResultSet('#', followSet, *index)){
                                                 findFollow(productionSet[i][0], followSet, index);
                                             }
                                         }
                                         prod = strtok(NULL, "|");
                                     }
                                 }
                             }
                       }
                     }
                     else{
                         findFollow(productionSet[i][0], followSet, index);
                     }
                 }
             }
         }
  }

void addToResultSet(char symbol, char followSet[], int *index){
        if (!isInResultSet(symbol, followSet, *index)){
            followSet[(*index)++] = symbol;
        }
}
 int isInResultSet(char symbol, char followSet[], int index){
         for (int i = 0; i < index; i++){
             if (followSet[i] == symbol){
                 return 1;
             }
         }
      return 0;
 }



