/*************************************************************************
	> File Name: 295.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年08月11日 星期日 10时34分23秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b, b = __temp; \
}


typedef struct {
    int *data;
    int n, size;
} Heap;

void HeapIncrease(Heap *p) {
    p->data = realloc(p->data, p->size * 2 * sizeof(int));
    p->size = p->size * 2;
    return ;
}

Heap *HeapCreate() {
    Heap *p = (Heap *)malloc(sizeof(Heap));
    p->size = 100;
    p->data = (int *)malloc(sizeof(int) * p->size);
    p->n = 0;
    return p;
}

void HeapClear(Head *p) {
    if (p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

int pushHeap(Heap *p, int val, char c) {
    if (p->cnt == p->size) HeapIncrease(p);
    p->data[p->cnt++] = val;
    int ind = p->cnt;
    switch(c) {
        case '>' : 
        while (ind >> 1 && p->data[ind] > p->data[ind >> 1]) {
            swap(p->data[ind], p->data[ind >> 1]);
            ind >>= 1;
        }
        break;
        case '<' : 
        while (ind >> 1 && p->data[ind] < p->data[ind >> 1]) {
            swap(p->data[ind], p->data[ind >> 1]);
            ind >>= 1;
        }
        break;
    }
    return 1;
}


typedef struct {
    Heap *max_heap, *min_heap;
} MedianFinder;

/** initialize your data structure here. */

MedianFinder* medianFinderCreate() {
    MedianFinder *p = (MedianFinder *)malloc(sizeof(MedianFinder));
    p->max_heap = HeapCreate();
    p->min_heap = HeapCreate();
    return p;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
  
}

double medianFinderFindMedian(MedianFinder* obj) {
  
}

void medianFinderFree(MedianFinder* obj) {
    if (obj == NULL) return ;
    HeapClear(obj->max_heap);
    HeapClear(obj->min_heap);
    free(obj);
    return ;
}

