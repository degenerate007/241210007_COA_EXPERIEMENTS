// types of addressing

#include <stdio.h>

int global_var = 50;

int main() {
    int a = 10, b = 20;
    int result = 0;
    // implicit
    result++;
    // immediate
    result = a + 5;
    // direct
    result = global_var;
    // indirect
    int *ptr = &a;
    result = *ptr;
    // register
    result = a + b;
    // register indirect
    int *p = &b;
    result = *p;
    // displacement
    int arr[3] = {1, 2, 3};
    // indexed
    result = arr[1];
    // base + offset
    result = *(arr + 2);
    // relative
    for (int i = 0; i < 3; i++) {
        result += arr[i];
    }
    // stack
    int stack_var = 30;
    result = stack_var;
    printf("result: %d\n", result);
    return 0;
}
