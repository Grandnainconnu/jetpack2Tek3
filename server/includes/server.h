/*
** server.h for Server in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 09:49:42 2017 Jean Walrave
** Last update Mon Jul 17 09:55:58 2017 Jean Walrave
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/time.h>
# include "network.h"

typedef struct		s_server
{
  t_nserver		*nserver;
  bool			game_is_running;
  struct timeval	clock;
}			t_server;

#endif /* !SERVER_H_ */
