/*************************************************************************
	> File Name: phome.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月17日 星期五 21时54分16秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char **env) {
    char string[20] = "./haizei";
    char username[20] = "USER=liujunming";
    for (int i = 0; env[i] != NULL ; i++) {
        if (strcmp(string, argv[0]) == 0 && strcmp(username, env[i]) == 0) {
        printf("hello haizei\n");
        } 
    }

    return 0;
}
