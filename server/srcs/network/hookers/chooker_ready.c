/*
** chooker_ready.c for Command hooker ready in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network/hookers
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 10:40:17 2017 Jean Walrave
** Last update Fri Jul 14 10:51:26 2017 Jean Walrave
*/

#include "network.h"

void	command_hooker_ready(t_nclient *nclient, \
			     const char *_ __attribute__((unused)))
{
  nclient->player->is_ready = true;
}
