#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fprintf_fscanf.h"
#include "fprintfs_fscanfs.h"
#include "fread_fwrite.h"
#include "freads_fwrite.h"
#include "fputs_fgets.h"

#define ARG_BUFFER 4
#define BUFFER 100

enum ArgsMode
{
	FPRINTF_FSCANF = 48,	// 0
	FPRINTFS_FSCANFS,
	FPUTS_FGETS,
	FREAD_FWRITE,
	FREADS_FWRITES
};