/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:39:14 by ecamara           #+#    #+#             */
/*   Updated: 2022/04/05 12:22:00 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_infile(t_data *data, int i)
{
	char	*str;
	char	*temp;

	str = NULL;
	if (data->infile.files[i] == NULL)
		return ;
	if (data->infile.modes[i] == 1)
	{
		while (!ft_strnstr(str, data->infile.files[i], ft_strlen(str)))
		{
			temp = readline("> ");
			if (ft_strnstr(temp, data->infile.files[i], ft_strlen(temp)))
				break ;
			str = ft_strjoin(str, temp);
			str = ft_strjoin(str, "\n");
			free (temp);
		}
		if (data->infile.files[i + 1] == NULL)
			write(data->fd[0][1], str, ft_strlen(str));
	}
	else
		data->fd[0][0] = open(data->infile.files[i], O_RDONLY);
	i++;
	if (data->infile.files[i] != NULL)
		ft_infile(data, i);
	else
	{
		//ft_print_fd(fd0[0]);
		dup2(data->fd[0][0], STDIN_FILENO);
	}
	close (data->fd[0][1]);
}

int	ft_outfile(t_data *data, int i)
{
	int	fd;

	if (data->outfile.files[i] == NULL)
		return (0);
	if (data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		open(data->outfile.files[i], O_TRUNC);
		fd = open(data->outfile.files[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return(0);
	}
	else if (data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		fd = open(data->outfile.files[i], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return(0);
	}
	i++;
	if (data->outfile.files[i] != NULL)
		ft_outfile(data, i);
	return (0);
}

void	ft_process(char *str, t_data *data, char boo)
{
	int	pid;
	int	status;

	(void)boo;
	ft_input(str, data);
	//ft_change_pipes(data);
	ft_infile(data, 0);
	ft_outfile(data, 0);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (!ft_cmd_cases(data))
			ft_search_cmd(data);
	}
	else
	{
		//close(fd0[1]);
		ft_error_child(waitpid(pid, &status, 0));
		ft_free_data(data);
		/*if (!boo)
			ft_last_pipes();*/
	}
}

void	ft_search_cmd(t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->path[i] != NULL)
	{
		temp = ft_strjoin(data->path[i], "/");
		temp = ft_strjoin(temp, data->cmd[0]);//free temp
		if (access(temp, X_OK) == 0)
		{
			execve(temp, data->cmd, data->env);
			exit(0);
		}
		free (temp);
		i++;
	}
	ft_putstr(data->cmd[0]);
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	exit (0);
}