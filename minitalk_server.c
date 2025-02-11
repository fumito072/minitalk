/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhoshina <fhoshina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:22:28 by fhoshina          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:32 by fhoshina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	recursive_func(int nb, int num)
{
	int	res;

	res = 0;
	if (num == 0)
		return (1);
	else if (num < 0)
		return (0);
	else
	{
		res += nb * recursive_func(2, num - 1);
		return (res);
	}
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	bitcnt = 0;
	static int	string_number = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		string_number = string_number + 0;
	if (sig == SIGUSR2)
		string_number = string_number + (recursive_func(2, 7 - bitcnt));
	bitcnt++;
	if (bitcnt == 8)
	{
		write(1, &string_number, 1);
		string_number = 0;
		bitcnt = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	signal;

	ft_printf("%d\n", getpid());
	signal.sa_sigaction = signal_handler;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	while (1)
		pause();
}
