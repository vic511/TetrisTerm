#include <unistd.h>
#include "my.h"

int		my_putchar(char c)
{
  return (write(1, &c, 1));
}

int		my_putstr(const char *d)
{
  size_t	p;
  int		f;

  f = 1;
  p = 0;
  while (d[p] && ++p);
  return (write(f, d, p));
}

int		my_putnbr_u(unsigned int n)
{
  unsigned int	nb;
  int		pow;
  int		len;
  int		i;

  len = 0;
  nb = n;
  pow = 1;
  while (nb >= 10 && ++len)
    {
      nb /= 10;
      pow *= 10;
    }
  i = -1;
  while (++i <= len)
    {
      my_putchar('0' + (n / pow % 10));
      n -= (n / pow * pow);
      pow /= 10;
    }
  return (i);
}

int	my_putnbr_bitwise(unsigned long n, int power, const char *base)
{
  int	start;
  int	i;
  int	len;

  if (my_strlen(base) < 2 || (size_t) (1 << power) > my_strlen(base))
    return (0);
  if (!n)
    return (my_putchar(*base));
  start = (sizeof(unsigned long) << 3);
  start -= (start - (start / power * power)) + power;
  while (((n >> start) & ((1 << power) - 1)) == 0)
    start -= power;
  i = start;
  len = 0;
  while (i >= 0)
    {
      my_putchar(base[(n >> i) & ((1 << power) - 1)]);
      i -= power;
      ++len;
    }
  return (len);
}

int	my_str_repeat(char c, int count)
{
  int	i;

  i = -1;
  while (++i < count)
    write(1, &c, 1);
  return (i);
}
