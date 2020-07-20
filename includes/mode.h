/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:04:29 by sseo              #+#    #+#             */
/*   Updated: 2020/07/16 13:20:41 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_H
# define MODE_H

#ifdef DEV_MODE
# define INITIAL_HP 100
# define BULLET_INIT_CNT 20
# define ENEMY_VIEWING_ANGLE 0.7
# define ENEMY_MV_SPD 0.03
# define ENEMY_ATK_SPD 1000000
# define ENEMY_DMG 0
# define BOSS_DMG 0
# define TRAP_DMG 10
# define POTION_DMG 30
# define HIT_PAUSE 100000
#endif

#ifdef BABY_MODE
# define INITIAL_HP 100
# define BULLET_INIT_CNT 20
# define ENEMY_VIEWING_ANGLE 0.7
# define ENEMY_MV_SPD 0.01
# define ENEMY_ATK_SPD 200000
# define ENEMY_DMG 1
# define BOSS_DMG 15
# define TRAP_DMG 10
# define POTION_DMG 30
# define HIT_PAUSE 100000
#endif

#ifdef NORMAL_MODE
# define INITIAL_HP 100
# define BULLET_INIT_CNT 20
# define ENEMY_VIEWING_ANGLE 0.7
# define ENEMY_MV_SPD 0.02
# define ENEMY_ATK_SPD 300
# define ENEMY_DMG 15
# define BOSS_DMG 20
# define TRAP_DMG 10
# define POTION_DMG 30
# define HIT_PAUSE 100000
#endif

#ifdef HARD_MODE
# define INITIAL_HP 100
# define BULLET_INIT_CNT 20
# define ENEMY_VIEWING_ANGLE 0.7
# define ENEMY_MV_SPD 0.03
# define ENEMY_ATK_SPD 300
# define ENEMY_DMG 15
# define BOSS_DMG 30
# define TRAP_DMG 10
# define POTION_DMG 30
# define HIT_PAUSE 100000
#endif

#endif
