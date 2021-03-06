/*
 * This file aims to find median in arrays, with different array conditions
 *     Single sorted arrays
 *     2 sorted arrays of equal sizes
 *     2 sorted arrays of different sized
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Get median of a sorted array
float median(int arr[], int arr_start_idx, int arr_end_idx) {
    // Even array
    int arr_size = arr_end_idx - arr_start_idx + 1;
    if(arr_size % 2 == 0) {
        return (arr[arr_start_idx + arr_size/2] + arr[arr_start_idx + arr_size/2-1])/2;
    } else {
        return arr[arr_start_idx + arr_size/2];
    }
}

//MEDIAN FOR 2 ARRAYS OF UNEQUAL LENGTHS
    // Base cases:
    // The smaller array has only one element
    // Case 0: N = 0, M = 2
    // Case 1: N = 1, M = 1.
    // Case 2: N = 1, M is odd
    // Case 3: N = 1, M is even
    // The smaller array has only two elements
    // Case 4: N = 2, M = 2
    // Case 5: N = 2, M is odd
    // Case 6: N = 2, M is even

// A utility function to find median of two integers
float MO2(int a, int b) {
    return ( a + b ) / 2.0;
}

// A utility function to find median of three integers
float MO3(int a, int b, int c) {
    return a + b + c - max(a, max(b, c)) - min(a, min(b, c));
}

// A utility function to find median of four integers
float MO4(int a, int b, int c, int d) {
    int Max = max( a, max( b, max( c, d ) ) );
    int Min = min( a, min( b, min( c, d ) ) );
    return ( a + b + c + d - Max - Min ) / 2.0;
}
 
// Utility function to find median of single array
float medianSingle(int arr[], int arr_size) {
    if (arr_size == 0)
        return -1;
    if (arr_size%2 == 0)
        return (arr[arr_size/2-1] + arr[arr_size/2])/2;
    return arr[arr_size/2];
}

// This function assumes that arr1 is smaller than or equal to arr2 and returns -1 if both arrays are empty
float getMedian_unequal_array(int arr1[], int arr1_size, int arr2[], int arr2_size) {
    // Case 0:        If smaller array is empty, return median from second array
    if (arr1_size == 0) {
        if (arr2_size == 0)
            return -1;
        else if (arr2_size % 2 == 0)
            return (arr2[arr2_size/2-1] + arr2[arr2_size/2])/2;
        return arr2[arr2_size/2];/* condition */
    }

    // Case 1:        If the smaller array has only one element
    if (arr1_size == 1) {
        // Case 1: If the larger array also has one element
        if (arr2_size == 1) {
            return (arr1[0] + arr2[0])/2;

        // Case 2: If the larger array has odd number of elements, then consider the middle 3 elements of larger array.
        } else if(arr2_size % 2 == 1) {
            int a = arr2[arr2_size/2 - 1];
            int b = arr2[arr2_size/2];
            int c = arr2[arr2_size/2 + 1];

            if (arr1[0] < a)
                return (a+b)/2;
            else if (arr1[0] > a && arr1[0] < b)
                return (arr1[0] + b)/2;
            else if (arr1[0] > b && arr1[0] < c)
                return (arr1[0] + b)/2;
            else
                return (b+c)/2;

        // Case 3: If the larger array has even number of element, then consider the middle 2 elements of larger array.
        } else {
            int a = arr2[arr2_size/2 - 1];
            int b = arr2[arr2_size/2];

            if (arr1[0] < a)
                return a;
            else if (arr1[0] > a && arr1[0] < b)
                return arr1[0];
            else
                return b;
        }
    }

    // Case 4: If the smaller array has two elements
    else if (arr1_size == 2) {
        // Case 4: If the larger array also has two elements, find median of 4 elements
        if (arr2_size == 2) {
            int Max = max(arr1[0], max(arr1[1], max(arr2[0], arr2[1])));
            int Min = min(arr1[0], min(arr1[1], min(arr2[0], arr2[1])));
            return (arr1[0] + arr1[1] + arr2[0] + arr2[1] - Max - Min)/2;
        }

        // Case 5: If the larger array has odd number of elements, then median will be one of the following 3 elements
        // 1. Middle element of larger array
        // 2. Max of first element of smaller array and element just before the middle in bigger array
        // 3. Min of second element of smaller array and element just after the middle in bigger array
        else if (arr2_size % 2 == 1) {
            int a = arr2[arr2_size/2];
            int b = max(arr1[0], arr2[arr2_size/2 - 1]);
            int c = min(arr1[1], arr2[arr2_size/2 + 1]);
            return a + b + c - max(a, max(b, c)) - min(a, min(b, c));

        // Case 6: If the larger array has even number of elements,
        // then median will be one of the following 4 elements
        // 1) & 2) The middle two elements of larger array
        // 3) Max of first element of smaller array and element just before the first middle element in bigger array
        // 4. Min of second element of smaller array and element just after the second middle in bigger array
        } else {
            int a = arr2[arr2_size/2];
            int b = arr2[arr2_size/2 - 1];
            int c = max(arr1[0], arr2[arr2_size/2 - 2]);
            int d = min(arr1[1], arr2[arr2_size/2 + 1]);
            int Max = max( a, max( b, max( c, d ) ) );
            int Min = min( a, min( b, min( c, d ) ) );

            return ( a + b + c + d - Max - Min ) / 2.0;
        }
    }

    int idxA = ( arr1_size - 1 ) / 2;
    int idxB = ( arr2_size - 1 ) / 2;

    // If A[idxA] <= B[idxB], then median must exist in A[idxA....] and B[....idxB]
    if (arr1[idxA] <= arr2[idxB] )
        return getMedian_unequal_array(arr1 + idxA, arr1_size/2 + 1, arr2, arr2_size - idxA );

    // If A[idxA] > B[idxB], then median must exist in A[...idxA] and B[idxB....]
    return getMedian_unequal_array(arr1, arr1_size/2 + 1, arr2 + idxA, arr2_size - idxA );
}

void median_test(int arr1[], int arr1_size, int arr2[], int arr2_size) {
    int arr1_index = 0;
    int arr2_index = 0;

    int median_index = 0;

    while(median_index < (arr1_size + arr2_size)/2) {

        if((arr1[arr1_index] < arr2[arr2_index]) && (arr1_index < arr1_size)) {
            arr1_index++;
            median_index++;
            if(median_index + 1 == (arr1_size + arr2_size)/2) {
                cout << arr1[arr1_index] << endl;
            }
        } else if((arr2[arr2_index] < arr1[arr1_index]) && (arr2_index < arr2_size)) {
            arr2_index++;
            median_index++;
            if(median_index + 1 == (arr1_size + arr2_size)/2) {
                cout << arr1[arr1_index] << endl;
            }
        } else {
            cout << "Could not find median" << endl;
            return;
        }
    }
}

// Median of 2 equal size sorted array
float getMedianEqualArray(int arr1[], int arr1_start_idx, int arr1_end_idx, int arr2[], int arr2_start_idx, int arr2_end_idx) {
    // return -1  for invalid input
    int arr1_size = arr1_end_idx - arr1_start_idx + 1;
    int arr2_size = arr2_end_idx - arr2_start_idx + 1;

    if(arr1_size <= 0 || arr2_size <= 0) {
        return -1;
    }

    if(arr1_size == 1 && arr2_size == 1) {
        return (arr1[arr1_start_idx] + arr2[arr2_start_idx])/2;
    }

    if(arr1_size == 2 && arr2_size == 2) {
        float curr_max = max(arr1[arr1_start_idx], arr2[arr2_start_idx]);
        float curr_min = min(arr1[arr1_end_idx], arr2[arr2_end_idx]);
        float median = (curr_max + curr_min) / 2;
        return median;
    }

    float arr1_median = median(arr1, arr1_start_idx, arr1_end_idx);    // median of the first array
    float arr2_median = median(arr2, arr2_start_idx, arr2_end_idx);    // median of the second array

    // If medians are equal, then we have found our answer
    // Return either m1 or m2
    if(arr1_median == arr2_median) {
        return arr1_median;
    }

    int arr1_mid_idx = (arr1_start_idx + arr1_end_idx)/2;
    int arr2_mid_idx = (arr2_start_idx + arr2_end_idx)/2;

    // m1 < m2 then median must exist in arr1[m1....] and arr2[....m2]
    // m1 > m2 then median must exist in arr1[....m1] and arr2[m2....]
    if(arr1_median < arr2_median) {
        return getMedianEqualArray(arr1, arr1_mid_idx, arr1_end_idx, arr2, arr2_start_idx, arr2_mid_idx);
    } else {
        return getMedianEqualArray(arr1, arr1_start_idx, arr1_mid_idx, arr2, arr2_mid_idx, arr2_end_idx);
    }
}

void medianSortedArraySameSize() {
    int arr1[] = {1, 2, 3, 5, 6};
    int arr2[] = {4, 6, 8, 9, 10};
    int arr1_size = sizeof(arr1)/sizeof(arr1[0]);
    int arr2_size = sizeof(arr2)/sizeof(arr2[0]);

    int arr1_start_idx = 0;
    int arr1_end_idx = arr1_size - 1;
    int arr2_start_idx = 0;
    int arr2_end_idx = arr2_size - 1;

    if(arr1_size == arr2_size) {
        cout << "Median is: " << getMedianEqualArray(arr1, arr1_start_idx, arr1_end_idx, arr2, arr2_start_idx, arr2_end_idx) << endl;
    } else {
        cout << "Doesn't work for arrays of unequal size";
    }
    return;
}

int main() {

    /*
     * Arrays of same size
     * Time complexing: O(log(min(n,m))) where n and m are lengths of the arrays
     * Space Complexity: O(1)
     */
    medianSortedArraySameSize();

    //int arr1[] = {900};
    //int arr2[] = {5, 8, 10, 20};

    //int arr1_size = sizeof(arr1)/sizeof(arr1[0]);
    //int arr2_size = sizeof(arr2)/sizeof(arr2[0]);

    //if (arr1_size > arr2_size)
    //    cout << "Median is: " << getMedian_unequal_array(arr2, arr2_size, arr1, arr1_size) << endl;
    //else
    //    cout << "Median is: " << getMedian_unequal_array(arr1, arr1_size, arr2, arr2_size) << endl;

    //median_test(arr1, arr1_size, arr2, arr2_size);
    return 0;
}
