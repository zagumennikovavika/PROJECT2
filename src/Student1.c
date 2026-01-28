#include "Student1.h"


/* 1.1 */
/* A recursive function for generating permutations */
void Generate(int* arr, int n, int* curPerm, int depth, 
              char* used, void (*callback)(int*, int)) {
    if (depth == n) {
        callback(curPerm, n); 
        return;
    }
    for (int i = 0; i < n; ++i) { 
        if (!used[i]) {
            curPerm[depth] = arr[i];
            used[i] = 1;
            Generate(arr, n, curPerm, depth + 1, used, callback);
            used[i] = 0;
        }
    }
}

/* The function of organizing the generation 
of all permutations using backtracking */
void PermutationsBacktrack(int arr[], int n, 
                           void (*callback)(int perm[], int n)) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: incorrect input parameters\n");
        return;
    }
    int* curPerm = (int*)malloc(n * sizeof(int));
    if (curPerm == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    char* used = (char*)calloc(n, sizeof(char));
    if (used == NULL) {
        free(curPerm);
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    Generate(arr, n, curPerm, 0, used, callback);
    free(curPerm);
    free(used);
}


/* 1.2 */
/* A recursive function for generating permutations using the 
in-place exchange method */
void GenerateSwap(int arr[], int n, int depth, 
                  void (*callback)(int perm[], int n)) {
    if (depth >= n) {
        callback(arr, n);
        return;
    }
    GenerateSwap(arr, n, depth + 1, callback);
    for (int i = depth + 1; i < n; ++i) {
        Swap(&arr[depth], &arr[i]);
        GenerateSwap(arr, n, depth + 1, callback);
        Swap(&arr[depth], &arr[i]);
    }
}

/* A function that organizes the recursive generation of permutations */
void PermutationsRecursiveSwap(int arr[], int n,
                               void (*callback)(int perm[], int n)) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: incorrect input parameters\n");
        return;
    }
    GenerateSwap(arr, n, 0, callback);
}


/* 1.3 */
/* Auxiliary quick sort function */
void QuickSort(int arr[], int left, int right) {
    if (left >= right)
        return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            Swap(&arr[i], &arr[j]);  
            i++;
            j--; 
        }
    }
    QuickSort(arr, left, j);
    QuickSort(arr, i, right);
}

/* Recursive generation function for all possible array permutations */
void GeneratePermutations(int arr[], int start, int end, 
                          void (*callback)(int perm[], int size)) {
    if (start == end) {
        callback(arr, end + 1);
        return;
    }
    for (int i = start; i <= end; ++i) {
        Swap(&arr[start], &arr[i]);
        GeneratePermutations(arr, start + 1, end, callback);
        Swap(&arr[start], &arr[i]);
    }
}

/* The main function that organizes the generation 
of all permutations in lexicographic order */
void PermRecursiveLexicographic(int arr[], int n, 
                                void (*callback)(int perm[], int n)) {
    if (arr == NULL || n <= 0) return;
    int* sortArr = malloc(n * sizeof(int));
    if (!sortArr) return;
    memcpy(sortArr, arr, n * sizeof(int));
    QuickSort(sortArr, 0, n - 1);
    GeneratePermutations(sortArr, 0, n - 1, callback);
    free(sortArr);
}




/* 1.4 */
/* The main function of checking the validity of partial solutions */
bool CheckConstraint(int partial[], int k, int nextElem, void* data) {
    (void)partial;  
    ConstraintData* ptr = (ConstraintData*)data;
    for (size_t i = 0; i < ptr->numPosConstraints; ++i) {
        if (ptr->posConstraints[i].element == nextElem && 
            ptr->posConstraints[i].position != k) {
            return false;
        }
    }
    return true;
}


/* The basic recursive function of generating permutations with constraints */
void GeneratePerm(int arr[], int n, int depth, int used[], int curPerm[], 
                  bool (*constraint)(int partial[], int k, int nextElem, void* data), 
                  void* constraintData, 
                  void (*callback)(int perm[], int n)) {
    if (depth >= n) {
        callback(curPerm, n);
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        curPerm[depth] = arr[i];
        
        bool constraint_passed = true;
        if (constraint != NULL) {
            constraint_passed = constraint(curPerm, depth, arr[i], constraintData);
        }
        
        if (constraint_passed) {
            used[i] = 1;
            GeneratePerm(arr, n, depth + 1, used, curPerm, constraint, 
            constraintData, callback);
            used[i] = 0;
        }
    }
}


/* An external interface function for generating permutations with constraints */
void PermutationsWithConstraints(int arr[], int n, 
                                 bool (*constraint)(int partial[], int k, 
                                 int nextElem, void* data), 
                                 void* constraintData, 
                                 void (*callback)(int perm[], int n)) {
    if (arr == NULL || n <= 0) return;
    int* used = calloc(n, sizeof(int));
    int* curPerm = malloc(n * sizeof(int));
    if (!used || !curPerm) {
        free(used);
        free(curPerm);
        return;
    }
    GeneratePerm(arr, n, 0, used, curPerm, constraint, constraintData, callback); 
    free(used);
    free(curPerm);
}





/* 1.5 */

CacheElem cache[1000];
int cacheSize = 0;

/* Auxiliary function for swapping two elements */
void Swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Key search in the cache */
long FindInCache(char *key) {
    for (int i = 0; i < cacheSize; ++i) {
        if (strcmp(cache[i].key, key) == 0) {
            return cache[i].value;
        }
    }
    return -1;
}

/* Saving to the cache */
void SaveToCache(char *key, long value) {
    strcpy(cache[cacheSize].key, key);
    cache[cacheSize++].value = value;
}

/* Factorial (recursive) */
long Factorial(long n) {
    if (n <= 1) return 1;
    return n * Factorial(n - 1);
}


/* Generating unique permutations using memoization */
void GenerateUniquePermutations(int arr[], int n, int start, int result[], 
                                void (*callback)(int perm[], int n)) {
    if (start >= n) {
        callback(result, n);
        return;
    }
    for (int i = start; i < n; ++i) {
        Swap(&result[start], &arr[i]);
        GenerateUniquePermutations(arr, n, start + 1, result, callback);
        Swap(&result[start], &arr[i]);
    }
}

/* The main method of generating permutations */
void MultisetPermutations(int arr[], int n, void (*callback)(int perm[], int n)) {
    QuickSort(arr, 0, n - 1); 
    int* result = malloc(n * sizeof(int)); 
    if (!result) return;
    memcpy(result, arr, n * sizeof(int));
    GenerateUniquePermutations(arr, n, 0, result, callback);
    free(result);
}
