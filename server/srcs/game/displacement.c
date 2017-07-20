/*
** displacement.c for Displacement in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs/game
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Mon Jul 17 17:09:31 2017 Jean Walrave
** Last update Tue Jul 18 18:32:20 2017 Jean Walrave
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "server.h"
#include "argparser.h"
#include "game.h"

extern t_server		*g_server;
extern t_argp_options	g_options;

void		update_players_positions(t_nclient *nclients)
{
  t_nclient	*nclient;
  t_nclient	*tnclient;

  nclient = nclients;
  while (nclient)
    {
      tnclient = nclients;
      while (tnclient)
        {
	  message_to_nclient(nclient, "PLAYER %d %0.2f %0.2f %d\n", \
			     tnclient->player->id,		    \
			     tnclient->player->x,		    \
			     tnclient->player->y,		    \
			     tnclient->player->score);
          tnclient = tnclient->next;
        }
      nclient = nclient->next;
    }
}

void			do_collisions(t_nclient *nclients)
{
  t_nclient		*nclient;
  int			position[2];

  nclient = nclients;
  while (nclient)
    {
      position[0] = get_player_position(nclient->player, &ceil);
      position[1] = get_player_position(nclient->player, &floor);
      if (g_options.map->width <= nclient->player->x || \
	  g_options.map->str[position[0]] == CELL_ELECTRIC_SQUARE || \
	  g_options.map->str[position[1]] == CELL_ELECTRIC_SQUARE)
	{
	  printf("[player] %d is dead.\n", nclient->player->id);
	  nclient->player->is_dead = true;
	}
      else if (g_options.map->str[position[0]] == CELL_COIN || \
	       g_options.map->str[position[1]] == CELL_COIN)
	{
	  printf("[player] %d hit a coin.\n", nclient->player->id);
	  player_earn_coin(nclients, nclient->player, \
			   (g_options.map->str[position[0]] == CELL_COIN ? \
			    position[0] : position[1]));
	}
      nclient = nclient->next;
    }
}

static void	do_gravity(t_player *player)
{
  double	y;
  double	velocity;

  player->velocity += (player->is_firing ? \
		       -g_options.gravity : g_options.gravity) / 200;
  y = player->y + player->velocity;
  velocity = 0;
  if (y > g_options.map->height - 1)
    y = g_options.map->height - 1;
  else if (y < 0)
    y = 0;
  else
    velocity = player->velocity;
  player->y = y;
  player->velocity = velocity;
}

void			do_displacement_cycle(t_nclient *nclients)
{
  double		x;
  double		y;
  double		displacement;
  struct timeval	now;

  gettimeofday(&now, NULL);
  x = now.tv_sec * 1000000 + now.tv_usec;
  y = g_server->clock.tv_sec * 1000000 + g_server->clock.tv_usec;
  displacement = ((x - y) / 1000000) / 0.2;
  while (nclients)
    {
      nclients->player->x += displacement;
      do_gravity(nclients->player);
      nclients = nclients->next;
    }
}
