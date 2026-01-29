/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:31:57 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/29 21:23:46 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	ft_handler(int sig, siginfo_t *inf, void *ptr)
{
	static int				pid;
	static unsigned char	c;
	static unsigned char	v;

	(void)ptr;
	if (pid != inf->si_pid)
	{
		pid = inf->si_pid;
		c = 0;
		v = 0;
	}
	if (sig == SIGUSR1)
		c += 1 << v;
	if (++v == CHAR_BIT)
	{
		v = 0;
		if (!c && write(1, "\n", 1) && !kill(pid, SIGUSR1))
			return ;
		else
			write(1, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(int argc, char **argv)
{
	t_sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (0);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	ft_mask(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	ft_sigaction(&sa);
	while (1)
		pause();
	return (0);
}
