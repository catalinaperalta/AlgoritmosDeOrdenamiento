//
//  Algoritmos.h
//  Tarea_2_algoritmos
//
//  Created by iCaty on 9/1/15.
//  Copyright (c) 2015 Catalina Peralta. All rights reserved.
//

#ifndef Tarea_2_algoritmos_Algoritmos_h
#define Tarea_2_algoritmos_Algoritmos_h

#include <algorithm>
#include <iterator>
#include <chrono>
#include <cstring>

/**********************************BUBBLE SORT**************************************/
void bubbleSort(int v[], int n)
{
    int temp;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            if (v[j-1] > v[j])
            {
                temp = v[j-1];
                v[j-1] = v[j];
                v[j] = temp;
            }
        }
    }
}

/**********************************COCKTAIL SORT**************************************/
void sSwap( int& a, int& b )
{
    int t = a;
   	a = b; b = t;
}

void cocktailSort(int arr[], int len)
{
    bool notSorted = true;
    while( notSorted )
    {
        notSorted = false;
        for( int a = 0; a < len - 1; a++ )
        {
            if( arr[a] > arr[a + 1] )
            {
                sSwap( arr[a], arr[a + 1] );
                notSorted = true;
            }
        }
        
        if( !notSorted ) break;
        notSorted = false;
        
        for( int a = len - 1; a > 0; a-- )
        {
            if( arr[a - 1] > arr[a] )
            {
                sSwap( arr[a], arr[a - 1] );
                notSorted = true;
            }
        }
    }
}

/**********************************INSERTION SORT**************************************/
void insertionSort(int v[], int n)
{
    int index;
    
    for (int i=1; i < n; i++)
    {
        index = v[i];
        int j = i-1;
        while (j >= 0 && v[j] > index)
        {
            v[j + 1] = v[j];
            j--; }
        v[j+1] = index;
    }
}

/**********************************BUCKET SORT**************************************/
void bucketSort(int a[], const int N)
{
    
    int m = 10001;
    int buckets[m];
    
    for(int i=0; i< m; ++i)
    {
        buckets[i]=0;
    }
    
    for (int i = 0; i < N; ++i)
    {
        ++buckets[a[i]];
    }
    
    for (int i =0, j = 0; j < m; ++j)
    {
        for (int k = buckets[j]; k > 0; --k)
        {
            a[i++] = j;
        }
    }
    
    
}

/**********************************COUNTING SORT**************************************/
void findMinMax(int a[], int N, int& mi, int& max)
{
    mi = 100;
    max = 0;
    
    for( int i = 0; i < N; i++ )
    {
        if( a[i] > max ) max = a[i];
        if( a[i] < mi ) mi = a[i];
    }
    
}


void countingSort( int a[], int N)
{
    int mi, max;
    int z=0;
    findMinMax(a, N, mi, max);
    int nlen = (max-mi)+1;
    int* temp = new int[nlen];
    memset(temp, 0, nlen * sizeof( int ));
    
    for( int i = 0; i < N; i++ )
    {
        temp[a[i] - mi]++;
    }
    
    for( int i = mi; i <= max; i++ )
    {
        while( temp[i - mi] )
        {
            a[z++] = i;
            temp[i - mi]--;
        }
    }
    
    
    delete [] temp;
}

/**********************************MERGE SORT**************************************/
void merge(int v[], int l, int m, int n, int N)
{
    int i, j, k;
    int aux[N];
    
    for(i=m+1;i>l;i--)
        aux[i-1] = v[i-1];
    
    for (j=m; j<n; j++)
        aux[n+m-j] = v[j+1];
    
    for(k=l;k<=n;k++)
        if (!(aux[i]> aux[j]))
            v[k] = aux[i++];
        else
            v[k] = aux[j--];
}

void mergeSort(int v[], int l, int n, int N)
{
    int m = (n+l)/2;
    if (n > l)
    {
        mergeSort (v, l, m, N);
        mergeSort (v, m+1, n, N);
        merge (v, l, m, n, N);
    }
}

/**********************************BINARY TREE SORT**************************************/
struct TreeNodeNum
{
    int data;
    TreeNodeNum* left;
    TreeNodeNum* right;
};
struct TreeNodeChar
{
    char data;
    TreeNodeChar* left;
    TreeNodeChar* right;
};

void insertNumLowToHigh(TreeNodeNum* &root, int newData)
{
    if (root == NULL)
    {
        root = new TreeNodeNum;
        root->data = newData;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    else if (newData > root->data)
    {
        insertNumLowToHigh(root->left, newData);
    }
    else
    {
        insertNumLowToHigh(root->right, newData);
    }
}

void printTreeNumLowToHigh(TreeNodeNum* node)
{
    if (node !=NULL)
    {
        printTreeNumLowToHigh(node->right);
        std::cout << node->data << " ";
        printTreeNumLowToHigh(node->left);
    }
}

void binSortNumLowToHigh(int array[], int size)
{
    TreeNodeNum* root;
    root = NULL;
    
    for (int i = 0; i < size; i++)
    {
        insertNumLowToHigh(root, array[i]);
    }
}

/**********************************RADIX SORT**************************************/
int getMax(int v[], int N)
{
    
    int max = v[0];
    
    for(int i=1; i<N; i++)
    {
        if(v[i]>max)
        {
            max = v[i];
        }
    }
    
    return max;
}

void countSort(int v[], int N, int exp)
{
    int output[N];
    int count[10] = {0};
    
    
    for(int i=0; i<N; i++)
    {
        count[(v[i]/exp)%10]++;
    }
    
    for(int i=1; i<10;i++)
    {
        count[i]+=count[i-1];
    }
    
    for (int i = N-1; i>=0; i--)
    {
        
        output[count[( v[i]/exp ) %10 ] -1] = v[i];
        count[(v[i]/exp)%10]--;
    }
    
    for(int i=0;i<N; i++)
    {
        v[i]=output[i];
    }
}

void radixSort(int v[], int N)
{
    int m = getMax(v, N);
    
    for(int exp = 1; m/exp>0; exp*=10)
    {
        countSort(v, N, exp);
    }
}

/**********************************SHELL SORT**************************************/
void shellSort(int v[], int N)
{
    int temp;
    
    for(int gap= N/2; gap>0; gap/=2)
    {
        for(int i=gap; i<N; i++)
        {
            for(int j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
            {
                temp = v[j];
                v[j]= v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}

/**********************************SELECTION SORT**************************************/
void selectionSort(int v[], int N)
{
    int minimo = 0;
    int temp;
    
    for(int i = 0; i < N-1; i++)
    {
        minimo = i;
        for(int j = i + 1; j < N; j++)
        {
            if (v[minimo] > v[j])
                minimo = j;
        }
        temp = v[minimo];
        v[minimo] = v[i];
        v[i] = temp;
    }
}

/**********************************HEAP SORT**************************************/
template<typename RandomAccessIterator>
void heapSort(RandomAccessIterator begin, RandomAccessIterator end) {
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}
void shift_down(int heap[],int i, int max)
{
    int i_big, c1, c2;
    while(i < max)
    {
        i_big = i;
        c1 = (2*i) + 1;
        c2 = c1 + 1;
        if( c1<max && heap[c1]>heap[i_big] )
            i_big = c1;
        if( c2<max && heap[c2]>heap[i_big] )
            i_big = c2;
        if(i_big == i) return;
        std::swap(heap[i],heap[i_big]);
        i = i_big;
    }
}

void to_heap(int arr[], int N)
{
    int i = (N/2) - 1;
    while(i >= 0)
    {
        shift_down(arr, i, N);
        --i;
    }
}

void heapSort(int arr[], int N)
{
    to_heap(arr, N);
    int end = N - 1;
    while (end > 0)
    {
        std::swap(arr[0], arr[end]);
        shift_down(arr, 0, end);
        --end;
    }
}

/**********************************QUICK SORT**************************************/
void quickSort(int v[], int primero, int ultimo)
{
    int izquierdo = primero;
    int derecho = ultimo;
    int temp;
    
    //Se selecciona pivote
    int pivote = v[primero];
    
    if ( primero < ultimo) // Paso base
    {
        // particion
        while ( izquierdo < derecho)
        {
            while ( (izquierdo < derecho) && !(v[izquierdo] > pivote)) izquierdo++;
            while (v[derecho]> pivote ) derecho--;
            
            if ( izquierdo < derecho) // se intercambian los contenidos
            {
                temp = v[derecho];
                v[derecho] = v[izquierdo];
                v[izquierdo] = temp;
            }
        }
        
        // Se intercambia el pivote con el elemento de la posición derecha
        temp = v[derecho];
        v[derecho] = v[primero];
        v[primero] = temp;
        
        // Paso recursivo
        quickSort ( v, primero, derecho-1);
        quickSort ( v, izquierdo, ultimo);
    }
}

#endif
