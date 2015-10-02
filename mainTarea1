//
//  main.cpp
//  Tarea_2_algoritmos
//
//  Created by iCaty on 9/1/15.
//  Copyright (c) 2015 Catalina Peralta. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Algoritmos.h"

void llenarArreglo(int a[],int N);
void imprimirArreglo(int a[]);

const unsigned long int N = 10;

int main(int argc, const char * argv[])
{
    int a[N];

    llenarArreglo(a, N);
    
/******************CONSEGUIR TIEMPOS DE EJECUCION DE ALGORITMOS****************************/
    auto begin = std::chrono::high_resolution_clock::now();
    bubbleSort(a, N);
    auto end = std::chrono::high_resolution_clock::now();
    auto bubble = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Bubble: "<<bubble.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    cocktailSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto cocktail = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Cocktail: "<<cocktail.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    insertionSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto insertion = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Insertion: "<<insertion.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    bucketSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto bucket = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Bucket: "<<bucket.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    countingSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto count = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Counting: "<<count.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    mergeSort(a, 0, N-1, N);
    end = std::chrono::high_resolution_clock::now();
    auto merge = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Merge: "<<merge.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    binSortNumLowToHigh(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto binary = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Binary Tree: "<<binary.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    radixSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto radix = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Radix: "<<radix.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    shellSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto shell = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Shell: "<<shell.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    selectionSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto selection = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Selection: "<<selection.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    heapSort(a, N);
    end = std::chrono::high_resolution_clock::now();
    auto heap = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Heap: "<<heap.count()<<std::endl;
    
    llenarArreglo(a, N);
    begin = std::chrono::high_resolution_clock::now();
    quickSort(a, 0, N-1);
    end = std::chrono::high_resolution_clock::now();
    auto quick = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Quick: "<<quick.count()<<std::endl;

    
    return 0;
}

void llenarArreglo(int a[],int N){
    std::ifstream file("/Users/iCaty/Desktop/array.txt");
    if(file.is_open())
    {
        for(int i = 0; i < N; ++i)
        {
            file >> a[i];
        }
    }
}

void imprimirArreglo(int a[])
{
    for(int i = 0; i<N; i++)
    {
        std::cout<<a[i]<<" ";
    }
    std::cout<<std::endl;
}
