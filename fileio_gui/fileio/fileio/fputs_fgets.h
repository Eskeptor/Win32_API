#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fputs_fgets()
{
	char* FILE_NAME = "fputs_fgets.txt";
	char str[BUFFER] = { 0, };
	FILE* file;
	errno_t err = fopen_s(&file, FILE_NAME, "w+");

	if (err != 0)
	{
		printf("%s 을(를) 열 수 없습니다.\n", FILE_NAME);
		exit(1);
	}

	char* cat_str = NULL;
	int cat_length = 0;
	fputs("[fputs & fgets]\n", stdout);
	while (1)
	{
		fputs("입력(종료: \\): ", stdout);
		scanf_s("%[^\n]s", str, BUFFER);
		while (getchar() != '\n');

		if (str[0] == '\\')
			break;

		if (strlen(str) >= 96)
		{
			cat_length = BUFFER + 4;
			cat_str = (char*)malloc(sizeof(char) * cat_length);
			strcpy_s(cat_str, cat_length, str);
			strcat_s(cat_str, BUFFER, "\n");
			fputs(cat_str, file);
			free(cat_str);
		}
		else
		{
			strcat_s(str, BUFFER, "\n");
			fputs(str, file);
		}
	}
	fflush(file);
	rewind(file);
	printf("\n\n");
	while (1)
	{
		fgets(str, BUFFER, file);
		if (feof(file))
			break;
		fputs("출력: ", stdout);
		fputs(str, stdout);
	}

	fclose(file);
}