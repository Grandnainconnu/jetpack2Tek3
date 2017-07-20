/*
** game.c for Game in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016/server/srcs
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 11:16:04 2017 Jean Walrave
** Last update Tue Jul 18 18:38:53 2017 Jean Walrave
*/

#include <stdio.h>
#include <math.h>
#include "server.h"
#include "network.h"
#include "argparser.h"
#include "game.h"

extern t_server		*g_server;
extern t_argp_options	g_options;

static bool	game_is_ended(t_nclient *nclients)
{
  while (nclients)
    {
      if (nclients->player->is_dead == true)
	return (true);
      nclients = nclients->next;
    }
  return (false);
}

static t_player	*who_win_game(t_nclient *nclients)
{
  if (nclients->player->is_dead == true && \
      nclients->next && nclients->next->player->is_dead == true && \
      nclients->player->x >= g_options.map->width)
    {
      if (nclients->player->score > nclients->next->player->score)
	return (nclients->player);
      if (nclients->player->score < nclients->next->player->score)
	return (nclients->next->player);
    }
  if (nclients->player->is_dead == true \
      && nclients->next && nclients->next->player->is_dead == false)
    return (nclients->next->player);
  else if (nclients->player->is_dead == false \
	   && nclients->next && nclients->next->player->is_dead == true)
    return (nclients->player);
  return (NULL);
}

static void	end_game(t_nclient *nclients)
{
  t_player	*winner;
  t_nclient	*nclient;

  winner = who_win_game(nclients);
  nclient = nclients;
  while (nclient)
    {
      message_to_nclient(nclient, "FINISH %d\n", winner ? winner->id : -1);
      reset_nclient(nclient);
      nclient = nclient->next;
    }
  reset_map(g_options.map);
  g_server->game_is_running = false;
  printf("Game is over.\n");
}

bool	players_are_ready(t_nclient *nclients)
{
  t_nclient	*nclient;

  nclient = nclients;
  while (nclient)
    {
      if (nclient->player->is_ready == false)
	return (false);
      nclient = nclient->next;
    }
  if (g_server->game_is_running == false)
    {
      message_to_nclients(nclients, "START\n");
      gettimeofday(&(g_server->clock), NULL);
      g_server->game_is_running = true;
      printf("New game is started!\n");
    }
  return (true);
}

void	execute_game_turn(t_nserver *nserver)
{
  if (game_is_ended(nserver->nclients))
    return (end_game(nserver->nclients));
  do_displacement_cycle(nserver->nclients);
  do_collisions(nserver->nclients);
  update_players_positions(nserver->nclients);
  gettimeofday(&(g_server->clock), NULL);
}
