/*************************************************************************
	> File Name: p1.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月16日 星期四 18时58分06秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>

struct IP {
    unsigned int num;
    unsigned char ip[4];
}

int is_little() {
    static int a = 1;
    return ((char *)(&a))[0];
}

int main() {
    unsigned int p1,p2,p3,p4;
    scanf("%d.%d.%d.%d", &p1, &p2, &p3, &p4);
    int zheng = 0;
    zheng = p1 * pow(256,3) + p2 * pow(256,2) + p3 * pow(256,1) + p4;
    printf("%d\n", zheng);

    char ip_str[25];
    

    
    return 0;
}
