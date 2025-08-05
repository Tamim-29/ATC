#include <stdio.h>      // For file operations like fopen, fgetc, printf
#include <string.h>     // For string comparison using strcmp
#include <ctype.h>      // For character checks like isalpha, isdigit, isalnum

// Define a list of C language keywords we want to detect
char keywords[7][10] = {
    "int", "float", "if", "else", "while", "return", "void"
};

// Function to check if a word is a keyword
int is_keyword(char *word) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(word, keywords[i]) == 0) // Compare with each keyword
            return 1; // Return true if match found
    }
    return 0; // Not a keyword
}

// Function to check if a character is an operator
int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '>' || ch == '<' || ch == '!');
}

// Function to check if a character is a delimiter (used to separate tokens)
int is_delimiter(char ch) {
    return (ch == ' ' || ch == ',' || ch == ';' || ch == '(' ||
            ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']');
}

// Main function
int main() {
    FILE *fptr;                   // File pointer to read from a file
    char ch, word[100];          // ch: current character, word[]: to store current word
    int i = 0;                   // Index for word array

    // Counters for each token type
    int total_keywords = 0;
    int total_identifiers = 0;
    int total_operators = 0;
    int total_numbers = 0;
    int total_arguments = 0;

    int inside_parentheses = 0;  // To track if we are inside function arguments

    // Open the file input.txt in read mode
    fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("File not found.\n");
        return 1; // Exit the program if file can't be opened
    }

    // Read character by character until end of file (EOF)
    while ((ch = fgetc(fptr)) != EOF) {
        // If the character is part of a word (letter, digit, underscore or dot)
        if (isalnum(ch) || ch == '.' || ch == '_') {
            word[i++] = ch; // Add it to the word buffer
        } else {
            // If a non-word character is found, we end the current word
            if (i > 0) {
                word[i] = '\0'; // Null-terminate the word
                i = 0;          // Reset word buffer index for next word

                // Check and categorize the word
                if (is_keyword(word)) {
                    printf("Keyword: %s\n", word);
                    total_keywords++;
                } else if (isdigit(word[0]) || (word[0] == '.' && isdigit(word[1]))) {
                    // A number could start with a digit or . followed by digit (like .5)
                    printf("Number: %s\n", word);
                    total_numbers++;
                } else if (isalpha(word[0]) || word[0] == '_') {
                    // If it starts with a letter or underscore, it's an identifier
                    if (inside_parentheses) {
                        printf("Argument: %s\n", word);
                        total_arguments++;
                    } else {
                        printf("Identifier: %s\n", word);
                        total_identifiers++;
                    }
                }
            }

            // If current character is an operator, handle it
            if (is_operator(ch)) {
                char next = fgetc(fptr); // Peek the next character

                // Handle two-character operators like ==, <=, !=, etc.
                if (next == '=' || (ch == '=' && next == '=')) {
                    printf("Operator: %c%c\n", ch, next); // Example: ==
                } else {
                    printf("Operator: %c\n", ch);         // Single-char operator like +
                    ungetc(next, fptr); // Put back the character if it’s not part of two-char operator
                }
                total_operators++; // Count this operator
            }

            // Track if we are inside function argument list (inside parentheses)
            if (ch == '(')
                inside_parentheses = 1;
            else if (ch == ')')
                inside_parentheses = 0;
        }
    }

    fclose(fptr); // Close the file after reading

    // Print summary of total counts
    printf("\n--- Summary ---\n");
    printf("Total Keywords   : %d\n", total_keywords);
    printf("Total Identifiers: %d\n", total_identifiers);
    printf("Total Numbers    : %d\n", total_numbers);
    printf("Total Operators  : %d\n", total_operators);
    printf("Total Arguments  : %d\n", total_arguments);

    return 0; // Program ends
}
