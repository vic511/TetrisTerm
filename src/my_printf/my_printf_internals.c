#include <stdlib.h>
#include "my.h"
#include "my_printf.h"

int	my_printf_s(t_fmt_params *params)
{
  char	*s;
  int	count;

  count = 0;
  s = va_arg(params->list, char *);
  if (s == NULL)
    s = "(null)";
  if (!(params->flags & PRINTF_FADJ))
    count += my_str_repeat(' ', params->padding - my_strlen(s));
  count += my_putstr(s);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int	my_printf_S(t_fmt_params *params)
{
  char	*s;
  int	count;

  s = va_arg(params->list, char *);
  if (s == NULL)
    s = "(null)";
  count = 0;
  if (!(params->flags & PRINTF_FADJ))
    count += my_str_repeat(' ', params->padding - my_printf_slen(s));
  count += my_showstr_octal(s);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int		my_printf_x(t_fmt_params *params)
{
  unsigned int	n;
  int		count;

  n = va_arg(params->list, unsigned int);
  if (params->flags & PRINTF_FCHAR)
    n = (unsigned char) n;
  else if (params->flags & PRINTF_FSHORT)
    n = (unsigned short int) n;
  count = 0;
  if (!(params->flags & PRINTF_FADJ) && !(params->flags & PRINTF_FZERO))
    count += my_str_repeat(' ', params->padding - my_printf_bitlen(n, 4) -
			   2 * !!(params->flags & PRINTF_FALT));
  if (params->flags & PRINTF_FALT)
    count += my_putstr("0x");
  if (!(params->flags & PRINTF_FADJ) && (params->flags & PRINTF_FZERO))
    count += my_str_repeat('0',
			   params->padding - my_printf_bitlen(n, 4) - count);
  count += my_putnbr_bitwise(n, 4, PRINTF_BASE);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int		my_printf_X(t_fmt_params *params)
{
  unsigned int	n;
  int		count;

  n = va_arg(params->list, unsigned int);
  if (params->flags & PRINTF_FCHAR)
    n = (unsigned char) n;
  else if (params->flags & PRINTF_FSHORT)
    n = (unsigned short int) n;
  count = 0;
  if (!(params->flags & PRINTF_FADJ) && !(params->flags & PRINTF_FZERO))
    count += my_str_repeat(' ', params->padding - my_printf_bitlen(n, 4) -
			   2 * !!(params->flags & PRINTF_FALT));
  if (params->flags & PRINTF_FALT)
    count += my_putstr("0X");
  if (!(params->flags & PRINTF_FADJ) && (params->flags & PRINTF_FZERO))
    count += my_str_repeat('0',
			   params->padding - my_printf_bitlen(n, 4) - count);
  count += my_putnbr_bitwise(n, 4, PRINTF_BASE_UPPER);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int	my_printf_c(t_fmt_params *params)
{
  char	c;
  int	count;

  count = 0;
  c = va_arg(params->list, int);
  if (!(params->flags & PRINTF_FADJ))
    count += my_str_repeat(' ', params->padding - 1);
  count += my_putchar(c);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}
