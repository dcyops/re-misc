#include "../includes/find_files.h"
#include "../includes/inspect_files.h"

int
init_nftw(int argc, char *argv[])
{
  int i, c, nfds;
  int errors = 0;
  int flags = FTW_PHYS;
  char start[PATH_MAX], finish[PATH_MAX];

  while ((c = getopt (argc, argv, "c")) != -1)
    {
      switch (c)
        {
        case 'c':
          flags |= FTW_CHDIR;
          break;
        default:
          break;
        }
    }

  getcwd (start, sizeof start);

  nfds = getdtablesize () - SPARE_FDS; /* leave some spare descriptors */
  for (i = optind; i < argc; i++)
    {
      if (nftw (argv[i], file_info, nfds, flags) != 0)
        {
          fprintf (stderr, "%s: %s: stopped early\n", argv[0], argv[i]);
          errors++;
        }
    }

  if ((flags & FTW_CHDIR) != 0)
    {
      getcwd (finish, sizeof finish);
      printf ("Starting dir: %s\n", start);
      printf ("Finishing dir: %s\n", finish);
    }

  return (errors != 0);
}

int
file_info (const char *file, const struct stat *sb, int flag, struct FTW *s)
{
  const char *name = file + s->base;
  printf ("%*s", s->level * 4, ""); /* indent over */

  switch (flag)
    {
    case FTW_F:
      /* If we find a file we examine its header */
      read_file_header (file);
      break;
    case FTW_D:
      printf ("%s (directory)\n", name);
      break;
    case FTW_DNR:
      printf ("%s (unreadable directory)\n", name);
      break;
    case FTW_SL:
      printf ("%s (symbolic link)\n", name);
      break;
    case FTW_NS:
      printf ("%s (stat failed): %s\n", name, strerror (errno));
      break;
    case FTW_DP:
    case FTW_SLN:
      printf ("%s: FTW_DP or FTW_SLN: can't happen!\n", name);
      break;
    default:
      printf ("%s: unknown flag %d: can't happen!\n", name, flag);
      return 1;
    }
  return 0;
}
