#include "libmx.h"

int mx_quicksort(char**arr, int left, int right){
    if (!arr){
        return -1;
    }
    if (left >= right){
        return 0;
    }

    char *mid = arr[(left + right) / 2];
    int l, r;
    int count = 0;
    l = left;
    r = right;

    while(l <= r){
        while(mx_strlen(arr[l]) < mx_strlen(mid)){
            l++;
        }

        while(mx_strlen(arr[r]) > mx_strlen(mid)){
            r--;
        }

	if(l <= r){
            if(mx_strlen(arr[l]) != mx_strlen(arr[r])){
		 char *p = arr[l];
                 arr[l] = arr[r];
                 arr[r] = p;
                 count++;
	    }
	    l++;
	    r--;
	}
    }

    if (left < r){
        count += mx_quicksort(arr, left, r);
    }

    if(right > l){
        count += mx_quicksort(arr, l, right);
    }

    return count;
}

