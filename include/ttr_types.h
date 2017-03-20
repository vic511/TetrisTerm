#ifndef TTR_TYPES_H_
# define TTR_TYPES_H_

# include <time.h>

# define TTR_KEYBUFF	(0x10)
# define GAME_DELAY	(1000000 / 1000)
# define UI_DELAY	((1000000 / 12) / GAME_DELAY)
# define MECHA_DELAY	((1000000 / 3) / GAME_DELAY)

# define LEVEL_STEPS	(10)

enum
  {
    TTR_KEYLEFT,
    TTR_KEYRIGHT,
    TTR_KEYTURN,
    TTR_KEYDROP,
    TTR_KEYQUIT,
    TTR_KEYPAUSE,
    TTR_KEYSNB,
    TTR_KEYNONE
  };

typedef struct	s_coords
{
  int		x;
  int		y;
}		t_coords;

typedef struct	s_map
{
  t_coords	size;
  int		*grid;
}		t_map;

typedef struct		s_curr
{
  t_map			mino;
  t_map			rotate;
  t_coords		pos;
  t_coords		realsize;
  const struct s_minos	*ptr;
}			t_curr;

typedef struct		s_data
{
  unsigned int		score;
  unsigned int		level;
  unsigned int		reallines;
  unsigned int		nlines;
  t_curr		curr;
  const struct s_minos	*next;
  time_t		timer;
}			t_data;

#endif /* !TTR_TYPES_H_ */
