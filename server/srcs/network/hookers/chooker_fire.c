/*
** chooker_fire.c for Command hooker fire in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network/hookers
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 10:40:33 2017 Jean Walrave
** Last update Mon Jul 17 09:43:34 2017 Jean Walrave
*/

#include <stdio.h>
#include <stdlib.h>
#include "network.h"

void	command_hooker_fire(t_nclient *nclient, const char *cmd)
{
  nclient->player->is_firing = atoi(cmd + 4);
}
