#include <stdio.h>
#include <string.h>
#include <ctype.h>


char keywords[7][10] = {
    "int",
    "float",
    "if",
    "else",
    "while",
    "return",
    "void"
};

int keyword_count = 7;

int is_keyword(char *word){
    for(int i = 0; i < keyword_count; i++){
        if(strcmp(word, keywords[i]) == 0){
            return 1; // Found a keyword
        }
    }
    return 0;
}

int main() {
    char ch, word[50];
    int total_keywords = 0, total_identifiers = 0, i = 0;


    FILE *fptr;
    fptr = fopen("input.txt", "r");

    if(fptr == NULL) {
        printf("File Not Found.\n");
        return 1;
    }

    while ((ch = fgetc(fptr)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            word[i++] = ch;
        } else {
            if (i != 0) {
                word[i] = '\0';
                i = 0;

                if (is_keyword(word)) {
                    printf("Keyword: %s\n", word);
                    total_keywords++;
                } else if (isalpha(word[0]) || word[0] == '_') {
                    printf("Identifier: %s\n", word);
                    total_identifiers++;
                }
            }
        }
    }

    fclose(fptr); // Close the file

    printf("\n--- Summary ---\n");
    printf("Total Keywords   : %d\n", total_keywords);
    printf("Total Identifiers: %d\n", total_identifiers);

    return 0;
}
