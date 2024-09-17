#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Function prototypes
int is_prime(int num);
int gcd(int a, int b);
int mod_inverse(int a, int m);
long long mod_pow(long long base, long long exp, long long mod);
void shuffleArray(int arr[], int size);
void rsa();
void diffie();
void nullingOut(char data[]);
void substitutionMasking(char data[], const char placeholder[]);
void characterScrambling(char data[]);
void hashMasking(char data[], int key);
void tokenize(char data[], const char token[]);
void randomPadding(char data[], int paddingLength);
void rotateCharacters(char data[], int shift);

int is_prime(int num) {
    int i;
    if (num <= 1) return 0; 
    if (num <= 3) return 1; 
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    int i;
    for (i = 1; i < m; i++) if ((a * i) % m == 1) return i;
    return -1; 
}

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void shuffleArray(int arr[], int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void rsa() {
    int p, q;
    printf("Enter first prime number (p): ");
    scanf("%d", &p);
    while (!is_prime(p)) {
        printf("%d is not a prime number, enter a prime number\n", p);
        scanf("%d", &p);
    }
    printf("Enter second prime number (q): ");
    scanf("%d", &q);
    while (!is_prime(q)) {
        printf("%d is not a prime number, enter a prime number\n", q);
        scanf("%d", &q);
    }
    if (p == q) {
        printf("p and q should not be equal. Try again.\n");
        return;
    }

    int n = p * q;
    int z = (p - 1) * (q - 1);
    int e, d;

    printf("Enter public key (e): ");
    scanf("%d", &e);
    while (gcd(e, z) != 1) {
        printf("Invalid public key. Enter another value for e: ");
        scanf("%d", &e);
    }

    d = mod_inverse(e, z);
    if (d == -1) {
        printf("Modular inverse not found. Choose a different e.\n");
        return;
    }

    printf("The value of d is %d\n", d);
    printf("The value of n is %d\n", n);
    printf("The value of z is %d\n", z);

    int message;
    printf("Enter a message to encrypt (as an integer less than n): ");
    scanf("%d", &message);

    if (message >= n) {
        printf("Message must be smaller than n (%d).\n", n);
        return;
    }

    long long ciphertext = mod_pow(message, e, n);
    long long decrypted_message = mod_pow(ciphertext, d, n);

    printf("Original Message: %d\n", message);
    printf("Encrypted Message (Ciphertext): %lld\n", ciphertext);
    printf("Decrypted Message: %lld\n", decrypted_message);
}

void diffie() {
    long long prime, primitive_root, a_private, b_private;
    printf("Enter the prime number, primitive root, and private keys of Alice and Bob:\n");
    scanf("%lld %lld %lld %lld", &prime, &primitive_root, &a_private, &b_private);
    long long a_public = mod_pow(primitive_root, a_private, prime);
    long long b_public = mod_pow(primitive_root, b_private, prime);
    long long shared_secret_alice = mod_pow(b_public, a_private, prime);
    long long shared_secret_bob = mod_pow(a_public, b_private, prime);
    printf("Shared prime number: %lld\n", prime);
    printf("Primitive root modulo prime: %lld\n\n", primitive_root);
    printf("Alice's public key: %lld\n", a_public);
    printf("Bob's public key: %lld\n\n", b_public);
    printf("Shared secret for Alice: %lld\n", shared_secret_alice);
    printf("Shared secret for Bob: %lld\n", shared_secret_bob);
}

void nullingOut(char data[]) {
    int i = 0;
    while (data[i] != '\0') {
        data[i] = '\0';
        i++;
    }
}

void substitutionMasking(char data[], const char placeholder[]) {
    int len = strlen(placeholder);
    int i = 0;
    while (data[i] != '\0') {
        data[i] = placeholder[i % len];
        i++;
    }
}

void characterScrambling(char data[]) {
    int len = strlen(data);
    srand(time(NULL));
    for (int i = 0; i < len; i++) {
        int j = rand() % len;
        char temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}

void hashMasking(char data[], int key) {
    int i = 0;
    while (data[i] != '\0') {
        data[i] ^= key;
        i++;
    }
}

void tokenize(char data[], const char token[]) {
    char temp[100];
    int i = 0, j = 0;
    while (data[i] != '\0') {
        if (data[i] == ' ' || data[i] == '\n') {
            temp[j] = '\0';
            printf("%s ", token);
            j = 0;
        } else {
            temp[j++] = data[i];
        }
        i++;
    }
    temp[j] = '\0';
    printf("%s ", token);
}

void randomPadding(char data[], int paddingLength) {
    int len = strlen(data);
    srand(time(NULL));
    for (int i = 0; i < paddingLength; i++) {
        int pos = rand() % (len + 1);
        memmove(&data[pos + 1], &data[pos], len - pos + 1);
        data[pos] = rand() % 256; 
        len++;
    }
    data[len] = '\0';
}

void rotateCharacters(char data[], int shift) {
    int len = strlen(data);
    for (int i = 0; i < len; i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' + shift) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' + shift) % 26;
        }
    }
}

int main() {
    int choice;
    int flag = 1;
    char sensitiveData[100];
    const char placeholder[] = "****";
    int arr[100];
    int size;
    int hashKey;
    const char token[] = "[TOKEN]";
    int paddingLength;
    int rotationShift;
    
    while (flag) {
        printf("1. RSA encryption\n");
        printf("2. Diffie Hellman\n");
        printf("3. Nulling Out Data\n");
        printf("4. Substitution Masking\n");
        printf("5. Character Scrambling\n");
        printf("6. Hash Masking\n");
        printf("7. Tokenization\n");
        printf("8. Random Padding\n");
        printf("9. Rotate Characters\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: rsa(); break;
            case 2: diffie(); break;
            case 3:
                printf("Enter sensitive data to null out: ");
                scanf(" %[^\n]s", sensitiveData);
                nullingOut(sensitiveData);
                printf("Nullified Data: %s\n", sensitiveData);
                break;
            case 4:
                printf("Enter sensitive data to mask: ");
                scanf(" %[^\n]s", sensitiveData);
                substitutionMasking(sensitiveData, placeholder);
                printf("Masked Data: %s\n", sensitiveData);
                break;
            case 5:
                printf("Enter sensitive data to scramble: ");
                scanf(" %[^\n]s", sensitiveData);
                characterScrambling(sensitiveData);
                printf("Scrambled Data: %s\n", sensitiveData);
                break;
            case 6:
                printf("Enter sensitive data to hash mask: ");
                scanf(" %[^\n]s", sensitiveData);
                printf("Enter hash key: ");
                scanf("%d", &hashKey);
                hashMasking(sensitiveData, hashKey);
                printf("Hash Masked Data: %s\n", sensitiveData);
                break;
            case 7:
                printf("Enter sensitive data to tokenize: ");
                scanf(" %[^\n]s", sensitiveData);
                tokenize(sensitiveData, token);
                printf("\n");
                break;
            case 8:
                printf("Enter sensitive data for random padding: ");
                scanf(" %[^\n]s", sensitiveData);
                printf("Enter padding length: ");
                scanf("%d", &paddingLength);
                randomPadding(sensitiveData, paddingLength);
                printf("Data with Padding: %s\n", sensitiveData);
                break;
            case 9:
                printf("Enter sensitive data to rotate: ");
                scanf(" %[^\n]s", sensitiveData);
                printf("Enter rotation shift: ");
                scanf("%d", &rotationShift);
                rotateCharacters(sensitiveData, rotationShift);
                printf("Rotated Data: %s\n", sensitiveData);
                break;
            case 10:
                flag = 0;
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}

