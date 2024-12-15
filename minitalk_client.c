/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhoshina <fhoshina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:22:03 by fhoshina          #+#    #+#             */
/*   Updated: 2024/12/15 16:16:51 by fhoshina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		ack_received;

void	ack_handler(int signum)
{
	if (signum == SIGUSR1)
		ack_received = 1;
}

void	send_signal(pid_t pid, char *string)
{
	int	i;
	int	j;

	i = 0;
	while (string[i])
	{
		j = 0;
		while (j < 8)
		{
			ack_received = 0;
			if (string[i] >> (7 - j) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!ack_received)
				usleep(100);
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	char	*message;
	pid_t	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (!pid)
		{
			ft_printf("error");
			return (0);
		}
		message = argv[2];
		if (message[0] == 0)
		{
			ft_printf("error");
			return (0);
		}
		signal(SIGUSR1, ack_handler);
		send_signal(pid, message);
	}
	return (0);
}
