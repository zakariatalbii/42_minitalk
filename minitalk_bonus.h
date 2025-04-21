/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:43:29 by zatalbi           #+#    #+#             */
/*   Updated: 2025/04/19 19:13:24 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# define _POSIX_C_SOURCE 199309L
# define _XOPEN_SOURCE 500

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct sigaction	t_sigaction;

int		ft_atoi(const char *str);
void	ft_putnbr(int n);

void	ft_sigaction(t_sigaction *sa);
void	ft_mask(sigset_t *set);
void	ft_kill(int pid, int sig);

#endif