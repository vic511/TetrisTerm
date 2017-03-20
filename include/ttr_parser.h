#ifndef TTR_PARSER_H_
# define TTR_PARSER_H_

# include "ttr_game.h"
# include "ttr_minos.h"

int	parser_parse(t_minos *, const t_coords *);
int	parser_checkminos(const t_minos *);

#endif /* !TTR_PARSER_H_ */
