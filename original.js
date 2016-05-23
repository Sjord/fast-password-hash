var passwordHash = require('password-hash');
var res, i;
for (i = 0; i < 20; i++) {
    res = passwordHash.generate('pass1234', {iterations: 300000})
    console.log(res);
}
