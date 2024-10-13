/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmateo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:33:10 by anmateo-          #+#    #+#             */
/*   Updated: 2024/08/28 20:48:47 by anmateo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal_to_server(int pid, int signal, char *msg)
{
	int	ret;

	if (signal == 1)
		ret = kill(pid, SIGUSR2);
	else if (signal == 0)
		ret = kill(pid, SIGUSR1);
	if (ret == -1)
		handle_error(3, msg, 0);
}

void	send_bit(int server_pid, char *msg, int state)
{
	static char	*copy = NULL;
	static int	bit_index = -1;
	static int	char_index = 0;
	static int	pid = 0;
	int			signal;

	if (bit_index == 8 || state == 2)
		handle_error(0, copy, state);
	if (state == 1)
	{
		copy = ft_strdup(msg);
		if (!copy)
			handle_error(4, NULL, 0);
		pid = server_pid;
	}
	bit_index++;
	if (bit_index == 8)
	{
		bit_index = 0;
		char_index++;
	}
	signal = ((copy[char_index] & (0x80 >> bit_index)) != 0);
	if (!copy[char_index] && bit_index == 7)
		bit_index++;
	send_signal_to_server(pid, signal, copy);
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		send_bit(0, NULL, 0);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		handle_error(1, NULL, 0);
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, signal_handler);
	send_bit(pid, argv[2], 1);
	while (1)
		pause();
}
