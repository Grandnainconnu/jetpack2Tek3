/*
** game.h for Game in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016
** 
** Made by Jean Walrave
** Login   <jean.walrave@epitech.net>
** 
** Started on  Fri Jul 14 09:19:46 2017 Jean Walrave
** Last update Tue Jul 18 18:23:52 2017 Jean Walrave
*/

#ifndef GAME_H_
# define GAME_H_

typedef struct s_nclient t_nclient;
typedef struct s_nserver t_nserver;

# include <stdbool.h>
# include "network.h"

typedef struct	s_player
{
  int		id;
  float		x;
  float		y;
  float		velocity;
  int		score;
  bool		is_ready;
  bool		is_firing;
  bool		is_dead;
}		t_player;

t_player	*create_player(void);
float		get_player_y(t_player *);
float		get_player_position(t_player *, double (*)(double));
void		reset_player(t_player *);

bool		players_are_ready(t_nclient *);
void		player_earn_coin(t_nclient *, t_player *, int);
void		execute_game_turn(t_nserver *);

void		update_players_positions(t_nclient *);
void		do_displacement_cycle(t_nclient *);
void		do_collisions(t_nclient *);

#endif /* !GAME_H_ */
