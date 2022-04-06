import java.io.*;
import java.util.*;

class PlayfairCipher{

    private static String secretKey;
    private static ArrayList<Character> alpha;
    private static Character[][] matrix;

    /* constructor */
    PlayfairCipher(String key){
        secretKey = key;
        String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        alpha = new ArrayList<Character>();
        for(int i = 0; i < letters.length(); i++){
            alpha.add(letters.charAt(i));
        }
        matrix = generateMatrix(secretKey);
    }

    public static String getKey(){
        return secretKey;
    }

    public static Character[][] getMatrix(){
        return matrix;
    }

    public static Character[][] generateMatrix(String key){
        
        Character[][] returnMatrix = new Character[5][5];
        ArrayList<Character> localAlpha = alpha;
        ArrayList<Character> uniqueChars = new ArrayList<Character>();
        int matrixI = 0, matrixJ = 0;

        for(int charInd = 0; charInd < key.length(); charInd++){

            Character c = key.charAt(charInd);
            if(Character.compare(c, 'J') == 0){
                c = 'I';
            }
            if(!uniqueChars.contains(c)){
                int alphaIndex = localAlpha.indexOf(c);
                uniqueChars.add(localAlpha.remove(alphaIndex));
            }

        }

        for(Character c : uniqueChars){
            returnMatrix[matrixI][matrixJ] = c;
            matrixJ = (matrixJ + 1)%5;
            if(matrixJ == 0){
                matrixI = (matrixI + 1)%5;
            }
        }
        
        // iterate over alphabet, check if it's in the matrix already,
        // and if not it goes into the remaining cells
        for(Character letter : localAlpha){
            // check if array has element
            if(!uniqueChars.contains(letter) && Character.compare(letter, 'J') != 0){
                returnMatrix[matrixI][matrixJ] = letter;
                matrixJ = (matrixJ + 1)%5;
                if(matrixJ == 0){
                    matrixI = (matrixI + 1)%5;
                }  
            }
        }
    
        // how do we handle the extra letter? just create a condition where if it 
        // isn't found just assume it's that letter?
        return returnMatrix;
    
    }

    public static String encrypt(String plaintext, Character[][] matrix){

        // remove whitespace and punctuation from plaintext input
        String processedPlaintext = plaintext.replaceAll(" ", "").replaceAll("\\p{Punct}", "").replaceAll("\n", "");
        
        // check that plaintext all uppercase
        for(int i = 0; i < processedPlaintext.length(); i++){
            Character c = processedPlaintext.charAt(i);
            if(!Character.isUpperCase(c)){
                System.out.println("Error: at least one character lowercase");
            }
        }
        
        // We don't know how many double letters are in the processed plaintext, and we want to wait until after we've
        // accounted for double letters that we tack on an extra "Z" if need be. So in the meantime we change how much 
        // we iterate over the list, since if it's odd we'll just ignore the last letter (b/c it has no pair)
        int extra = 0;
        if(processedPlaintext.length()%2 == 1){
            extra++;
        }
        for(int ind = 0; ind < processedPlaintext.length() - 1 - extra; ind += 2){
            Character c1 = processedPlaintext.charAt(ind);
            Character c2 = processedPlaintext.charAt(ind+1);
            if(Character.compare(c1,c2) == 0){
                processedPlaintext = processedPlaintext.substring(0,ind + 1) + "X" + processedPlaintext.substring(ind + 1);
                ind++;
            }
        }

        // check if padding is necessary
        if(processedPlaintext.length()%2 == 1){
            processedPlaintext += "Z";
        }

        // split processed plaintext into pairs and store
        ArrayList<String> pairs = new ArrayList<String>();
        for(int i = 0; i < processedPlaintext.length(); i += 2){
            String sub = processedPlaintext.substring(i,i+2);
            pairs.add(sub);
        }

        String newCipher = "";

        // iterate over list of pairs
        for(String pair : pairs){
            
            // indices of each char in matrix
            int i1 = 0, j1 = 0, i2 = 0, j2 = 0;

            // both checks if both characters in the pair have been found
            int both = 0;
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(matrix[i][j] == pair.charAt(0)){
                        i1 = i;
                        j1 = j;
                        both++;
                    }
                    if(matrix[i][j] == pair.charAt(1)){
                        i2 = i;
                        j2 = j;
                        both++;
                    }
                    if(both == 2){
                        break;
                    }
                }
            }

            // change indices according to the three rules
            
            int newI1 = i1, newJ1 = j1, newI2 = i2, newJ2 = j2;
            
            if(j1 == j2){
                newI1 = (i1 + 1) % 5;
                newI2 = (i2 + 1) % 5;
            } else if(i1 == i2){
                newJ1 = (j1 + 1) % 5;
                newJ2 = (j2 + 1) % 5;
            } else {
                newJ1 = j2;
                newJ2 = j1;
            }

            // assign new values and add to decoded string
            pair = Character.toString(matrix[newI1][newJ1]) + Character.toString(matrix[newI2][newJ2]);
            newCipher += pair;

        }

        return newCipher;

    }

    public static String decrypt(String ciphertext, Character[][] matrix){

        // remove whitespace and punctuation from plaintext input
        String processedCiphertext = ciphertext.replaceAll(" ", "").replaceAll("\\p{Punct}", "").replaceAll("\n", "");
        
        // check if ciphertext is of even length
        if(processedCiphertext.length()%2 == 1){
            processedCiphertext += "Z";
            System.out.println("Error: Ciphertext must be of even length");
        }
        
        // check that plaintext all uppercase
        for(int i = 0; i < processedCiphertext.length(); i++){
            Character c = processedCiphertext.charAt(i);
            if(!Character.isUpperCase(c)){
                System.out.println("Error: at least one character lowercase");
            }
        }

        // split processed plaintext into pairs and store
        ArrayList<String> pairs = new ArrayList<String>();
        for(int i = 0; i < processedCiphertext.length(); i += 2){
            String sub = processedCiphertext.substring(i,i+2);
            pairs.add(sub);
        }

        String newPlain = "";

        // iterate over pairs
        for(String pair : pairs){
            
            // indices of each char in matrix
            Character c1 = pair.charAt(0);
            Character c2 = pair.charAt(1);
            int i1 = 0, j1 = 0, i2 = 0, j2 = 0;

            // both checks if both characters in the pair have been found
            int both = 0;
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(matrix[i][j] == c1){
                        i1 = i;
                        j1 = j;
                        both++;
                    }
                    if(matrix[i][j] == c2){
                        i2 = i;
                        j2 = j;
                        both++;
                    }
                    if(both == 2){
                        break;
                    }
                }
            }

            // change indices according to the three rules
            int newI1 = i1, newJ1 = j1, newI2 = i2, newJ2 = j2;
            if(j1 == j2){
                newI1 = (i1 - 1) % 5;
                if(newI1 < 0){
                    newI1 = 4;
                }
                newI2 = (i2 - 1) % 5;
                if(newI2 < 0){
                    newI2 = 4;
                }
            } else if(i1 == i2){
                newJ1 = (j1 - 1) % 5;
                if(newJ1 < 0){
                    newJ1 = 4;
                }
                newJ2 = (j2 - 1) % 5;
                if(newJ2 < 0){
                    newJ2 = 4;
                }
            } else {
                newJ1 = j2;
                newJ2 = j1;
            }

            // assign new values and add to decoded string
            pair = Character.toString(matrix[newI1][newJ1]) + Character.toString(matrix[newI2][newJ2]);

            newPlain += pair;

        }

        return newPlain;
    
    }

    public static void main(String[] args){

        String inputKey = "RAYQUAZA";
        String inputPlain = "POKEMON TOWER DEFENSE YOUR MISSION IN THIS FUN STRATEGY TOWER DEFENSE GAME IS TO HELP PROFESSOR OAK TO STOP ATTACKS OF WILD RATTATA. SET OUT ON YOUR OWN POKEMON JOURNEY, TO CATCH AND TRAIN ALL POKEMON AND TRY TO SOLVE THE MYSTERY BEHIND THESE ATTACKS. YOU MUST PLACE POKEMON CHARACTERS STRATEGICALLY ON THE BATTLEFIELD SO THAT THEY STOP ALL WAVES OF ENEMY ATTACKER DURING THE BATTLE YOU WILL LEVEL UP AND EVOLVE YOUR POKEMON. YOU CAN ALSO CAPTURE OTHER POKEMON DURING THE BATTLE AND ADD THEM TO YOUR TEAM. USE YOUR MOUSE TO PLAY THE GAME. GOOD LUCK";

        PlayfairCipher pfc = new PlayfairCipher(inputKey);
        Character[][] matrix = pfc.getMatrix();

        System.out.println("\nKey matrix:");
        for(int i=0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                System.out.print(Character.toString(matrix[i][j]) + " ");
            }
            System.out.println();
        }

        System.out.println("\nOriginal plaintext: \n" + inputPlain + "\n");
        
        String outputCipher = pfc.encrypt(inputPlain, matrix);
        System.out.println("Output cipher: \n" + outputCipher + "\n");

        String outputPlain = pfc.decrypt(outputCipher, matrix);
        System.out.println("Output plaintext: \n" + outputPlain + "\n");

    }

}