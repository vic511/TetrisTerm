#include "my.h"
#include "my_printf.h"

int	my_printf_n(t_fmt_params *params)
{
  void	*ptr;

  ptr = va_arg(params->list, void *);
  if (params->flags & PRINTF_FCHAR)
    *((char *) ptr) = params->length;
  else if (params->flags & PRINTF_FSHORT)
    *((short int *) ptr) = params->length;
  else
    *((int *) ptr) = params->length;
  return (0);
}

