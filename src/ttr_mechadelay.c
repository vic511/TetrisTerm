#include "ttr_mecha.h"
#include "ttr_types.h"

int		mecha_fall(t_map *map, t_curr *curr)
{
  t_coords	it;

  if (curr->pos.y + curr->mino.size.y >= map->size.y)
    return (0);
  it.y = -1;
  while (++it.y < curr->mino.size.y && (it.x = -1))
    while (++it.x < curr->mino.size.x)
      if (mecha_getpx(&curr->mino, it.x, it.y) &&
	  mecha_getpx(map, curr->pos.x + it.x, curr->pos.y + it.y + 1))
	return (0);
  ++curr->pos.y;
  return (1);
}

int		mecha_freeze(t_map *map, t_data *data)
{
  int		color;
  t_coords	it;

  if (data->curr.pos.y < 0)
    return (0);
  it.y = -1;
  while (++it.y < data->curr.mino.size.y && (it.x = -1))
    while (++it.x < data->curr.mino.size.x)
      if (mecha_getpx(&data->curr.mino, it.x, it.y) &&
	  mecha_getpx(map, data->curr.pos.x + it.x, data->curr.pos.y + it.y))
	return (0);
  it.y = -1;
  while (++it.y < data->curr.mino.size.y && (it.x = -1))
    while (++it.x < data->curr.mino.size.x)
      if ((color = mecha_getpx(&data->curr.mino, it.x, it.y)))
	mecha_setpx(map, data->curr.pos.x + it.x, data->curr.pos.y + it.y,
		    color);
  data->curr.mino.size.x = 0;
  return (1);
}
