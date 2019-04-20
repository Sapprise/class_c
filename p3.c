/*************************************************************************
	> File Name: p3.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年04月20日 星期六 15时43分22秒
 ************************************************************************/

#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) != EOF && n != 0) {
        switch(n) {
                    case 1: printf("one\n"); 
                    case 2: printf("two\n"); 
                    case 3: printf("three\n"); break;
                    default: printf("error\n"); 
                
        }

    }
    return 0;
}
