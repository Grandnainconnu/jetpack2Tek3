/*
** argparser.h for Arguments parser in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 08:34:37 2017 Jean Walrave
** Last update Tue Jul 18 01:22:13 2017 Mex
*/

#ifndef ARGPARSER_H_
# define ARGPARSER_H_

# define ERR_INVALID_ARGUMENTS "Arguments invalides\n"

# include <stdbool.h>
# include "map.h"

typedef struct	s_argp_treatment
{
  char		key;
  bool		(*tf)(const char *);
}		t_argp_treatment;

typedef struct	s_argp_options
{
  unsigned int	port;
  float		gravity;
  t_map		*map;
}		t_argp_options;

bool	targument_port(const char *);
bool	targument_gravity(const char *);
bool	targument_map(const char *);

bool	treat_arguments(int, char **);

#endif /* !ARGPARSER_H_ */
