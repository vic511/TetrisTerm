#include "ttr_types.h"
#include "ttr_ui.h"
#include "my.h"

int		ui_pause(time_t *timer,
			 const char * const *keys, size_t keysize)
{
  bool		ok;
  time_t	old;
  int		key;
  WINDOW	*pause;

  if (!(pause = newwin(WPAUSE_HEIGHT + 2, WPAUSE_WIDTH + 2,
		       (LINES - WPAUSE_HEIGHT) / 2,
		       (COLS - WPAUSE_WIDTH) / 2)) ||
      (ok = !ui_soundsplay(2, SOUND_PAUSE, SOUND_MUSIC)))
    return (0);
  box(pause, 0, 0);
  mvwprintw(pause, 1, (WPAUSE_WIDTH - MY_STRLEN(MSG_PAUSE)) / 2 + 1,
	    MSG_PAUSE);
  wrefresh(pause);
  old = time(NULL);
  while (!ok)
    if ((key = ui_getch(keys, keysize)) < 0)
      return (0);
    else
      ok = (key == TTR_KEYPAUSE);
  *timer += time(NULL) - old;
  ui_soundskill();
  delwin(pause);
  return (1);
}

int		ui_lost(const t_data *data,
			const char * const * keys, size_t keysize)
{
  int		minutes;
  int		seconds;
  int		key;
  WINDOW	*lost;

  if (!(lost = newwin(WINFOS_HEIGHT + 2, WINFOS_WIDTH + 2,
		       (LINES - WINFOS_HEIGHT) / 2,
		       (COLS - WINFOS_WIDTH) / 2)))
    return (0);
  mvwprintw(lost, 1, 1, SCORE_FMT, data->score);
  mvwprintw(lost, 3, 1, LINES_FMT, data->nlines);
  mvwprintw(lost, 5, 1, LEVEL_FMT, data->level);
  minutes = (time(NULL) - data->timer) / 60;
  seconds = (time(NULL) - data->timer) % 60;
  mvwprintw(lost, 7, 1, TIMER_FMT, minutes, seconds);
  box(lost, 0, 0);
  mvwprintw(lost, 0, (WINFOS_WIDTH - MY_STRLEN(TITLE_LOST) + 2) / 2,
	    TITLE_LOST);
  wrefresh(lost);
  while ((key = ui_getch(keys, keysize)) >= 0 && key != TTR_KEYQUIT);
  delwin(lost);
  return (1);
}
