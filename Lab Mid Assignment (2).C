#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of keywords
char keywords[][10] = {
    "int", "float", "if", "else", "for", "while", "return"
};
int keywordCount = 7;

// Function to check if a word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a string is a number
int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '.')
            return 0;
    }
    return 1;
}

int main() {
    char code[200];
    printf("Enter a line of code:\n");
    fgets(code, sizeof(code), stdin);

    char token[50];
    int i = 0, j = 0;

    int keywordCnt = 0, identifierCnt = 0, numberCnt = 0, operatorCnt = 0, argumentCnt = 0;

    printf("\n--- Tokens Found ---\n");

    while (code[i] != '\0') {
        // If space or punctuation, process the token
        if (isspace(code[i]) || strchr("+-*/=(){}", code[i])) {
            if (j != 0) { // we have a token ready
                token[j] = '\0';

                if (isKeyword(token)) {
                    printf("Keyword: %s\n", token);
                    keywordCnt++;
                }
                else if (isNumber(token)) {
                    printf("Number: %s\n", token);
                    numberCnt++;
                }
                else {
                    printf("Identifier: %s\n", token);
                    identifierCnt++;
                }

                j = 0; // reset token
            }

            // Check for operators
            if (strchr("+-*/=", code[i])) {
                printf("Operator: %c\n", code[i]);
                operatorCnt++;
            }

            // Check for arguments (inside parentheses)
            if (code[i] == '(' || code[i] == ')') {
                printf("Argument symbol: %c\n", code[i]);
                argumentCnt++;
            }
        }
        else {
            token[j++] = code[i]; // building the token
        }
        i++;
    }

    // Display counts
    printf("\n--- Summary ---\n");
    printf("Keywords: %d\n", keywordCnt);
    printf("Identifiers: %d\n", identifierCnt);
    printf("Numbers: %d\n", numberCnt);
    printf("Operators: %d\n", operatorCnt);
    printf("Arguments: %d\n", argumentCnt);

    return 0;
}
