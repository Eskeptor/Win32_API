#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAN 'M'
#define WOMAN 'W'
#define TRUE 1
#define FALSE 0

typedef int BOOL;
typedef struct _POINT
{
	int x;
	int y;
}POINT;

void freads_fwrite()
{
	char* FILE_NAME = "freads_fwrite.txt";
	FILE* file;
	errno_t err = fopen_s(&file, FILE_NAME, "wb+");

	if (err != 0)
	{
		printf("%s ��(��) �� �� �����ϴ�.\n", FILE_NAME);
		exit(1);
	}

	puts("[fread_s & fwrite]");
	POINT point;
	char tmp[BUFFER] = { 0, };
	int idx = 0;
	while (1)
	{
		printf("<Point %d ���� �Է�(����: \\)>\n", idx + 1);
		printf("x��ǥ(����): ");
		scanf_s("%s", tmp, BUFFER);
		while (getchar() != '\n');
		if (tmp[0] == '\\')
			break;
		point.x = atoi(tmp);

		printf("y��ǥ(����): ");
		scanf_s("%s", tmp, BUFFER);
		while (getchar() != '\n');
		if (tmp[0] == '\\')
			break;
		point.y = atoi(tmp);

		fwrite(&point, sizeof(POINT), 1, file);
		idx++;
	}
	fflush(file);
	rewind(file);
	idx = 0;
	printf("\n\n");
	while (1)
	{
		fread_s(&point, sizeof(POINT), sizeof(POINT), 1, file);
		if (feof(file))
			break;
		printf("<Point %d ���� ���>\n", ++idx);
		printf("x��ǥ(����): %d\n", point.x);
		printf("y��ǥ(����): %d\n", point.y);
	}

	fclose(file);
}