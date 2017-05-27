//
//  main.c
//  labaAsA
//
//  Created by Георгий Фалилеев on 20.05.17.
//  Copyright © 2016 Георгий Фалилеев. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <mm_malloc.h>
#include <time.h>

unsigned long int comp = 0, moves = 0;
double T;
int kol;

// Cтруктура чисел
typedef struct pack
{
    double a;
    long int num;
} p;
// Бинарное дерево
struct bin_tree {
    long int data;
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;

/*СОРТИРОВКИ*/
void bubble(long int n, p *pack);
void insertion(long int n, p *pack);
void quickA(p *pack, long int low, long int high);

/*Поиски*/
int interpolation(int a, int n, p *pack);
int linear(long int a, int n, p *pack);

void insert(node ** tree, long int val);
node* search(node ** tree, long int val);

void createmas(p *pack, int n);//Генерация чисел
int openfiles(p *pack, int n);//Открытие файлов
void handwrite(p *pack, int n);//Ввод элементов вручную

void originalSave(p *pack, int n, long int *originalArray);//Сохранение неотсортированной структуры
void originalDownload(p *pack, int n, long int *originalArray);// Загрузка неостортированной структуры








int main(int argc,char *argv[])
{
    node *root = NULL, *min;
    
    long int *originalArray;
    long int key;
    long int k;
    double Tstart,Tend;
    int inputinput, file, i;
    long int value;
    int inter;
    printf("Введите размер: ");
    scanf("%i", &kol);
    p *pack;
    pack=(struct pack*)malloc(kol*sizeof(struct pack));
    originalArray = (long int*)malloc(kol * sizeof(long int));
    printf("1. Генерация чисел.\n2. Открытие файла.\n3. Ручной ввод чисел.\n");
    scanf("%d",&inputinput);
    switch (inputinput) {
        case 1:{
            printf("Идет генерация чисел...\n");
            createmas(pack, kol);
            printf("Генерация чисел завершена...\n");
            //Для просмотра сгенерированного списка
            /*for (i=0; i<s; i++) {
                printf("%lu\n", pack[i].num);
            }*/
            break;
        }
        case 2: {
            file = openfiles(pack, kol);
            if (file == -1) {
                printf("Ошибка при открытии файла.\n");
                return 0;
            }
            break;
        }
        case 3: {
            handwrite(pack, kol);
            printf("Массив заполнен\n");
            break;
        }
        default: {
            printf ("Ошибка\n");
            return (0);
            break;
        }
    }
    originalSave(pack, kol, originalArray);
    printf("СОРТИРОВКИ:\n");
    

    printf("1. Сортировка вставками.\n");
    Tstart = clock();
    insertion (kol, pack);
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
   
    
    printf("2. Быстрая сортировка.\n");
    originalDownload(pack, kol, originalArray);
    Tstart = clock();
    quickA(pack, 0, kol-1);
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
    
    
    printf("3. Сортировка обменами.\n");
    originalDownload(pack, kol, originalArray);
    Tstart = clock();
    bubble(kol, pack);
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
    
    //Для просмотра отсортированного массива
    /*for (i=0; i<s; i++) {
        printf("%lu\n", pack[i].num);
    }*/
    key = pack[kol-1].num;
    
    printf("4. Сортировка деревом.\n");
    originalDownload(pack, kol, originalArray);
    Tstart = clock();
    for(k=0; k<kol-1; k++) {
        value = pack[k].num;
        insert(&root, value);
    }
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
    
    printf("ПОИСКИ НАИБОЛЬШЕГО ЭЛЕМЕНТА В ОТСОРТИРОВАННОМ МАССИВЕ\n");
    printf("Элементы для поиска равен %lu\n", key);
    quickA(pack, 0, kol-1);
    
    printf("Поиск деревом\n");
    Tstart = clock();
    min = search(&root, key);
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("Искомая ветка: %lu\n", min->data);
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
   
    
    
    printf("Последовательный поиск\n");
    Tstart = clock();
    k = linear(key, kol, pack);
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("Индекс элемента равен: %ld\n", k);
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
    quickA(pack, 0, kol-1);
    
    
    printf("Интерполяционный поиск\n");
    Tstart = clock();
    inter = interpolation(key,kol,pack);
    Tend=clock();
    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
    printf("Индекс элемента равен: %d\n", inter);
    printf("\nЗатраченное время на сортировку:  %lf sec",T);
    printf("\nКоличество перемещений: [%lu]", moves);
    printf("\nКоличество сравнений: [%lu]\n", comp);
    printf("----------------------------------\n");
    moves=0;
    comp=0;
    T = 0;
    return 0;
}
int interpolation(int a, int n, p *pack) {
    int lo = 0, hi = (n - 1);
    
    while (lo <= hi && a >= pack[lo].num && a <= pack[hi].num)
    {
        int pos = lo + (((double)(hi-lo)/((pack[hi].num-pack[lo].num)))*(a - pack[lo].num));
        
        if (pack[pos].num == a) {
            comp++;
            return pos;
        }
        if (pack[pos].num < a) {
            lo = pos + 1;
            comp++;
        }
        else {
            hi = pos - 1;
            comp++;
        }
        
        moves++;
    }
    return -1;
}

void insert(node ** tree, long int val) {
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        comp++;
        return;
    }
    
    if(val <= (*tree)->data)
    {
        insert(&(*tree)->left, val);
        comp++;
        moves++;
    }
    else if(val >= (*tree)->data)
    {
        insert(&(*tree)->right, val);
        comp++;
        moves++;
    }
    
}

void print_inorder(node * tree) {
    if (tree)
    {
        print_inorder(tree->left);
        printf("[%lu]",tree->data);
        print_inorder(tree->right);
    }
}


node* search(node ** tree, long val) {
    if(!(*tree))
    {
        comp++;
        return NULL;
    }
    
    if(val < (*tree)->data)
    {
        comp++;
        moves++;
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        comp++;
        moves++;
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        comp++;
        return *tree;
    }
    return *tree;
}

void bubble(long int n, p *pack) {
    unsigned long int i, j, tmp;
    for (i=0; i<n-1; i++) {
        for (j=0; j<n-(1+i); j++) {
            if(pack[j].num > pack[j+1].num) {
                tmp = pack[j].num;
                pack[j].num = pack[j+1].num;
                pack[j+1].num = tmp;
                comp++;
            }
            moves++;
            
        }
    }
}

void insertion(long int n, p *pack) {
    unsigned long int newElement;
    int location,i;
    for ( i = 1; i < n; i++) {
        newElement = pack[i].num;
        location = i - 1;
        while(location >= 0 && pack[location].num > newElement){
            pack[location+1].num = pack[location].num;
            location = location - 1;
            moves++;
            comp++;
        }
        pack[location+1].num = newElement;
        moves++;
    }
}

void quickA(p *pack, long int low, long int high)
{
    long int l=low,r=high;
    static long int i,sred,min,max;
    p temp;
    min=l;
    max=r;
    for (i=l; i<r; ++i)
    {
        if (pack[i].num > pack[max].num) max=i;
        if (pack[i].num < pack[min].num) min=i;
    }
    sred=(pack[max].num + pack[min].num)/2;
    while (l <= r)
    {
        while (pack[l].num < sred)
        {
            ++l;
            moves++;
        }
        while (pack[r].num > sred)
        {
            --r;
            moves++;
        }
        if (l <= r)
        {
            temp=pack[l];
            pack[l]=pack[r];
            pack[r]=temp;
            --r;
            ++l;
            comp++;
        }
        moves++;
    }
    if (low < r){
        quickA(pack, low, r);
        comp++;
        
    }
    if (high > l) {
        quickA(pack, l, high);
        comp++;
    }
}


int linear(long int a, int n, p *pack) {
    int i ;
    unsigned long int lol;
    for (i=0; i<n; i++) {
        lol = pack[i].num;
        if (a==lol) {
            comp++;
            return i;
        }
        moves++;
    }
    return -1;
}

void createmas (p *pack, int n) {
    int i;
    long int * mas;
    mas = (long int *)malloc(kol * sizeof(long int));
    for ( i = 0; i < kol; i++) {
        mas[i]=rand()%500;
        pack[i].num = mas[i];
        pack[i].a = 1.0;
    }
}

int openfiles(p *pack, int n) {
    int i;
    printf("Введите название файла: ");
    char *fname=(char *)malloc(50);
    scanf("%s",fname);
    FILE *f1=fopen(fname,"rb");
    if(f1==NULL) {
        printf("Error.\n");
        return -1;
    }
    fseek(f1,0,SEEK_SET);
    for (i=0; i<n; i++) {
        fscanf(f1,"%lf,%lu\n",&pack[i].a,&pack[i].num);
    }
    free(fname);
    fclose(f1);
    return 1;
}

void handwrite(p *pack, int n) {
    int i;
    long int * mas;
    mas = (long int *)malloc(kol * sizeof(long int));
    printf("Вводите элементы:\n");
    for ( i = 0; i < kol; i++) {
        scanf("%lu", &mas[i]);
        pack[i].num = mas[i];
        pack[i].a = 1.1;
    }
}

void originalSave(p *pack, int n, long int *originalArray) {
    int i;
    for (i=0; i<n; i++) {
        originalArray[i] = pack[i].num;
    }
}
void originalDownload(p *pack, int n, long int *originalArray) {
    int i;
    for (i=0; i<n; i++) {
        pack[i].num = originalArray[i];
    }
}
