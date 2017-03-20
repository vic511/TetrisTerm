#include <term.h>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "my.h"
#include "ttr_mecha.h"
#include "ttr_game.h"

static int		game_saveandalloc(t_game *game)
{
  struct termios	newterm;
  size_t		gridlen;

  if (ioctl(0, TCGETS, &game->oldterm) < 0)
    return (my_errmsg(0, "Cannot save current terminal attributes"));
  my_memcpy(&newterm, &game->oldterm, sizeof(newterm));
  newterm.c_lflag &= ~ICANON;
  newterm.c_cc[VMIN] = 0;
  newterm.c_cc[VTIME] = 0;
  if (ioctl(0, TCSETS, &newterm) < 0)
    return (my_errmsg(0, "Cannot set canonical mode"));
  gridlen = game->data.curr.realsize.x * game->data.curr.realsize.x *
    sizeof(int);
  if (!(game->data.curr.mino.grid = malloc(gridlen)))
    return (my_errmsg(0, "Unable to allocate"));
  if (!(game->data.curr.rotate.grid = malloc(gridlen)))
    return (my_errmsg(0, "Unable to allocate"));
  my_memset(game->data.curr.mino.grid, 0, gridlen);
  my_memset(game->data.curr.rotate.grid, 0, gridlen);
  gridlen = game->map.size.x * game->map.size.y * sizeof(int);
  if (!(game->map.grid = malloc(gridlen)))
    return (my_errmsg(0, "Unable to allocate"));
  my_memset(game->map.grid, 0, gridlen);
  return (1);
}

int		game_init(t_game *game)
{
  size_t	len;
  size_t	key;

  initscr();
  game->data.level = game->opts.level;
  game->data.reallines = (game->opts.level - 1) * 2;
  key = 0;
  my_memset(&game->data.curr.mino.size, 0, sizeof(game->data.curr.mino.size));
  my_memcpy(&game->map.size, &game->opts.mapsize, sizeof(game->map.size));
  if (!game_saveandalloc(game))
    return (0);
  game->keysize = 0;
  while (key < TTR_KEYSNB)
    if ((len = my_strlen(game->opts.keys[key++])) < game->keysize)
      game->keysize = len;
  my_memcpy(&game->wins.dnext, &game->data.curr.realsize,
	    sizeof(game->wins.dnext));
  return (1);
}

int	game_end(t_game *game)
{
  free(game->data.curr.mino.grid);
  free(game->map.grid);
  if (ioctl(0, TCSETS, &game->oldterm) < 0)
    return (0);
  endwin();
  return (1);
}

int		game_main(t_game *game)
{
  int		key;
  unsigned int	loops;

  my_memcpy(&game->wins.dmap, &game->opts.mapsize, sizeof(game->wins.dmap));
  ui_init(&game->wins, game->opts.wnext);
  key = TTR_KEYNONE;
  game->data.timer = time(NULL);
  loops = 0;
  while (key != TTR_KEYQUIT && ++loops)
    {
      ui_checktermsize(&game->wins, &game->data.timer);
      if ((key = ui_getch(game->opts.keys, game->keysize)) < 0)
	break ;
      if (key == TTR_KEYPAUSE)
	if (ui_pause(&game->data.timer, game->opts.keys, game->keysize) < 0)
	  break ;
      if (!mecha_update(game, key, loops))
	break ;
      if (loops % UI_DELAY == 0)
	ui_write(&game->map, &game->wins, &game->data);
      usleep(GAME_DELAY);
    }
  ui_lost(&game->data, game->opts.keys, game->keysize);
  ui_end(&game->wins);
  return (1);
}
