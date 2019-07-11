/*************************************************************************
	> File Name: my_sleep_pause.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年07月10日 星期三 12时19分29秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void slep() {

}

int main() {
    while(1) {
    signal(SIGALRM, slep);
    int time;
    scanf("%d", &time);
    alarm(time);
        pause();
        printf("时间到\n");
    }
    return 0;
}
