/*
 * Copyright (C) 2010 Martin Willi
 * Copyright (C) 2010 revosec AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include <stdio.h>
#include <unistd.h>

#include <library.h>
#include <debug.h>

int main(int argc, char *argv[])
{
	chunk_t res;

	library_init(NULL);
	atexit(library_deinit);
	lib->plugins->load(lib->plugins, NULL, PLUGINS);

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <url>\n", argv[0]);
	}
	if (lib->fetcher->fetch(lib->fetcher, argv[1], &res, FETCH_END) == SUCCESS)
	{
		ignore_result(write(1, res.ptr, res.len));
		free(res.ptr);
		return 0;
	}
	return 1;
}