/*
** nserver.c for Network server in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 20:40:10 2017 Jean Walrave
** Last update Fri Jul 14 09:02:04 2017 Jean Walrave
*/

#include <stdlib.h>
#include <unistd.h>
#include "network.h"

t_nserver	*create_nserver(int fd)
{
  t_nserver	*nserver;

  if ((nserver = malloc(sizeof(t_nserver))) == NULL)
    return (NULL);
  nserver->fd = fd;
  nserver->hfd = fd;
  nserver->nclients = NULL;
  return (nserver);
}

void		remove_nserver(t_nserver *nserver)
{
  close(nserver->fd);
  remove_nclients(&(nserver->nclients));
  free(nserver);
}
