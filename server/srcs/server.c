/*
** server.c for Server in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 08:29:49 2017 Jean Walrave
** Last update Mon Jul 17 22:45:15 2017 Jean Walrave
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "argparser.h"
#include "network.h"
#include "server.h"

t_argp_options	g_options = {0, 0, NULL};
t_server	*g_server;

static bool	display_usage(int ac, char **av)
{
  int		i;

  i = 0;
  while (++i < ac)
    if (!strcmp(av[i], "-h") || !strcmp(av[i], "--help"))
      return (true);
  return (false);
}

static t_server	*create_server(int fd)
{
  t_server	*server;

  if ((server = malloc(sizeof(t_server))) == NULL)
    return (NULL);
  server->nserver = create_nserver(fd);
  server->game_is_running = false;
  return (server);
}

static void	quit(int signal)
{
  if (signal == SIGPIPE)
    return ;
  remove_nserver(g_server->nserver);
  free(g_options.map->str);
  free(g_options.map);
  free(g_server);
}

int		main(int ac, char **av)
{
  int		fd;

  if (display_usage(ac, av) == true)
    return (printf("usage: %s -p <port> -g <gravity> -m <map>\n", av[0]), 0);
  if (treat_arguments(ac, av) == false)
    return (fprintf(stderr, ERR_INVALID_ARGUMENTS), 84);
  if ((fd = create_socket_server(g_options.port)) == -1 || \
      (g_server = create_server(fd)) == NULL || \
      signal(SIGINT, &quit) == SIG_ERR ||
      signal(SIGPIPE, &quit) == SIG_ERR)
    return (-1);
  socket_server_listen(g_server->nserver);
  return (0);
}
