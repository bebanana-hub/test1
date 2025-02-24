/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:44:15 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 18:28:50 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "so_long.h"

# define MAX_TEXTURE 10

//? # define PATH "./assets/"

//? #define GR1 PATH "ground/ground1.png"
//? #define GR2 PATH "ground/ground2.png"
//? #define GR3 PATH "ground/ground3.png"

//? #define WL PATH "wall/wall.png"

//? #define COLL_FULL PATH "loot/Chest_full.png"
//? #define COLL_EMPTY PATH "loot/Chest_empty.png"

//? #define OP_EX PATH "exit/Open_exit.png"
//? #define CL_EX PATH "exit/Closed_exit.png"

//? #define R_PL PATH "Player/Player_R1.png"
//? #define L_PL PATH "Player/Player_L1.png"

extern char	*g_a_path[MAX_TEXTURE];

//? char *A_PATH[MAX_TEXTURE] ={
//? 	GR1,
//? 	GR2,
//? 	GR3,
//? 	WL,
//? 	COLL,
//? 	CL_EX,
//? 	OP_EX,
//? 	R_PL,
//? };

enum e_IN_A
{
	IN_GR1,
	IN_GR2,
	IN_GR3,
	IN_WL,
	IN_COLL_FULL,
	IN_COLL_EMPTY,
	IN_CL_EX,
	IN_OP_EX,
	IN_R_PL,
	IN_L_PL,
};

#endif
