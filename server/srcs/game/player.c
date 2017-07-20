/*
** player.c for Player in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 09:57:45 2017 Jean Walrave
** Last update Tue Jul 18 18:43:50 2017 Jean Walrave
*/

#include <stdlib.h>
#include <math.h>
#include "argparser.h"
#include "game.h"

extern t_argp_options	g_options;

t_player	*create_player(void)
{
  static int	id = 0;
  t_player	*player;

  if ((player = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  player->id = id++;
  reset_player(player);
  return (player);
}

void	reset_player(t_player *player)
{
  player->score = 0;
  player->x = 0;
  player->y = (int)(g_options.map->height / 2);
  player->velocity = 0;
  player->is_ready = false;
  player->is_firing = false;
  player->is_dead = false;
}

float	get_player_y(t_player *player)
{
  return (g_options.map->height - 1 - player->y);
}

float	get_player_position(t_player *player, double (*callback)(double))
{
  return ((g_options.map->width * callback(get_player_y(player))) \
	  + callback(player->x));
}

void		player_earn_coin(t_nclient *nclients, t_player *player, \
				 int position)
{
  double	(*callback)(double);

  player->score++;
  callback = position == get_player_position(player, &ceil) ? &ceil : &floor;
  g_options.map->str[position] = CELL_TAKEN_COIN;
  while (nclients)
    {
      message_to_nclient(nclients, "COIN %d %d %d\n",	\
                         player->id,			\
                         (int)callback(player->x),	\
                         (int)callback(player->y));
      nclients = nclients->next;
    }
}
