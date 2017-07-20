/*
** network.h for Network in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 20:13:00 2017 Jean Walrave
** Last update Mon Jul 17 22:33:37 2017 Jean Walrave
*/

#ifndef NETWORK_H_
# define NETWORK_H_

# define MAX_SOCKET_QUEUE 2
# define MAX_SOCKET_READ_SIZE 4096

typedef struct s_player t_player;

# include <sys/select.h>
# include "game.h"

typedef struct		s_nclient
{
  int			fd;
  t_player		*player;
  struct s_nclient	*next;
}			t_nclient;

typedef struct		s_nserver
{
  int			fd;
  int			hfd;
  fd_set		rfds;
  t_nclient		*nclients;
}			t_nserver;

typedef struct		s_command_hooker
{
  const char		*key;
  void			(*hf)(t_nclient *, const char *);
}			t_command_hooker;

t_nserver	*create_nserver(int);
void		remove_nserver(t_nserver *);

t_nclient	*create_nclient(t_nclient **);
void		read_from_nclient(t_nclient *, char *);
void		reset_nclient(t_nclient *);
void		remove_nclients(t_nclient **);

void		socket_server_listen(t_nserver *);
int		create_socket_server(unsigned int);

int		message_to_nclient(t_nclient *, const char *, ...);
int		message_to_nclients(t_nclient *, const char *, ...);

bool		handle_command(t_nclient *, const char *);
void		command_hooker_id(t_nclient *, const char *);
void		command_hooker_map(t_nclient *, const char *);
void		command_hooker_ready(t_nclient *, const char *);
void		command_hooker_fire(t_nclient *, const char *);

#endif /* !NETWORK_H_ */
