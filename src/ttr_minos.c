#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "my.h"
#include "ttr_game.h"
#include "ttr_minos.h"
#include "ttr_parser.h"

static int	minos_add(t_minos **minoslist, const char *filename,
			  const t_coords *mapsize)
{
  t_minos	*minos;
  t_minos	**curr;
  int		ret;

  if (!(minos = malloc(sizeof(*minos))))
    return (0);
  if (!(minos->stream = my_fopen(filename)) && xfree(minos))
    return (0);
  curr = minoslist;
  while (*curr)
    curr = &(*curr)->next;
  minos->next = NULL;
  minos->shape = NULL;
  my_strncpy(minos->name, filename + MY_STRLEN(MINOS_DIR),
	     my_strrchr(filename, '.') - filename - MY_STRLEN(MINOS_DIR));
  ret = parser_parse(minos, mapsize);
  *curr = minos;
  return (ret);
}

static int	minos_filter(const struct dirent *ent)
{
  char		*pos;

  if ((pos = my_strrchr(ent->d_name, '.')) &&
      pos != ent->d_name &&
      !my_strcmp(MINOS_EXT, pos))
    return (1);
  return (0);
}

int		minos_free(t_minos *minos)
{
  int		i;

  if (minos->shape)
    {
      i = 0;
      while (i < minos->size.y)
	free(minos->shape[i++]);
      free(minos->shape);
    }
  free(minos);
  return (1);
}

int		minos_freelist(t_minos *minoslist)
{
  t_minos	*curr;
  t_minos	*tmp;

  curr = minoslist;
  while (curr != NULL)
    {
      tmp = curr->next;
      minos_free(curr);
      curr = tmp;
    }
  return (1);
}

t_minos		*minos_getall(const t_coords *mapsize)
{
  struct dirent	**enttab;
  t_minos	*minoslist;
  char		name[MINOS_NAMELEN + MY_STRLEN(MINOS_DIR)];
  char		*pos;
  int		i;
  int		entlen;

  if ((entlen = scandir(MINOS_DIR, &enttab, minos_filter, alphasort)) < 0)
    return (NULL);
  minoslist = NULL;
  i = -1;
  while (++i < entlen)
    {
      pos = my_strrchr(enttab[i]->d_name, '.');
      my_strcpy(name, MINOS_DIR);
      my_strncat(name, enttab[i]->d_name, name - pos - 1);
      minos_add(&minoslist, name, mapsize);
      free(enttab[i]);
    }
  free(enttab);
  return (minoslist);
}
