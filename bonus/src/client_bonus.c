/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:32:01 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/29 21:20:42 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	ft_isdigits(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!*str)
		return (1);
	return (0);
}

static int	ft_ready(int i)
{
	static int	ready;

	if (i == 1)
		ready = 1;
	else if (i == 0)
		ready = 0;
	return (ready);
}

static void	ft_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Done\n", 5);
		exit(0);
	}
	ft_ready(1);
}

static void	ft_sender(unsigned char c, int pid)
{
	unsigned char	v;

	v = 0;
	while (v++ < CHAR_BIT)
	{
		ft_ready(0);
		if (c & 1)
			ft_kill(pid, SIGUSR1);
		else
			ft_kill(pid, SIGUSR2);
		while (!ft_ready(-1))
			usleep(1);
		c >>= 1;
	}
}

int	main(int argc, char **argv)
{
	t_sigaction	sa;
	char		*str;
	int			pid;

	if (argc != 3)
		return (write(2, "Error\n", 6), 1);
	ft_mask(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_handler;
	ft_sigaction(&sa);
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || !ft_isdigits(argv[1]))
		return (write(2, "Error\n", 6), 1);
	str = argv[2];
	while (*str)
		ft_sender(*str++, pid);
	ft_sender(*str, pid);
	return (0);
}
