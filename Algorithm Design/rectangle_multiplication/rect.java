/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rectangle_multiplication;

import static java.lang.Math.floor;

/**
 *
 * @author FOA5
 */
public class rect {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
String x = "23694237847239462310275753894";
String y = "-91047823903431247239482239472394723348";
String result = rectangle (x,y);
System.out.println(result);
    }    
static String rectangle(String firstNumber , String secondNumber){
    String x = firstNumber;     //assigning the first number as x
    String y = secondNumber;    //assigning the second number as y
    boolean sign_checker =true; //used as a flag to determine the final result sign 
    if ("-".equals(Character.toString(x.charAt(0))) && "-".equals(Character.toString(y.charAt(0)))){ // checking sign process
        x = x.substring(1); // in case x has a negative sign, remove it
        y = y.substring(1); // in case y has a negative sign, remove it
    }
    else if ("-".equals(Character.toString(x.charAt(0)))){ // checking sign for x only
            x = x.substring(1);  
            sign_checker =false; // put the flag false
    }
    else if ("-".equals(Character.toString(y.charAt(0)))){ // checking sign for y only
            y = y.substring(1);
            sign_checker =false;
    }
    int []arrayx= new int [x.length()]; //create array for x
    for (int counter =0; counter<x.length(); counter++){ //loop for assignment process
        arrayx[counter]= Integer.parseInt(Character.toString(x.charAt(counter))); //assigning x values into the array
    }
    int []array= new int [y.length()]; //create array for y
    for (int counter =0; counter<y.length(); counter++){
        array[counter]= Integer.parseInt(Character.toString(y.charAt(counter)));
    }
    int value; // to store the multiplication value when column * row
    int locator, firstDigit, secondDigit, controller;
    int [][] arrayxy = new int [array.length][arrayx.length*2]; // creating 2D array
    for (int i =0; i < array.length; i++){ // the second number values
        locator=0; // used to identifiy the row
        for (int j =0; j < arrayx.length; j++){ // the first number values
            value = arrayx[j] * array[i]; // multiplication process
            firstDigit = (int) floor(value/10); // eleminating the second digit
            secondDigit = value % 10;           // eleminating the first digit
            controller=0; // to control the while loop function
            while (controller <1){ // assigning each digit into the 2D array process
                arrayxy[i][locator]= firstDigit;
                locator++;
                arrayxy[i][locator]=secondDigit;
                locator++;
                controller++;
            }
        }
    }
        
    int final_array_size = (array.length + arrayx.length)+1; // create the final result array size
    int [] total = new int[final_array_size]; // create the final result array
    total[final_array_size-1] = arrayxy[array.length-1][(arrayx.length*2)-1]; // assigning the right and bottom most digit
    final_array_size = (final_array_size-1) -1; // reduce the available field in the array
    int sum =0;
    int carryout =0;
    int row, column;
    boolean checker;
    if(array.length!=1){ // to ensure that the array has mutiple rows otherwise go tp the second process
        for (int i = array.length -2; i >= 0;i --){ // loop to move vertically
            row =i;
            column = arrayx.length * 2 -1; // number of columens
            checker = false;
            while (!checker){
                sum = sum + arrayxy[row][column]; // addition process
                if (column < (arrayx.length*2)-1  && column!= 0){ // to move diagonally
                    column --;
                    sum = sum + arrayxy[row][column];
                }
                row ++;    
                column --;
                if (row>array.length-1  || column < 0){ // to ensure no exceeding the last column and row
                    checker = !false; // stop the loop
                    if(sum >=10){ // to determine if there is leftover or not
                        total[final_array_size] = sum % 10;
                        carryout = (int) floor(sum /10); // store the leftover for the next addition process
                        sum=carryout;
                        final_array_size --;
                    }
                    else{ // in case there is no leftover
                        total[final_array_size] = sum % 10;
                        carryout = (int) floor(sum /10);
                        sum=carryout;
                        final_array_size --;
                    }
                }
            }
        }
    }
    for(int j = (arrayx.length*2)-2 ; j>=0; j-=2){ // loop to move horizontally 
        int counter = 0; //used in case we have one row only 
        row = 0;
        column = j;
        checker = false;
        while(!checker){
            if(array.length==1){ //to ensure that in case we have one row, the addition process keeps adding the values
                row =0;
                counter++;
            }
            sum = sum + arrayxy[row][column]; //addition process
            if (column!= 0){
                column --;
                sum = sum + arrayxy[row][column];
            }
            row ++; // to move diagonally 
            column --;
            if ( column < 0|| counter == 1){
                checker=!false; // stop the while loop
                if(sum >=10){ //to determine if there is leftover or not
                    total[final_array_size] = sum % 10;
                    carryout = (int) floor(sum /10);// store the leftover for the next addition process
                    sum=carryout;
                    final_array_size --;
                }else{  // in case there is no leftover
                    total[final_array_size] = sum % 10;
                    carryout = (int) floor(sum /10);
                    sum=carryout;
                    final_array_size --;
                }
            }
        }
    }
    String result=""; // to store the final result into String form
    for(int de =0; de< total.length;de++) // combining the digits saved into the array as one number
        result = result + Integer.toString(total[de]);    
    int Zero_check =0;
    while(Zero_check< result.length()){ // to elimenate the zeros in the lefthand
        if (Character.getNumericValue(result.charAt(Zero_check))>0 || result.length()==1){ // in case we have one zero, keep it
            break;
        }
        else result = result.substring(1); // removing the unnecessary zeros
    }
    if(sign_checker == false) // check the number sign
        if (Integer.parseInt(Character.toString(result.charAt(0)))!= 0) // ensure it is not zero
            result="-"+result; // assigning negatives if necessary
    return result; //returning the product value
}
    
}
   

       
    
