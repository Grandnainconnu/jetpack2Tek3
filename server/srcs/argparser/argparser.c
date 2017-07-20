/*
** argparser.c for Arguments parser in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 09:43:56 2017 Jean Walrave
** Last update Thu Jul 13 17:43:40 2017 Jean Walrave
*/

#include <unistd.h>
#include <stdio.h>
#include "argparser.h"

static t_argp_treatment	g_argp_treatments[] = {
  {'p', &targument_port},
  {'g', &targument_gravity},
  {'m', &targument_map},
};

bool	treat_arguments(int argc, char **argv)
{
  int	i;
  int	option;
  int	options[2];

  options[0] = 0;
  options[1] = (int)(sizeof(g_argp_treatments) / sizeof(t_argp_treatment));
  while ((option = getopt(argc, argv, ":p:g:m:")) != -1)
    {
      i = -1;
      while (++i < options[1])
	if (g_argp_treatments[i].key == option)
	  {
	    if (g_argp_treatments[i].tf(optarg) == true)
	      options[0]++;
	  }
      if (i > options[1])
	break;
    }
  return (options[0] == options[1]);
}
