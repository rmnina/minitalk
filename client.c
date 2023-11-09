/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:27:38 by jdufour           #+#    #+#             */
/*   Updated: 2023/11/02 13:59:15 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bits = 0;

long int	ft_atoi(const char *str)
{
	long int	i;
	long int	sign;
	long int	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	ft_error(int i)
{
	if (i == 0)
		ft_printf("Wrong arguments.\
		Try ./client [server pid] \"message\"\n");
	if (i == 1)
		ft_printf("BAD PID\n");
	if (i == 2)
		ft_printf("Error sigaction\n");
	exit(EXIT_FAILURE);
}

void	send_message(char c, pid_t pid)
{
	int		bit;
	int		i;

	i = 0;
	while (i < 8)
	{
		bit = (c & (1 << i));
		if (bit == 0)
		{
			if (kill(pid, SIGUSR1) != 0)
				ft_error(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) != 0)
				ft_error(1);
		}
		i++;
		usleep(400);
	}
}

void	client_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("%d Bits Received !", g_bits);
}

int	main(int argc, char **argv)
{
	int					i;
	pid_t				pid;
	struct sigaction	sigact;

	if (argc != 3 || !is_all_num(argv[1]))
		ft_error(0);
	i = 0;
	pid = ft_atoi(argv[1]);
	sigact.sa_handler = client_handler;
	sigact.sa_flags = 0;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		ft_error(2);
	while (argv[2][i] != '\0')
	{
		send_message(argv[2][i], pid);
		g_bits += 8;
		i++;
	}
	send_message('\0', pid);
	if (g_bits > 9700)
		pause();
	return (0);
}
