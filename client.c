/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:11:49 by aarribas          #+#    #+#             */
/*   Updated: 2022/05/27 08:28:07 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <signal.h>
#include <zconf.h>

static int	send_bin(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (--bit > -1)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
	}
	return (0);
}

static int	ft_process_client(int pid_id, char *str)
{
	int	i;

	i = 0;
	while (str[i] >= ' ' && str[i] <= '~')
	{
		if (send_bin(pid_id, SIGUSR1))
			return (1);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		kill(pid_id, SIGUSR1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	pid_id;

	if (ac < 3)
	{
		ft_putstr_fd("Necesitas insertar PID y string\n", 1);
		return (1);
	}
	if (ac == 3)
	{
		pid_id = ft_atoi(av[1]);
		if (pid_id == 0)
			return (1);
		if (pid_id)
			ft_process_client(pid_id, av[2]);
	}
	return (0);
}
