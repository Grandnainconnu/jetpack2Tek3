/*
** hooker.c for Hooker in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/network/hookers
**
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 10:29:49 2017 Jean Walrave
** Last update Mon Jul 17 09:04:08 2017 Jean Walrave
*/

#include <string.h>
#include "network.h"

static t_command_hooker	g_command_hookers[] = {
  {"ID", &command_hooker_id},
  {"MAP", &command_hooker_map},
  {"READY", &command_hooker_ready},
  {"FIRE", &command_hooker_fire},
};

bool	handle_command(t_nclient *nclient, const char *command)
{
  int	i;

  i = -1;
  while (++i < (int)(sizeof(g_command_hookers) / sizeof(t_command_hooker)))
    {
      if (!strncmp(g_command_hookers[i].key, command, \
		   strlen(g_command_hookers[i].key)))
	return (g_command_hookers[i].hf(nclient, command), true);
    }
  return (false);
}
