#include <stdbool.h>



bool binsearch(int x, int v[], int n) {
    int curr = n/2;
    int first = 0;
    int last = n-1;
    while(last - first > 1) {
        if(v[curr] > x) {
            last = curr - 1;
        } else {
            first = curr;
        }
        curr = first + (last - first) / 2;
    }
    return x == v[first] || x == v[last];
}
