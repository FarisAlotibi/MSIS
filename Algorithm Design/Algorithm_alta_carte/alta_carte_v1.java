/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Algorithm_alta_carte_multiplication;

import static java.lang.Math.floor;

/**
 *
 * @author FRISCA
 */
public class alta_carte_v1 {
 
public static void main(String[] args) {
    
String a = "2369423784723946231";
String b = "91047823903431247239482239472394723348";
//String total = alta_carte_twoLargeNumber_Multiplication(a,b);
//System.out.print(total);
//multiplication_by_two(b);
division_by_two(a,b);

}
//static String alta_carte_twoLargeNumber_Multiplication(String x, String y){
//    String a =x;
//    String b =y;
//    long total =0;
//    String secondNumbers [] = multiplication_by_two(b);
//    boolean sign_checker =true;
//    if (a<0 && b<0){
//    a=a*-1;
//    b=b*-1;
//    }
//	else if (a<0){
//    a = a * -1;
//	sign_checker =false;
//    }
//    else if (b<0){
//    b = b * -1;
//	sign_checker =false;
//    }
//
//    while (a>=1){
//    if (a%2 ==1){
//    total = total + b;
//    }
//    b= b*2;
//    a = (long) floor(a/2);
//    }
//	if (sign_checker == false){
//	total = total *-1;}
//    return total;
//
//    }
static String multiplication_by_two (String secondNumbers){
    String b = secondNumbers;
    String total="";
//    String []arrayOfSecondNumbers= new String[10];
    int save=0,carryout,multiplication;
//    for(int i = 0; i<10; i ++ ){
        for(int j=b.length()-1; j>=0; j--){
            multiplication = (Integer.parseInt(String.valueOf(b.charAt(j)))*2)+save;
            total= Integer.toString(multiplication%10)+total;
            carryout = (int) floor(multiplication /10);
            if(carryout > 0)
                save = carryout;
            else
                save = 0;
            
            if (j == 0 && save != 0 ){
                total = save + total;
            }
            
        }
return total;        
//System.out.println(total);
//    }
}
static void division_by_two (String firstNumbers, String secondNumbers){
    String a = firstNumbers;
    String b = secondNumbers;
    String result = "";
    String increase ="";
    String [] oddNumbers = new String [25];
    String [] correspondingNumbers = new String [25];
    int carryout = -1;
    int division;
    int counter =0;
    
    boolean loopStop= false;
    while(!loopStop){
    int checker = Integer.parseInt(Character.toString(a.charAt(a.length()-1))) %2;
    
        if( checker == 1 ){
            oddNumbers[counter]= a;
            correspondingNumbers[counter] = b;
            counter ++;
        }
        

        
        result = "";
        increase ="";
        carryout = -1;
        for (int i = 0; i < a.length();){

            if ( carryout > 0){
                division = Integer.parseInt(Integer.toString(carryout)+Character.toString(a.charAt(i)));
            }
            else
                division = Integer.parseInt(Character.toString(a.charAt(i)));
            
            if (division == 0){
                result =result + Integer.toString((int) floor(division / 2));
                //System.out.print(result);
                carryout = Integer.parseInt(result) % 2;
                i++;
            }
            else if(division < 2 && i !=a.length()-1){
                increase = Integer.toString(division) + Character.toString(a.charAt(i+1));
                result =result + Integer.toString((int) floor(Integer.parseInt(increase) / 2));
                carryout = Integer.parseInt(increase) % 2;
                i+=2;
            }
            else if (division < 2 && i == a.length()){
                increase = Integer.toString(division) + Integer.toString(0);
                result =result + Integer.toString((int) floor(Integer.parseInt(increase) / 2));
                i++;
            }
            else if ( division > 2){
                result =result + Integer.toString((int) floor(division / 2));
                carryout = division % 2;
                i++;
            }
            else if (division == 2){
                result =result + Integer.toString((int) floor(division / 2));
                carryout = division % 2;
                i++;
            }
        
        }
        //System.out.println(result);
        b= multiplication_by_two(b);
        //System.out.println(result);
        a = result;
       // System.out.print(a.charAt(0));
        if (1 == Integer.parseInt(Character.toString(a.charAt(0))) && a.length() == 1){
                   loopStop = true;
                   oddNumbers[counter]= a;
                   correspondingNumbers[counter] = b;
        }
    }   
        for(int j=0; j<oddNumbers.length;j++){
           // if(oddNumbers[j]!= null){
        System.out.print(oddNumbers[j]);
        System.out.print(" ----- ");
        System.out.println(correspondingNumbers[j]);
        //}
        }
        String sum = addition(correspondingNumbers);
        System.out.println(sum);
        
        
    }
static String addition(String a[]){
    String []reciev_array = a;
    int carryout =0;
    int save=0;
    String sum="";
    String base = reciev_array[0];
    for(int i=1; i<reciev_array.length; i++){
        if(reciev_array[i].length() != base.length()){
            for(int k = 0; k<reciev_array[i].length()- base.length(); k++){
                    base = "0" + base;
            }
        }
        for(int j =reciev_array[i].length()-1; j>=0; j--){
            save = Integer.parseInt(Character.toString(reciev_array[i].charAt(j))) + 
                   Integer.parseInt(Character.toString(base.charAt(j))) + carryout;
            carryout = (int) floor(save/10);
            if(j == 0){
                sum = Integer.toString(save) + sum;
            }
            else
                sum = Integer.toString(save % 10) + sum;
        }
        base=sum;
        sum ="";
        carryout =0;
        save=0;
    }
    
    return base;
}
}
