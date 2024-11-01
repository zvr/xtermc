/* xtermc -- control the running xterm */

/*
    Copyright (C) 2024 Alexios Zavras
    SPDX-License-Identifier: GPL-3.0-or-later
 */

#define _GNU_SOURCE
#include <errno.h>
#include <error.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== interface definitions ===== */

#define PROGRAM "xtermc"
#define VERSION "1.2.0"
#define AUTHOR  "Alexios Zavras (zvr)"

static char         *short_options = "b:c:f:ht:V";
static struct option long_options[] = {
    { "background",  required_argument, 0, 'b' },
    { "bg",          required_argument, 0, 'b' },
    { "borderwidth", required_argument, 0, 'B' },
    { "bw",          required_argument, 0, 'B' },
    { "cc",          required_argument, 0, 'c' },
    { "cursor",      required_argument, 0, 'c' },
    { "fg",          required_argument, 0, 'f' },
    { "foreground",  required_argument, 0, 'f' },
    { "help",        no_argument,       0, 'h' },
    { "title",       required_argument, 0, 't' },
    { "version",     no_argument,       0, 'V' },
    { 0,	     0,		 0, 0   }
};

void
print_version(void)
{
    printf("%s %s\n", PROGRAM, VERSION);
    printf("Written by %s.\n", AUTHOR);
    exit(EXIT_SUCCESS);
}

void
print_help(void)
{
    printf("Usage: %s [OPTION] ...\n", program_invocation_short_name);
    puts("Set characteristics of the current xterm.");
    puts("Options may be one or more of:");
    puts("\t-t, --title=TEXT            set the window title");
    puts("\t-f, --foreground=COLOR      set the foreground color");
    puts("\t-b, --background=COLOR      set the background color");
    puts("\t-c, --cursor=COLOR          set the cursor color");
    puts("");
    puts("\t-V, --version  output version information and exit");
    puts("\t-h, --help     display this help and exit");

    exit(EXIT_SUCCESS);
}

/* ===== setting xterm characteristics ===== */

/* all the sordid details at
https://invisible-island.net/xterm/ctlseqs/ctlseqs.html
 */

void
set_title(char *title)
{
    printf("\033]0;%s\007", title);
}

#define FOREGROUND 10
#define BACKGROUND 11
#define CURSOR     12

void
set_color(int type, char *color)
{
    char *prefix = "";
    if (*color >= '0' && *color <= '9')
	prefix = "#";
    printf("\033]%d;%s%s\007", type, prefix, color);
}

/* ===== main program, arg processing ===== */

char *title = NULL;
char *bgcolor = NULL;
char *cursorcolor = NULL;
char *fgcolor = NULL;

int
main(int argc, char **argv)
{
    int c;

    while (1) {
	int opt_index;
	c = getopt_long_only(
	    argc, argv, short_options, long_options, &opt_index);
	if (c == -1)
	    break;
	switch (c) {
	    case 'b':
		bgcolor = strdup(optarg);
		break;
	    case 'c':
		cursorcolor = strdup(optarg);
		break;
	    case 'f':
		fgcolor = strdup(optarg);
		break;
	    case 't':
		title = strdup(optarg);
		break;
	    case 'V':
		print_version();
		/* NOTREACHED */
	    case 'h':
		print_help();
		/* NOTREACHED */

	    case 0:
		break;
	    case '?':
		break;
	    default:
		exit(EXIT_FAILURE);
		/* NOTREACHED */
	}
    }
    if (optind < argc)
	error(0, 0, "non-options command-line arguments ignored");

    if (title)
	set_title(title);
    if (bgcolor)
	set_color(BACKGROUND, bgcolor);
    if (fgcolor)
	set_color(FOREGROUND, fgcolor);
    if (cursorcolor)
	set_color(CURSOR, cursorcolor);

    exit(EXIT_SUCCESS);
}
