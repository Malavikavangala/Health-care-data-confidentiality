#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void nullingOut(char *data) {
    while (*data != '\0') {
        *data = '\0';
        data++;
    }
}
void substitutionMasking(char *data, char *placeholder) {
    int len = strlen(placeholder);
    int i = 0;
    while (*data != '\0') {
        *data = placeholder[i % len];
        data++;
        i++;
    }
}
void characterScrambling(char *data) {
    int len = strlen(data);
    srand(time(NULL));
    int i;
    for ( i = 0; i < len; i++) {
        int j = rand() % len;
        char temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}
void shuffleArray(int arr[], int size) {
    srand(time(NULL));
    int i;
    for ( i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
void hashMasking(char *data, int key) {
    while (*data != '\0') {
        *data ^= key;
        data++;
    }
}
void tokenize(char *data, char *token) {
    char *tokenizedData = strtok(data, " ");
    while (tokenizedData != NULL) {
        printf("%s ", token);
        tokenizedData = strtok(NULL, " ");
    }
}
void redact(char *data) {
    while (*data != '\0') {
        *data = '#';
        data++;
    }
}
void randomPadding(char *data, int paddingLength) {
    int len = strlen(data);
    int i;
    srand(time(NULL));
    for ( i = 0; i < paddingLength; i++) {
        int pos = rand() % len;
        memmove(&data[pos + 1], &data[pos], len - pos + 1);
        data[pos] = rand() % 256; 
        len++;
    }
}
void rotateCharacters(char *data, int shift) {
    int len = strlen(data);
    int i;
    for (i = 0; i < len; i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' + shift) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' + shift) % 26;
        }
    }
}
int main() {
    int choice;
    char sensitiveData[100];
    char placeholder[] = "****";
    int arr[100];
    int size;
    int hashKey;
    char token[] = "[TOKEN]";
    int paddingLength;
    int rotationShift;
    do {
        printf("\nData Masking Techniques Menu:\n");
        printf("1. Nulling Out Data\n");
        printf("2. Substitution Masking\n");
        printf("3. Character Scrambling Masking\n");
        printf("4. Shuffle Array Masking\n");
        printf("5. Hash Masking\n");
        printf("6. Tokenization\n");
        printf("7. Redact Data\n");
        printf("8. Random Padding\n");
        printf("9. Rotate Characters\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter sensitive data to null out: ");
                scanf(" %[^\n]s", sensitiveData);
                nullingOut(sensitiveData);
                printf("Nullified Data: %s\n", sensitiveData);
                break;
            case 2:
                printf("Enter sensitive data to mask: ");
                scanf(" %[^\n]s", sensitiveData);
                substitutionMasking(sensitiveData, placeholder);
                printf("Masked Data: %s\n", sensitiveData);
                break;
            case 3:
                printf("Enter sensitive data to scramble: ");
                scanf(" %[^\n]s", sensitiveData);
                characterScrambling(sensitiveData);
                printf("Scrambled Data: %s\n", sensitiveData);
                break;
            case 4:	
                printf("Enter the size of array: ");
                scanf("%d", &size);
                printf("Enter %d elements for the array: ", size);
                int i;
                for ( i = 0; i < size; i++) {
                    scanf("%d", &arr[i]);
                }
                shuffleArray(arr, size);
                printf("Shuffled Array: ");
                for (i = 0; i < size; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;
            case 5:
                printf("Enter sensitive data to hash mask: ");
                scanf(" %[^\n]s", sensitiveData);
                printf("Enter hash key (integer): ");
                scanf("%d", &hashKey);
                hashMasking(sensitiveData, hashKey);
                printf("Hash Masked Data: %s\n", sensitiveData);
                break;
            case 6:
                printf("Enter sentence to tokenize: ");
                getchar(); // consume newline left by previous scanf
                fgets(sensitiveData, sizeof(sensitiveData), stdin);
                tokenize(sensitiveData, token);
                printf("\n");
                break;
            case 7:
                printf("Enter sensitive data to redact: ");
                scanf(" %[^\n]s", sensitiveData);
                redact(sensitiveData);
                printf("Redacted Data: %s\n", sensitiveData);
                break;
            case 8:
                printf("Enter sensitive data for random padding: ");
                scanf(" %[^\n]s", sensitiveData);
                printf("Enter padding length: ");
                scanf("%d", &paddingLength);
                randomPadding(sensitiveData, paddingLength);
                printf("Padded Data: %s\n", sensitiveData);
                break;
            case 9:
                printf("Enter sensitive data to rotate characters: ");
                scanf(" %[^\n]s", sensitiveData);
                printf("Enter rotation shift (positive or negative integer): ");
                scanf("%d", &rotationShift);
                rotateCharacters(sensitiveData, rotationShift);
                printf("Rotated Data: %s\n", sensitiveData);
                break;
            case 10:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 10.\n");
                break;
        }
    } while (choice != 10);
    return 0;
}

