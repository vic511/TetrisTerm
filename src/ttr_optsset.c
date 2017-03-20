#include "my.h"
#include "ttr_opts.h"

int		opts_setlevel(char * const *argv, const t_optparam *param)
{
  unsigned int	*level;
  char		*ptr;
  char		*pos;

  ptr = NULL;
  level = param->data;
  if (!my_strcmp(*argv, "-l"))
    ptr = argv[1];
  else
    ptr = *argv + my_strlen(param->longname);
  *level = my_strtoul(ptr, &pos, 10);
  if (!*level || *pos)
    return (my_errmsg(0, "Incorrect level argument"));
  return (1);
}

int		opts_setbool(char * const *argv, const t_optparam *param)
{
  bool		*ptr;

  (void) argv;
  ptr = param->data;
  *ptr = 1;
  return (1);
}

int		opts_setkey(char * const *argv, const t_optparam *param)
{
  char		**key;
  char		*ptr;

  if (!my_strncmp(*argv, "-k", 2))
    ptr = argv[1];
  else
    ptr = *argv + my_strlen(param->longname);
  if (!*ptr)
    return (my_errmsg(0, "Keys value cannot be empty"));
  key = param->data;
  *key = ptr;
  return (1);
}

int		opts_setmapsize(char * const *argv, const t_optparam *param)
{
  t_coords	*mapsize;
  char		*pos;
  char		*sizeptr;
  t_coords	coords;

  if (!(pos = my_strchr(*argv, '=')))
    return (0);
  mapsize = param->data;
  sizeptr = pos + 1;
  coords.y = my_strtoul(sizeptr, &pos, 10);
  if (!coords.y || *pos != ',' || !pos[1])
    return (my_errmsg(0, "Incorrect mapsize rows value"));
  sizeptr = pos + 1;
  coords.x = my_strtoul(sizeptr, &pos, 10);
  if (!coords.x || *pos)
    return (my_errmsg(0, "Incorrect mapsize cols value"));
  mapsize->x = coords.x;
  mapsize->y = coords.y;
  return (1);
}
