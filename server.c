/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:11:53 by aarribas          #+#    #+#             */
/*   Updated: 2022/05/28 13:25:37 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int			status = 1;

static void	ft_client_information(int signal)
{
	static size_t	i;
	static int		bit;
	static char		buf[1002];

	if (--bit == -1) //significa que nos encontramos en la posición 0
	{
		bit = 6; // 6+0 = 7
		i++;     // i = 1;
	}
	buf[i] &= ~(1 << 7); // 0000 0001
	if (signal == SIGUSR1)
		buf[i] |= (1 << bit); //0000 1101
	else if (signal == SIGUSR2)
		buf[i] &= ~(1 << bit);
	if (i == 1001 || buf[i] == 127) // CHAR 127 = DEL
	{
		buf[i] = 0;
		write(1, buf, i + 1);
		ft_memset(buf, '\0', 1001);
		i = 0;
		bit = 0;
	}
}

static void	ft_close_server(int signal)
{
	signal = 2;
	ft_putstr_fd("Servidor down\n", 1);
	status = 0;
}

static void	ft_print_pid(void)
{
	__pid_t	nb_pid;

	nb_pid = getpid();
	if (nb_pid == 0)
		return ;
	ft_putnbr_fd(nb_pid, 1);
}

int	main(int ac, char **av)
{
	*av = NULL;
	if (ac != 1)
	{
		ft_putstr_fd("Server sin parametros.", 1);
		return (1);
	}
	else
	{
		ft_print_pid();
		ft_putchar_fd('\n', 1);
		signal(SIGUSR1, ft_client_information);
		signal(SIGUSR2, ft_client_information);
		signal(SIGINT, ft_close_server);
		while (status)
		{
		}
	}
	return (0);
}
