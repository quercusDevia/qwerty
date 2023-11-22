#include "uls.h"

void sort_files(char **arr, int numOfFile) {

	for (int i = 0; i < numOfFile - 1; i++) {
		for (int j = i + 1; j < numOfFile; j++) {
            if (mx_strcasecmp(arr[i], arr[j]) > 0) {
				char *temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

