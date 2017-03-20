#include <fcntl.h>
#include "my.h"
#include "ttr_types.h"
#include "ttr_minos.h"
#include "ttr_mecha.h"

static int	mecha_setcurr(t_curr *curr,
			      const t_map *map, const t_minos *minos)
{
  t_coords	it;

  curr->ptr = minos;
  curr->mino.size.x = minos->size.x;
  curr->mino.size.y = minos->size.y;
  my_memset(curr->mino.grid, 0,
	    curr->mino.size.x * curr->mino.size.y * sizeof(int));
  curr->pos.y = - minos->size.y + 1;
  curr->pos.x = (map->size.x - minos->size.x) / 2;
  it.y = -1;
  while (++it.y < minos->size.y && (it.x = -1))
    while (minos->shape[it.y][++it.x])
      mecha_setpx(&curr->mino, it.x, it.y,
		  (minos->shape[it.y][it.x] == '*') * minos->color);
  return (1);
}

static int	mecha_getnewmino(t_game *game)
{
  const t_minos	*minos;

  if (!game->data.next)
    {
      game->data.next = minos_getrand(game->minos);
      minos = game->data.next;
      while (game->minos->next && minos == game->data.next)
	minos = minos_getrand(game->minos);
    }
  else
    minos = game->data.next;
  mecha_setcurr(&game->data.curr, &game->map, minos);
  minos = game->data.next;
  while (game->minos->next && game->data.next == minos)
    game->data.next = minos_getrand(game->minos);
  return (1);
}

int		mecha_update(t_game *game, int key, unsigned int loops)
{
  unsigned int	mod;

  mecha_updatescore(&game->map, &game->data);
  if (game->data.curr.mino.size.x <= 0)
    mecha_getnewmino(game);
  mod = MECHA_DELAY - (game->data.level - 1) * LEVEL_STEPS;
  if ((game->data.level - 1) * LEVEL_STEPS >= MECHA_DELAY)
    mod = 10;
  if (!(loops % mod))
    if (!mecha_fall(&game->map, &game->data.curr) &&
	!mecha_freeze(&game->map, &game->data))
      return (0);
  if (key != TTR_KEYNONE && !mecha_handlekey(&game->map, &game->data, key))
    return (0);
  return (1);
}

int	mecha_setpx(const t_map *map, int x, int y, int color)
{
  if (x < 0 || y < 0 || x >= map->size.x || y >= map->size.y)
    return (0);
  map->grid[(y * map->size.x) + x] = color;
  return (1);
}

int	mecha_getpx(const t_map *map, int x, int y)
{
  if (x < 0 || y < 0 || x >= map->size.x || y >= map->size.y)
    return (0);
  return (map->grid[(y * map->size.x) + x]);
}
