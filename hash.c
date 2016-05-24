#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>

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

static inline void sha1_cpy(SHA_CTX *restrict out, const SHA_CTX *restrict in)
{
  out->h0 = in->h0;
  out->h1 = in->h1;
  out->h2 = in->h2;
  out->h3 = in->h3;
  out->h4 = in->h4;
}

void do_hash()
{
    char salt[] = "ea911135";
    char pass[] = "pass1234";

    unsigned char digest[20] = {0};
    int digest_len = sizeof(digest);
    char mdString[41] = {0};

    char padded_salt[64] = {0};
    strcpy(padded_salt, salt);
    char i_key_pad[64];
    char o_key_pad[64];

    for (int i = 0; i < 64; i++) {
        i_key_pad[i] = 0x36 ^ padded_salt[i];
    }

    for (int i = 0; i < 64; i++) {
        o_key_pad[i] = 0x5c ^ padded_salt[i];
    }

    SHA_CTX work_inner, work_outer;
    SHA1_Init(&work_inner);
    SHA1_Init(&work_outer);

    strcpy(mdString, pass);

    for (int iter = 0; iter < 300000; iter++) {

        SHA1_Init(&work_inner);
        SHA1_Init(&work_outer);

        SHA1_Update(&work_outer, o_key_pad, 64);
        SHA1_Update(&work_inner, i_key_pad, 64);
 
        SHA1_Update(&work_inner, mdString, strlen(mdString));
        SHA1_Final(digest, &work_inner);

        SHA1_Update(&work_outer, digest, 20);
        SHA1_Final(digest, &work_outer);

        bin2hex(digest, digest_len, mdString);
    }
 
    printf("HMAC digest: %s\n", mdString);
    // should print f27f36023135a1dfb51517be5be0b421ee061d35
}

int main() {
    for (int i = 0; i < 20; i++) {
        do_hash();
    }
}
 
