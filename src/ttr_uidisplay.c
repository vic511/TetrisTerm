#include <ncurses.h>
#include <time.h>
#include "ttr_mecha.h"
#include "ttr_ui.h"
#include "my.h"

static void	ui_writenext(WINDOW *win, const t_coords *dim,
			     const t_minos *next)
{
  t_coords	pos;
  t_coords	it;

  wclear(win);
  UI_COLORON(win, next->color);
  pos.x = ((dim->x / 2) - next->size.x) / 2;
  pos.y = (dim->y - next->size.y) / 2;
  it.y = 0;
  while (it.y < next->size.y)
    {
      it.x = 0;
      while (next->shape[it.y][it.x])
	{
	  if (it.x < next->size.x && next->shape[it.y][it.x] == '*')
	    mvwprintw(win, pos.y + it.y + 1, (pos.x + it.x) * 2 + 1,
		      "[]");
	  ++it.x;
	}
      ++it.y;
    }
  UI_COLOROFF(win, next->color);
  box(win, 0, 0);
  mvwprintw(win, 0, (dim->x - MY_STRLEN(TITLE_NEXT) + 2) / 2, TITLE_NEXT);
  wrefresh(win);
}

static void	ui_writemap(WINDOW *win, const t_coords *dim,
			    const t_map *map, const t_curr *curr)
{
  t_coords	it;
  int		color;

  wclear(win);
  it.y = -1;
  while (++it.y < map->size.y && (it.x = -1))
    while (++it.x < map->size.x)
      if ((color = mecha_getpx(map, it.x, it.y)))
	{
	  UI_COLORON(win, color);
	  mvwprintw(win, it.y + 1, it.x * 2 + 1, "[]");
	  UI_COLOROFF(win, color);
	}
  UI_COLORON(win, curr->ptr->color);
  it.y = -1;
  while (++it.y < curr->mino.size.y && (it.x = -1))
    while (++it.x < curr->mino.size.x)
      if (mecha_getpx(&curr->mino, it.x, it.y))
	mvwprintw(win, curr->pos.y + it.y + 1, (curr->pos.x + it.x) * 2 + 1,
		  "[]");
  UI_COLOROFF(win, curr->ptr->color);
  box(win, 0, 0);
  mvwprintw(win, 0, (dim->x - MY_STRLEN(TITLE_MAP) + 2) / 2, TITLE_MAP);
  wrefresh(win);
}

void		ui_write(const t_map *map, const t_win *wins,
			 const t_data *data)
{
  int		minutes;
  int		seconds;

  clear();
  refresh();
  wclear(wins->infos);
  mvwprintw(wins->infos, 1, 1, SCORE_FMT, data->score);
  mvwprintw(wins->infos, 3, 1, LINES_FMT, data->nlines);
  mvwprintw(wins->infos, 5, 1, LEVEL_FMT, data->level);
  minutes = (time(NULL) - data->timer) / 60;
  seconds = (time(NULL) - data->timer) % 60;
  mvwprintw(wins->infos, 7, 1, TIMER_FMT, minutes, seconds);
  box(wins->infos, 0, 0);
  mvwprintw(wins->infos, 0, (WINFOS_WIDTH - MY_STRLEN(TITLE_INFOS) + 2) / 2,
	    TITLE_INFOS);
  wrefresh(wins->infos);
  ui_writemap(wins->map, &wins->dmap, map, &data->curr);
  if (wins->next)
    ui_writenext(wins->next, &wins->dnext, data->next);
}

void		ui_checktermsize(const t_win *wins, time_t *timer)
{
  time_t	old;
  bool		toosmall;

  old = time(NULL);
  toosmall = false;
  while (COLS < wins->size.x || LINES < wins->size.y)
    {
      toosmall = true;
      clear();
      move(LINES / 2, COLS / 2 - MY_STRLEN(ERR_TOOSMALL) / 2);
      printw(ERR_TOOSMALL);
      refresh();
      usleep(GAME_DELAY);
    }
  if (toosmall)
    {
      *timer += time(NULL) - old;
      clear();
      refresh();
    }
}
