/*************************************************************************
	> File Name: p1.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年04月20日 星期六 15时13分15秒
 ************************************************************************/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if(n == 0) {
    printf("FOOLISH\n");
    }else if(n < 60) {
    printf("FAIL\n");
    }else if(n < 75) {
    printf("MEDIUM\n");
    }else if(n <= 100) {
    printf("GOOD\n");
    }
    return 0;
}
