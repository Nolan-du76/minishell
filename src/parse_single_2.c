/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:42:07 by mjuette           #+#    #+#             */
/*   Updated: 2023/10/31 09:42:09 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_block(t_word **bck, int *j, char *s)
{
	if (*j != 0)
	{
		(*bck)->next = ft_calloc(1, sizeof(t_word));
		(*bck) = (*bck)->next;
		(*bck)->str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
		*j = 0;
	}
}

int	chevrons(t_word **bck, int *i, int *j, char *s)
{
	if ((*i > 0 && s[*i - 1] != '\\') || *i == 0)
	{
		if (*i >= 1 && !is_whitespace(s[*i - 1]))
			create_new_block(bck, j, s);
		(*bck)->str[*j++] = s[*i++];
		if ((*bck)->str[*j - 1] == s[*i])
			(*bck)->str[*j++] = s[*i++];
		if ((*i < (int)ft_strlen(s)) && s[*i] != '\0' && !is_whitespace(s[*i]) && (s[*i] != '<' && s[*i] != '>'))
			create_new_block(bck, j, s);
		if ((*i < (int)ft_strlen(s)) && s[*i] == 0)
			return (0);
	}
	else
		(*bck)->str[*j++] = s[*i++];
	return (1);
}

void	escape(t_word **bck, int *i, int *j, char *s)
{
	if (is_escapable(s[*i + 1]))
	{
		i++;
		(*bck)->str[(*j)++] = s[(*i)++];
	}
	else
		(*bck)->str[(*j)++] = s[(*i)++];
}

void	parse_single_2(char *s, t_word *c)
{
	int	i;
	int	j;
	int	quoted;
	t_word	*bck;

	bck = c;
	i = 0;
	j = 0;
	quoted = 0;
	bck->str = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	(void)c;
	log_parse_single(s);
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		/*/TODO : Correction 💢️💢️ pour les \\\\\\\\\*/
		if (s[i] == '\\' && !quoted)
			escape(&bck, &i, &j, s);
		else if ((s[i] == '"' || s[i] == '\'') && !quoted)
		{
			quoted = 1;
			if (i >= 1 && !is_whitespace(s[i - 1]))
				create_new_block(&bck, &j, s);
			bck->quote = s[i];
			i++;
		}
		else if ((s[i] == '\'' || s[i] == '"') && quoted && s[i] == bck->quote)
		{
			quoted = 0;
			if (s[i + 1] != '\0' && !is_whitespace(s[i + 1]) && s[i+1] != '<'&& s[i+1] != '>')
				create_new_block(&bck, &j, s);
			i++;
		}
		
		else if (is_whitespace(s[i]) && !quoted)
		{
			create_new_block(&bck, &j, s);
			i++;
		}
		else if ((s[i] == '<' || s[i] == '>') && !quoted)
		{
			if ((i > 0 && s[i - 1] != '\\') || i == 0)
			{
				if (i >= 1 && !is_whitespace(s[i - 1]))
					create_new_block(&bck, &j, s);
				bck->str[j++] = s[i++];
				if (bck->str[j - 1] == s[i])
					bck->str[j++] = s[i++];
				if ((i < (int)ft_strlen(s)) && s[i] != '\0' && !is_whitespace(s[i]) && (s[i] != '<' && s[i] != '>'))
				{
					if (j != 0)
					{
						bck->next = ft_calloc(1, sizeof(t_word));
						bck = bck->next;
						bck->str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
						j = 0;
					}
				}
				if ((i < (int)ft_strlen(s)) && s[i] == 0)
					break ;
			}
			else
				bck->str[j++] = s[i++];	
		}
		else
			bck->str[j++] = s[i++];
	}
	bck->str[j++] = 0;
	bck->next = NULL;
}
