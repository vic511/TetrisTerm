#include "my_file.h"

t_file		*my_fopen(const char *path)
{
  t_file	*file;

  if ((file = malloc(sizeof(*file))) == NULL)
    return (NULL);
  if ((file->fd = open(path, O_RDONLY)) < 0)
    {
      free(file);
      return (NULL);
    }
  file->save = NULL;
  file->savelen = 0;
  return (file);
}

t_file		*my_fdopen(const int fd)
{
  t_file	*file;

  if ((file = malloc(sizeof(*file))) == NULL)
    return (NULL);
  file->fd = fd;
  file->save = NULL;
  file->savelen = 0;
  return (file);
}

int		my_fclose(t_file *file)
{
  int		fd;

  if (file == NULL)
    return (-1);
  free(file->save);
  fd = file->fd;
  free(file);
  if (fd >= 0 && fd <= 2)
    return (0);
  return (close(fd));
}
