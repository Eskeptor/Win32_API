#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 100

void fprintf_fscanf()
{
	char* FILE_NAME = "fprintf_fscanf.txt";
	char str[BUFFER] = { 0, };
	FILE* file;
	errno_t err = fopen_s(&file, FILE_NAME, "w+");

	if (err != 0)
	{
		printf("%s ��(��) �� �� �����ϴ�.\n", FILE_NAME);
		exit(1);
	}

	puts("[fprintf & fscanf]");
	while (1)
	{
		printf("�Է�(����: \\): ");
		scanf_s("%[^\n]s", str, BUFFER);
		while (getchar() != '\n');
		if (str[0] == '\\')
			break;
		fprintf(file, "%s\n", str);
		fflush(file);
	}
	rewind(file);
	printf("\n\n");
	while (1)
	{
		if (feof(file))
			break;
		fscanf(file, "%s\n", str);
		printf("���: %s\n", str);
	}
	fclose(file);
}