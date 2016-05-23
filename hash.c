#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>

void bin2hex(unsigned char *bin, unsigned int binsz, char * result)
{
    char          hex_str[]= "0123456789abcdef";
    unsigned int  i;

    result[binsz * 2] = 0;

    for (i = 0; i < binsz; i++) {
        result[i * 2 + 0] = hex_str[(bin[i] >> 4) & 0x0F];
        result[i * 2 + 1] = hex_str[(bin[i]     ) & 0x0F];
    }  
}

void do_hash()
{
    char salt[] = "ea911135";
    char pass[] = "pass1234";
    
    unsigned char digest[20];
    int digest_len;
    char mdString[40];

    strcpy(mdString, pass);

    HMAC_CTX orig, copy;
    HMAC_CTX_init(&orig);
    HMAC_CTX_init(&copy);

    HMAC_Init_ex(&orig, salt, strlen(salt), EVP_sha1(), NULL);

    for (int iter = 0; iter < 300000; iter++) {
        HMAC_CTX_copy(&copy, &orig);
        HMAC_Update(&copy, mdString, strlen(mdString));
        HMAC_Final(&copy, digest, &digest_len);

        bin2hex(digest, digest_len, mdString);
    }
 
    HMAC_CTX_cleanup(&copy);
    HMAC_CTX_cleanup(&orig);
    printf("HMAC digest: %s\n", mdString);
    // should print f27f36023135a1dfb51517be5be0b421ee061d35
}

int main() {
    for (int i = 0; i < 20; i++) {
        do_hash();
    }
}
 
