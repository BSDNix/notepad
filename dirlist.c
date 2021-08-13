#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <fnmatch.h>
#include <fts.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/* still better than C++ */ 

int entcmp(const FTSENT **a, const FTSENT **b)
{
	return strcmp((*a)->fts_name, (*b)->fts_name);
}
void pmatch(char *dir, const char *pattern)
{
	FTS *tree;
	FTSENT *f;
	char *argv[] = { dir, NULL};
	
	tree = fts_open(argv, FTS_LOGICAL | FTS_NOSTAT, entcmp);
	if (tree == NULL)
		err(1, "fts_open");

	while ((f = fts_read(tree)))
	{
		switch (f->fts_info)
		{
			case FTS_DNR:
		 	case FTS_ERR:
			case FTS_NS:
				warn("%s", f->fts_path);
				continue;
			case FTS_DP:
				continue;
		}
		if (fnmatch(pattern, f->fts_name, FNM_PERIOD) == 0)
			puts(f->fts_path);

		if (f->fts_info == FTS_DC)
			warnx("%s: fucking cycle ofzo idk", f->fts_path);
	}
	if (errno != 0)
		err(1, "fts_read");
	if (fts_close(tree) < 0)
		err(1, "fts_close");
}
main()
{
	pmatch(".", "*.c");
	return 0;
}


