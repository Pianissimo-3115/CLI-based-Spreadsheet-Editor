#include <stdio.h>
#include <math.h>

int std(int* arr, int n) {
    if (n <= 1) return 0;  // Avoid division by zero

    int sum = 0, mean;
    double variance = 0.0;

    // Calculate mean
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    mean = sum / n;
    printf("%d\n",mean);
    // Calculate variance
    for (int i = 0; i < n; i++) {
        variance += (arr[i] - mean) * (arr[i] - mean);
        printf("%f\n",variance);
    }
    printf("%f\n",variance);
    variance /= n;

    // Return integer standard deviation (rounded)
    return (int)round(sqrt(variance));
}


int main(){
    int arr[] = {10, 20};
    int n=2;
    printf("Standard deviation: %d\n", std(arr, n));
    return 0;
}