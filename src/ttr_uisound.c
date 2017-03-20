#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "ttr_ui.h"
#include "my.h"

static int	ui_soundplay(char *sound)
{
  char		buff[256];

  sprintf(buff, "aplay -q %s 2>/dev/null", sound);
  system(buff);
  return (1);
}

int		ui_soundsplay(size_t nsounds, ...)
{
  char		*sound;
  va_list	list;
  size_t	i;
  pid_t		pid;

  va_start(list, nsounds);
  i = 0;
  while (i < nsounds)
    {
      sound = va_arg(list, char *);
      if (!(pid = fork()))
	exit(!ui_soundplay(sound));
      else if (pid < 0)
	return (0);
      ++i;
    }
  va_end(list);
  return (1);
}

int		ui_soundskill(void)
{
  system("killall aplay");
  return (1);
}
