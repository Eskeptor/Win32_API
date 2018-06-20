#include "head.h"


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		fputs("�Ű����� ����", stderr);
		exit(1);
	}

	char arg[ARG_BUFFER] = { 0, };
	strcpy_s(arg, ARG_BUFFER, argv[1]);

	switch (arg[1])
	{
	case FPRINTF_FSCANF:
		fprintf_fscanf();
		break;
	case FPRINTFS_FSCANFS:
		fprintfs_fscanfs();
		break;
	case FREAD_FWRITE:
		fread_fwrite();
		break;
	case FREADS_FWRITES:
		freads_fwrite();
		break;
	case FPUTS_FGETS:
		fputs_fgets();
		break;
	default:
		fputs("�������� �ʴ� ���ڹ�ȣ\n", stderr);
		break;
	}
	
	printf("�����Ϸ��� ���͸� ��������.");
	getchar();
	return 0;
}