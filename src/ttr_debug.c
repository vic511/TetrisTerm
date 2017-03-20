#include "ttr_debug.h"
#include "my.h"

static void	debug_showminos(const t_minos *minoslist)
{
  unsigned int	len;
  const t_minos	*curr;
  int		i;

  if (!minoslist)
    return ;
  len = 0;
  curr = minoslist;
  while (curr && ++len)
    curr = curr->next;
  my_printf("Tetriminos : %u\n", len);
  curr = minoslist;
  while (curr)
    {
      my_printf("Tetriminos : Name %s : ", curr->name);
      if (!curr->shape)
	MY_PUTSTR("Error\n");
      else if (my_printf("Size %u*%u : Color %d :\n",
			 curr->size.x, curr->size.y, curr->color) && !(i = 0))
	while (i < curr->size.y && my_printf("%s\n", curr->shape[i++]));
      curr = curr->next;
    }
}

static void	debug_printkey(const char *text, const char *key)
{
  size_t	i;
  size_t	j;

  my_putstr(text);
  i = 0;
  while (key[i])
    {
      j = 0;
      while (key[i + j] && key[i + j] != ' ' && key[i + j] != 27)
	j++;
      write(1, &key[i], j);
      if (key[i + j] == ' ')
	MY_PUTSTR("(space)");
      else if (key[i + j] == 27)
	MY_PUTSTR("^E");
      else if (!key[i + j])
	break;
      i += j + 1;
    }
  MY_PUTSTR("\n");
}

void	debug_main(const t_minos *minoslist, const t_opts *options)
{
  if (!options->debug)
    return ;
  MY_PUTSTR("*** DEBUG MODE ***\n");
  debug_printkey("Key Left : ", options->keys[TTR_KEYLEFT]);
  debug_printkey("Key Right : ", options->keys[TTR_KEYRIGHT]);
  debug_printkey("Key Turn : ", options->keys[TTR_KEYTURN]);
  debug_printkey("Key Drop : ", options->keys[TTR_KEYDROP]);
  debug_printkey("Key Quit : ", options->keys[TTR_KEYQUIT]);
  debug_printkey("Key Pause : ", options->keys[TTR_KEYPAUSE]);
  my_printf("Next : %s\n", options->wnext ? "No" : "Yes");
  my_printf("Level : %u\n", options->level);
  my_printf("Size : %u*%u\n", options->mapsize.y, options->mapsize.x);
  debug_showminos(minoslist);
  MY_PUTSTR("Press any key to start Tetris\n");
}

int	debug_getinput(const t_opts *options)
{
  char	buff[16];
  int	len;

  if (!options->debug)
    return (1);
  while (!(len = read(0, buff, sizeof(buff))))
    usleep(1000);
  if (len < 0)
    return (0);
  return (1);
}
