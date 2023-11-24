#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count){
     int left = 0;
     int right = size - 1;
     int mid = (left + right) / 2;

     while(left <= right){
         *count += 1;

         if(mx_strcmp(arr[mid], s) == 0){
             return mid;
         }

         else if(mx_strcmp(arr[mid], s) > 0){
             right = mid -1;
         
	 }

         else if(mx_strcmp(arr[mid], s) < 0){
             left = mid + 1;
         }

         mid = (left + right) / 2;
    }
    
     *count = 0;
     return -1;
}

