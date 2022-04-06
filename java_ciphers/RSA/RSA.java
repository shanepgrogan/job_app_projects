// Shane Grogan
// B00327174
// Assignment 5
// Question 2: RSA Cipher

import java.util.*;

class RSA{

    // instance variables
    private static int n;
    private static int publicKey;
    private static int privateKey;

    // constructor
    RSA(int p, int q){
        n = p*q;
        publicKey = choosePublicKey(p, q, n);
        privateKey = choosePrivateKey(p, q, publicKey);
    }

    // accessor methods
    public int getN(){
        return n;
    }

    public int getPublicKey(){
        return publicKey;
    }

    public int getPrivateKey(){
        return privateKey;
    }

    // choose integer e relatively prime to (p-1)(q-1)
    public int choosePublicKey(int p, int q, int n){
        int relPrimeProduct = (p-1)*(q-1);
        int e = 2;
        while(e < n){
            if(gcd(e, relPrimeProduct) == 1){
                return e;
            } else {
                e++;
            }
        }
        return e;
    }

    // choose integer d such that ed % (p-1)(q-1) == 1
    public int choosePrivateKey(int p, int q, int e){
        int d = 1;
        int relPrimeProduct = (p-1)*(q-1);
        while(true){
            if(e*d % relPrimeProduct == 1){
                return d;
            } else {
                d++;
            }
        }
    }

    // encryption method
    public int encrypt(int plaintext, int pubKey, int n){
        return modExponent(plaintext, pubKey, n);
    }

    // decryption method
    public int decrypt(int ciphertext, int privKey, int n){
        return modExponent(ciphertext, privKey, n);
    }

    // method for computing large powers with modular exponentiation
    public int modExponent(int base, int power, int modulus){
        ArrayList<Integer> factors = new ArrayList<Integer>();
        while(power > 1) {
            int fac = base * base;
            factors.add(fac % modulus);
            power -= 2;
        }
        if(power == 1){
            factors.add(base % modulus);
        }
        while(factors.size() > 1) {
            ArrayList<Integer> newFactors = new ArrayList<Integer>();
            int i = 0;
            int newFac = 1;
            while(i < factors.size()){
                newFac *= factors.get(i);
                if(newFac < modulus && i+1 < factors.size()) {
                    i++;
                } else {
                    newFactors.add(newFac % modulus);
                    newFac = 1;
                    i++;
                }
            }
            factors = newFactors;
        }
        
        return factors.get(0);
    
    }

    // find gcd with Euclid's algorithm
    public int gcd(int a, int b){
        int t;
        while(b != 0){
            t = b;
            b = a%b;
            a = t;
        }
        return a;
    }

    public static void main(String[] args){

        Scanner s = new Scanner(System.in);
        
        // Enter p,q in one line: e.g. "p q", "p  q", "p   q", etc.
        System.out.print("Enter the prime numbers, p and q: ");
        int p = s.nextInt();
        int q = s.nextInt();

        // Calculate RSA
        System.out.println("\nCalculating RSA values ...\n");
        RSA rsa = new RSA(p,q);
        System.out.printf("Public RSA key is (%d, %d)\n", rsa.getPublicKey(), rsa.getN());
        System.out.printf("Private RSA key is (%d, %d)\n", rsa.getPrivateKey(), rsa.getN());

        System.out.print("\nEnter the plaintext message m (an integer): ");
        int m = s.nextInt();
        System.out.println("\nEncrypting m...");
        int c = rsa.encrypt(m, rsa.getPublicKey(), rsa.getN());
        System.out.printf("The ciphertext c is   %d\n", c);
        System.out.println("\nDecrypting c ...");
        int decM = rsa.decrypt(c, rsa.getPrivateKey(), rsa.getN());
        System.out.printf("The plaintext m is   %d\n", decM);

        s.close();

    }

}