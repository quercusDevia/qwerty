#include "../inc/uls.h"

void mx_swapStructs(t_manager** t1, t_manager** t2) {
	t_manager* temporaryObj = *t1;
	*t1 = *t2;
	*t2 = temporaryObj;
}

void mx_sortObjs(t_manager ***inp, t_flags** flags, char** argv) {

    t_manager **textOfFile = *inp;
	char* argOfStr = NULL;

	for (int j = 1; argv[j] != NULL; j++) {
		if (argv[j][0] == '-') {
			argOfStr = mx_strjoin(argOfStr, argv[j]);
		}
	}

	bool usedInCycle = false;

	if (argOfStr != NULL) {
		for (int i = 0; argOfStr[i] != '\0'; i++) {

			for (int j = 0; textOfFile[j + 1] != NULL; j++) {

				for (int k = j + 1; textOfFile[k] != NULL; k++) {

					if (argOfStr[i] == 'c') {
						////////
						(*flags)->c = 1;
						(*flags)->u = 0;

						if (((*flags)->l && !(*flags)->t) || ((*flags)->S && !(*flags)->l) || !(*flags)->t) {
							continue;
						}

						struct stat fstBuffer = textOfFile[j]->statistic;
						struct stat secBuffer = textOfFile[k]->statistic;
						////////////////////////////////////////////////
						long int fstTime = fstBuffer.st_ctimespec.tv_sec;
						long int secTime = secBuffer.st_ctimespec.tv_sec;

						if (fstTime < secTime || (fstTime == secTime && mx_strcmp(textOfFile[j]->name, textOfFile[k]->name) > 0)) {
							mx_swapStructs(&textOfFile[j], &textOfFile[k]);
						}

						usedInCycle = true;
					}

					if (argOfStr[i] == 'u') {
						(*flags)->c = 0;
						(*flags)->u = 1;

						if (((*flags)->l && !(*flags)->t) || ((*flags)->S && !(*flags)->l) || !(*flags)->t) {
							///////////
							continue;
						}

						struct stat fstBuffer = textOfFile[j]->statistic;
						struct stat secBuffer = textOfFile[k]->statistic;
						////////////////////////////////////////////////
						long int fstTime = fstBuffer.st_atimespec.tv_sec;
						long int secTime = secBuffer.st_atimespec.tv_sec;

						if (fstTime < secTime || (fstTime == secTime && mx_strcmp(textOfFile[j]->name, textOfFile[k]->name) > 0)) {
							mx_swapStructs(&textOfFile[j], &textOfFile[k]);
						}

						usedInCycle = true;

					}

					if (argOfStr[i] == 'S') {

						struct stat fstBuffer = textOfFile[j]->statistic;
						struct stat secBuffer = textOfFile[k]->statistic;
						////////////////////////////////////////////////
						int size1 = fstBuffer.st_size;
						int size2 = secBuffer.st_size;

						if (size1 < size2 || (fstBuffer.st_size == secBuffer.st_size && mx_strcmp(textOfFile[j]->name, textOfFile[k]->name) > 0)) {
							mx_swapStructs(&textOfFile[j], &textOfFile[k]);
						}

						(*flags)->S = 1;
						usedInCycle = true;
					}

					if (!(*flags)->u && !(*flags)->c && (*flags)->t) {

						struct stat fstBuffer = textOfFile[j]->statistic;
						struct stat secBuffer = textOfFile[k]->statistic;
						////////////////////////////////////////////////
						long int fstTime = fstBuffer.st_mtimespec.tv_sec;
						long int secTime = secBuffer.st_mtimespec.tv_sec;

						if (fstTime < secTime || (fstTime == secTime && mx_strcmp(textOfFile[j]->name, textOfFile[k]->name) > 0)) {
							mx_swapStructs(&textOfFile[j], &textOfFile[k]);
						}

						usedInCycle = true;
					}

				}
			}
		}
	}

	if (!usedInCycle) {
		
		for (int i = 0; textOfFile[i + 1] != NULL; i++) {


			for (int j = i + 1; textOfFile[j] != NULL; j++) {

				if (mx_strcmp(textOfFile[i]->name, textOfFile[j]->name) > 0) {
					mx_swapStructs(&textOfFile[i], &textOfFile[j]);

				}
			}
		}
	}

	if ((*flags)->r) {
		int lengthOfText = 0;

		for (int j = 0; textOfFile[j] != NULL; j++) {
			lengthOfText++;
		}

		for (int j = 0; j < lengthOfText / 2; j++) {
			mx_swapStructs(&textOfFile[j], &textOfFile[lengthOfText - j - 1]);
		}

	}

}
