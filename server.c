/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:27:46 by jdufour           #+#    #+#             */
/*   Updated: 2023/10/27 19:41:32 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strjoin_char(char *s1, const char s2)
{
	int		size;
	char	*res;
	int		i;

	i = 0;
	size = 0;
	while (s1 && s1[size])
		size++;
	res = malloc(sizeof(char) * (size + 2));
	if (!(res))
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = s2;
	res[i] = '\0';
	free(s1);
	return (res);
}

void	print_message(int *octet, siginfo_t *c_pid)
{
	static char	*message = NULL;

	if (message == NULL)
	{
		message = (char *)malloc(1);
		message[0] = '\0';
	}
	message = ft_strjoin_char(message, *octet);
	if (*octet == '\0')
	{
		ft_printf("%s\n", message);
		free(message);
		message = NULL;
		kill(c_pid->si_pid, SIGUSR1);
	}
}

void	server_handler(int signum, siginfo_t *c_pid, void *tmp)
{
	static int	octet = 0;
	static int	i = 0;

	(void)tmp;
	if (i < 8)
	{
		if (signum == SIGUSR2)
			octet |= (1 << i);
		i++;
	}
	if (i == 8)
	{
		print_message(&octet, c_pid);
		i = 0;
		octet = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sigact;

	pid = getpid();
	ft_printf("SERVER PID : %d\n", pid);
	sigact.sa_sigaction = server_handler;
	sigact.sa_flags = SA_SIGINFO;
	while (1)
	{
		if (sigaction(SIGUSR1, &sigact, NULL) == -1 || \
		sigaction(SIGUSR2, &sigact, NULL) == -1)
		{
			ft_printf("Sigaction error\n");
			exit(EXIT_FAILURE);
		}
		pause();
	}
	ft_printf("\n");
	return (0);
}
