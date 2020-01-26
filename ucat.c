/******************************************************************************
 *	Copyright (C) 2020	Alejandro Colomar Andrés		      *
 *	SPDX-License-Identifier:	BSD-2-Clause			      *
 ******************************************************************************/
/*
 * This example source code uses a C library buffered I/O interface to
 * URL reads.  It supports fopen(), fread(), fgets(), feof(), fclose(),
 * rewind(). Supported functions have identical prototypes to their normal
 * libc namesakes and are preceaded by url_ .
 *
 * Using this code you can replace your program's fopen() with url_fopen()
 * and fread() with url_fread() and it becomes possible to read remote streams
 * instead of (only) local files. Local files (ie those that can be directly
 * fopened) will drop back to using the underlying libc implementations.
 *
 * See the main() function that shows an app that retrieves from a specified
 * url using url_fread() and writes to stdout (similar to cat).
 *
 * This code requires libcurl 7.17 or later and libalx 1~b10 or later.
 */

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

