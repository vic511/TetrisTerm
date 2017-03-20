#include "ttr_mecha.h"
#include "ttr_ui.h"
#include "my.h"

static void	mecha_linestroll(unsigned int nlines)
{
  if (!nlines)
    return ;
  if (nlines == 3)
    ui_soundsplay(1, SOUND_TRIPLE);
  else if (nlines > 1)
    ui_soundsplay(1, SOUND_WOAH);
}

static int	mecha_removeline(t_map *map, int off)
{
  int		y;

  y = off;
  while (y > 0)
    {
      my_memcpy(&map->grid[y * map->size.x],
		&map->grid[(y - 1) * map->size.x],
		map->size.x * sizeof(int));
      --y;
    }
  my_memset(map->grid, 0, map->size.x * sizeof(int));
  return (1);
}

int			mecha_updatescore(t_map *map, t_data *data)
{
  t_coords		it;
  int			filled;
  unsigned int		nlines;

  nlines = 0;
  it.y = -1;
  while (++it.y < map->size.y)
    {
      filled = 0;
      it.x = -1;
      while (++it.x < map->size.x)
	filled += !!mecha_getpx(map, it.x, it.y);
      if (filled == map->size.x)
	{
	  ++nlines;
	  mecha_removeline(map, it.y);
	}
    }
  if (!nlines)
    return (1);
  mecha_linestroll(nlines);
  data->nlines += nlines;
  data->score += nlines * nlines + data->level - 1 + (map->size.x) / 4;
  data->level = (data->reallines += nlines) / 2 + 1;
  return (1);
}
