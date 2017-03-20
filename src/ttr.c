#include <ncurses.h>
#include "my.h"
#include "ttr_game.h"
#include "ttr_debug.h"
#include "ttr_opts.h"
#include "ttr_minos.h"

static void		ttr_showhelp(const char *path)
{
  MY_PUTSTR("Usage: ");
  my_putstr(path);
  MY_PUTSTR(" [options]\n"
	    "Options:\n"
	    "   --help\t\tDisplay this help\n"
	    "   -l --level={num}\tStart Tetris at level num (def: 1)\n"
	    "   -kl --key-left={K}\tMove the tetrimino LEFT using the K key "
	    "(def: left arrow)\n"
	    "   -kr --key-right={K}\tMove the tetrimino RIGHT using the K key "
	    "(def: right arrow)\n"
	    "   -kt --key-turn={K}\tTURN the tetrimino clockwise 90d using "
	    "the K key  (def: top arrow)\n"
	    "   -kd --key-drop={K}\tDROP the tetrimino using the K key "
	    "(def: down arrow)\n"
	    "   -kq --key-quit={K}\tQUIT the using the K key (def: 'Q' key)\n"
	    "   -kp --key-pause={K}\tPAUSE/RESTART the game using the K key "
	    "(def: space bar)\n"
	    "   --map-size={row,col}\tSet the numbers of rows and columns of "
	    "the map (def: 20,10)\n"
	    "   -w --without-next\tHide next tetrimino (def: false)\n"
	    "   -d --debug\t\tDebug mode (def: false)\n");
}

static int		ttr_main(int argc, char **argv,
				 t_game *game, t_optparam *params)
{
  if (!opts_init(&game->opts) ||
      !opts_parse(argc - 1, &argv[1], params) ||
      !opts_checkconflicts(&game->opts) ||
      !(game->minos = minos_getall(&game->opts.mapsize)))
    return (84);
  debug_main(game->minos, &game->opts);
  minos_errorfilter(&game->minos);
  minos_getmax(game->minos, &game->data.curr.realsize);
  srand(((intptr_t) &game->minos) >> 12);
  if (!game_init(game) || !debug_getinput(&game->opts))
    return (84);
  game_main(game);
  minos_freelist(game->minos);
  if (!game_end(game))
    return (84);
  return (0);
}

int			main(int argc, char **argv)
{
  static t_game		g;
  static t_optparam	params[] =
    {
      {"--without-next", "-w", false, &g.opts.wnext, opts_setbool},
      {"--debug",      "-d",  false, &g.opts.debug, opts_setbool},
      {"--level=",     "-l",  true,  &g.opts.level, opts_setlevel},
      {"--key-left=",  "-kl", true,  &g.opts.keys[TTR_KEYLEFT], opts_setkey},
      {"--key-right=", "-kr", true,  &g.opts.keys[TTR_KEYRIGHT], opts_setkey},
      {"--key-turn=",  "-kt", true,  &g.opts.keys[TTR_KEYTURN], opts_setkey},
      {"--key-drop=",  "-kd", true,  &g.opts.keys[TTR_KEYDROP], opts_setkey},
      {"--key-quit=",   "-kq", true,  &g.opts.keys[TTR_KEYQUIT], opts_setkey},
      {"--key-pause=",  "-kp", true,  &g.opts.keys[TTR_KEYPAUSE], opts_setkey},
      {"--map-size=",  NULL,  true,  &g.opts.mapsize, opts_setmapsize},
      {NULL, NULL, false, NULL, NULL}
    };
  int		i;

  i = -1;
  while (++i < argc)
    if (!my_strcmp(argv[i], "--help"))
      {
	ttr_showhelp(argc ? argv[0] : "./tetristerm");
	return (0);
      }
  return (ttr_main(argc, argv, my_memset(&g, 0, sizeof(g)), params));
}
