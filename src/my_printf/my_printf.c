#include <stdlib.h>
#include "my.h"
#include "my_printf.h"

static void	get_funcs(int (**)(t_fmt_params *));
static void	init_params(const char *, t_fmt_params *);
static void	parse_format(t_fmt_params *);

int		my_printf(const char *fmt, ...)
{
  int		i;
  va_list	list;
  t_fmt_params	params;

  va_start(list, fmt);
  params.index = 0;
  params.length = 0;
  va_copy(params.list, list);
  i = -1;
  while (fmt[++i])
    {
      if (fmt[i] != '%')
	{
	  params.length += my_putchar(fmt[i]);
	  continue;
	}
      va_copy(params.orig, list);
      init_params(&fmt[i], &params);
      parse_format(&params);
      i += params.shift;
    }
  va_end(list);
  return (params.length);
}

static void	init_params(const char *fmt, t_fmt_params *params)
{
  params->flags = 0;
  my_printf_dap(fmt, params);
  my_printf_flags(fmt, params);
  my_printf_pad(fmt, params);
  my_printf_lm(fmt, params);
  va_copy(params->list, params->orig);
  while (--params->counter > 0)
    va_arg(params->list, int);
  params->fmt = fmt[params->shift];
}

static void	parse_format(t_fmt_params *params)
{
  char		*pos;
  int		(*funcs[PRINTF_FMTS_NB])(t_fmt_params *);

  pos = my_strrchr(PRINTF_FMTS, params->fmt);
  if (!pos)
    {
      params->shift = my_putchar('%') * (params->fmt == '%');
      --params->index;
      ++params->length;
      return ;
    }
  get_funcs(funcs);
  params->length += funcs[pos - PRINTF_FMTS](params);
}

static void	get_funcs(int (**funcs)(t_fmt_params *))
{
  funcs[0] = &my_printf_s;
  funcs[1] = &my_printf_S;
  funcs[2] = &my_printf_x;
  funcs[3] = &my_printf_X;
  funcs[4] = &my_printf_c;
  funcs[5] = &my_printf_b;
  funcs[6] = &my_printf_p;
  funcs[7] = &my_printf_d;
  funcs[8] = &my_printf_d;
  funcs[9] = &my_printf_o;
  funcs[10] = &my_printf_u;
  funcs[11] = &my_printf_n;
}
