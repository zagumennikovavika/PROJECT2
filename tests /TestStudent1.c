#include "Student1.h"

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        printf("Assertion '%s' failed at line %d.\n", #cond, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

#define ASSERT_EQUAL(a, b) ASSERT_TRUE((a) == (b))
#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))
 
int callbackCount = 0;

void CountingCallback(int perm[], int n) {
    (void)perm;
    (void)n;    
    callbackCount++;
}

void TestGenerate() {
    int arr[] = {1, 2};
    int n = 2;
    int curPerm[n];  
    char used[n];    
    memset(used, 0, sizeof(used));
    callbackCount = 0;
    Generate(arr, n, curPerm, 0, used, CountingCallback);
    
    ASSERT_EQUAL(callbackCount, 2);
    printf("Test Generate() PASSED!\n");
}

void TestPermutationsBacktrack() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;
    PermutationsBacktrack(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);

    int arr2[] = {42};
    callbackCount = 0;
    PermutationsBacktrack(arr2, 1, CountingCallback);
    ASSERT_EQUAL(callbackCount, 1);
    
    int arr3[] = {1, 1};
    callbackCount = 0;
    PermutationsBacktrack(arr3, 2, CountingCallback);
    ASSERT_EQUAL(callbackCount, 2); 
    printf("Test PermutationsBacktrack() PASSED!\n");
}


void TestGenerateSwap() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;

    GenerateSwap(arr, n, 0, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    printf("Test GenerateSwap() PASSED!\n");
}


void TestPermutationsRecursiveSwap() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;

    PermutationsRecursiveSwap(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    printf("Test PermutationsRecursiveSwap() PASSED!\n");
}

void TestQuickSort() {
    int arr[] = {3, 1, 2};
    int n = 3;
    QuickSort(arr, 0, n - 1);
    ASSERT_EQUAL(arr[0], 1);
    ASSERT_EQUAL(arr[1], 2);
    ASSERT_EQUAL(arr[2], 3);

    int arr2[] = {42};
    QuickSort(arr2, 0, 0);
    ASSERT_EQUAL(arr2[0], 42);
    
    int arr3[] = {3, 1, 3, 2, 1};
    QuickSort(arr3, 0, 4);
    ASSERT_EQUAL(arr3[0], 1);
    ASSERT_EQUAL(arr3[1], 1);
    ASSERT_EQUAL(arr3[2], 2);
    ASSERT_EQUAL(arr3[3], 3);
    ASSERT_EQUAL(arr3[4], 3);

    printf("Test QuickSort() PASSED!\n");
}


void TestGeneratePermutations() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;

    GeneratePermutations(arr, 0, n - 1, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    printf("Test GeneratePermutations() PASSED!\n");
}


void TestPermRecursiveLexicographic() {
    int arr[] = {3, 1, 2};
    int n = 3;
    callbackCount = 0;

    PermRecursiveLexicographic(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    printf("Test PermRecursiveLexicographic() PASSED!\n");
}


void TestCheckConstraint() {
    PosConstraint constraints1[] = {{5, 2}};  
    ConstraintData data1 = {
        .posConstraints = constraints1,
        .numPosConstraints = 1,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    int partial1[] = {1, 2};  
    ASSERT_FALSE(CheckConstraint(partial1, 2, 5, &data1));  
    
    int partial2[] = {1};  
    ASSERT_TRUE(CheckConstraint(partial2, 1, 5, &data1));  
    
    int partial3[] = {1, 2};  
    ASSERT_TRUE(CheckConstraint(partial3, 2, 3, &data1));  

    PosConstraint constraints2[] = {{1, 0}, {3, 2}};
    ConstraintData data2 = {
        .posConstraints = constraints2,
        .numPosConstraints = 2,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    int partial4[] = {1, 2};  
    ASSERT_FALSE(CheckConstraint(partial4, 2, 3, &data2));  
   
    int partial5[] = {3, 2};  
    ASSERT_TRUE(CheckConstraint(partial5, 0, 3, &data2));  
    
    int partial5b[] = {1, 2};  
    ASSERT_FALSE(CheckConstraint(partial5b, 0, 1, &data2)); 
    
    int partial5c[] = {2, 3};  
    ASSERT_TRUE(CheckConstraint(partial5c, 2, 1, &data2));  
    
    ConstraintData empty_cd = {
        .posConstraints = NULL,
        .numPosConstraints = 0,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    int partial6[] = {1, 2, 3};  
    ASSERT_TRUE(CheckConstraint(partial6, 3, 4, &empty_cd));  
    
    RelConstraint relConstraints[] = {{1, 3}};  
    ConstraintData data3 = {
        .posConstraints = NULL,
        .numPosConstraints = 0,
        .relConstraints = relConstraints,
        .numRelConstraints = 1
    };
    
    int partial7[] = {1, 2}; 
    ASSERT_TRUE(CheckConstraint(partial7, 2, 3, &data3));  
   
    int partial8[] = {2};  
    ASSERT_FALSE(CheckConstraint(partial8, 1, 3, &data3));  
    
    int partial9[] = {3};  
    ASSERT_FALSE(CheckConstraint(partial9, 1, 1, &data3));  
    
    int partial10[] = {2};  
    ASSERT_TRUE(CheckConstraint(partial10, 1, 1, &data3));  

    PosConstraint posCons[] = {{2, 1}};      
    RelConstraint relCons[] = {{1, 4}};      
    ConstraintData data4 = {
        .posConstraints = posCons,
        .numPosConstraints = 1,
        .relConstraints = relCons,
        .numRelConstraints = 1
    };
    
    int partial11[] = {1};  
    ASSERT_FALSE(CheckConstraint(partial11, 1, 2, &data4));  
   
    int partial12[] = {3};  
    ASSERT_FALSE(CheckConstraint(partial12, 1, 4, &data4));  
    
    int partial13[] = {2, 1};  
    ASSERT_TRUE(CheckConstraint(partial13, 2, 4, &data4));  
    
    RelConstraint multiRel[] = {{1, 3}, {2, 4}};
    ConstraintData data5 = {
        .posConstraints = NULL,
        .numPosConstraints = 0,
        .relConstraints = multiRel,
        .numRelConstraints = 2
    };
    
    int partial14[] = {1, 3};  
    ASSERT_FALSE(CheckConstraint(partial14, 2, 4, &data5));  
    
    int partial15[] = {2};  
    ASSERT_FALSE(CheckConstraint(partial15, 1, 3, &data5));  
    
    int partial16[] = {1, 2, 3};  
    ASSERT_TRUE(CheckConstraint(partial16, 3, 4, &data5));  
    
    printf("Test CheckConstraint() PASSED!\n");
}


void TestCacheFunctions() {
    char key1[] = "test_key_1";
    long val1 = 12345L;
    SaveToCache(key1, val1);
    
    long found_val = FindInCache(key1);
    ASSERT_EQUAL(found_val, val1);
    
    char key2[] = "test_key_2";
    long val2 = 67890L;
    SaveToCache(key2, val2);
    
    found_val = FindInCache(key2);
    ASSERT_EQUAL(found_val, val2);
    
    found_val = FindInCache(key1);
    ASSERT_EQUAL(found_val, val1);
    
    char nonexistent_key[] = "not_in_cache";
    long missing_val = FindInCache(nonexistent_key);
    ASSERT_EQUAL(missing_val, -1); 
    
    printf("Test FindInCache()/SaveToCache() PASSED!\n");
}


void TestFactorial() {
    ASSERT_EQUAL(Factorial(0), 1);
    ASSERT_EQUAL(Factorial(1), 1);
    ASSERT_EQUAL(Factorial(5), 120);
    ASSERT_EQUAL(Factorial(10), 3628800);
    printf("Test Factorial() PASSED!\n");
}

void TestSwap() {
    int a = 1, b = 2;
    Swap(&a, &b);
    ASSERT_EQUAL(a, 2);
    ASSERT_EQUAL(b, 1);
    
    Swap(&a, &b);
    ASSERT_EQUAL(a, 1);
    ASSERT_EQUAL(b, 2);
    
    a = b = 5;
    Swap(&a, &b);
    ASSERT_EQUAL(a, 5);
    ASSERT_EQUAL(b, 5);

    printf("Test Swap() PASSED!\n");
}

void TestGeneratePerm() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;
    
    int used[n];
    int curPerm[n];
    memset(used, 0, sizeof(used));
    
    GeneratePerm(arr, n, 0, used, curPerm, NULL, NULL, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    printf("Test GeneratePerm() PASSED!\n");
}

void TestPermutationsWithConstraints() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;
    PermutationsWithConstraints(arr, n, NULL, NULL, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    
    PosConstraint posCons[] = {{2, 0}};  
    ConstraintData data = {
        .posConstraints = posCons,
        .numPosConstraints = 1,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    callbackCount = 0;
    PermutationsWithConstraints(arr, n, CheckConstraint, &data, CountingCallback);
    ASSERT_EQUAL(callbackCount, 4);  
    
    printf("Test PermutationsWithConstraints() PASSED!\n");
}

void TestGenerateUniquePermutations() {
    int arr[] = {1, 1, 2};
    int n = 3;
    int result[n];
    memcpy(result, arr, n * sizeof(int));
    callbackCount = 0;

    GenerateUniquePermutations(arr, n, 0, result, CountingCallback);
    ASSERT_EQUAL(callbackCount, 3);
    printf("Test GenerateUniquePermutations() PASSED!\n");
}


void TestMultisetPermutations() {
    int arr[] = {1, 1, 2};
    int n = 3;
    callbackCount = 0;
    MultisetPermutations(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 3);
    
    int arr2[] = {1, 2, 3};
    callbackCount = 0;
    MultisetPermutations(arr2, 3, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    
    printf("Test MultisetPermutations() PASSED!\n");
}

void TestEmptyArray() {
    int arr[] = {};
    int n = 0;
    
    callbackCount = 0;
    PermutationsBacktrack(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 1);
    
    callbackCount = 0;
    PermutationsRecursiveSwap(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 1);
    
    callbackCount = 0;
    PermRecursiveLexicographic(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 1);
    
    callbackCount = 0;
    PermutationsWithConstraints(arr, n, NULL, NULL, CountingCallback);
    ASSERT_EQUAL(callbackCount, 1); 
    
    printf("Test EmptyArray() PASSED!\n");
}

void TestEdgeCases() {
    int one_element[] = {42};
    callbackCount = 0;
    PermutationsBacktrack(one_element, 1, CountingCallback);
    ASSERT_EQUAL(callbackCount, 1); 
    
    int duplicate_arr[] = {7, 7};
    callbackCount = 0; 
    PermutationsBacktrack(duplicate_arr, 2, CountingCallback);
    ASSERT_EQUAL(callbackCount, 2); 
    
    int large_arr[] = {1, 2, 3, 4, 5};
    callbackCount = 0;
    PermutationsBacktrack(large_arr, 5, CountingCallback);
    ASSERT_EQUAL(callbackCount, 120); 
    printf("Test Edge Cases PASSED!\n");
}


int main() {
    printf("Running unit tests:\n\n");
    
    TestSwap();                
    TestFactorial();          
    TestQuickSort();           
    TestCheckConstraint();     
    TestGenerate();           
    TestPermutationsBacktrack();
    TestGenerateSwap();        
    TestPermutationsRecursiveSwap(); 
    TestGeneratePermutations(); 
    TestPermRecursiveLexicographic(); 
    TestGeneratePerm();        
    TestPermutationsWithConstraints();
    TestGenerateUniquePermutations(); 
    TestMultisetPermutations();   
    TestEmptyArray();
    TestEdgeCases();           
    TestCacheFunctions();
    
    printf("\nAll tests completed successfully!\n");
    return EXIT_SUCCESS;
} 
