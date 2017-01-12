/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Algorithm_alta_carte_multiplication;

import static java.lang.Math.floor;

/**
 *
 * @author FOA5
 */
public class alta_carte_v2 {
 
public static void main(String[] args) {
    
String a = "23694237847239462310275753894";
String b = "-91047823903431247239482239472394723348";
String output = alta_carte_twoLargeNumber_Multiplication(a,b);
System.out.println(output);
}

static String alta_carte_twoLargeNumber_Multiplication (String firstNumbers, String secondNumbers){
    String a = firstNumbers; // assigning the first number 
    String b = secondNumbers; // assigning the second number
    String oddNumbers=""; // to store the odd number from the first number
    int counter =0; // used to control when to store the second number in the base
    String base=""; // to store the first value of the second number
    boolean sign_checker =true;  // to check the numbers signs
    if ("-".equals(Character.toString(a.charAt(0))) && "-".equals(Character.toString(b.charAt(0)))){ // checking sign process
    a=a.substring(1);// in case a has a negative sign, remove it
    b=b.substring(1);// in case b has a negative sign, remove it
    }
    else if ("-".equals(Character.toString(a.charAt(0)))){ // checking sign for a only
            a=a.substring(1);
            sign_checker =false; // put the flag false
    }
    else if ("-".equals(Character.toString(b.charAt(0)))){ // checking sign for b only
            b=b.substring(1);
            sign_checker =false;
    }
    
    boolean loopStop= false;
    if(a!= "0"){// in case the first number 0
    while(!loopStop){  // to perform multiplication and division  concurrently
    int checker = Integer.parseInt(Character.toString(a.charAt(a.length()-1))) %2; // to determine whether the number odd or even
    
        if( checker == 1 && counter ==0 ){ // to store the first number of b in the base when the first number,a, is odd
            oddNumbers=a;
            System.out.print(oddNumbers); // output
            System.out.print("----");  // output
            base = b;  // storing the second number in the base
            System.out.println(b);
            counter ++;
        }
        else if (checker == 1 && counter == 1){  // perform the storing process to the subsequent secondnumbers into the base
            oddNumbers=a;
            System.out.print(oddNumbers);
            System.out.print("----");
            base = addition(base, b);// send the two parameters to be added and saved into the base
            System.out.println(b);
            
        }

    String division_result = "";
    int divided_value = Integer.parseInt(Character.toString(a.charAt(0))); // getting the first value
    int location;
    for(location = 0; location < a.length(); location++)// division process
    {
        division_result = division_result + (divided_value / 2);// to divided the number by 2

        if(location < a.length() - 1)
           divided_value = Integer.parseInt(String.valueOf(divided_value % 2) + Integer.parseInt(Character.toString(a.charAt(location+1))));
    }

        b= multiplication_by_two(b);// send the second number to get multiplied by two

        int Zero_check =0;
        while(Zero_check< division_result.length()){
            if (Character.getNumericValue(division_result.charAt(Zero_check))>0 ){ // to eliminate the left 0s
                break;
            }
            else division_result = division_result.substring(1);// eliminate left 0s
            
            }

        a = division_result;// store the division result as the firstNumber

        if (1 == Integer.parseInt(Character.toString(a.charAt(0))) && a.length() == 1){
                   loopStop = true;
                   if (counter == 0){
                    base =  b;   
                   }
                   else 
                       base = addition(base, b);// send two numbers to be added
                   oddNumbers=a;
                   System.out.print(oddNumbers);
                   System.out.print("----");
                   System.out.println(b);
        }
    }
    }
    else 
        base = "0";// if the final value is zero, store it as zero
        if(sign_checker == false)
            if (Integer.parseInt(Character.toString(base.charAt(0)))!= 0)
                base = "-" + base;// add the sign if applicable
    return base;// return the product result
}

static String multiplication_by_two (String secondNumbers){// multiplication function
    String b = secondNumbers;
    String total="";
    int save=0,carryout,multiplication;
        for(int j=b.length()-1; j>=0; j--){
            multiplication = (Integer.parseInt(String.valueOf(b.charAt(j)))*2)+save;// to multiply each digit by 2
            total= Integer.toString(multiplication%10)+total;   // to save the right digit into the total
            carryout = (int) floor(multiplication /10);    // to get the leftover and add it to the next mutiplication
            if(carryout > 0)  // to evaluate the leftover
                save = carryout;
            else
                save = 0;
            if (j == 0 && save != 0 ){
                total = save + total;
            }
        }
        return total;        // return the result of the multiplication
}

static String addition(String x, String y){   //addition function
    int carryout =0;
    int save=0;
    String sum="";
    String base = x;
    String secondNumber = y;
        if(secondNumber.length() != base.length()){
            for(int k = 0; k<=secondNumber.length()- base.length(); k++){  // adding 0s process in case the 1st number has less digits
                    base = "0" + base;    // adding 0s to the left to make both lengths equal
                  
            }
        }
        for(int j =secondNumber.length()-1; j>=0; j--){   // addition process
                save = Integer.parseInt(Character.toString(secondNumber.charAt(j))) + 
                       Integer.parseInt(Character.toString(base.charAt(j))) + carryout; // adding two corresponding digits and leftover if applicable
                carryout = (int) floor(save/10);  // getting the leftover to be added next
            if(j == 0){   // evaluating whether the addition process at the last two digits or not
                if (save>=10){
                    sum = Integer.toString(save) + sum;
                }
                else 
                    sum = Integer.toString(save%10) + sum;
            }
            else
                sum = Integer.toString(save % 10) + sum;
        }
        base=sum;  // assign the addition result to be the base
    return base;  // return the addition result
}
}
