#ifndef TTR_OPTS_H_
# define TTR_OPTS_H_

# include <stddef.h>
# include <stdbool.h>
# include "ttr_types.h"

# define OPTS_TERMUP	"kcuu1"
# define OPTS_TERMLEFT	"kcub1"
# define OPTS_TERMDOWN	"kcud1"
# define OPTS_TERMRIGHT	"kcuf1"
# define OPTS_BUFFLEN	16

typedef struct	s_opts
{
  const char	*keys[TTR_KEYSNB];
  unsigned int	level;
  bool		debug;
  bool		wnext;
  bool		help;
  t_coords	mapsize;
}		t_opts;

typedef struct	s_optparam
{
  const char	*longname;
  const char	*shortname;
  bool		reqarg;
  void		*data;
  int		(*apply)(char * const *, const struct s_optparam *);
}		t_optparam;

int	opts_init(t_opts *);
int	opts_parse(int, char * const *, const t_optparam *);
int	opts_setbool(char * const *, const t_optparam *);
int	opts_setkey(char * const *, const t_optparam *);
int	opts_setmapsize(char * const *, const t_optparam *);
int	opts_setlevel(char * const *, const t_optparam *);
int	opts_checkconflicts(const t_opts *);

#endif /* !TTR_OPTS_H_ */
