#include "my_printf.h"
#include "my.h"

void	my_printf_dap(const char *fmt, t_fmt_params *params)
{
  int	i;

  params->shift = 1;
  params->counter = -1;
  i = 0;
  if (fmt[1] >= '0' && fmt[1] <= '9')
    {
      while (fmt[i + 1] >= '0' && fmt[i + 1] <= '9')
	++i;
      if (fmt[i + 1] == '$')
	{
	  params->counter = my_getnbr(&fmt[1]);
	  ++i;
	}
    }
  if (params->counter < 0)
    {
      i = 0;
      params->counter = ++params->index;
    }
  params->shift += i;
}

void	my_printf_lm(const char *fmt, t_fmt_params *params)
{
  if (my_strncmp(&fmt[params->shift], "hh", 2) == 0)
    {
      params->flags |= PRINTF_FCHAR;
      params->shift += 2;
    }
  else if (fmt[params->shift] == 'h')
    {
      params->flags |= PRINTF_FSHORT;
      ++params->shift;
    }
}

void	my_printf_flags(const char *fmt, t_fmt_params *params)
{
  char	c;

  while (my_strrchr("#+ 0-", fmt[params->shift]))
    {
      c = fmt[params->shift];
      params->flags |=
	PRINTF_FALT	* (c == '#')	|
	PRINTF_FSIGN	* (c == '+')	|
	PRINTF_FBLANK	* (c == ' ')	|
	PRINTF_FZERO	* (c == '0')	|
	PRINTF_FADJ	* (c == '-');
      ++params->shift;
    }
}

void	my_printf_pad(const char *fmt, t_fmt_params *params)
{
  int	padding;
  int	len;

  padding = my_getnbr(&fmt[params->shift]);
  params->padding = padding;
  len = 0;
  while (fmt[params->shift + len] >= '0' && fmt[params->shift + len] <= '9')
    len++;
  params->shift += len;
}
