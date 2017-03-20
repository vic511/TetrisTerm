#include <stdlib.h>
#include "my_printf.h"
#include "my.h"

int		my_printf_b(t_fmt_params *params)
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
    count += my_str_repeat(' ', params->padding - my_printf_bitlen(n, 1) -
			   2 * !!(params->flags & PRINTF_FALT));
  if (params->flags & PRINTF_FALT)
    count += my_putstr("0b");
  if (!(params->flags & PRINTF_FADJ) && (params->flags & PRINTF_FZERO))
    count += my_str_repeat('0',
			   params->padding - my_printf_bitlen(n, 1) - count);
  count += my_putnbr_bitwise(n, 1, PRINTF_BASE);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int	my_printf_d(t_fmt_params *params)
{
  int	n;
  int	count;

  n = va_arg(params->list, int);
  if (params->flags & PRINTF_FCHAR)
    n = (char) n;
  else if (params->flags & PRINTF_FSHORT)
    n = (short int) n;
  count = 0;
  if (!(params->flags & PRINTF_FADJ) && !(params->flags & PRINTF_FZERO))
    count += my_str_repeat(' ', params->padding - my_printf_dlen(n) -
			   !!((params->flags & PRINTF_FSIGN && n >= 0) |
			      (params->flags & PRINTF_FBLANK && n >= 0)));
  if (params->flags & PRINTF_FSIGN && n >= 0)
    count += my_putchar('+');
  else if (params->flags & PRINTF_FBLANK && n >= 0)
    count += my_putchar(' ');
  count += (n < 0 ? my_putchar('-') : 0);
  if (!(params->flags & PRINTF_FADJ) && (params->flags & PRINTF_FZERO))
    count += my_str_repeat('0',
			   params->padding - my_printf_dlen(n) - count);
  count += my_putnbr_u(n < 0 ? -n : n);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int		my_printf_p(t_fmt_params *params)
{
  unsigned long	p;
  int		count;

  p = (unsigned long) va_arg(params->list, void *);
  if (p == (unsigned long) NULL)
    return (my_putstr("(nil)"));
  count = 0;
  if (!(params->flags & PRINTF_FADJ) && !(params->flags & PRINTF_FZERO))
    count += my_str_repeat(' ', params->padding -
			   my_printf_bitlen(p, 4) - 2);
  count += my_putstr("0x");
  if (!(params->flags & PRINTF_FADJ) && (params->flags & PRINTF_FZERO))
    count += my_str_repeat('0',
			   params->padding - my_printf_bitlen(p, 4) - count);
  count += my_putnbr_bitwise(p, 4, PRINTF_BASE);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int		my_printf_o(t_fmt_params *params)
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
    count += my_str_repeat(' ', params->padding - my_printf_bitlen(n, 3) -
			   !!(params->flags & PRINTF_FALT));
  if ((params->flags & PRINTF_FALT) && n != 0)
    count += my_putchar('0');
  if (!(params->flags & PRINTF_FADJ) && (params->flags & PRINTF_FZERO))
    count += my_str_repeat('0',
			   params->padding - my_printf_bitlen(n, 3) - count);
  count += my_putnbr_bitwise(n, 3, PRINTF_BASE);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}

int		my_printf_u(t_fmt_params *params)
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
    count += my_str_repeat(' ', params->padding - my_printf_dlen(n));
  else if (!(params->flags & PRINTF_FADJ))
    count += my_str_repeat('0', params->padding - my_printf_dlen(n));
  count += my_putnbr_u(n);
  if (params->flags & PRINTF_FADJ)
    count += my_str_repeat(' ', params->padding - count);
  return (count);
}
