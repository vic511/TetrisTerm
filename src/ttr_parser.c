#include <stdlib.h>
#include "my.h"
#include "ttr_parser.h"

static int	parser_getheader(t_minos *minos, const t_coords *mapsize)
{
  char		*curr;
  char		*line;

  if (!(line = my_getline(minos->stream)))
    return (0);
  minos->size.x = my_strtoul(line, &curr, 10);
  if ((minos->size.x <= 0 || minos->size.x > mapsize->x || *curr++ != ' ') &&
      xfree(line))
    return (0);
  minos->size.y = my_strtoul(curr, &curr, 10);
  if ((minos->size.y <= 0 || minos->size.y > mapsize->y || *curr++ != ' ') &&
      xfree(line))
    return (0);
  minos->color = my_strtoul(curr, &curr, 10);
  if ((minos->color <= 0 || (*curr && *curr != ' ')) && xfree(line))
    return (0);
  return (1);
}

static int	parser_checkline(const char *line, int size_x)
{
  int		i;
  int		countstars;
  bool		shootingstars;

  shootingstars = false;
  countstars = 0;
  i = 0;
  while (line[i])
    if (line[i] != ' ' && line[i] != '*')
      return (0);
    else
      {
	countstars += (line[i] == '*');
	shootingstars |= (line[i] == '*');
	++i;
      }
  if (countstars > size_x)
    shootingstars = false;
  return (shootingstars);
}

static size_t	parser_getshapeoffset(const t_minos *minos)
{
  int		i;
  int		min;
  int		off;

  min = minos->size.x;
  i = 0;
  while (i < minos->size.y)
    {
      off = 0;
      while (minos->shape[i][off] == ' ' && ++off);
      if (off < min)
	min = off;
      ++i;
    }
  return (min);
}

static int	parser_getshape(t_minos *minos)
{
  int		i;
  size_t	offset;
  int		i2;

  if (!(minos->shape = malloc(sizeof(char *) * minos->size.y)))
    return (0);
  i = 0;
  while (i < minos->size.y)
    if (!(minos->shape[i] = my_getline(minos->stream)) ||
	!parser_checkline(minos->shape[i++], minos->size.x))
      {
	i2 = 0;
	while (i2 < i)
	  free(minos->shape[i2++]);
	free(minos->shape);
	minos->shape = NULL;
	return (0);
      }
  offset = parser_getshapeoffset(minos);
  i = 0;
  while (i < minos->size.y)
    my_strrtrim(my_strlshift(minos->shape[i++], offset), ' ');
  return (1);
}

int		parser_parse(t_minos *minos, const t_coords *mapsize)
{
  if (!parser_getheader(minos, mapsize) ||
      !parser_getshape(minos) ||
      !parser_checkminos(minos))
    {
      my_fclose(minos->stream);
      return (0);
    }
  my_fclose(minos->stream);
  return (1);
}
