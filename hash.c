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
    for (int iter = 0; iter < 300000; iter++) {
        HMAC(EVP_sha1(), salt, strlen(salt), mdString, strlen(mdString), digest, &digest_len);
        for(int i = 0; i < 20; i++) {
             sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
        }
    }
 
    printf("HMAC digest: %s\n", mdString);
}

int main() {
    for (int i = 0; i < 20; i++) {
        do_hash();
    }
}
 