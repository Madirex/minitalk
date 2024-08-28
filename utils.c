/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmateo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:32:38 by anmateo-          #+#    #+#             */
/*   Updated: 2024/08/28 20:39:06 by anmateo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_error_message(int err)
{
	const char	*error_messages[] = {"se requieren 2 argumentos.",
		"error en el kernel o mala gestión de señales UNIX.",
		"error en el proceso kill. PID incorrecto o server offline.",
		"memoria insuficiente o texto demasiado largo."};

	if (err >= 1 && err <= 4)
	{
		ft_putstr_fd("🔴 ", 2);
		ft_putendl_fd(error_messages[err - 1], 2);
	}
	else
		ft_putendl_fd("🔴 error desconocido", 2);
}

void	handle_error(int error_code, char *resource_to_free, int server_error)
{
	if (server_error == 2)
		ft_putendl_fd("🔴 error en el servidor", 2);
	else if (error_code == 0)
		ft_putendl_fd("🟢 mensaje enviado con éxito", 1);
	else
		print_error_message(error_code);
	free(resource_to_free);
	exit(EXIT_FAILURE);
}
