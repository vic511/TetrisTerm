#include "my.h"

int		my_showstr_octal(const char *str)
{
  size_t	i;
  int		len;

  i = 0;
  len = 0;
  while (str[i])
    {
      if ((str[i] >= 0x20 && str[i] <= 0x7e) == 0)
	{
	  len += my_putchar('\\');
	  if ((str[i] & 007) == str[i])
	    len += my_putstr("00");
	  else if ((str[i] & 077) == str[i])
	    len += my_putstr("0");
	  len += my_putnbr_bitwise((unsigned char) str[i], 3, "01234567");
	}
      else
	len += my_putchar(str[i]);
      ++i;
    }
  return (len);
}

int		my_errmsg(int code, const char *s)
{
  size_t	len;

  len = 0;
  while (s[len] && ++len);
  write(2, s, len);
  write(2, "\n", 1);
  return (code);
}
