#ifndef STUDENT1_H
#define STUDENT1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct PositionConstraint {
    int element;
    int position;
} PosConstraint;

typedef struct RelativeConstraint {
    int elemA;
    int elemB;
} RelConstraint;

typedef struct ConstraintData {
    PosConstraint* posConstraints;
    size_t numPosConstraints;
    RelConstraint* relConstraints;
    size_t numRelConstraints;
} ConstraintData;

typedef struct CacheElem {
    char key[100];
    long value;
} CacheElem;

void Generate(int* arr, int n, int* curPerm, int depth, 
              char* used, void (*callback)(int*, int));
void PermutationsBacktrack(int arr[], int n, 
                           void (*callback)(int perm[], int n));
void GenerateSwap(int arr[], int n, int depth, 
                  void (*callback)(int perm[], int n));
void PermutationsRecursiveSwap(int arr[], int n,
                               void (*callback)(int perm[], int n));
void QuickSort(int arr[], int left, int right);
void GeneratePermutations(int arr[], int start, int end, 
                          void (*callback)(int perm[], int size));
void PermRecursiveLexicographic(int arr[], int n,
                                void (*callback)(int perm[], int n));
bool CheckConstraint(int partial[], int k, int nextElem, void* data);
void GeneratePerm(int arr[], int n, int depth, int used[], 
                  int curPerm[], bool (*constraint)(int partial[],
                  int k, int next_elem, void* data),
                  void* constraintData, void (*callback)(int perm[], int n));
void PermutationsWithConstraints(int arr[], int n,
                                 bool (*constraint)(int partial[], int k, 
                                 int nextElem, void* data),
                                 void* constraintData,
                                 void (*callback)(int perm[], int n));
long FindInCache(char *key);
void SaveToCache(char *key, long value);
long Factorial(long n);
void Swap(int *a, int *b);
void GenerateUniquePermutations(int arr[], int n, int start, int result[], 
                                void (*callback)(int perm[], int n));
void MultisetPermutations(int arr[], int n, 
                          void (*callback)(int perm[], int n));

#endif  /* STUDENT1_H */ 
