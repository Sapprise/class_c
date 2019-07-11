/*************************************************************************
	> File Name: sleep_select.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年07月09日 星期二 18时08分53秒
 ************************************************************************/
// 倒计时－利用select实现
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void my_sleep(int s, int us) {
    struct timeval timeout;
    timeout.tv_sec = s, timeout.tv_usec = us;
    select(0, NULL, NULL, NULL, &timeout);
    printf("时间到！\n");
}

int main() {
    int s = 0,us = 0;
    printf("请输入需要定时的时间(  )秒, (  )微秒\n");
    scanf("%d %d", &s, &us);
    my_sleep(s, us);
    return 0;
}
