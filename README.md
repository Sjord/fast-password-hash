## Fast password-hash

[Node-password-hash](https://github.com/davidwood/node-password-hash), but faster. 

Don't use this project or [node-password-hash](https://github.com/davidwood/node-password-hash) in production for hashing passwords.

## Building

    gcc -g -o hash hash.c -lcrypto

## Timings

Times for 300,000 iterations:

| implementation  | time    |
|-----------------|---------|
| original        | 0.933 s |
| naive C         | 0.733 s |
| reuse HMAC ctx  | 0.587 s |
| fast `bin2hex`  | 0.180 s |
| lean copy       | 0.124 s |
