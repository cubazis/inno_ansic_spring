//
// Created by cubazis on 25.05.18.
//

#include <memory.h>
#include <math.h>
#include "task.h"

/** The stub function
 *  just to demonstrate how to work with ck_assert
 *  please look for test case for stub function in test_task.c
 */

int stub(void)
{
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

char* array_changer(const char c[])
{
	char j = 0;
	int size = 0;
	STRING_LEN(size, c);
	char* b = ALLOCATE(size);

	for (;j < size;) {
		if(c[j] == 'c')
			b[j] = 'b';
		else
			b[j] = c[j];
		j++;
	}
	return b;
}

/** YOUR SOLUTIONS */

/** [1.20] */
char* detab(const char input[])
{
	int i = 0;
	int new_array_length = 0;
	while (input[i] != '\0') {
		if (input[i] == '\t') new_array_length = new_array_length + 4;
		else new_array_length = new_array_length + 1;

		i++;
	}

	char new_array[new_array_length+1];
	new_array[new_array_length] = '\0';

	i = 0;
	int j = 0;
	while (input[i] != '\0') {
		if (input[i] == '\t') {
			new_array[j] = ' ';
			j++;
			new_array[j] = ' ';
			j++;
			new_array[j] = ' ';
			j++;
			new_array[j] = ' ';
			j++;
			i++;
		} else {
			new_array[j] = input[i];
			j++;
			i++;
		};
	}
	char *r = new_array;
	return r;
}

/** [Additional] */
int string_size(const char input[]) {
	int i = 0;
	while (input[i] != '\0') {
		i++;
	}
	return i;
}

/** [1.21] */
char* entab(const char input[]) {

	int i = 0; //index for input array
	int j = 0; //index for temporary array

	int size = string_size(input); //size without "\0" (end char)

	char temp[size+1]; // "+1" for closing char

	while (input[i] != '\0') {
		if (input[i] == ' ' & i <= size - 4) {
			if (input[i + 1] == ' ' & input[i + 2] == ' ' & input[i + 3] == ' ') {
				temp[j] = '\t';
				i = i + 4;
				j = j + 1;
			} else {
				temp[j] = input[i];
				i = i + 1;
				j = j + 1;
			}
		} else {
			temp[j] = input[i];
			i = i + 1;
			j = j + 1;
		}
	}
	temp[j] = '\0';

	char returning_array[j+1];
	returning_array[j] = '\0';

	i = 0;
	while (temp[i] != '\0') {
		returning_array[i] = temp[i];
		i++;
	}

	char* r = returning_array;
	return r;
};

/** [Additional] */
int hex_to_int(char x) {
	switch (x) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': return 10;
		case 'B': return 11;
		case 'C': return 12;
		case 'D': return 13;
		case 'E': return 14;
		case 'F': return 15;

		default: return 0;
	}
}

/** [2.3] */
int htoi(const char s[]) {
	int power = 0;
	int size = string_size(s);
	int value = 0;

	for (int j = size-1; j >= 0; j--) {
		value += hex_to_int(s[j])*(pow(16, power));
		power++;
	}
	return value;
};

/** [2.4] */
char* squeeze(const char s1[], const char s2[]) {
	int i = 0; //index for input array
	int dictionary[256] = {0};
	while (s2[i] != '\0') {
		int index = s2[i];
		dictionary[index] = 1;
		i++;
	}

	int j = 0;
	int new_length = 0;
	while (s1[j] != '\0') {
		int index = s1[j];
		if (dictionary[index] == 0) {
			new_length++;
		}
		j++;
	}

	char returning_array[new_length+1];
	returning_array[new_length] = '\0';

	i = 0;
	j = 0;
	while (returning_array[i] != '\0' | s1[j] != '\0') {
		int index = s1[j];
		if (dictionary[index] == 0) {
			returning_array[i] = s1[j];
			j++;
			i++;
		} else {
			j++;
		}
	}

	char* r =  returning_array;
	return r;
};

/** [3.1] */
int binsearch(int x, int v[], int n)
{
	int low = 0, high = n - 1, mid = 0;

	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid+1;
	}
	return v[low]==x ? low : -1;
}

/** [3.2] */
char* escape(const char from[])
{
	int size = 0, id = 0, i = 0;

	STRING_LEN(size, from);

	char *out = ALLOCATE(2 * size + 1);
	char c = from[0];

	for (; c != '\0'; i++)
	{
		c = from[i];

		switch (c)
		{
			case '\n':
				out[id++] = '\\';
				out[id++] = 'n';
				break;
			case '\t':
				out[id++] = '\\';
				out[id++] = 't';
				break;
			default:
				out[id++] = c;
		}
	}
	out[id] = '\0';
	return out;
}

/** [3.3] */
char* expand(const char s1[])
{
	int size = 0, id = 0, i = 0;
	char c = s1[i];
	if (c == '-')
		size++, c = s1[++i];
	while (c != '\0')
	{
		if (c != '-' || s1[i+1] == '\0')
			size++, c = s1[++i];
		else
		{
			size = size + (s1[i-1] > s1[i+1] ? s1[i-1] : s1[i+1]) - (s1[i-1] < s1[i+1] ? s1[i-1] : s1[i+1]);
			i++;
			c = s1[++i];
		}
	}

	char *out = ALLOCATE(size+1);
	c = s1[0], i = 0;

	if (c == '-')
		out[id++] = c, c = s1[++i];
	while (c != '\0')
	{
		if (c != '-' || s1[i+1] == '\0')
			out[id++] = c, c = s1[++i];
		else
		{
			char d = (char) (s1[i - 1] < s1[i + 1] ? 1 : -1);
			for (char z = d; out[id-1] != s1[i+1]; z = z + d)
				out[id++] = (s1[i - 1] + z);
			i++;
			c = s1[++i];
		}

	}
	out[id] = '\0';
	return out;
}

/** [Additional] */
void reverse(char s[])
{
	int i, j;
    char c;
	for (i = 0, j = (int) (strlen(s) - 1); i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/** [3.4] */
char* itoa(int n)
{
	int i, sign;
	char *s = ALLOCATE(11);
	sign = n < 0 ? -1 : 1;
	i = 0;
	do {
		s[i++] = (char) (sign * (n % 10) + '0');
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return s;
}

/** [3.5] */
char* itob(int n, int b) {
	char * result = ALLOCATE(sizeof(int)*8);
	char i = sizeof(int)*8 -1;
	for(; i>=0 && n != 0; i--, n/=b){
		char temp = n % b;
		if(temp < 10){
			temp += '0';
		}else {
			temp += 'A'-10;
		}
		result[i] = temp;
	}
	return result+i+1;
}

/** [4.1] */
int strrindex(const char s[], const char t[]) {
	int i = 0;
	int j = 0;
	STRING_LEN(i,t);
	STRING_LEN(j,s);
	i = j - i;
	int k = 0;
	for(;i >=0; i--, j--){
		for(k = 0; t[k] != '\0' && s[i + k] == t[k]; k++);
		if(k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

/** [4.2] */
double atofe(const char s[]) {
	double value = 0;
	int sign = 1;
	int power;
	int ind;
	int sign_ = 1;
	int exponent = 0;
	for(ind = 0; s[ind] == ' ';ind++);
	if(s[ind] == '-' || s[ind] == '+'){
		sign = s[ind] == '-' ? -1 : 1;
		ind++;
	}
	for(; IS_DIGIT(s[ind]);ind++){
		value = value * 10.0 + s[ind] -'0';
	}
	if(s[ind] == '.') {
		ind++;
		double power = 10.0;
		if(IS_DIGIT(s[ind])){
			for(;IS_DIGIT(s[ind]); ind++){
				value += (s[ind]-'0') / power;
				power *= 10.0;
			}
		}
	}
	if(s[ind] == 'e' || s[ind] == 'E'){
		ind++;
		if(s[ind] == '-' || s[ind] == '+'){
			sign_ = s[ind] == '-' ? -1 : 1;
			ind++;
		}

		for(; IS_DIGIT(s[ind]);ind++){
			exponent = exponent * 10 + s[ind] -'0';
		}
	}
	value = sign == -1 ? -value : value;
	double m = sign_ == -1 ? 0.1 : 10.0;
	for(int j = 0; j < exponent; j++){
		value *= m;
	}
	return value;
}

/** [1.22] */
char* enter(int n,const char input[]){
	int size =0;
	int i = 0;
	while(input[i]!='\0'){
		size++;
		i++;
	}

	if (size>n&&n!=0){
		int k = size/n;
		int new_size = size+k;
		char arr[new_size+1];
		arr [new_size]='\0';


		int counter = 1;
		int howmanytimes = 0;

		for (int j = 0; j <new_size+1; ++j) {
			if (counter>n){
				arr[j]='\n';
				howmanytimes++;
				counter=0;
			}
			arr[j+howmanytimes]=input[j];
			counter++;
		}
		char *r = arr;
		return r;
	}
	char *m=input;
	return m;

}

/** [1.23] */
char* flush(const char input[]){
	int i=0;

	int siz =sizer(input);
	char arr[siz];
	int s = 0;
	int j;
	int l;


	while(input[i]!='\0'){
		if (input[i]=='/'&&input[i+1]=='/'){
			while(input[i]!='\n') i++;
		}


		if (input[i]=='/'&&input[i+1]=='*'){
			int k = i+2;
			while (input[k]!='*'&&input[k+1]!="/"){
				k++;
			}
			i=k+2;
		}
		arr[s]=input[i];
		s++;
		i++;

	}
	char *t =arr;
	return t;
}

/** [Additional] */
int sizer(const char input[]){
	int i=0;
	int size = 0;
	while(input[i]!='\0'){
		if (input[i]=='/'&&input[i+1]=='/'){
			int k =i+2;
			while (input[k]!='\n'){
				k++;
			}
			i=k;
			size++;
		}
		else if (input[i]=='/'&&input[i+1]=='*'){
			int k = i+2;
			while (input[k]!='*'&&input[k+1]!="/"){
				k++;
			}
			i=k+1;
		}
		else {size++;}

		i++;

	}
	return size;
}

/** [2.5] */
int any(const char s1[],const char s2[]) {
	int i;
	int j;
	int len = strlen(s1);
	int min = len;
	for (i = 0; s1[i] != '\0'; i++)
		for (j = 0; s2[j] != '\0'; j++)
			if (s2[j] == s1[i] && i < min)
				min = i;
	if (min == len)
		min = -1;
	return min;
}

/** [2.6] */
unsigned int setbits(unsigned int x,int p,int n,unsigned int y)
{
    unsigned int a = 1;
    unsigned int b = 0;
    for (n; n > 0; --n)
    {   b = b | a;
        a = a << 1;   }
    a = b;
    a = a << p;
    a = ~a;
    x = x & a;
    b = b & y;
    b = b << p;
    x = x | b;
    return x;
}

/** GET FROM task.h */
