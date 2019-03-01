//
// Created by cubazis on 25.05.18.
//

#include <task.h>

/** Увы, я накосячил когда наспех формулировал задание detab поэтому получилось
 * две различных формулировки:
 * 1) моя формулировка на github по сути требует реализовать функцию replace,
 *    для замены некоторого символа (в нашем случае символа '\t') некоторой подстрокой (в нашем случае 4мя проелами)
 * 2) оригинальная формулировка, которая требует реализации функции detab, заменяющей '\t' на соответствующее
 * количество пробелов (в моей формулировке 4 пробела). Оригинальная detab должна работать иначе,
 * но здесь я приведу решение в соответствии с тем что "я сформулировал" для задания.
 */

char* detab(const char input[])
{
	/** Итак фактичеси мы заменяем любой попавшийся символ '\t' на 4 пробела
	 *  поэтому заведем соответсвующие переменные для искомого паттерна ch,
	 *  и того паттерна tch на который мы заменяем
	 */
	char ch = '\t';
	char tch = ' ';

	/** полезно будет сразу завести переменную tabinc для обозначения колличества пробелов
	 * на которые мы заменяем символ табуляции '\t'
	 */
	size_t tabinc = 4;

	/** Заведем вспомогательный указатель *t чтобы итерировать по "входной строке" */
	const char *t;

	/** str_len нам пригодится для хранения длины входной строки */
	size_t str_len = 0;

	/** это нам нужно для подсчета символов '\t' во входной строке */
	int tabs_count = 0;

	/** тут пользуемся идеоматической конструкцией for(t=input; *t; t++)
	 *  t = input - выставляем указатель на первый символ "строки"
	 *
	 *  при этом понимаем что никаких строк нет и указатель char * всегда "тычет" в начало соответствующего
	 *  участка памяти
	 *
	 *  условие *t, это разыменование указателя t
	 *  условие *t эквиввалентно условию *t != '\0' или *t != 0 или p[0] != '\0'
	 *  когда *t достигнет терминального символа '\0' он же 0x00, произойдет выход
	 *  из цикла for. однако этот цикл сломается если "строка" не содержит терминального символа
	 * */
	for(t = input; *t; t++){
		/** считаем длину входной строки и количество табов */
		++str_len;
		tabs_count += (*t == ch);

	}

	/** выделяем память под новую строку один раз, причем мы уже знаем сколько нам ее нужно
	 *  конечно можно было сделать вариант с перевыделением памяти, но чем больше табов во входной
	 *  строке, тем сильнее вы забьете стек перевыделяя память
	 */
	char *res = malloc(str_len + (tabinc-1)*tabs_count + 1);

	/** заводим указатель ptr для итерирования по строке input, и в цикле формируем в памяти
	 * строку res */
	char *ptr = res;
	for(t=input; *t; t++) {
		if(*t == ch) {
			for (int i = 0; i < tabinc; ++i) {
				*ptr++ = tch;
			}
		} else {
			*ptr++ = *t;
		}
	}
	/** не забываем терминальный символ =) */
	*ptr = 0;
	return res;
}


char* entab(const char input[])
{
	int nb = 0; // nb - необходимое колличество пробелов
	int nt = 0; // nt - необходимое колличество табуляций
	int pos = 1; // pos - позиция текущего символа в тексте

	/** Итак фактичеси мы заменяем любой попавшийся символ '\t' на 4 пробела
	 *  поэтому заведем соответсвующие переменные для искомого паттерна ch,
	 *  и того паттерна tch на который мы заменяем
	 */
	char tch = '\t';
	char ch = ' ';

	/** полезно будет сразу завести переменную tabinc для обозначения колличества пробелов
	 * на которые мы заменяем символ табуляции '\t'
	 */
	size_t tabinc = 4;

	/** Заведем вспомогательный указатель *t чтобы итерировать по "входной строке" */
	const char *t;

	/** str_len нам пригодится для хранения длины входной строки */
	size_t str_len = 0;

	/** это нам нужно для подсчета символов '\t' во входной строке */
	int tabs_count = 0;

	for(t = input; *t; t++){
		/** считаем длину входной строки и количество табов */
		++str_len;
		tabs_count += (*t == ch);

	}

	char *res = malloc(str_len*sizeof(char));
	char *ptr = res;
	for(t=input; *t; t++) {
		if (*t == ch) { // если встречаем пробел
			++pos; // сдвигаем указатель на следующий за ним элемент
			if ((pos % tabinc) == 0) { // проверяем являится ли следующий элемент границей табуляции, если да - копим табуляцию
				++nt;
				nb = 0;
			}
			else { // иначе - копим пробел
				++nb;
			}
		}
		else if (*t == '\n') { // если конец строки
			//выводим накопившиеся пробелы, если таковые были до конца строки, табуляции не потеряются
			// потому как табуляции естественным образом выводятся в блоке else
			for (; nb > 0; --nb) {
				*ptr++ = ch;
			}
			*ptr++ = *t;
			nb = 0;
			nt = 0;
			pos = 1;
		}
		else {
			for (; nt > 0; --nt) {
				*ptr++ = tch;
			}
			for (; nb > 0; --nb) {
				*ptr++ = ch;
			}
			if(*t == tch){
				*ptr++ = tch;
			}
			else { // выводим любой другой символ
				*ptr++ = *t;
			}
			++pos;
		}
	}
	/** не забываем терминальный символ =) */
	*ptr = 0;
	return res;
}

char* enter(int n, const char input[])
{
	int len = 0;
	const char* t;
	for(t = input; *t; t++){++len;}
	char *res = malloc((len+len/n)*sizeof(char));
	char *ptr = res;
	int i = 0;
	for(t = input; *t; t++){
		if((i)%n == 0 && i != 0){
			*ptr++ = '\n';
		}
		*ptr++ = *t;
		++i;
	}
	return res;
}

char* flush(const char input[])
{
	int len = 0;
	for(const char* t = input; *t; t++){++len;}
	char *res = malloc(len*sizeof(char));
	char *ptr = res;
	const char* t;
	for(t = input; *t; t++)
	{
		if(*t == '/'){
			++t;
			if(*t == '*'){
				while (1){
					++t;
					char c = *t;
					if(c == '*'){
						++t;
						c = *t;
						if(c == '/'){
							++t;
							break;
						}
					}
				}
			} else if(*t == '/'){
				while (1){
					++t;
					char c = *t;
					if(c == '\n'){
						break;
					}
				}
			}
		}
		*ptr++ = *t;
	}
	*ptr = 0;
	return res;
}

int htoi(const char s[])
{
	enum {NO, YES};
	int hex = 0, sign = YES, i = 0, n = 0;
	if(s[i] == '0'){
		++i;
		if(s[i] == 'x' || s[i] == 'X'){
			++i;
		}
	}
	while (sign == YES){
		if(s[i] >= '0' && s[i] <= '9'){
			hex = s[i] - '0';
		}
		else if(s[i] >= 'a' && s[i] <= 'f'){
			hex = s[i] - 'a' + 10;
		}
		else if(s[i] >= 'A' && s[i] <= 'F'){
			hex = s[i] - 'A' + 10;
		}
		else{
			sign = NO;
		}
		if(sign == YES){
			n = 16 * n + hex;
		}
		++i;
	}

	return n;
}

char* squeeze(const char s1[], const char s2[])
{
	int z = 0;
	for(const char* t = s1; *t; t++){++z;}

	char *res = malloc(z*sizeof(char));
	char *ptr = res;
	int i, j, k;
	for(i = k = 0; s1[i] != '\0'; i++){
		for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++);
		if(s2[j] == '\0'){
			*ptr++ = s1[i];
		}
	}
	*ptr = 0;
	return res;
}

int any(const char s1[], const char s2[])
{
	int i = 0, j = 0;
	while (s2[i] != '\0'){
		while (s1[j] != '\0'){
			if(s1[j] == s2[i]){
				return j;
			}
			++j;
		}
		++i;
	}
	return -1;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return x & ~(~(~0 << n) << (p+1-n)) | (y & ~(~0 << n)) << (p+1-n);
}

int binsearch(int x, int v[], int n)
{
	int low = 0, high = n - 1, mid;
	mid = (low+high)/2;
	while (low <= high && x != v[mid]){
		if (x < v[mid]){
			high = mid - 1;
		} else {
			low = mid + 1;
		}
		mid = (low+high)/2;
	}
	if(x == v[mid]){
		return mid;
	}
	else{
		return -1;
	}
}


char* escape(const char from[])
{
	char ch1 = '\t';
	char ch2 = '\n';
	char ch = '\\';
	int seq_count  = 0;
	size_t str_len = 0;

	const char *t;
	for(t = from; *t; t++){
		++str_len;
		seq_count += (*t == ch1);
		seq_count += (*t == ch2);
		seq_count += (*t == '\a');
		seq_count += (*t == '\b');
		seq_count += (*t == '\f');
		seq_count += (*t == '\v');
		seq_count += (*t == '\r');
		seq_count += (*t == '\\');
		seq_count += (*t == '\'');
		seq_count += (*t == '\"');
		seq_count += (*t == '\?');
	}
	char *res = malloc((str_len + seq_count)* sizeof(char));
	char *to = res;
	for(t = from; *t; t++) {
		switch (*t){
			case '\n':
				*to++ = ch;
				*to++ = 'n';
				break;
			case '\t':
				*to++ = ch;
				*to++ = 't';
				break;
			case '\b':
				*to++ = ch;
				*to++ = 'b';
				break;
			case '\v':
				*to++ = ch;
				*to++ = 'v';
				break;
			case '\r':
				*to++ = ch;
				*to++ = 'r';
				break;
			case '\a':
				*to++ = ch;
				*to++ = 'a';
				break;
			case '\f':
				*to++ = ch;
				*to++ = 'f';
				break;
			case '\\':
				*to++ = ch;
				*to++ = '\\';
				break;
			case '\'':
				*to++ = ch;
				*to++ = '\'';
				break;
			case '\"':
				*to++ = ch;
				*to++ = '\"';
				break;
			case '\?':
				*to++ = ch;
				*to++ = '\?';
				break;
			default:
				*to++ = *t;
				break;
		}
	}
	*to = 0;
	return res;
}

char* expand(const char s1[])
{
	char c;
	int i = 0, j = 0;
	while ((c = s1[i++]) != '\0'){
		if(s1[i] == '-' && s1[i+1] >= c){
			i++;
			while (c < s1[i]){
				j++;
				c++;
			}
		} else {
			j++;
		}
	}
	char *res = malloc((j)*sizeof(char));
	char *s2 = res;
	i = 0, j = 0;
	while ((c = s1[i++]) != '\0'){
		if(s1[i] == '-' && s1[i+1] >= c){
			i++;
			while (c < s1[i]){
				*s2++ = c++;
			}
		} else {
			*s2++ = c;
		}
	}
	*s2 = 0;
	return res;
}

char* itoa(int n)
{
	void reverse(char *s){
		char ch, *c1, *c2;

		/** выставляем указатель на последний элемент */
		for (c2 = s; *c2 != '\0'; ++c2)
			;
		if (c2 > s)
			--c2;

		/** делаем туда-сюда пока поинтеры не встретятся*/
		for (c1 = s; c1 < c2; ++c1, --c2) {
			ch = *c1;
			*c1 = *c2;
			*c2 = ch;
		}
	}
	int i = 0, j, sign = n, m = n;
	int prefix = 0;

	do{i++;} while ((m /= 10) != 0);

	if(sign < 0){
		prefix+=1;
	}
	char *res = malloc((i+prefix)*sizeof(char));
	char *ptr = res;
	do{
		*ptr++ = (char) (abs(n % 10) + '0');
	} while ((n /= 10) != 0);
	if (sign < 0){
		*ptr++ = '-';
	}
	*ptr++ = 0;
	reverse(res);
	return res;
}

char* itob(int n, int b)
{

	void reverse(char *s){
		char ch, *c1, *c2;

		/** выставляем указатель на последний элемент */
		for (c2 = s; *c2 != '\0'; ++c2)
			;
		if (c2 > s)
			--c2;

		/** делаем туда-сюда пока поинтеры не встретятся*/
		for (c1 = s; c1 < c2; ++c1, --c2) {
			ch = *c1;
			*c1 = *c2;
			*c2 = ch;
		}
	}

	int i = 0, j, sign = n, m = n;

	do{i++;} while ((m /= b) != 0);
	int prefix = 0;
	if(b == 16){
		prefix+=2;
	}
	if(b == 8){
		prefix+=1;
	}
	if(sign < 0){
		prefix+=1;
	}
	char *res = malloc((i+prefix)*sizeof(char));
	char *ptr = res;
	do{
		j = abs(n % b);
		*ptr++ = (char) ((j <= 9) ? j + '0' : j + 'a' - 10);
	} while ((n /= b) != 0);
	if(b == 16){
		*ptr++ = 'x';
		*ptr++ = '0';
	}
	if(b == 8){
		*ptr++ = '0';
	}
	if(sign < 0){
		*ptr++ = '-';
	}
	*ptr++ = 0;
	reverse(res);
	return res;
}


int strrindex(const char s[], const  char t[])
{
	int i, j, k, l = -1;
	for (i = 0; s[i] != '\0' ; ++i) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {
			;
		}
		if(k > 0 && t[k] == '\0'){
			l = i;
		}
	}
	return l;
}

double atofe(const char s[])
{
	double val, power, exp;
	int i, sign, sign2;

	/** есть в ctype.h */
	int isdigit(char c){
		if(c >= '0' && c <= '9'){
			return 1;
		}
		return 0;
	}

	/** есть в ctype.h */
	int isspace(char c){
		if(c == ' ' || c == '\t'){
			return 1;
		}
		return 0;
	}

	double power10(double n){
		double p;
		for (p = 1; n > 0; --n) {
			p = p * 10.0;
		}
		return p;
	}

	// пропуск пробелов
	for (i = 0; i < isspace(s[i]); ++i) {
		;
	}
	sign = (s[i] == '-') ? -1:1;
	if(s[i] == '-' || s[i] == '+'){
		i++;
	}
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if(s[i] == '.'){
		i++;
	}
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i] == 'e' || s[i] == 'E'){
		i++;
		sign2 = (s[i] == '-') ? -1:1;
		if(s[i] == '-' || s[i] == '+'){
			i++;
		}
		for (exp = 0.0; isdigit(s[i]); i++) {
			exp = 10.0 * exp + (s[i] - '0');
		}
		if(sign2 == 1){
			return (sign * val / power) * power10(exp);
		} else if(-1 == sign2){
			return (sign * val / power) / power10(exp);
		}
	}
	return sign * val / power;
}