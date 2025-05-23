/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:32:56 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/23 23:29:54 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	write(2, "\b\b  \b\b", 6);
}

void	sigint_handler(int sig)
{
	(void)sig;
	//write(2, "\b\b  \b\b", 6);//boh non si capisce se ci va bash una volta fa in un modo una volta nell'altro
	write(1, "\n", 1);
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_second(int sig)
{
	(void)sig;
	g_exit_status = 130;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	close(0);
}
/*
void	signal_handler_heredoc(int sig)
{
	(void)sig;
	signal(SIGINT, cntrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		if (g_kill_pid > 0)
		{
			kill(g_kill_pid, SIGKILL);
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (g_kill_pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_kill_pid == -2)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
} */
