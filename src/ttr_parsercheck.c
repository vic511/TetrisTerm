#include "ttr_parser.h"

int	parser_checkminos(const t_minos *minos)
{
  int	y;
  int	i;
  char	*line;

  if ((line = my_getline(minos->stream)))
    {
      free(line);
      return (0);
    }
  y = 0;
  while (y < minos->size.y)
    {
      line = minos->shape[y];
      i = 0;
      while (line[i])
	if (i >= minos->size.x)
	  return (0);
	else
	  ++i;
      ++y;
    }
  return (1);
}
