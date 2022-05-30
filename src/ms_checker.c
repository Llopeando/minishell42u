/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/05/30 14:19:14 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_checker(char *str)
// {
// 	int	i;
// 	char hold;

// 	i = 0;
// 	i += ft_pass(str + i);
// 	if (str[i] == '|')
// 		ft_error(2);
// 	while (str[i])
// 	{
// 		i += ft_pass(str + i);
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			if (str[ft_pass(str + i, str[i]] != str[i])
// 				ft_error(1);
// 			else
// 				i += ft_pass(str + i, str[i]);
// 		else if ()
// 	}
	
// }

// int	ft_inputchecker(char *str)
// {
// 	int	c;

// 	c = 0;
// 	while (str[c])
// 	{
// 		if (str[c] && (str[c] == '|' && str[c + 1] == '|'))
// 			ft_checker(str, 0);
// 		if (str[c] && (str[c] == '<' || str[c] == '>'))
// 			ft_checker(str, 1);
// 		c++;
// 	}
// }

int	ft_checker(char *str, t_data *data)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[c])
	{
		if (str[c] && (str[c] == '|' && str[c + 1] == '|'))
		{
			printf("bashie: input error: '%s'\n", str);
			data->status = 258;
			return (1);
		}
		if (str[c] && (str[c] == '<' || str[c] == '>'))
			i++;
		if (i == 3)
		{
			printf("bashie: input error: '%s'\n", str);
			return (1);
		}
		c++;
	}
	return (0);
}
