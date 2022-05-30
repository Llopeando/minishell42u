/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/05/30 14:19:42 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// as

void	ft_spacesremover(t_data *data)
{
	int		frnt;
	int		bck;
	int		fill;
	char	*fnl_cmd;

	if (!data->str)
		return ;
	frnt = 0;
	while (data->str[frnt] == 32)
		frnt++;
	bck = ft_strlen(data->str);
	while (bck > 0 && data->str[bck - 1] == 32)
		bck--;
	if (bck == 0)
		return ;
	fill = (bck - 1);
	bck = (bck - frnt);
	frnt = 0;
	fnl_cmd = (char *)malloc(sizeof(char) * (bck + 1));
	bck--;
	while (bck >= 0)
	{
		fnl_cmd[bck] = data->str[fill];
		bck--;
		frnt++;
		fill--;
	}
	fnl_cmd[frnt] = '\0';
	free(data->str);
	data->str = fnl_cmd;
}

int	count_ms(char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 1;
	j = 0;
	c = 0;
	while (s[k] != '\0')
	{
		if (s[k] == '\'' || s[k] == '\"')
			k += ft_pass_2(s + k, s[k]);
		if (s[k] == '|')
			i++;
		if (s[k] != '\0')
			k++;
	}
	return (i);
}

void	ft_bridge(t_data *data, int i, int j, char **env)
{
	int	index;
	int	r;

	r = 0;
	while (j + 1 <= count_ms(data->str, '|'))
	{
		if ((data->str[i] == '\'' || data->str[i] == '\"') && r == 1)
				i += ft_pass_2(data->str + i, data->str[i]);
		else if (data->str[i] != '|' && r == 0)
		{
			index = i;
			r = 1;
			if (data->str[i] == '\'' || data->str[i] == '\"')
				i += ft_pass_2(data->str + i, data->str[i]);
		}
		else if ((data->str[i] == '|' || data->str[i] == '\0') && r == 1)
		{
			ft_process(ft_substr(data->str, index,
					(i - index)), data, j, count_ms(data->str, '|'), env);
			r = 0;
			if (data->str[i] == '|')
				i++;
			j++;
		}
		if (data->str[i] != '\0' && data->str[i] != '|')
			i++;
		if (data->str[i] == ' ')
			i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	struct sigaction	sa;
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = ft_dup_2d(env);
	data.path = ft_split(getenv("PATH"), ':');
	sa.sa_sigaction = sighandler;
	rl_catch_signals = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		data.str = readline("bashie > ");
		add_history(data.str);
		if (data.str == NULL)
		{
			exit (0);
		}
		if (data.str[0] == '\0' || ft_checker(data.str, &data))
		{
			free(data.str);
			continue ;
		}
		ft_spacesremover(&data);
		ft_init_pipes(&data);
		ft_bridge(&data, 0, 0, env);
		ft_close_pipes(&data);
		dup2(1, STDIN_FILENO);
		free(data.str);
	}
	ft_freeo(data.env, 1);
	return (0);
}

void	ft_new_line(void)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(int signal, siginfo_t *a, void *b)
{
	(void)a;
	(void)b;
	if (signal == 0)
		exit (0);
	if (signal == 2)
	{
		ft_new_line();
	}
}
