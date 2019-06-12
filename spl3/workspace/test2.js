function checkPalindrom (str) {
    str = str.toLowerCase();
    return str == str.split('').reverse().join('');
}

if(checkPalindrom('Civic')){
    console.log('palindrome');
}
else{
    console.log('not palindrome');
}