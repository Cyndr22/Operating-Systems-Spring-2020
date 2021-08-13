#include <stdio.h>
#include <string.h>

int main()
{
	char names[30][10];
	char temp[10];
	int count = 0;

	//printf("Please enter student names one at a time.\n");
	//printf("finish input by pressing EOF.\n");

	while (!feof(stdin)) {
        //printf("Student %i: ", count);
		scanf("%s", names[count]);
        count++;
	}
	//printf("\n");

	for (int i; i < count; i++) {
		for (int j = i+1; j < count; j++) {
			if(strcmp(names[i], names[j]) > 0) {
				strcpy(temp, names[i]);
				strcpy(names[i], names[j]);
				strcpy(names[j], temp);
			}
		}
	}
	for (int i; i < count; i++) {
        printf("%s\n", names[i]);
	}

	return 0;
}
