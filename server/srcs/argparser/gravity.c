/*
** gravity.c for Gravity argument parser in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 10:23:55 2017 Jean Walrave
** Last update Thu Jul 13 20:18:56 2017 Jean Walrave
*/

#include <stdlib.h>
#include "server.h"
#include "argparser.h"

extern t_argp_options	g_options;

bool	targument_gravity(const char *value)
{
  g_options.gravity = atof(value);
  return (true);
}
