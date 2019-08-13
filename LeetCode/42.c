/*************************************************************************
	> File Name: 42.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年07月17日 星期三 20时33分12秒
 ************************************************************************/

#include <stdio.h>


int trap(int *height, int heightSize) {
    int n = heightSize, ans = 0, top = -1;
    int *stack = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < heightSize; i++) {
        while (top != -1 && height[stack[top]] <= height[i]) {
            if (top >= 1) {
                int w = i - stack[top - 1] - 1;
                int val1 = height[i] - height[stack[top]];
                int val2 = height[stack[top - 1]] - height[stack[top]];
                int h = (val1 < val2 ? val1 : val2);
                ans += h * w;
            }
            top--;
        } 
        stack[++top] = i;
    }
    free(stack);
    return ans;
}
