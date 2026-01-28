#include "Student1.h"

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        printf("Assertion '%s' failed at line %d.\n", #cond, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

#define ASSERT_EQUAL(a, b) ASSERT_TRUE((a) == (b))
#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))
 
static int callbackCount = 0;

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
    printf("!Test PermRecursiveLexicographic() PASSED!\n");
}


void TestCheckConstraint() {
    PosConstraint constraints1[] = {{5, 2}};
    ConstraintData data1 = {
        .posConstraints = constraints1,
        .numPosConstraints = 1,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    int partial1[] = {1, 2, 5};
    ASSERT_TRUE(CheckConstraint(partial1, 2, 5, &data1));
    
    int partial2[] = {1, 5, 3};
    ASSERT_FALSE(CheckConstraint(partial2, 1, 5, &data1));
    
    int partial3[] = {1, 2, 3};
    ASSERT_TRUE(CheckConstraint(partial3, 2, 3, &data1));
    
    PosConstraint constraints2[] = {{1, 0}, {3, 2}};
    ConstraintData data2 = {
        .posConstraints = constraints2,
        .numPosConstraints = 2,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    int partial4[] = {1, 2, 3};
    ASSERT_TRUE(CheckConstraint(partial4, 2, 3, &data2));  
    
    int partial5[] = {3, 2, 1};
    ASSERT_FALSE(CheckConstraint(partial5, 0, 3, &data2)); 
    
   
    ConstraintData empty_cd = {
        .posConstraints = NULL,
        .numPosConstraints = 0,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    int partial6[] = {1, 2, 3, 4};
    ASSERT_TRUE(CheckConstraint(partial6, 3, 4, &empty_cd));
    
    printf("Test CheckConstraint() PASSED!\n");
}


void TestGeneratePerm() {
    int arr[] = {1, 2, 3, 4};
    int n = 4;
    int used[n];
    int curPerm[n];
    memset(used, 0, sizeof(used));
    callbackCount = 0;

    GeneratePerm(arr, n, 0, used, curPerm, NULL, NULL, CountingCallback);
    ASSERT_EQUAL(callbackCount, 24);
    printf("Test GeneratePerm() PASSED!\n");
}


void TestPermutationsWithConstraints() {
    int arr[] = {1, 2, 3};
    int n = 3;
    callbackCount = 0;

    PermutationsWithConstraints(arr, n, NULL, NULL, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    

    PosConstraint pcons = {1, 0};
    ConstraintData cdata = {
        .posConstraints = &pcons,
        .numPosConstraints = 1,
        .relConstraints = NULL,
        .numRelConstraints = 0
    };
    
    callbackCount = 0;
    PermutationsWithConstraints(arr, n, CheckConstraint, &cdata, CountingCallback);

    ASSERT_EQUAL(callbackCount, 2);
    
    printf("Test PermutationsWithConstraints() PASSED!\n");
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
    
    printf("Test Swap() PASSED!\n");
}


void TestGenerateUniquePermutations() {
    int arr[] = {1, 1, 2};
    int n = 3;
    int result[n];
    memcpy(result, arr, n * sizeof(int));
    callbackCount = 0;

    GenerateUniquePermutations(arr, n, 0, result, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    printf("Test GenerateUniquePermutations() PASSED!\n");
}


void TestMultisetPermutations() {
    int arr[] = {1, 1, 2};
    int n = 3;
    callbackCount = 0;
    MultisetPermutations(arr, n, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    
    int arr2[] = {1, 2, 3};
    callbackCount = 0;
    MultisetPermutations(arr2, 3, CountingCallback);
    ASSERT_EQUAL(callbackCount, 6);
    
    printf("Test MultisetPermutations() PASSED!\n");
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
    TestEdgeCases();           
    TestCacheFunctions();
    
    printf("\nAll tests completed successfully!\n");
    return EXIT_SUCCESS;
}
