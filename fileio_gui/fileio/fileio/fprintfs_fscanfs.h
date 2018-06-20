#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 100

void fprintfs_fscanfs()
{
	char* FILE_NAME = "fprintfs_fscanfs.txt";
	char str[BUFFER] = { 0, };
	FILE* file;
	errno_t err = fopen_s(&file, FILE_NAME, "w+");

	if (err != 0)
	{
		printf("%s 을(를) 열 수 없습니다.\n", FILE_NAME);
		exit(1);
	}

	puts("[fprintf_s & fscanf_s]");
	while (1)
	{
		printf("입력(종료: \\): ");
		scanf_s("%[^\n]s", str, BUFFER);
		while (getchar() != '\n');
		if (str[0] == '\\')
			break;
		fprintf_s(file, "%s\n", str);
		fflush(file);
	}
	rewind(file);
	printf("\n\n");
	while (1)
	{
		if (feof(file))
			break;
		fscanf_s(file, "%s\n", str, BUFFER);
		printf("출력: %s\n", str);
	}
	fclose(file);
}