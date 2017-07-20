/*
** nclient.c for Network client in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 20:34:16 2017 Jean Walrave
** Last update Mon Jul 17 22:22:09 2017 Jean Walrave
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "game.h"
#include "argparser.h"
#include "network.h"

extern t_argp_options	g_options;

t_nclient	*create_nclient(t_nclient **nclients)
{
  t_nclient	*nclient;
  t_nclient	*tmp;

  if ((nclient = malloc(sizeof(t_nclient))) == NULL ||
      (nclient->player = create_player()) == NULL)
    return (NULL);
  nclient->fd = -1;
  nclient->next = NULL;
  if (*nclients)
    {
      tmp = *nclients;
      while (tmp && tmp->next)
	tmp = tmp->next;
      tmp->next = nclient;
    }
  else
    *nclients = nclient;
  return (nclient);
}

void		read_from_nclient(t_nclient *nclient, char *commands)
{
  static char	*delimiters = "\n";
  char		*command;

  command = strtok(commands, delimiters);
  while (command)
    {
      printf("Client %d sent: '%s'\n", nclient->fd, command);
      if ((handle_command(nclient, command)) == false)
	printf("Unable to handle command.\n");
      command = strtok(NULL, delimiters);
    }
}

void		reset_nclient(t_nclient *nclient)
{
  if (nclient->fd != -1)
    close(nclient->fd);
  reset_player(nclient->player);
  nclient->fd = -1;
}

void		remove_nclients(t_nclient **nclients)
{
  t_nclient	*nclient;

  while (*nclients)
    {
      nclient = *nclients;
      *nclients = (*nclients)->next;
      if (nclient->fd != -1)
	close(nclient->fd);
      free(nclient->player);
      free(nclient);
    }
}
