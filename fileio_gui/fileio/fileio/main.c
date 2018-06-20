#include "head.h"


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		fputs("매개변수 오류", stderr);
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
		fputs("존재하지 않는 인자번호\n", stderr);
		break;
	}
	
	printf("종료하려면 엔터를 누르세요.");
	getchar();
	return 0;
}