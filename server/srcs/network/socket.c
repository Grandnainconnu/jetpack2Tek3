/*
** socket.c for Socket in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 19:07:38 2017 Jean Walrave
** Last update Mon Jul 17 23:05:13 2017 Jean Walrave
*/

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "network.h"

static bool	initialize_clients(t_nserver *nserver)
{
  int		i;
  t_nclient	*nclient;

  FD_ZERO(&(nserver->rfds));
  FD_SET(nserver->fd, &(nserver->rfds));
  if (nserver->nclients == NULL)
    {
      i = -1;
      while (++i < MAX_SOCKET_QUEUE)
	if (create_nclient(&(nserver->nclients)) == NULL)
	  return (fprintf(stderr, "Unable to create client '%d'.\n", i), false);
    }
  nclient = nserver->nclients;
  while (nclient)
    {
      if (nclient->fd != -1)
	{
	  FD_SET(nclient->fd, &(nserver->rfds));
	  nserver->hfd = nclient->fd > nserver->hfd ? \
	    nclient->fd : nserver->hfd;
	}
      nclient = nclient->next;
    }
  return (true);
}

static int		accept_socket_client(t_nserver *nserver)
{
  int			socket_client_size;
  int			nclient_fd;
  t_nclient		*nclient;
  struct sockaddr_in	socket_client;

  socket_client_size = sizeof(socket_client);
  if ((nclient_fd = accept(nserver->fd, (struct sockaddr *)&socket_client, \
			   (socklen_t *)&socket_client_size)) < 0)
    return (-1);
  nclient = nserver->nclients;
  while (nclient)
    {
      if (nclient->fd == -1)
	{
	  printf("[+] New client '%d' !\n", nclient_fd);
	  return ((nclient->fd = nclient_fd), 0);
	}
      nclient = nclient->next;
    }
  close(nclient_fd);
  return (-1);
}

static void	listen_from_client(t_nserver *nserver)
{
  char		buffer[MAX_SOCKET_READ_SIZE];
  t_nclient	*nclient;

  nclient = nserver->nclients;
  while (nclient)
    {
      if (FD_ISSET(nclient->fd, &(nserver->rfds)))
	{
	  memset(buffer, 0, MAX_SOCKET_READ_SIZE);
	  if (!recv(nclient->fd, buffer, MAX_SOCKET_READ_SIZE, 0))
	    nclient->player->is_dead = true;
	  else
	    read_from_nclient(nclient, buffer);
	}
      nclient = nclient->next;
    }
}

void			socket_server_listen(t_nserver *nserver)
{
  listen(nserver->fd, MAX_SOCKET_QUEUE);
  printf("[+] Waiting for incoming connections...\n");
  while (initialize_clients(nserver) != false)
    {
      if (select(nserver->hfd + 1, &(nserver->rfds), NULL, NULL, \
		 &(struct timeval){0, 50000}) == -1)
	{
	  fprintf(stderr, "Erreur\n");
	  break;
	}
      if (FD_ISSET(nserver->fd, &(nserver->rfds)) && \
	  accept_socket_client(nserver) == -1)
	fprintf(stderr, "[-] Unable to accept client.\n");
      listen_from_client(nserver);
      if (players_are_ready(nserver->nclients))
	execute_game_turn(nserver);
    }
}

int			create_socket_server(unsigned int port)
{
  int                   fd;
  struct sockaddr_in    server;
  struct protoent	*tcpp;

  if ((tcpp = getprotobyname("TCP")) == NULL ||
      (fd = socket(AF_INET, SOCK_STREAM, tcpp->p_proto)) == -1)
    return (fprintf(stderr, "[-] Could not create socket\n"), -1);
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    return (fprintf(stderr, "[-] Could not set SO_REUSEADDR\n"), -1);
  printf("[+] Socket created\n");
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);
  if (bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    return (fprintf(stderr, "[-] Bind failed\n"), -1);
  printf("[+] Bind done\n");
  return (fd);
}
