/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package determiningFloatNumber;
// import java.io.BufferedReader;
// import java.io.FileReader;
import static java.lang.Math.pow;

/**
 *
 * @author FRISCA
 */
public class determiningFloatNumber {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
//        String text = "2.0";
//        String text = "+2.0";
//        String text = "-2.0";
//        String text = "2a.0";
//        String text = "2";
//        String text = "a2";
//        String text = "-3";
        String text = "333+33.";
//        String text =".3";
//        String text = "4.2.1";
//        String text = "0.0";
//        String text = "000.0000";
//        String text = "0";
//          String text = "null";
        Float result = determiningFloatNumbers(text);
       System.out.print("The float result is: ");
       System.out.println(result);
    }
    
    static Float determiningFloatNumbers (String stringValue){
        String text = stringValue;
        String left ="";
        String right = "";
        boolean zero = true;
        int digitCountBefore = 0, digitCountAfter =0;
        boolean neg = false, dec = false, num = false;
        int counter =0;
        int location = 0;
        float numberAsFloat =0;
        for(int i =0; i< text.length(); i++){
            if(String.valueOf(text.charAt(i)).equals(String.valueOf("."))){
                dec = true;
                
                counter ++;
                location = i;
            }
            else if(String.valueOf(text.charAt(i)).equals(String.valueOf("-")))
                 neg = true;
            else if(String.valueOf(text.charAt(i)).equals(String.valueOf("+")))
                 neg = false;
            else if(Character.getNumericValue(text.charAt(i)) >=0 && Character.getNumericValue(text.charAt(i)) <= 9){
                if(Character.getNumericValue(text.charAt(i))!=0){
                    zero = false;
                }
                num = true;
            }
            else {
                num = false;
                break;
            }
        }
        if ( dec == true && counter == 1){
            for( int j = 0; j < text.length(); j++){
                if(String.valueOf(text.charAt(j)).equals(String.valueOf("-")) || String.valueOf(text.charAt(j)).equals(String.valueOf("+"))){
                 // skip this iteration   
                }
                else if ( j < location){
                    left = left + text.charAt(j);
                    digitCountBefore++;
                }
                else if ( j > location){
                    right = right + text.charAt(j);
                    digitCountAfter++;
                }
            }
        }
        if ( neg == true && dec == true && num == true && counter ==1 && zero == false){
            System.out.print("Negative decimal number: ");
            System.out.println(text);
            System.out.print(digitCountBefore);
            System.out.print(" digits before decimal:");
            for (int k =0; k<left.length(); k++){
                System.out.print(left.charAt(k));
                System.out.print(",");
            }
            System.out.println();
            System.out.print(digitCountAfter);
            System.out.print(" digits after decimal:");
            for (int k =0; k<right.length(); k++){
                System.out.print(right.charAt(k));
                System.out.print(",");
            }
            System.out.println();
        }
        else if (neg == false && dec == true && num == true && counter ==1 && zero == false){
            System.out.print("Positive decimal number: ");
            System.out.println(text);
            System.out.print(digitCountBefore);
            System.out.print(" digits before decimal:");
            for (int k =0; k<left.length(); k++){
                System.out.print(left.charAt(k));
                System.out.print(",");
            }
            System.out.println();
            System.out.print(digitCountAfter);
            System.out.print(" digits after decimal:");
            for (int k =0; k<right.length(); k++){
                System.out.print(right.charAt(k));
                System.out.print(",");
            }
            System.out.println();
        }
        else if ( neg == true && dec == false && num == true && zero == false){
            System.out.print("Not a decimal number: ");
            System.out.println(text);
        }
        else if ( neg == false && dec == false && num == true && zero == false ){
            System.out.print("Not a decimal number: ");
            System.out.println(text);
        }
        else if (num == false || counter > 1){
            System.out.print("Not a decimal number: ");
            System.out.println(text);
        }
        else if (zero == true && num == true){
            System.out.print("Zero number: ");
            System.out.println(text);
        }
        

        if ( dec == true && num == true && counter == 1){
            
            for(int i = 0;i < left.length(); i++)
                
                numberAsFloat += (left.charAt(i) -'0') * pow(10, left.length() - i -1);
            
            for(int i = right.length()-1; i >= 0; i--)
                
                numberAsFloat += (right.charAt(i)-'0') * pow (0.1, i+1);
            
            if(neg == true)
                
                numberAsFloat =numberAsFloat*-1;
            
            return numberAsFloat;
        }
        else 
            
            return null;
        
    }
}
