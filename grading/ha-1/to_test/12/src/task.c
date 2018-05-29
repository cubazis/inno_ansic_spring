//
// Created by cubazis on 25.05.18.
//

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "task.h"

/** The stub function
 *  just to demonstrate how to work with ck_assert
 *  please look for test case for stub function in test_task.c
 */

int stub(void) {
    return 42;
}

/** The array_changer function
 *  just to demonstrate how to work with returning of array from function
 *
 *  1) C language doesn't have strings
 *  2) array in a C language is just a segment of memory
 *  3) C lang doesn't have ability to pass array as parameter in a function
 *  4) we suppose that you don't know about memory allocation through pointers
 *
 *  so, we provide you simple demo function which change 'c' char in input array
 *  	input parameter: constant array of chars
 *  	output: pointer to memory segment in which resulting array starts
 *
 *  	extra stuff: we provide you three define macros in task.h.
 *  		you can use them in your solutions
 *  		if you don't want to use them please, don't delete them - somebody may use it
 *
 *  please look for test case for array_changer function in test_task.c
 */

char *array_changer(const char c[]) {
    char i = 0, j = 0;
    STRING_LEN(i, c);
    char *b = ALLOCATE(i);

    for (; j < i;) {
        if (c[j] == 'c')
            b[j] = 'b';
        else
            b[j] = c[j];
        j++;
    }

    return b;
}

/** YOUR SOLUTIONS */
char* detab(const char input[]) {
    int i = 0, counter = 0, j = 0, temp = 0;
    STRING_LEN(i, input);               //i = length of string
    NUMBER_OF(counter, '\t', input);//counter = number of tabs in sequence

    char* output = ALLOCATE(i +3*counter);
    counter = 0;
    for (; j < i;j++) {
        if (input[j] == '\t')                       //if tab is found
        {
            for (int k = 0; k < 4; k++) {            //place 4 spaces
                output[j + 3 * counter + k] = ' ';
            }
            counter++;                               //increase counter
        } else
            output[j + 3 * counter] = input[j];      //else just copy from input

        STRING_LEN(temp, output);

    }
    output[j+counter*3] = '\0';
    return output;
}


char *entab(const char input[]) {
    int i = 0, counter = 0, j = 0, k = 0;
    SPACE_TO_TAB_COUNTER(counter, input);   //define number of tabs to be inserted
    STRING_LEN(i, input);
    char *output = ALLOCATE(i - 3 * counter);   //so the output array size <= input array size
    int space_counter = 0;                  //counter for spaces going one by one (together)
    for (; j < i;) {                             //j - iterator for input, k - for output
        if (input[j] == ' ') {                //case space found - place tab or go further
            space_counter += 1;
            if (space_counter == 4) {
                output[k] = '\t';
                k++;
                space_counter = 0;
            }
        } else {                                    //case space not found - insert collected spaces and copy from input
            for (; space_counter > 0; space_counter--) {
                output[k] = ' ';
                k++;
            }
            space_counter = 0;
            output[k] = input[j];
            k++;

        }
        j++;
    }
    output[k] = '\0';
    return output;

}

char *enter(int n, const char input[]) {
    int i = 0, counter = 0, j = 0;
    STRING_LEN(i, input);
    if (i % n == 0) counter = i / n - 1;
    else counter = i / n;
    char *output = ALLOCATE(i + counter);
    int enter_counter = 0;

    for (; j < i;) {
        output[j + enter_counter] = input[j];
        j++;
        if ((j % n) == 0 && enter_counter < counter) {      //after every n chars place \n
            output[j + enter_counter] = '\n';               //there must not be \n in the end
            enter_counter += 1;
        }

    }
    output[j + enter_counter] = '\0';
    return output;

}
char *flush(const char input[], char output []){
    int i = 0;
    int count = 0;
    while (input[i] != '\0' ) {
        if (input[i] == '"'){
            output[count ++] = '"';
            ++i;
            output[count++] = input[i];
            while(input[i] != '"') {
                ++i;
                output[count++] = input[i];
            }
        }
        else if (input[i] == '/'){
            ++i;
            if (input[i] == '/') {
                while (input[i] != '\n' && input[i] != '\0')
                    ++i;
                if (input[i] == '\n') {output[count] = input[i];
                count++; } else {
                    output[count] = '\0'; break;}
            }

            else if ( input[i] == '*'){
                ++i;
                while ( input[i+1] != '/' || input[i] != '*'){

                    ++i;               }
            }
            else output[count++] = input[i];
        }
        else {
            output[count++] = input[i];
        }
        i = i + 1;
    }
    output[count] = '\0';
}

int htoi(const char input[]) {
    int i = 0, j = 2, result = 0;
    STRING_LEN(i, input);
    if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X') && i > 2) {

        for (; j < i; j++) {
            int base = 16;
            int number = 0;
            if (isdigit(input[j])) {             //define a number
                number = input[j] - '0';
            } else {
                switch (input[j]) {
                    case 'A':
                        number = 10;
                        break;
                    case 'a':
                        number = 10;
                        break;
                    case 'B':
                        number = 11;
                        break;
                    case 'b':
                        number = 11;
                        break;
                    case 'C':
                        number = 12;
                        break;
                    case 'c':
                        number = 12;
                        break;
                    case 'D':
                        number = 13;
                        break;
                    case 'd':
                        number = 13;
                        break;
                    case 'E':
                        number = 14;
                        break;
                    case 'e':
                        number = 14;
                        break;
                    case 'F':
                        number = 15;
                        break;
                    case 'f':
                        number = 15;
                        break;
                    default:
                        return -1;             //if there is wrong input return -1

                }
            }
            int power = i - j - 1;
            POW(base, power);
            result += number * base;           //add 16 in power needed * number
        }
    } else return -1;
    return result;

}

int strrindex(const char s[], const char t[]) {
    int a1 = 0, a2 = 0, i = 0, found = 0, j = 0;
    STRING_LEN(a1, s);
    STRING_LEN(a2, t);
    i = a1 - a2;
    for (; i > -1 && found == 0;) {                        //start from the right side of array
        found = 1;
        for (j = i; (j - i) < a2 && found == 1; j++) {     //start checking from current plase (left -> right)
            if (s[j] != t[j - i]) found = 0;               //if some char does not match, go further
        }                                                  //if all match -> found, stop loop
        if (found == 0) i--;
    }
    if (found == 0) return -1;
    else return i;
}

double atofe(const char s[]) {

    double val, power,mantisa,exp = 1.0,result = 0.0;
    int i, sign,esign, size, epower ;

    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.') i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    //additional part

    if (s[i] == 'E' ||s[i] == 'e') {                  //find e, if exist
        i++;
        exp = 10.0;
    }
    esign = (s[i] == '-') ? -1 : 1;                   //denote sign
    if (s[i] == '+' || s[i] == '-')
        i++;
    for(epower = 0; isdigit(s[i]); i++) {             //denote power
        epower = 10 * epower + (s[i] - '0');
    }
    POW(exp,epower);
    mantisa = sign * (val/power);
    return esign == 1 ? mantisa * exp : mantisa / exp; //culculate result

}
char *itoa(int n, char s[], int w){
void reverse(char s[]);

int i,sign;
if ((sign = n) < 0)
n = -n;
i = 0;
do {
s[i++] = n % 10 + '0';
}
while ((n /=10) > 0);
if (sign <0)
s[i++] = '-';
while(i<w)
s[i++]=' ';
s[i] = '\0';
reverse(s);
return s;
}
//KATYKHA EBASH(2)
void reverse(char s[])
{
    int i,j,c;

    for(i=0,j=strlen(s)-1;i<j;i++,j--)
        c=s[i],s[i]=s[j],s[j]=c;
}
char *itob(int n, char s[], int b){
    void reverse(char s[]);
    int i = 0;
    int sign;
    if ((sign = n) <0)
        n = - n;
    while (n>0){
        int j = n % b;
        if (j<=9) {
            s[i++] = j + '0';
        }
        else
            s[i++] = j + 'a' - 10;
        n = n / b;
    }
    if (sign < 0) {
        s[i++] = '-';
    }
    if ( i > 0) {
        s[i] = '\0';
        reverse(s);
    }
    else s[i] = '0';
    s[++i] = '\0';
}
int binsearch( int x, int v[], int n){
    int low, high, mid;
    low = 0;
    high = n -1;
    mid = (low+high)/2;

    while( low < high && x!=v[mid]){
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low+high)/2;
    }
    if (x == v[mid]){
        return mid;
    }
    else return -1; /* no match */
}
char *escape(const char from[], char to[]){
   int i = 0;
    int count = 0;
    for ( i = 0; i<strlen(from); i++){
        switch (from[i]) {
            case '\n':to[count++] = '\\';
                to[count++] = 'n';
                break;
            case '\t':to[count++] = '\\';
                    to[count++] = 't';
                break;
            default:
                to[count++] = from[i];
                break;
        }

    }
    to[count] = '\0';
}

char *expand(const char s1[],  char s2[]){
    int i = 0;
    int j = 0;
    while(s1[i] != '\0') {
        int p = s1[i];
        if (s1[i + 1] == '-' && s1[i + 2] >= p) {
            i++;
            while (p < s1[i + 1])
                s2[j++] = p++;
        } else if (s1[i] != '-')
            s2[j++] = s1[i];

        ++i;
    }
    s2[j]='\0';
}




unsigned setbits(unsigned x, int p, int n, unsigned y){
    if (n>p) n=p;
    unsigned z = (~((~0)<<n))<<(p-n);
    unsigned result = x&(~z)|(z&(y<<p-n));
    return result;
}

char* squeeze(const char s1[], const char s2[])
{
    int i, j, k;
    char* s = (char*) s1;
    bool exist;
    for (i = j = 0; s[i] != '\0'; i++) {
        exist = false;
        for (k = 0; s2[k] != '\0'; k++)
            if (s[i] == s2[k]) {
                exist = true;
                break;
            }
        if (!exist)
            s[j++] = s[i];
    }
    s[j] = '\0';
    return s;
}

int any(const char s1[], const char s2[]) {
    int i, k;
    for (i = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0'; k++)
            if (s1[i] == s2[k]) return i;
    }
    return -1;
}
/** GET FROM task.h */
