#include "ttr_types.h"
#include "ttr_mecha.h"
#include "my.h"

static int	mecha_rotate(t_curr *curr)
{
  t_coords	it;

  my_memset(curr->rotate.grid, 0,
	    curr->realsize.x * curr->realsize.x * sizeof(int));
  curr->rotate.size.x = curr->mino.size.y;
  curr->rotate.size.y = curr->mino.size.x;
  it.y = 0;
  while (it.y < curr->mino.size.y)
    {
      it.x = 0;
      while (it.x < curr->mino.size.x)
	{
	  mecha_setpx(&curr->rotate, it.y, curr->mino.size.x - it.x - 1,
		      mecha_getpx(&curr->mino, it.x, it.y));
	  ++it.x;
	}
      ++it.y;
    }
  return (1);
}

static int	mecha_checkcollision(const t_map *map, const t_coords *pos,
				     const t_map *mino, int xoff)
{
  t_coords	it;

  if (pos->x + mino->size.x + xoff > map->size.x ||
      pos->y + mino->size.y > map->size.y)
    return (1);
  it.y = -1;
  while (++it.y < mino->size.y && (it.x = -1))
    while (++it.x < mino->size.x)
      if (mecha_getpx(mino, it.x, it.y) &&
	  mecha_getpx(map, pos->x + it.x + xoff, pos->y + it.y))
	return (1);
  return (0);
}

int		mecha_handlekey(t_map *map, t_data *data, int key)
{
  if (key == TTR_KEYRIGHT &&
      data->curr.pos.x + data->curr.mino.size.x < map->size.x &&
      !mecha_checkcollision(map, &data->curr.pos, &data->curr.mino, 1))
    ++data->curr.pos.x;
  if (key == TTR_KEYLEFT && data->curr.pos.x > 0 &&
      !mecha_checkcollision(map, &data->curr.pos, &data->curr.mino, -1))
    --data->curr.pos.x;
  if (key == TTR_KEYTURN)
    if (mecha_rotate(&data->curr) &&
	!mecha_checkcollision(map, &data->curr.pos, &data->curr.rotate, 0))
      {
	my_memcpy(data->curr.mino.grid, data->curr.rotate.grid,
		  data->curr.realsize.x * data->curr.realsize.x * sizeof(int));
	my_memcpy(&data->curr.mino.size, &data->curr.rotate.size,
		  sizeof(data->curr.mino.size));
      }
  if (key == TTR_KEYDROP)
    {
      while (mecha_fall(map, &data->curr));
      return (mecha_freeze(map, data));
    }
  return (1);
}
