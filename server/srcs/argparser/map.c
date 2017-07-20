/*
** map.c for Map argument parser in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 10:14:34 2017 Jean Walrave
** Last update Sat Jul 15 10:55:05 2017 Jean Walrave
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "map.h"
#include "argparser.h"

extern t_argp_options	g_options;

static char	*read_map(FILE *file)
{
  int		i;
  int		bsize;
  int		rsize;
  char		*buffer;

  fseek(file, 0, SEEK_END);
  bsize = ftell(file);
  rewind(file);
  if ((buffer = malloc(sizeof(char) * (bsize + 1))) == NULL || \
      (rsize = fread(buffer, 1, bsize, file)) != bsize)
    return (NULL);
  buffer[bsize] = '\0';
  i = -1;
  while (buffer[++i])
    if (buffer[i] == '\n')
      continue;
    else if (buffer[i] != CELL_COIN && buffer[i] != CELL_SPACE	\
	     && buffer[i] != CELL_ELECTRIC_SQUARE)
      return (free(buffer), NULL);
  return (buffer);
}

bool	targument_map(const char *value)
{
  FILE	*file;
  char	*map;

  if ((file = fopen(value, "r")) && (map = read_map(file)) && \
      (g_options.map = create_map(map)))
    return (free(map), fclose(file), true);
  return (false);
}
