#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>

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

        for(int i = 0; i < 20; i++) {
             sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
        }
    }
 
    HMAC_CTX_cleanup(&copy);
    HMAC_CTX_cleanup(&orig);
    printf("HMAC digest: %s\n", mdString);
}

int main() {
    for (int i = 0; i < 20; i++) {
        do_hash();
    }
}
 
