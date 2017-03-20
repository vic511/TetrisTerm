#ifndef TTR_MINOS_H_
# define TTR_MINOS_H_

# include "ttr_types.h"
# include "my_file.h"

# define MINOS_DIR	"tetriminos/"
# define MINOS_EXT	".tetrimino"
# define MINOS_NAMELEN	(256 - sizeof(MINOS_EXT) - 1)

typedef struct		s_minos
{
  unsigned int		color;
  t_coords		size;
  t_file		*stream;
  char			name[MINOS_NAMELEN];
  char			**shape;
  struct s_minos	*next;
}			t_minos;

t_minos		*minos_getall(const t_coords *);
void		minos_errorfilter(t_minos **);
void		minos_getmax(const t_minos *, t_coords *);
const t_minos	*minos_getrand(const t_minos *);
int		minos_free(t_minos *);
int		minos_freelist(t_minos *);

#endif /* !TTR_MINOS_H_ */
