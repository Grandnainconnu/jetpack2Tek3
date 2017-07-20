/*
** map.c for Map in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 20:20:30 2017 Jean Walrave
** Last update Mon Jul 17 23:06:52 2017 Jean Walrave
*/

#include <stdlib.h>
#include "map.h"

static int	get_map_width(const char *map)
{
  int	i;
  int	width;

  width = 0;
  i = -1;
  while (map[++i] && map[i] != '\n')
    width++;
  return (width);
}

static int      get_map_height(const char *map)
{
  int           i;
  int           height;

  height = 1;
  i = -1;
  while (map[++i])
    if (map[i] == '\n')
      height++;
  return (height);
}

static bool	is_valid_width(const char *map)
{
  int		i;
  int		width;
  int		twidth;

  width = get_map_width(map);
  twidth = 0;
  i = -1;
  while (map[++i])
    {
      if (map[i] != '\n')
	twidth++;
      else if (twidth != width)
	return (false);
      else
	twidth = 0;
    }
  return (true);
}

t_map		*create_map(char *map)
{
  int		i[2];
  t_map		*nmap;

  if (is_valid_width(map) == false || (nmap = malloc(sizeof(t_map))) == NULL)
    return (NULL);
  nmap->width = get_map_width(map);
  nmap->height = get_map_height(map);
  if ((nmap->str = malloc(nmap->width * nmap->height + 1)) == NULL)
    return (NULL);
  i[0] = 0;
  i[1] = 0;
  while (map[i[0]])
    {
      if (map[i[0]] != '\n')
	{
	  nmap->str[i[1]] = map[i[0]];
	  i[1]++;
	}
      i[0]++;
    }
  nmap->str[i[1]] = '\0';
  return (nmap);
}

void	reset_map(t_map *map)
{
  int	i;

  i = -1;
  while (map->str[++i])
    {
      if (map->str[i] == CELL_TAKEN_COIN)
	map->str[i] = CELL_COIN;
    }
}
