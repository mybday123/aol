#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

enum Options {
    DECODE,
    ENCODE
};

char *encode_text(char* text, int key) {
    if (!text)
        return NULL;

    int charlen = strlen(text);
    char *ciphered_text = malloc(charlen + 1);
    if (ciphered_text == NULL)
        return NULL;

    for (int i = 0; text[i] != '\0'; ++i) {
        char letter = text[i];

        if(isalnum(letter)) {
            /* Letters */
            if (islower(letter)) {
                letter = (letter - 'a' + key) % 26 + 'a';
            }
            else if (isupper(letter)) {
                letter = (letter - 'A' + key) % 26 + 'A';
            }
            /* Numbers */
            else if (isdigit(letter)) {
                letter = (letter - '0' + key) % 10 + '0';
            }
        }
        ciphered_text[i] = letter;
    }
    ciphered_text[charlen] = '\0';
    return ciphered_text;
}

char *decode_text(char* text, int key) {
    if (!text)
        return NULL;

    int charlen = strlen(text);
    char *deciphered_text = malloc(charlen + 1);
    if (!deciphered_text)
        return NULL;

    for (int i = 0; text[i] != '\0'; ++i) {
        char letter = text[i];

        if(isalnum(letter)) {
            /* Letters */
            if (islower(letter)) {
                letter = (letter - 'a' - key + 26) % 26 + 'a';
            }
            else if (isupper(letter)) {
                letter = (letter - 'A' - key + 26) % 26 + 'A';
            }
            /* Numbers */
            else if (isdigit(letter)) {
                letter = (letter - '0' - key + 26) % 10 + '0';
            }
        }
        deciphered_text[i] = letter;
    }
    deciphered_text[charlen] = '\0';
    return deciphered_text;
}

int main(int argc, char **argv) {
    int option = ENCODE;
    int key = 5;
    char* text = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            option = DECODE;
        }
        else if (strcmp(argv[i], "-e") == 0) {
            option = ENCODE;
        }
        else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                key = atoi(argv[++i]);
            }
            else {
                puts("-n expected a number");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                text = argv[++i];
            }
            else {
                puts("-t expected a text");
                exit(EXIT_FAILURE);
            }
        }
        else {
            printf("Unknown option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }
    
    /* Read from stdin if -f is not given */   
    if (!text) {
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            exit(EXIT_FAILURE);
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        text = buffer;
    }
    char *processed_text = NULL;
    switch (option) {
        case ENCODE:
            processed_text = encode_text(text, key);
            break;
        case DECODE:
            processed_text = decode_text(text, key);
            break;
    }

    if (processed_text) {
        printf("%s\n", processed_text);
        free(processed_text);
        exit(EXIT_SUCCESS);
    }
    else
        exit(EXIT_FAILURE);
    
    return 0;
}
