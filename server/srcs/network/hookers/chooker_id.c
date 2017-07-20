/*
** chooker_id.c for Command hooker id in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network/hookers
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 10:39:48 2017 Jean Walrave
** Last update Mon Jul 17 22:34:27 2017 Jean Walrave
*/

#include <stdio.h>
#include "network.h"

void	command_hooker_id(t_nclient *nclient, \
			  const char *_ __attribute__((unused)))
{
  message_to_nclient(nclient, "ID %d\n", nclient->player->id);
}
