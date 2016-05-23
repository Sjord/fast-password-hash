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

