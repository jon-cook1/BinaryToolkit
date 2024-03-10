/*****
 * Project 01: Binary toolkit
 * COSC 208, Introduction to Computer Systems, Fall 2023
 *****/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // for atoi from ChatGPT
#define MAX_BINARY_LEN 32

/*Prints the 2^n steps for converting a binary number to an integer. Is roughly coded and 
could be more efficient, but still runs in n time*/

void printSteps(char binNum[], char sign, int lastOne){
    //printf("Last: %d\n",lastOne);

    int len = strlen(binNum);
    if (sign == 'u'){
        for (int i = 2; i < len; i++){
            if (binNum[i] == '1'){
                printf("2^%u",len-i-1);
            if (i-1 != lastOne)
                    printf(" + ");
                else
                    printf("\n");
            }
        }
        for (int i = 2; i < len; i++){
            if (binNum[i] == '1'){
                printf("%u",(1 << (len-i-1)));
                if (i-1 != lastOne)
                    printf(" + ");
                else
                    printf("\n");
            }
        }
    }
    else{
        int condition = 1;
        for (int i = 2; i < len; i++){
            if (binNum[i] == '1'){
                if (condition){
                    printf("-");
                    condition = 0;
                }
                printf("2^%d",len-i-1);
                if (i-1 != lastOne)
                    printf(" + ");
                else
                    printf("\n");
            }
        }
        condition = 1;
        for (int i = 2; i < len; i++){
            if (binNum[i] == '1'){
                if (condition){
                    printf("-");
                    condition = 0;
                }
                printf("%d",(1 << (len-i-1)));
                if (i-1 != lastOne)
                    printf(" + ");
                else
                    printf("\n");
            }
        }
    }
}
/*Converts a binary number to its decimal equivalent*/

int binToDec(char binNum[],char sign, int print){
    unsigned int total = 0;
    int lastOne = 0;
    int len = strlen(binNum);
    for (int i = 2; i < len; i++){
        if (binNum[i] == '1'){
            lastOne = i-1;
            unsigned int currentVal = 1 << (len-1-i);
            if (i == 2 && sign == 's')
                currentVal *= -1;
            total += currentVal;
        }
    }
    if (print){
        printSteps(binNum, sign, lastOne);
        if (sign == 'u')
            printf("%u\n",total);
        else
            printf("%d\n",total);
    }
    return total;
}

/*Converts a decimal number to its binary equivalent*/
void decToBin(int decVal, int bits){
    int pos = 1;
    if (decVal < 0)
        pos = 0;

    if (pos && (1<<(bits-2)<decVal)){
        printf("overflow\n");
        return;
    }
    else if (!pos && (1<<(bits-1))*-1>decVal){
        printf("underflow\n");
        return; 
    }
    char bin[bits];
    int total = 0;
    //0 is neg 1 is pos 
    int inde = 0;
    if (pos){
        printf("-2^%d does not fit\n",(bits-1));
        bin[inde] = '0';
    }
    else{
        total = (1 << (bits - 1))*-1;
        printf("0 + -2^%d = %d\n",(bits-1),total);
        bin[inde] = '1';
    }
    for (int i = bits-2; i >= 0; i--){
        inde++;
        int current = 1 << i;
        
        if (current+total > decVal){
            printf("2^%d does not fit\n",(i));
            bin[inde] = '0';
        }
        else{
            printf("%d + 2^%d = %d\n", total,i,total+current);
            total += current;
            bin[inde] = '1';
        }
    }
    printf("0b");
    for (int i = 0; i < strlen(bin); i++){
        if (bin[i] == '1' || bin[i] == '0')
            printf("%c", bin[i]);
    }
    printf("\n");
    }

/*
Poorly named function that flips the sign of a binary number.

flips the bits then adds one.
*/
void flipBits(char num[]){
    for (int i=2; i<strlen(num); i++){
        if (num[i] == '0')
            num[i] = '1';
        else 
            num[i] = '0';
    }
    /*for (int i = 0; i < strlen(num); i++){
        printf("%c", num[i]);
    }
    printf("\n");*/
    int inc = 1;
    char bit = num[strlen(num)-inc]; 
    //add one
    while (bit == '1'){
        num[strlen(num)-inc] = '0';
        inc ++;
        bit = num[strlen(num)-inc];
    }
    num[strlen(num)-inc] = '1';
    //for (int i = 0; i < strlen(num); i++)
        //printf("%c", num[i]);
    //printf("\n");
}

/*Helper function to print the results of adding two binary numbers*/
void printaddBin(char first[], char second[], char carryBits[], char sum[]){
    printf("  ");
    for (int i = 0; i < strlen(first); i++){
        if (carryBits[i] != '1')
            printf(" ");
        else
            printf("%c", carryBits[i]);
    }
    printf("\n  ");
    for (int i = 0; i < strlen(first); i++)
        printf("%c", first[i]);
    printf("\n+ ");
    for (int i = 0; i < strlen(first); i++)
        printf("%c", second[i]);
    printf("\n");
    for (int i = 0; i < strlen(first) + 2; i++)
        printf("-");
    printf("\n  ");
    for (int i = 0; i < strlen(first) + 2; i++)
        printf("%c",sum[i]);
    printf("\n");

    char firstSign = 'u';
    char secondSign = 'u';
    char sumSign = 'u';

    if (first[2] == '1')
        firstSign = 's';
    if (second[2] == '1')
        secondSign = 's';
    if (sum[2] == '1')
        sumSign = 's';

    int firstDec = binToDec(first,firstSign,0);
    int secondDec = binToDec(second,secondSign,0);
    int sumDec = binToDec(sum,sumSign,0);
    
    //need to figure out over and underflow here. How to distinguish between the two
    //done- i think so?
    if (carryBits[1] == '1'){
        if (firstDec > 0 && secondDec > 0)
            printf("overflow\n");
        else   
            printf("underflow\n");  
    }
    printf("%d + %d = %d\n", firstDec,secondDec,sumDec);
}

/*Given a binary number, arithmetic sign (+,-), second binary number
If sign == -,  flip sign of second binary number
Then add both via carrying bits in traditional addition*/
void addBin(char operate, char first[], char second[]){
    int len = strlen(first);
    if (operate == '-'){
        if (second[2] == '1')
            flipBits(second);
        else
            flipBits(second);
    }
    char carryBits[len];
    char sum[len];
    carryBits[0] = ' ';
    sum[0] = '0';
    sum[1] = 'b';
    //int finalCarryIndex = 0;

    for (int i = len-1; i > 1; i--){
        if (first[i] == '1' && second[i] == '1'){
            sum[i] = '0';
            carryBits[i-1] = '1'; 
            //finalCarryIndex = i-1;
            if (carryBits[i] == '1')
                sum[i] = '1';
        }
        else if (first[i] == '1' || second[i] == '1'){
            sum[i] = '1';
            if (carryBits[i] == '1')
                sum[i] = '0';
        }
        else{
            sum[i] = '0';
            if (carryBits[i] == '1')
                sum[i] = '1';
        }
    }
    printaddBin(first,second,carryBits,sum);
}

/* Distinguish between bintoDeco/dectoBin and binary arithmetic, then call approporiate function*/
int main(int argc, char *argv[]) {
    //conversion request
    if (argc == 3) {
        // Store first argument in array
        char number[MAX_BINARY_LEN + 2 + 1];
        strcpy(number, argv[1]);

        // Store second argument in array
        char option[3];
        strcpy(option, argv[2]);
        // perform conversion
        
        if (option[0] == 'u' || option[0] == 's'){
            binToDec(number,option[0],1);
        } 
        else{
            int arrToInt = atoi(number); // from ChatGPT
            int arrToInt2 = atoi(option); //could use for loop with base ten system but this is much cleaner
            decToBin(arrToInt,arrToInt2);  
        }
    }
    else if (argc == 4) {
        //arithmetic call
        // Store first argument in array
        char firstNum[MAX_BINARY_LEN + 2 + 1];
        strcpy(firstNum, argv[1]); 

        // Store second argument in array
        char operation[2];
        strcpy(operation, argv[2]);

        // Store third argument in array
        char secondNum[MAX_BINARY_LEN + 2 + 1];
        strcpy(secondNum, argv[3]);

        addBin(operation[0],firstNum,secondNum);
    }
    else {
        printf("Invalid number of arguments\n");
        return 1;
    }
}
 