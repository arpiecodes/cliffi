#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple function that adds two integers
int add(int a, int b) {
    return a + b;
}

// Function that concatenates two strings
// Note: This function returns a pointer to a static buffer for simplicity. Not thread-safe.
const char* concat(const char* a, const char* b) {
    static char result[256];
    strncpy(result, a, sizeof(result) - 1);
    strncat(result, b, sizeof(result) - strlen(result) - 1);
    return result;
}

// Function that multiplies two floating-point numbers
double multiply(double a, double b) {
    return a * b;
}

// A function that takes a pointer to an integer, increments it, and returns the result
int increment_at_pointer(int* a) {
    if (a) {
        (*a)++;
        return *a;
    }
    return 0;
}

int* get_array_of_int(int a, size_t size) {
    int* arr = calloc(size, sizeof(int));
    for (size_t i = 0; i < size; i++) {
        arr[i] = a;
    }
    return arr;
}

// A function that returns a static string
const char* get_message() {
    return "Hello, ffitool!";
}

// Struct for demonstration
typedef struct {
    int x;
    double y;
} Point;

// Function that modifies a struct
void modify_point(Point* p, int x, double y) {
    if (p) {
        p->x = x;
        p->y = y;
    }
}

//Function that takes an array of integers and returns the sum
int sum_array(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Function that demonstrates deeper pointer depths
int increment_at_pointer_pointer(int** pp) {
    if(pp && *pp) {
        (**pp)++;
        return **pp;
    }
    return -1;
}

// Function returning a dynamically allocated array of doubles
double* get_array_of_doubles(size_t size) {
    double* arr = (double*) malloc(size * sizeof(double));
    for(size_t i = 0; i < size; ++i) {
        arr[i] = i * 0.5;  // Arbitrary values
    }
    return arr;
}


// Entry point to prevent the compiler from complaining when compiling as a shared library
// This function will not be called; it's just to satisfy the linker.
int main() {
    return 0;
}
