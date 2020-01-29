/******************************************************************************
 *	Copyright (C) 2020	Alejandro Colomar Andrés		      *
 *	SPDX-License-Identifier:	BSD-2-Clause			      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALX_NO_PREFIX
#include <libalx/base/compiler/size.h>
#include <libalx/extra/curl/fcurl/fclose.h>
#include <libalx/extra/curl/fcurl/fopen.h>
#include <libalx/extra/curl/fcurl/fread.h>
#include <libalx/extra/curl/fcurl/URL_FILE.h>


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/


/******************************************************************************
 ******* enum / struct / union ************************************************
 ******************************************************************************/


/******************************************************************************
 ******* static prototypes ****************************************************
 ******************************************************************************/
int	ucat	(const char *url);
void	ucat__	(FILE *restrict ostream, URL_FILE *restrict istream);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
int	main	(int argc, char *argv[])
{
	const char	*url;
	int		status;

	if (argc < 2)
		url	= NULL;
	else
		url	= argv[1];

	status	= ucat(url);
	if (status) {
		fprintf(stderr, "ucat(%s) error code = %i\n", url, status);
		return	EXIT_FAILURE;
	}

	return	0;
}


/******************************************************************************
 ******* static function definitions ******************************************
 ******************************************************************************/
int	ucat	(const char *url)
{
	URL_FILE	*istream;

	if (!url  ||  !strcmp(url, "-")) {
		istream	= url_stdin;
	} else {
		istream	= url_fopen(url, "r");
		if (!istream)
			return	errno;
	}

	ucat__(stdout, istream);

	if (istream != url_stdin)
		return	url_fclose(istream);

	return	0;
}

void	ucat__	(FILE *restrict ostream, URL_FILE *restrict istream)
{
	size_t	n;
	char	buf[BUFSIZ];

	do {
		n	= url_fread(buf, 1, ARRAY_SIZE(buf), istream);
		fwrite(buf, 1, n, ostream);
	} while (n);
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/

