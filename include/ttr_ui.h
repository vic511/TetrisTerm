#ifndef TTR_UI_H_
# define TTR_UI_H_

# include <stdbool.h>
# include <ncurses.h>
# include "ttr_types.h"

# define MIN(N1, N2)	((N1) < (N2) ? (N1) : (N2))

# define ERR_TOOSMALL	"Terminal too small!"
# define MSG_PAUSE	"PAUSE"
# define FIELD_HSCORE	"High Score"
# define FIELD_SCORE	"Score"
# define FIELD_LINES	"Lines"
# define FIELD_LEVEL	"Level"
# define FIELD_TIMER	"Timer"

# define UI_SEPLEN	2
# define TITLE_INFOS	"INFORMATIONS"
# define WINFOS_HEIGHT	7
# define WINFOS_WIDTH	28
# define TITLE_MAP	"TETRISTERM"
# define TITLE_NEXT	"NEXT"
# define WNEXT_HEIGHT	6
# define WNEXT_WIDTH	12
# define WPAUSE_HEIGHT	1
# define WPAUSE_WIDTH	7
# define TITLE_LOST	"WELL PLAYED !"

# define SCORE_FMT	"Score%23u"
# define LINES_FMT	"Lines%23u"
# define LEVEL_FMT	"Level%23u"
# define TIMER_FMT	"Timer                  %02u:%02u"

# define SOUND_CMDLEN	256
# define SOUND_MUSIC	"sounds/music.wav"
# define SOUND_PAUSE	"sounds/pause.wav"
# define SOUND_TRIPLE	"sounds/triple.wav"
# define SOUND_WOAH	"sounds/woah.wav"

# define UI_COLORMAX		MIN(7, COLOR_PAIRS)
# define UI_COLORON(W, C)	wattron(W, COLOR_PAIR(C % UI_COLORMAX + 1))
# define UI_COLOROFF(W, C)	wattroff(W, COLOR_PAIR(C % UI_COLORMAX + 1))

typedef struct		s_win
{
  WINDOW		*map;
  t_coords		dmap;
  t_coords		pmap;
  WINDOW		*infos;
  t_coords		pinfos;
  WINDOW		*next;
  t_coords		dnext;
  t_coords		pnext;
  t_coords		size;
}			t_win;

int	ui_init(t_win *, bool);
void	ui_end(const t_win *);
void	ui_checktermsize(const t_win *, time_t *);
int	ui_getch(const char * const *, size_t);
void	ui_computepos(t_win *);
void	ui_write(const t_map *, const t_win *, const t_data *);
int	ui_pause(time_t *, const char * const *, size_t);
int	ui_soundsplay(size_t, ...);
int	ui_soundskill(void);
int	ui_lost(const t_data *, const char * const *, size_t);
void	ui_colorinit(void);

#endif /* !TTR_UI_H_ */
