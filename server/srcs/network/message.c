/*
** message.c for Message in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 18:32:42 2017 Jean Walrave
** Last update Mon Jul 17 22:48:27 2017 Jean Walrave
*/

#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include "network.h"

static bool	fd_is_available(int fd)
{
  return (fcntl(fd, F_GETFL) != -1);
}

int		message_to_nclient(t_nclient *nclient, const char *fmt, ...)
{
  int		wb;
  va_list	args;

  wb = 0;
  if (fd_is_available(nclient->fd))
    {
      va_start(args, fmt);
      wb += vdprintf(nclient->fd, fmt, args);
      va_end(args);
    }
  return (wb);
}

int		message_to_nclients(t_nclient *nclients, \
				    const char *fmt, ...)
{
  int		wb;
  t_nclient	*nclient;
  va_list	args;

  wb = 0;
  nclient = nclients;
  while (nclient)
    {
      if (fd_is_available(nclient->fd))
	{
	  va_start(args, fmt);
	  wb += vdprintf(nclient->fd, fmt, args);
	  va_end(args);
	}
      nclient = nclient->next;
    }
  return (wb);
}
