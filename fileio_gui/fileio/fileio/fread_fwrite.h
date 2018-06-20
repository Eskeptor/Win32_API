#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100
#define MAN 'M'
#define WOMAN 'W'
#define TRUE 1
#define FALSE 0

typedef int BOOL;
typedef struct _HUMAN
{
	char name[BUFFER];
	int age;
	char sex;
}HUMAN;

void fread_fwrite()
{
	char* FILE_NAME = "fread_fwrite.txt";
	FILE* file;
	errno_t err = fopen_s(&file, FILE_NAME, "wb+");

	if (err != 0)
	{
		printf("%s 을(를) 열 수 없습니다.\n", FILE_NAME);
		exit(1);
	}

	puts("[fread & fwrite]");
	HUMAN human;
	char tmp[BUFFER] = { 0, };
	int idx = 0;
	while (1)
	{
		printf("<Human %d 정보 입력(종료: \\)>\n", idx + 1);
		printf("이름: ");
		scanf_s("%[^\n]s", tmp, BUFFER);
		while (getchar() != '\n');
		if (tmp[0] == '\\')
			break;
		strcpy_s(human.name, sizeof(tmp) / sizeof(char), tmp);

		printf("나이: ");
		scanf_s("%s", tmp, BUFFER);
		while (getchar() != '\n');
		if (tmp[0] == '\\')
			break;
		human.age = atoi(tmp);

		printf("성별(M, W): ");
		scanf_s("%c", &tmp[0], sizeof(char));
		while (getchar() != '\n');
		if (tmp[0] == '\\')
			break;
		human.sex = tmp[0];

		fwrite(&human, sizeof(HUMAN), 1, file);
		idx++;
	}
	fflush(file);
	rewind(file);
	idx = 0;
	printf("\n\n");
	while (1)
	{
		fread(&human, sizeof(HUMAN), 1, file);
		if (feof(file))
			break;
		printf("<Human %d 정보 출력>\n", ++idx);
		printf("이름: %s\n", human.name);
		printf("나이: %d\n", human.age);
		printf("성별: %c\n", human.sex);
	}

	fclose(file);
}