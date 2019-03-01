
#include <stdlib.h>

char* itob(int n, char s[], int b) {
    int curr = 0;
    int sign = (n >= 0) ? 1 : -1;

    if(n == 0) {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    while (n != 0) {
        int digit = abs(n % b);
        if (digit < 10) {
            s[curr] = (char)(digit + '0');
        } else {
            s[curr] = (char)(digit - 10 + 'a');
        }
        n /= b;
        curr++;
    }
    int size = curr;
    if(sign == -1) {
        s[curr++] = '-';
        size++;
    }
    int middle = size / 2;
    while(curr > middle) {
        curr--;
        char t = s[curr];
        s[curr] = s[size - curr - 1];
        s[size - curr - 1] = t;
    }
    s[size] = '\0';

    return s;
}
