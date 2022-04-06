import java.io.*;
import java.util.*;

class MatrixTranspositionCipher{

    public static String encrypt(String plaintext, Integer[] array){
        
        /* construct the matrix, dimensions being a function of the 
            input plaintext size. */
        int ptSize = plaintext.length();
        int N = array.length;
        int M = (ptSize + (N - ptSize%N)%N)/N;

        Character[][] matrix = new Character[M][N];

        /* puts the plaintext into the matrix */
        int matrixI = 0, matrixJ = 0;
        for(int charInd = 0; charInd < ptSize; charInd++){

            Character c = plaintext.charAt(charInd);
            matrix[matrixI][matrixJ] = c;
            matrixJ = (matrixJ + 1)%N;
            if(matrixJ == 0){
                matrixI = (matrixI + 1)%M;
            }

        }

        /* fills any remaining cells with '%' */
        while(!(matrixI == 0 && matrixJ == 0)){

            matrix[matrixI][matrixJ] = '%';
            matrixJ = (matrixJ + 1) % N;
            if(matrixJ == 0){
                matrixI = (matrixI + 1)%M;
            }

        }

        /* prints matrix to console */
        for(int i=0; i < M; i++){
            for(int j = 0; j < N; j++){
                System.out.print(Character.toString(matrix[i][j]) + " ");
            }
            System.out.println();
        }

        /* constructs ciphertext according to the input array */
        String ciphertext = "";
        for(int j: array){
            for(int i = 0; i < M; i++){
                ciphertext += Character.toString(matrix[i][j-1]);
            }
        }

        return ciphertext;

    }

    public static String decrypt(String ciphertext, Integer[] array){

        int ctSize = ciphertext.length();
        int M = array.length;
        int N = (ctSize + (M - ctSize%M)%M)/M;

        Character[][] matrix = new Character[M][N];

        /* puts the ciphertext into the matrix */
        int matrixI = 0, matrixJ = 0;
        for(int charInd = 0; charInd < ctSize; charInd++){

            Character c = ciphertext.charAt(charInd);
            matrix[matrixI][matrixJ] = c;
            matrixJ = (matrixJ + 1)%N;
            if(matrixJ == 0){
                matrixI = (matrixI + 1)%M;
            }

        }

        /* fills any remaining cells with '%' */
        while(!(matrixI == 0 && matrixJ == 0)){

            matrix[matrixI][matrixJ] = '%';
            matrixJ = (matrixJ + 1) % N;
            if(matrixJ == 0){
                matrixI = (matrixI + 1)%M;
            }

        }

        /* having set up the matrix as in the encryption method,
            we now create a second matrix for decryption:
            we iterate twice over the array and stop when
            the current entry matches the position of the
            number in the array, and shift the rows accordingly
        */
        Character[][] newMatrix = new Character[N][M];
        for(int i = 1; i < array.length + 1; i++){
            for(Integer num : array){
                if(num == i){
                    int ind = Arrays.asList(array).indexOf(num);
                    newMatrix[i-1] = matrix[ind];
                    break;
                }
            }
        }

        /* print the resulting matrix to the console, which will have
            the plaintext entered row-wise */
        for(int i=0; i < M; i++){
            for(int j = 0; j < N; j++){
                System.out.print(Character.toString(newMatrix[i][j]) + " ");
            }
            System.out.println();
        }

        /* reconstructs plaintext according to the new matrix */
        String plaintext = "";
        for(int j = 0; j < N; j++){
            for(int i = 0; i < M; i++){
                plaintext += Character.toString(newMatrix[i][j]);
            }
        }

        return plaintext;

    }

    public static void main(String[] args){

        Integer[] keyArray = {2, 3, 1, 4};
        String plaintext = "dont%hit%the%red%button%yet";

        System.out.println("\nEncryption:");
        String outputCipher = encrypt(plaintext, keyArray);
        System.out.println(outputCipher);

        System.out.println("\nDecryption:");
        String outputPlain = decrypt(outputCipher, keyArray);
        System.out.println(outputPlain);

    }

}