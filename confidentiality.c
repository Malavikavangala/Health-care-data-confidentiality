#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int mod_inverse(int a, int m) {
	int i;
    for ( i = 1; i < m; i++)
        if ((a * i) % m == 1)
            return i;
    return -1; 
}
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
void encryptDecrypt(char *input, char *key) {
    int keyLen = strlen(key);
    int inputLen = strlen(input);
    int i;
    for ( i = 0; i < inputLen; i++) {
        input[i] = input[i] ^ key[i % keyLen];
    }
}
void shuffleArray(int arr[], int size) {
    srand(time(NULL));
    int i;
 for (i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void deleteSensitiveData(char *data, char *placeholder) {
	int i;
    for (i = 0; data[i] != '\0'; i++) {
        data[i] = placeholder[i % strlen(placeholder)];
    }
}
void rsa(){
	int p, q;
    printf("Enter first prime number (p): ");
    scanf("%d", &p);
    printf("Enter second prime number (q): ");
    scanf("%d", &q);
    int n = p * q;
    int z= (p - 1) * (q - 1);
    int e, d;
    printf("Enter public key (e): ");
    scanf("%d", &e);
    while (gcd(e, z) != 1) {
        printf("Invalid public key. Enter another value for e: ");
        scanf("%d", &e);
    }
    d = mod_inverse(e, z);
    printf("the value of d is %d\n",d);
    printf("the value of z is %d\n",z);
    int message;
    printf("\nEnter a message to encrypt: ");
    scanf("%d", &message);
    long long ciphertext = mod_pow(message, e, n);
    long long decrypted_message = mod_pow(ciphertext, d, n);
    printf("\nOriginal Message: %d\n", message);
    printf("Encrypted Message (Ciphertext): %lld\n", ciphertext);
    printf("Decrypted Message: %lld\n", decrypted_message);
}
void diffie(){
	long long prime;  
    long long primitive_root;
    long long a_private;
    long long b_private;
    printf("enter the prime number,primitive root and private keys of and b\n");
    scanf("%lld %lld %lld %lld",&prime,&primitive_root,&a_private,&b_private);
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
void encrypt(){
char originalMessage[] = "Hello, encryption and decryption!";
    char key[] = "secretkey";
    printf("Original Message: %s\n", originalMessage);
    encryptDecrypt(originalMessage, key);
    printf("Encrypted Message: %s\n", originalMessage);
    encryptDecrypt(originalMessage, key);
    printf("Decrypted Message: %s\n", originalMessage);
}
void shuffling(){
int sensitiveData[15];
	int j;
	printf("print the sensitive data\n");
	for(j=0;j<15;j++)
	 scanf("%d",&sensitiveData[j]);  
    int dataSize = sizeof(sensitiveData) / sizeof(sensitiveData[0]);
    printf("Original Data: ");
    int i;
    for (i = 0; i < dataSize; i++) {
        printf("%d ", sensitiveData[i]);
    }
    printf("\n");
    shuffleArray(sensitiveData, dataSize);
    printf("Shuffled Data: ");
    for (i = 0; i < dataSize; i++) {
        printf("%d ", sensitiveData[i]);
    }
    printf("\n");
}
void substitute(){
	char sensitiveData[10];
    int i;
    printf("enter the data\n");
    for(i=0;i<10;i++)
    scanf("%c",&sensitiveData[i]);
    char placeholder[] = "****"; 
    printf("Original Data: %s\n", sensitiveData);
    deleteSensitiveData(sensitiveData, placeholder);
    printf("Masked Data: %s\n", sensitiveData);
}
int main(){
	int choice,flag=1;
	while(flag){
	printf("1.RSA encryption\n2.Diffie Hellman\n3.Simple encryption\n4.Shuffling-data masking\n5.Substitution-data masking");
	printf("\nenter your choice:");
    scanf("%d",&choice);
    switch(choice){
    	case 1:rsa();
    	break;
    	case 2:diffie();
    	break;
    	case 3:encrypt();
    	break;
    	case 4:shuffling();
    	break;
    	case 5:substitute();
    	break;
    	default:
    		printf("\ninvalid choice");
    		break;
    }
	printf("if you want to continue,\n enter 1 \nelse 0\n");
	scanf("%d",&flag);
}
}
