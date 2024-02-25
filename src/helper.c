//
// Created by shobhit on 22/2/24.
//

#include "helper.h"

#include <stdlib.h>
#include <string.h>

char digitToChar(int digit) {
    char c;
    switch (digit) {
        case 0:
            c = '0';
            break;
        case 1:
            c = '1';
            break;
        case 2:
            c = '2';
            break;
        case 3:
            c = '3';
            break;
        case 4:
            c = '4';
            break;
        case 5:
            c = '5';
            break;
        case 6:
            c = '6';
            break;
        case 7:
            c = '7';
            break;
        case 8:
            c = '8';
            break;
        case 9:
            c = '9';
            break;
    }
    return c;
}

char* intToStr_dyn(long int num) {
    // determine number of digits of num
    long int temp = num;
    int count = 0;
    while(temp != 0) {
        temp = temp/10;
        count++;
    }
    // convert int to str
    char *buff = (char*) malloc(count + 1);
    buff[count] = '\0';
    int i = 0;
    while(num != 0) {
        char c = digitToChar(num%10);
        num = num/10;
        buff[count - i - 1] = c;
        i++;
    }
    return buff;
}