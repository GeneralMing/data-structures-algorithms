#include<stdio.h>
#include<stdlib.h>

int main()
{
	char testcases[1000];
	system("gcc ./main.c");
	system("./a.out --test < test_input.txt > test_output.txt");
	FILE* fp;
	fp = fopen("test_output.txt", "r");
	fscanf(fp, "%[^.*\n]s", testcases);
	fclose(fp);
	printf("%s\n", testcases);
	return 0;
}