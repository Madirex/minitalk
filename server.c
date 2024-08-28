/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmateo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:34:44 by anmateo-          #+#    #+#             */
/*   Updated: 2024/08/28 20:43:56 by anmateo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal_error(char *to_free, int pid, int error_code)
{
	kill(pid, SIGUSR2);
	handle_error(error_code, to_free, 0);
}

char	*append_char(char *str, char c, int reset, int pid)
{
	static int	size = 1;
	int			len;
	char		*new_str;

	if (reset)
	{
		size = 1;
		free(str);
		return (NULL);
	}
	len = -1;
	new_str = malloc(size + 1);
	if (!new_str)
		handle_signal_error(str, pid, 4);
	if (str)
	{
		while (str[++len])
			new_str[len] = str[len];
	}
	new_str[size - 1] = c;
	new_str[size++] = '\0';
	free(str);
	return (new_str);
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	pos = 0;
	static char	*message = NULL;

	(void)context;
	if (!info->si_pid)
		handle_error(2, message, 0);
	if (sig == SIGUSR2)
		c |= (1 << (7 - pos));
	pos++;
	if (pos == 8)
	{
		if (c)
			message = append_char(message, c, 0, info->si_pid);
		else
		{
			ft_putstr_fd("\n📲 Cliente: ", 1);
			ft_putstr_fd(message, 1);
			message = append_char(message, c, 1, 0);
		}
		pos = 0;
		c = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		handle_signal_error(message, info->si_pid, 3);
}

int	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGKILL);
	act.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putstr_fd("🚀Servidor iniciado\nPID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
