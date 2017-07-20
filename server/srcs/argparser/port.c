/*
** port.c for Port argument parser in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 10:16:55 2017 Jean Walrave
** Last update Thu Jul 13 20:20:12 2017 Jean Walrave
*/

#include <stdlib.h>
#include "server.h"
#include "argparser.h"

extern t_argp_options	g_options;

bool	targument_port(const char *value)
{
  int	port;

  if ((port = atoi(value)) && port > 0 && port < 65535)
    return (g_options.port = port, true);
  return (false);
}
