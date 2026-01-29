/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:47:25 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/29 21:02:41 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	long long	num;
	int			sign;

	sign = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '+') - (*str == '-');
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && num > (num * 10 + (*str - 48)))
			return (-1);
		else if (sign == -1 && - num < (-num * 10 - (*str - 48)))
			return (0);
		num = num * 10 + (*str++ - 48);
	}
	num *= sign;
	return ((int)num);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n == INT_MIN)
	{
		c = -(n % 10) + '0';
		ft_putnbr(n / 10);
		write(1, &c, 1);
	}
	else if (n < 0)
	{
		c = -n;
		write(1, "-", 1);
		write(1, &c, 1);
	}
	else if (n > 9)
	{
		c = n % 10 + '0';
		ft_putnbr(n / 10);
		write(1, &c, 1);
	}
	else if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

void	ft_sigaction(t_sigaction *sa)
{
	int	v;

	v = sigaction(SIGUSR1, sa, NULL);
	v += sigaction(SIGUSR2, sa, NULL);
	if (v)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	ft_mask(sigset_t *set)
{
	int	v;

	v = sigemptyset(set);
	v += sigaddset(set, SIGUSR1);
	v += sigaddset(set, SIGUSR2);
	if (v)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	ft_kill(int pid, int sig)
{
	if (sig == SIGUSR1 && kill(pid, SIGUSR1))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	else if (sig == SIGUSR2 && kill(pid, SIGUSR2))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}
