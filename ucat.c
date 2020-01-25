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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALX_NO_PREFIX
#include <libalx/base/compiler/size.h>
#include <libalx/extra/curl/fcurl/fclose.h>
#include <libalx/extra/curl/fcurl/fopen.h>
#include <libalx/extra/curl/fcurl/fread.h>
#include <libalx/extra/curl/fcurl/init.h>
#include <libalx/extra/curl/fcurl/URL_FILE.h>


int main(int argc, char *argv[])
{
	URL_FILE	*istream;

	size_t		nread;
	char		buf[BUFSIZ];
	const char	*url;
	int		status;

	status	= 0;

	if (argc > 2) {
		fprintf(stderr, "Usage:  url_cat [url or file]\n");
		return	EXIT_FAILURE;
	}

	status	= url_init();
	if (status) {
		fprintf(stderr, "couldn't url_init();  error code = %i\n", status);
		return	EXIT_FAILURE;
	}

	if ((argc < 2)  ||  !strcmp(argv[1], "-")) {
		istream		= url_stdin;
		goto no_file;
	}

	url	= argv[1];
	istream	= url_fopen(url, "r");
	if (!istream) {
		fprintf(stderr, "couldn't url_fopen() %s\n", url);
		status	= EXIT_FAILURE;
		goto err_fopen;
	}
no_file:
	do {
		nread = url_fread(buf, 1, ARRAY_SIZE(buf), istream);
		fwrite(buf, 1, nread, stdout);
	} while (nread);

	if (istream != url_stdin)
		status	|= url_fclose(istream);
err_fopen:
	status	|= url_deinit();

	if (status)
		return	EXIT_FAILURE;
	return	0;
}

