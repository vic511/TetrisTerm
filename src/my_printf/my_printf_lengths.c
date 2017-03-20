#include "my.h"
#include "my_printf.h"

int	my_printf_bitlen(unsigned long n, int power)
{
  int	start;

  if (n == 0)
    return (1);
  start = (sizeof(unsigned long) << 3);
  start -= (start % power) + power;
  while (((n >> start) & ((1 << power) - 1)) == 0)
      start -= power;
  return (start / power + 1);
}

int	my_printf_slen(char *s)
{
  int	i;
  int	len;

  len = 0;
  i = -1;
  while (s[++i])
      len += 1 + 3 * !(s[i] >= 0x20 && s[i] <= 0x7e);
  return (len);
}

int	my_printf_dlen(int n)
{
  int	len;

  len = 1;
  while ((n <= -10 || n >= 10) && ++len)
    n /= 10;
  return (len);
}
