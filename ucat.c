/******************************************************************************
 *	Copyright (C) 2020	Alejandro Colomar Andrés		      *
 *	SPDX-License-Identifier:	BSD-2-Clause			      *
 ******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ALX_NO_PREFIX
#include <libalx/extra/curl/fcurl/init.h>
#include <libalx/nix/ucat/ucat.h>


int main(int argc, char *argv[])
{
	const char	*url;
	int		status;

	if (argc < 2)
		url	= NULL;
	else
		url	= argv[1];

	status	= nix_ucat(url);
	if (status) {
		fprintf(stderr, "nix_ucat(%s) error code = %i\n", url, status);
		return	EXIT_FAILURE;
	}

	return	0;
}

