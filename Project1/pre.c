#include <stdio.h>
#include <string.h>

int main()
{
	char names[30][10];
	float gpas[30];
	int count = 0;

	//printf("Please enter student information (name gpa) one line per student.\n");
	//printf("finish input by pressing EOF.\n");

	while (!feof(stdin)) {
        //printf("Student %i: ", count);
		scanf("%s %f", names[count], &gpas[count]);
        count++;
	}
	//printf("\n");

	while (count >= 0) {
        if(gpas[count] >= 3.0)
            printf("%s\n", names[count]);
        count--;
	}

	return 0;
}