/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 19:56:27 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/07 19:56:27 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	builtin_echo(char **cmd)
{
	int		i;
	BOOL	newline;

	newline = 1;
	i = 1;
	if (ft_strcmp(cmd[1], "-e") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (cmd[i] != NULL || cmd[i])
	{
		if (ft_strcmp(cmd[i], "") != 0)
			ft_printf("%s ", cmd[i]);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
