/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rectangle_multiplication;

import static java.lang.Math.floor;

/**
 *
 * @author FRISCA
 */
public class Rectangle_Multi {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        int []arrayx = new int[3];
        arrayx[0] = 9;
        arrayx[1] = 8;
        arrayx[2] = 1;
        
        
        int []array = new int[3];
        array[0] = 0;
//        array[1] = 2;
//        array[2] = 3;
//        array[3] = 4;
        
        int  total ;
        total = rectangular(arrayx,array);
//        for( int k =1; k<total.length; k++){
//        System.out.print(total[k]);}
System.out.print(total);
        System.out.println();

    }    
    static int rectangular(int x[], int y[]){
     
        int [] arrayx = x;
        int [] array = y;
        int value;
        int b, firstDigit, secondDigit, f;
        int [][] arrayxy = new int [array.length][arrayx.length*2];
        for (int i =0; i < array.length; i++){
	b=0;
	for (int j =0; j < arrayx.length; j++){
	value = arrayx[j] * array[i];
	firstDigit = (int) floor(value/10); 
        secondDigit = value % 10;
        f=0;
        while (f <1){
        arrayxy[i][b]= firstDigit;
        b++;
        arrayxy[i][b]=secondDigit;
        b++;
        f++;
        }}}
        int final_array_size = (array.length + arrayx.length)+1;
        int [] total = new int[final_array_size];
        total[final_array_size-1] = arrayxy[array.length-1][(arrayx.length*2)-1];
        final_array_size = (final_array_size-1) -1;
        int sum =0;
        int carryout =0;
        int row, column;
        boolean checker;
        for (int I = array.length -2; I >= 0;I --){
        row =I;
        column = arrayx.length * 2 -1;
        checker = false;
        while (!checker){
        sum = sum + arrayxy[row][column];
        if (column < (arrayx.length*2)-1  && column!= 0){
        column --;
        sum = sum + arrayxy[row][column];}
        row ++;
        column --;
        if (row>array.length-1  || column < 0){
        checker=!false; // =true
        if(sum >=10){
        total[final_array_size] = sum % 10;
        carryout = (int) floor(sum /10);
        sum=carryout;
        final_array_size --;
        }else{
            total[final_array_size] = sum % 10;
            carryout = (int) floor(sum /10);
            sum=carryout;
            final_array_size --;
        }}}}  
        for(int j = (arrayx.length*2)-2 ; j>=0; j-=2){
        row = 0;
        column = j;
        checker = false;
        while(!checker){
        sum = sum + arrayxy[row][column];
        if (column!= 0){
        column --;
        sum = sum + arrayxy[row][column];
        }
        row ++;
        column --;
        if ( column < 0){
        checker=!false; // =true
        if(sum >=10){
        total[final_array_size] = sum % 10;
        carryout = (int) floor(sum /10);
        sum=carryout;
        final_array_size --;
        }else{
            total[final_array_size] = sum % 10;
            carryout = (int) floor(sum /10);
            sum=carryout;
            final_array_size --;
        }}}}
//        int [] arrray;
//        arrray= new int [6];

String result="";
        for(int de =0; de< total.length;de++)
            result = result + Integer.toString(total[de]);
        
        int product_result = Integer.valueOf(result);
        
        return product_result;
    }
    
}
   

       
    
