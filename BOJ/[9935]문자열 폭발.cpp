#include <iostream>
#include <cstdio>

using namespace std;
char str[1000001];
int strLen = 0;
char target[37];
int targetLen = 0;
int tar_index[37];
char resultStr[1000001];
int tCnt[1000001];
int resultLen = 0;

void cal_target() {
    tar_index[0] = -1;
    for (int i = 1; i < targetLen; i++) {
        int j = tar_index[i - 1];
        while ((tar_index[i] != tar_index[j + 1]) && (j >= 0)) {
            j = tar_index[j];
        }
        if (target[i] == target[j + 1]) {
            tar_index[i] = j + 1;
        }
        else {
            tar_index[i] = -1;
        }
    }
}

void explode() {
    int t = 0;
    int i = 1;
    resultStr[0] = str[0];
    resultLen = 1;
    while (i <= strLen) {
        char c = resultStr[resultLen - 1];
        //printf("%d %d %c %c ", i, t, c, target[t]);
        if (c == target[t]) {
            t++;
            if (t == targetLen) {
                resultLen -= targetLen;
                t = resultLen > 0 ? tCnt[resultLen - 1] : 0;
            }
            resultStr[resultLen++] = str[i++];
            tCnt[resultLen - 2] = t;
        }
        else if (t == 0) {
            resultStr[resultLen++] = str[i++];
            tCnt[resultLen - 2] = t;
        }
        else {
            t = tar_index[t - 1] + 1;
        }

        //printf("%d %d\n", t, tCnt[resultLen - 2]);
    }
}

int main()
{
    char input;
    while ((input = getchar()) != '\n') {
        str[strLen++] = input;
    }
    while ((input = getchar()) != '\n') {
        target[targetLen++] = input;
    }
    str[strLen] = target[targetLen] = '\0';
    cal_target();
    explode();
    if (resultLen == 1) {
        printf("FRULA");
    }
    else {
        for (int i = 0; i < resultLen - 1; i++) {
            printf("%c", resultStr[i]);
        }
    }
}

