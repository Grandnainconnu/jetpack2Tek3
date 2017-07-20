/*
** chooker_map.c for Command hooker map in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network/hookers
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 10:40:05 2017 Jean Walrave
** Last update Mon Jul 17 22:35:04 2017 Jean Walrave
*/

#include <stdio.h>
#include "argparser.h"
#include "network.h"

extern t_argp_options	g_options;

void	command_hooker_map(t_nclient *nclient, \
			   const char *_ __attribute__((unused)))
{
  message_to_nclient(nclient, "MAP %d %d %s\n",
		     g_options.map->width,
		     g_options.map->height,
		     g_options.map->str);
}
