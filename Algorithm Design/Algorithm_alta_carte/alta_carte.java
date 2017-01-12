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
public class alta_carte {
    
    /**
     *
     * @param args
     */
public static void main(String[] args) {
    
long a = 2;//23694237847239462310275753894;
long b = 9;//91047823903431247239482239472394723348;
long total = alta_carte_twoLargeNumber_Multiplication(a,b);
System.out.print(total);

}
static long alta_carte_twoLargeNumber_Multiplication(long x, long y){
    long a =x;
    long b =y;
    long total =0;
    boolean sign_checker =true;
    if (a<0 && b<0){
    a=a*-1;
    b=b*-1;
    }
	else if (a<0){
    a = a * -1;
	sign_checker =false;
    }
    else if (b<0){
    b = b * -1;
	sign_checker =false;
    }

    while (a>=1){
    if (a%2 ==1){
    total = total + b;
    }
    b= b*2;
    a = (long) floor(a/2);
    }
	if (sign_checker == false){
	total = total *-1;}
    return total;

    }
    
}
