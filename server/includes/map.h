/*
** map.h for Map in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Thu Jul 13 18:52:23 2017 Jean Walrave
** Last update Mon Jul 17 23:07:08 2017 Jean Walrave
*/

#ifndef MAP_H_
# define MAP_H_

# define CELL_COIN 'c'
# define CELL_TAKEN_COIN '-'
# define CELL_SPACE '_'
# define CELL_ELECTRIC_SQUARE 'e'

# include <stdbool.h>

typedef struct	s_map
{
  unsigned int	width;
  unsigned int	height;
  char		*str;
}		t_map;

t_map	*create_map(char *);
void	reset_map(t_map *);

#endif /* !MAP_H_ */
