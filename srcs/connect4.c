/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:05:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 11:15:21 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

void	usage(char *prgm_name) {
	ft_putstr_fd("This programe take 2 arguments.", STDERR_FILENO);
	ft_putstr_fd("Please lauch it like this: './", STDERR_FILENO);
	if (prgm_name != NULL)
		ft_putstr_fd(prgm_name, STDERR_FILENO);
	else
		ft_putstr_fd("connect4", STDERR_FILENO);
	ft_putstr_fd(" [number of lines] [number of columns].", STDERR_FILENO);
}

int	main(int argc, char *argv[]) {
	if (argc != 3) {
		usage(argv[0]);
		return 1;
	}
	return 0;
}
