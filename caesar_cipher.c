#include <stdio.h>
#include <ctype.h>

char text[100], cipher, temp;
int key, choice;

// Encoder function
// cipher = (cipher - 'a' + key) % 26 + 'a'
void encode_cipher() {
    printf("Enter the text you want to encode: ");
    scanf("%c", &temp); // Clear the buffer
    scanf("%[^\n]s", text);
    printf("Enter the key: ");
    scanf("%d", &key);

    // Go through each characters one by one
    for (int i = 0; text[i] != '\0'; ++i) {
        cipher = text[i];

        if(isalnum(cipher)) {
            // Lowercase
            if (islower(cipher)) {
                cipher = (cipher - 'a' + key) % 26 + 'a';
            }

            // Uppercase
            if (isupper(cipher)) {
                cipher = (cipher - 'A' + key) % 26 + 'A';
            }

            // Numbers
            if (isdigit(cipher)) {
                cipher = (cipher - '0' + key) % 10 + '0';
            }
            
        }
        text[i] = cipher;
        
    }
    printf("Encrypted text: %s\n", text);
}

// Decoder function
// cipher = (cipher - 'a' - key + 26) % 26 + 'a'
void decode_cipher() {
    printf("Enter the text you want to decode: ");
    scanf("%c", &temp); // Clear the buffer
    scanf("%[^\n]s", text);
    printf("Enter the key: ");
    scanf("%d", &key);

    // Go through each characters one by one
    for (int i = 0; text[i] != '\0'; ++i) {
        cipher = text[i];

        if(isalnum(cipher)) {
            // Lowercase        
            if (islower(cipher)) {
                cipher = (cipher - 'a' - key + 26) % 26 + 'a';
            }

            // Uppercase
            if (isupper(cipher)) {
                cipher = (cipher - 'A' - key + 26) % 26 + 'A';
            }

            // Numbers
            if (isdigit(cipher)) {
                cipher = (cipher - '0' - key + 10) % 10 + '0';
            }
            
        }
        text[i] = cipher;
        
    }
    printf("Decoded text: %s\n", text);
}

// Main menu code
int main() {
    printf("\n******************************************************************\n");
    printf("              Welcome to the Caesar Cipher Program!\n");
    printf("******************************************************************\n\n");
    printf("What operations you want to do?\n\n");
    printf("1. Encode Text\n");
    printf("2. Decode Text\n");
    printf("3. Exit\n\n");
    printf("Choose the operation you want to do(1-3): ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("You have chosen encode.\n");
            encode_cipher();
            break;
        case 2:
            printf("You have chosen decode.\n");
            decode_cipher();
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Exiting...\n");
            return 0;
    }

    return 0;
}
