#ifndef TTR_GAME_H_
# define TTR_GAME_H_

# include <ncurses.h>
# include <termios.h>
# include <stdbool.h>
# include "ttr_opts.h"
# include "ttr_minos.h"
# include "ttr_ui.h"
# include "ttr_types.h"

typedef struct		s_game
{
  t_data		data;
  t_map			map;
  t_minos		*minos;
  t_opts		opts;
  t_win			wins;
  size_t		keysize;
  struct termios	oldterm;
}			t_game;

int	game_init(t_game *);
int	game_end(t_game *);
int	game_main(t_game *);

#endif /* !TTR_GAME_H_ */
