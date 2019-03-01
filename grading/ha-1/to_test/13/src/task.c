#include "task.h"

int stub(void) {
    return 42;
}

/**
 * Substitutes all tabs for spaces in {@param input}
 * @param input Text
 * @return Text with all spaces
 */
char *detab(const char input[]) {
    int detabLength = 0, initialLength = 0;

    STRING_LEN(initialLength, input);
    // Find total needed detabbed length
    for (int i = 0; i < initialLength; ++i)
        detabLength = (input[i] != '\t') ? (detabLength + 1) : (detabLength + 4);


    // Define variable for index shift
    int shift = 0;
    // Allocate new string
    char *result = ALLOCATE(detabLength + 1);
    // Fill string with characters
    for (int i = 0; i < initialLength; ++i) {
        if (input[i] != '\t') result[shift++] = input[i];
        else {
            for (int l = shift; l <= shift + 3; l++) {
                result[l] = ' ';
            }
            shift += 4;
        }
    }

    result[detabLength] = '\0';
    result = realloc(result, detabLength * sizeof(char));
    return result;
}

/**
 * Substitutes all spaces that could be tabs for tabs in {@param input}
 * @param input Text
 * @return Text with tabs where possible
 */
char *entab(const char input[]) {
    int spaceCount = 0;
    int length = 0;
    STRING_LEN(length, input);
    char *result = ALLOCATE(length);
    for (int i = 0; i < length; ++i) result[i] = input[i];

    for (int i = 0; i < length; i++) {
        if (result[i] == ' ')
            spaceCount++;
        if (result[i] != ' ')
            spaceCount = 0;
        if (spaceCount == 4) {
            i -= 3;
            length -= 3;
            result[i] = '\t';
            for (int t = i + 1; t < length; t++)
                result[t] = result[t + 3];
            spaceCount = 0;
            result[length] = '\0';
        }
    }

    return result;
}

/**
 * Fold {@param input} into several lines with length {@param n} upscaled to the nearest space
 * @param n Max length
 * @param input Text to fold
 * @return Folded text
 */
char *enter(int n, const char input[]) {
    int length = 0;
    STRING_LEN(length, input);
    char *result = ALLOCATE(length);
    for (int i = 0; i < length; ++i)
        result[i] = input[i];


    int i = 0;
    int location, spaceIndex = 0;
    if (length >= n) {
        i = 0;
        location = 0;
        while (i < length) {
            while (result[i] != ' ') {
                ++location;
                ++i;
            }
            spaceIndex = i;

            if (location >= n) {
                result[spaceIndex] = '\n';
                location = 0;
            }
            ++location;
            ++i;
        }
    }

    result[length] = '\0';
    return result;
}

/**
 * Deletes all C-style comments from {@param input}
 * @param input C code to delete comments in
 * @return Clean code
 */
char *flush(const char input[]) {

    int length = 0;
    STRING_LEN(length, input);

    char *result = ALLOCATE(length);
    int currentIndex = 0;

    for (int i = 0; input[i] != '\0'; ++i) {

        if (input[i] == '/' && input[i + 1] == '*') {
            i += 2;
            while (input[i] != '*' || input[i + 1] != '/') ++i;
            ++i;
            continue;
        }

        // When single-line comment found, skip characters until a new line appears
        if (input[i] == '/' && input[i + 1] == '/') {
            while (input[i] != '\n') ++i;
            continue;
        }

        result[currentIndex] = input[i];
        ++currentIndex;
    }

    result[currentIndex] = '\0';
    return result;
}

/**
 * Converts hexadecimal representation of a number to its decimal form
 * @param s Hexadecimal string
 * @return Integer representation
 */
int htoi(const char s[]) {

    int length = 0;
    STRING_LEN(length, s);

    int result = 0;
    int offset = (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) ? 2 : 0, power = 0, temp = 0;
    for (int i = length - 1; i >= offset; --i) {
        if (s[i] - '0' >= 0 && s[i] - '9' <= 0)
            temp = s[i] - '0';
        else if (s[i] - 'A' >= 0 && s[i] - 'F' <= 0)
            temp = s[i] - 'A' + 10;
        else if (s[i] - 'a' >= 0 && s[i] - 'f' <= 0)
            temp = s[i] - 'a' + 10;
        else
            return 0;

        result += pow(16, power) * temp;
        ++power;
    }

    return result;

}

/**
 * Deletes all character occurrences from {@param s1} with pattern of {@param s2}
 * @param s1 Input string
 * @param s2 Characters to delete
 * @return Result string wjth deleted characters
 */
char *squeeze(const char s1[], const char s2[]) {
    int contains = 0;

    int firstLength = 0, secondLength = 0;
    STRING_LEN(firstLength, s1);
    STRING_LEN(secondLength, s2);
    char *result = ALLOCATE(firstLength);

    int currentIndex = 0;
    for (int i = 0; i < firstLength; ++i) {
        contains = 0;
        for (int j = 0; j < secondLength; ++j) {
            if (s2[j] == s1[i]) {
                contains = 1;
                break;
            }
        }
        if (!contains) result[currentIndex++] = s1[i];
    }

    return result;

}

/**
 * Finds and returns index in {@param s1} of first occurrence of any character in {@param s2}
 * @param s1 String to search character in
 * @param s2 String - pattern for search
 * @return Index of the first element
 */
int any(const char s1[], const char s2[]) {

    int firstLength = 0, secondLength = 0;
    STRING_LEN(firstLength, s1);
    STRING_LEN(secondLength, s2);

    for (int i = 0; i < firstLength; ++i) {
        for (int j = 0; j < secondLength; ++j) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }

    return -1;

}

/**
 * Classic binary search, like in the book
 * @param x Element to find
 * @param v Array to find element in
 * @param n Length of array
 * @return Index of element found, -1 if none
 */
int binsearch_unoptimized(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/**
 * Classic binary search, optimized version
 * @param x Element to find
 * @param v Array to find element in
 * @param n Length of array
 * @return Index of element found, -1 if none
 */
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;
    while (low <= high && x != v[mid]) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}

/**
 * Converts all escape sequences in {@param from} to human-readable form in {@return char}
 * @param from Input string to convert escape characters within
 * @return String with human-readable escape charaters
 */
char *escape(const char from[]) {

    int length = 0;
    STRING_LEN(length, from);
    char *result = ALLOCATE(length);

    int i = 0, j = 0;
    while (from[i]) {
        switch (from[i]) {

            // Alert
            case '\a':
                result[j++] = '\\';
                result[j] = 'a';
                break;

                // Backspace
            case '\b':
                result[j++] = '\\';
                result[j] = 'b';
                break;

                // Formfeed
            case '\f':
                result[j++] = '\\';
                result[j] = 'f';
                break;

                // Newline
            case '\n':
                result[j++] = '\\';
                result[j] = 'n';
                break;

                // Return
            case '\r':
                result[j++] = '\\';
                result[j] = 'r';
                break;

            case '\t':
                result[j++] = '\\';
                result[j] = 't';
                break;

                // Vertical tab
            case '\v':
                result[j++] = '\\';
                result[j] = 'v';
                break;

                // Backslash
            case '\\':
                result[j++] = '\\';
                result[j] = '\\';
                break;

                // Question mark
            case '\?':
                result[j++] = '\\';
                result[j] = '\?';
                break;

                // Single quote
            case '\'':
                result[j++] = '\\';
                result[j] = '\'';
                break;

                // Double quote
            case '\"':
                result[j++] = '\\';
                result[j] = '\"';
                break;

                // Not an escape character, just copy
            default:
                result[j] = from[i];
                break;
        }
        ++i;
        ++j;
    }

    // Null-terminated string
    result[j] = '\0';

    return result;
}

/**
 * Converts integer to its string representation
 * @param n Integer to convert
 * @return String with integer
 */
char *itoa(int n) {

    char *result = ALLOCATE(33);

    int negative = n < 0 ? 1 : 0;
    if (negative) n = -n;
    int k = 0;
    do {
        result[k++] = (char) (n % 10 + '0');
    } while ((n /= 10) > 0);
    if (negative) result[k++] = '-';
    result[k] = '\0';

    int len = 0;
    STRING_LEN(len, result);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char c = result[i];
        result[i] = result[j];
        result[j] = c;
    }

    return result;

}

/**
 * Converts integer number {@param n} into the string representation of base {@param b}
 * @param n Number to convert
 * @param b Base
 * @return String with represented number
 */
char *itob(int n, int b) {

    if (b < 2 || b > 36) return "Invalid base\n";

    char *result = ALLOCATE(33);

    int m, negative;
    negative = n < 0 ? 1 : 0;
    if (negative) n = -n;

    int k = 0;
    do {
        m = n % b;
        if (m < 10) {
            result[k++] = (char) (m + '0');
        } else {
            result[k++] = (char) (m + 'a' - 10);
        }
    } while ((n /= b) > 0);

    if (negative)
        result[k++] = '-';
    result[k] = '\0';

    int len = 0;
    STRING_LEN(len, result);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char c = result[i];
        result[i] = result[j];
        result[j] = c;
    }

    return result;

}

/**
 * Finds first rightmost occurrence of {@param t} in {@param s} and {@return int} index of the character, -1 if none
 * @param s String to search within
 * @param t Character to search in the string
 * @return Index of the first occurrence of the character, -1 if none
 */
int strrindex(const char s[], const char t) {

    int length = 0;
    STRING_LEN(length, s);
    int index = -1;

    for (int i = 0; i < length; ++i)
        if (s[i] == t)
            index = i;

    return index;

}
