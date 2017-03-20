#include <ncurses.h>
#include <stdlib.h>
#include "my.h"
#include "ttr_types.h"
#include "ttr_opts.h"
#include "ttr_ui.h"

int	ui_init(t_win *wins, bool wnext)
{
  curs_set(0);
  keypad(stdscr, TRUE);
  ui_colorinit();
  ui_computepos(wins);
  wins->next = NULL;
  if (!(wins->map = newwin(wins->dmap.y + 2, wins->dmap.x + 2,
			   wins->pmap.y, wins->pmap.x)) ||
      !(wins->infos = newwin(WINFOS_HEIGHT + 2, WINFOS_WIDTH + 2,
			     wins->pinfos.y, wins->pinfos.x)) ||
      (!wnext && !(wins->next = newwin(wins->dnext.y + 2, wins->dnext.x + 2,
				       wins->pnext.y, wins->pnext.x))))
    return (0);
  box(wins->infos, 0, 0);
  box(wins->map, 0, 0);
  if (wins->next)
    box(wins->next, 0, 0);
  return (1);
}

void	ui_end(const t_win *wins)
{
  delwin(wins->map);
  delwin(wins->infos);
  delwin(wins->next);
}

int		ui_getch(const char * const *keys, size_t keysize)
{
  char		buff[TTR_KEYBUFF + 1];
  ssize_t	len;
  int		key;

  (void) keysize;
  if ((len = read(0, buff, TTR_KEYBUFF)) < 0)
      return (-1);
  if (!len)
    return (TTR_KEYNONE);
  buff[len] = 0;
  key = -1;
  while (++key < TTR_KEYSNB)
    if (!my_strcmp(keys[key], buff))
      return (key);
  return (TTR_KEYNONE);
}

void	ui_computepos(t_win *wins)
{
  wins->dmap.x *= 2;
  wins->dnext.x *= 2;
  wins->size.x =
    WINFOS_WIDTH + UI_SEPLEN + 4 +
    wins->dmap.x + UI_SEPLEN + 2 +
    wins->dnext.x + UI_SEPLEN;
  wins->size.y = MAX(wins->dnext.y, wins->dmap.y) + UI_SEPLEN;
  wins->pinfos.y = (wins->dmap.y - WINFOS_HEIGHT) / 2;
  wins->pinfos.x = 2;
  wins->pmap.y = (MAX(wins->dmap.y, WINFOS_HEIGHT) - wins->dmap.y) / 2;
  wins->pmap.x = WINFOS_WIDTH + UI_SEPLEN + 4;
  wins->pnext.y = (MAX(wins->dmap.y, wins->dnext.y) - wins->dnext.y) / 2;
  wins->pnext.x = wins->pmap.x + wins->dmap.x + UI_SEPLEN + 2;
}
