/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhoshina <fhoshina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:22:28 by fhoshina          #+#    #+#             */
/*   Updated: 2024/11/29 00:42:59 by fhoshina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*string_func(char *string, char string_number)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	// if (string == NULL)
	// 	tmp = malloc(2);
	// else
	tmp = malloc(ft_strlen(string) + 2 * sizeof(char));
	if (!tmp)
		return (NULL);
	while (string[i])
		tmp[j++] = string[i++];
	tmp[j++] = (char)string_number;
	tmp[j] = '\0';
	free(string);
	return (tmp);
}

int	comeback_func(int nb, int num)
{
	int res;
	res = 0;
	if (num == 0)
		return (1);
	else if (num < 0)
		return (0);
	else
	{
		res += nb * comeback_func(2, num - 1);
		return (res);
	}
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	bitcnt = 0;
	static int	string_number = 0;
	static int	string_end_number = 0;
	static char	*string;

	if (!string)
		string = ft_strdup("");
	if (sig == SIGUSR1)
		string_number = string_number + 0;
	if (sig == SIGUSR2)
		string_number = string_number + (comeback_func(2, 7 - bitcnt));
	bitcnt++;
	if (bitcnt == 8)
	{
		string = string_func(string, string_number);
		if (string_number == '\0')
		{
			ft_printf("%s\n", string);
			free(string);
			string = NULL;
		}
		string_number = 0;
		bitcnt = 0;

		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction signal;

	printf("server pid = %d\n", getpid());

	signal.sa_sigaction = signal_handler;
	signal.sa_flags = 0;
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);

	while (1)
		pause();
}