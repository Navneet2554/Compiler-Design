// FULL PHASE

#include <stdio.h>
#include <string.h>

#define MAX 100

// Function to identify parts of the production and eliminate left recursion if present
void identifyPartsAndEliminateLeftRecursion(char *production) {
    char nonTerminal = production[0];  // The first character is the non-terminal
    char *token;
    char subProductions[MAX][MAX];
    int count = 0;

    // Skip '->' and split by '|'
    token = strtok(production + 4, "|");

    while (token != NULL) {
        strcpy(subProductions[count++], token);
        printf("Non-terminal: %c\n", nonTerminal);
        printf("Variable part: %s\n", token);
        token = strtok(NULL, "|");
    }

    // Now eliminate left recursion if any
    char alpha[MAX][MAX], beta[MAX][MAX];
    int alphaCount = 0, betaCount = 0;

    for (int i = 0; i < count; i++) {
        if (subProductions[i][0] == nonTerminal) {
            // If production has left recursion (starts with the non-terminal)
            strcpy(alpha[alphaCount++], subProductions[i] + 1); // Store the part after the non-terminal
        } else {
            // Otherwise, store it as beta
            strcpy(beta[betaCount++], subProductions[i]);
        }
    }

    // If there's no left recursion, no further action is needed
    if (alphaCount == 0) {
        printf("The given production does not have left recursion.\n");
        return;
    }

    // Print the new grammar after eliminating left recursion
    printf("Grammar after eliminating left recursion:\n");

    // Beta productions
    for (int i = 0; i < betaCount; i++) {
        printf("%c -> %s%c\'\n", nonTerminal, beta[i], nonTerminal);
    }

    // Alpha productions
    for (int i = 0; i < alphaCount; i++) {
        printf("%c\' -> %s%c\'\n", nonTerminal, alpha[i], nonTerminal);
    }
    printf("%c\' -> ε\n", nonTerminal); // Epsilon (ε) production
}

int main() {
    int numProductions;
    char productions[MAX][MAX];

    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);

    for (int i = 0; i < numProductions; i++) {
        printf("Enter production %d (e.g., L -> L,S | S): ", i + 1);
        scanf(" %[^\n]", productions[i]);
    }

    printf("\nIdentifying parts and eliminating left recursion for each production:\n");
    for (int i = 0; i < numProductions; i++) {
        printf("\nProduction %d:\n", i + 1);
        identifyPartsAndEliminateLeftRecursion(productions[i]);
    }

    return 0;
}
