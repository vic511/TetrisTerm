#include "my_file.h"

static char	*gnl_extend(char *save, const char *buff, int len, int newlen)
{
  char		*ret;
  int		i;

  if ((ret = malloc(newlen + 1)) == NULL)
    return (NULL);
  i = -1;
  while (++i < len)
    ret[i] = save[i];
  --i;
  while (++i < newlen)
    ret[i] = buff[i - len];
  free(save);
  return (ret);
}

static char	*gnl_dupshift(char **save, int *savelen, int len)
{
  char		*dup;
  int		duplen;
  int		linefeed;
  int		i;

  if (!(linefeed = 0) && (*save == NULL || (len <= 0 && *savelen <= 0)))
    {
      free(*save);
      *save = NULL;
      *savelen = 0;
      return (NULL);
    }
  duplen = -1;
  while (++duplen < *savelen && !(linefeed = (*save)[duplen] == '\n'));
  if ((dup = malloc(duplen + 1)) == NULL)
    return (NULL);
  i = -1;
  while (++i < duplen)
    dup[i] = (*save)[i];
  dup[i] = 0;
  i = -1;
  while ((++i) + duplen + 1 < *savelen)
    (*save)[i] = (*save)[i + duplen + 1];
  *savelen -= duplen + linefeed;
  return (dup);
}

static int	gnl_haslinefeed(const char *save, int savelen)
{
  int		i;

  i = -1;
  while (++i < savelen)
    if (save[i] == '\n')
      return (1);
  return (0);
}

char		*my_getline(t_file *file)
{
  char		buff[READ_SIZE + 1];
  char		*ret;
  int		len;
  int		i;

  while (!(*buff = 0) && !(len = gnl_haslinefeed(file->save, file->savelen)))
    {
      if ((len = read(file->fd, buff, READ_SIZE)) <= 0)
	break;
      if ((file->save = gnl_extend(file->save, buff, file->savelen,
				   file->savelen + len)) == NULL)
	return (NULL);
      file->save[file->savelen += len] = 0;
      i = -1;
      while (++i < len && file->save[i] != '\n');
      if (i == len && len < READ_SIZE)
	break;
    }
  ret = gnl_dupshift(&file->save, &file->savelen, len);
  return (ret);
}
