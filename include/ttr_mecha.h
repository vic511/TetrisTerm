#ifndef TTR_MECHA_H_
# define TTR_MECHA_H_

# include "ttr_game.h"
# include "ttr_types.h"

# define COLOR_ERR	(-1)
# define COLOR_VOID	(0)

enum
  {
    MECHA_ROTUP,
    MECHA_ROTLEFT,
    MECHA_ROTDOWN,
    MECHA_ROTRIGHT,
    MECHA_ROTSNB
  };

int	mecha_fall(t_map *, t_curr *);
int	mecha_freeze(t_map *, t_data *);
int	mecha_handlekey(t_map *, t_data *, int);
int	mecha_update(t_game *, int, unsigned int);
int	mecha_updatescore(t_map *, t_data *);
int	mecha_setpx(const t_map *, int, int, int);
int	mecha_getpx(const t_map *, int, int);

#endif /* !TTR_MECHA_H_ */
