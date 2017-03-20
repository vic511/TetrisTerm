#ifndef MY_PRINTF_H_
# define MY_PRINTF_H_

# define PRINTF_FMTS		"sSxXcbpdioun"
# define PRINTF_FMTS_NB		12
# define PRINTF_BASE		"0123456789abcdef"
# define PRINTF_BASE_UPPER	"0123456789ABCDEF"
# define PRINTF_FCHAR		(1 << 0)
# define PRINTF_FSHORT		(1 << 1)
# define PRINTF_FALT		(1 << 2)
# define PRINTF_FSIGN		(1 << 3)
# define PRINTF_FBLANK		(1 << 4)
# define PRINTF_FZERO		(1 << 5)
# define PRINTF_FADJ		(1 << 6)

# include <stdarg.h>

typedef struct	s_fmt_params
{
  va_list	list;
  va_list	orig;
  char		fmt;
  unsigned int	shift;
  int		counter;
  unsigned int	index;
  unsigned int	flags;
  int		length;
  int		padding;
}		t_fmt_params;

int	my_printf(const char *, ...);
void	my_printf_dap(const char *, t_fmt_params *);
void	my_printf_lm(const char *, t_fmt_params *);
void	my_printf_flags(const char *, t_fmt_params *);
void	my_printf_pad(const char *, t_fmt_params *);
int	my_printf_bitlen(unsigned long, int);
int	my_printf_slen(char *);
int	my_printf_dlen(int);
int	my_printf_s(t_fmt_params *);
int	my_printf_S(t_fmt_params *);
int	my_printf_o(t_fmt_params *);
int	my_printf_x(t_fmt_params *);
int	my_printf_X(t_fmt_params *);
int	my_printf_c(t_fmt_params *);
int	my_printf_b(t_fmt_params *);
int	my_printf_d(t_fmt_params *);
int	my_printf_p(t_fmt_params *);
int	my_printf_u(t_fmt_params *);
int	my_printf_n(t_fmt_params *);

#endif /* !MY_PRINTF_H_ */
