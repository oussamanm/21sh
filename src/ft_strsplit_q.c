/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:22:18 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:23:35 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"


///***  Count Words
static int		ft_count_word_q(const char *str, char *c)
{
	int i;
	int rtn;
	int	i_bln;
	int temp;

	i = -1;
	i_bln = 0;
	rtn = (str && str[0] != '\0' && ft_check_char(c, str[0]) != 1) ? 1 : 0;
	while (str[++i] != '\0')
	{
		/// if find " or ' got to the last char in word
		if (ft_check_char("\"\'\0", str[i]) && (temp = str[i]))
		{
			if ((temp = ft_find_char((char *)&str[i + 1], temp)) != -1)
				i += (temp);
		}
		if (ft_check_char(c, str[i]))
			i_bln = 1;
		else if (i_bln == 1 && !(i_bln = 0))
			rtn++;
	}
	return (rtn);
}

///*** get len of Word
static int		ft_getlen_q(char const *str, char *c)
{
	int i;
	int is_quot;

	if (str == NULL || !str[0])
		return (-1);
	is_quot = ft_check_char("\'\"\0", str[0]) ? str[0] : 0;
	i = (is_quot) ? 1 : 0;
	while (str[i] != '\0')
	{
		//if (is_quot && (str[i] == 34 || str[i] == 39))
		if (is_quot && str[i] == is_quot)		
			is_quot = 0;
		else if (!is_quot && (str[i] == 34 || str[i] == 39))
			is_quot = str[i];
		else if (!is_quot && ft_check_char(c, str[i]) && str[i - 1] != '\\') /// review i - 1
			break ;
		i++;
	}
	if (is_quot && i == 1)
		return (-1);
	return (i);
}

///*** get Index of First Word
static int		ft_getindx_q(char const *str, char *c)
{
	int i;
	int i_bln;
	int is_quot;

	i = 0;
	i_bln = 0;
	is_quot = 1;
	while (str[i] != '\0')
	{
		if (ft_check_char(c, str[i]) != 1 && str[i - 1] != '\\') /// add condition if \ exist before || check i - 1 if null
		{
			i_bln = 1;
			break ;
		}
		i++;
	}
	if (i_bln == 0)
		return (-1);
	else
		return (i);
}

///*** Check if quote isn't correct
void		ft_check_quot(char **src)
{
	char *temp;
	int quote;
	int i;
	int index;

	i = 0;
	temp = NULL;
	index = 0;
	quote = 0;
	while (TAB(i))
	{
		if (((TAB(i) == 34 || TAB(i) == 39) && (quote = TAB(i))) || index == -1)
		{
			index = ft_find_char(&TAB(i + 1), quote);
			if (TAB(i + 1 + index -1) == 92)
				index = 0;
			if (index != -1)
				i += (index + 1);
			else
			{
				ft_putstr("-> ");
				//get_next_line(0, &temp);
				//temp = ft_read_sh(0);
				*src = ft_strjoir(*src, "\n", 1);
				*src = ft_strjoir(*src, temp, 3);
			}
		}
		i++;
	}
}

char			**ft_str_split_q(char **str, char *c)
{
	int		i;
	int		j;
	int		i_firstw;
	int		i_lenw;
	char	**s_re;

	i = 0;
	j = 0;
	if (*str == NULL || c == NULL)
		return (NULL);
	/// Check Norme
	//ft_check_quot(str);
	if (!(s_re = (char **)malloc(sizeof(*s_re) * ft_count_word_q(*str, c) + 1)))
		return (NULL);
	while (STR(i) != '\0')
	{
		if ((i_firstw = ft_getindx_q(&(STR(i)), c)) == -1) /// index of first Word
			break ;
		i += i_firstw;
		if ((i_lenw = ft_getlen_q(&(STR(i)), c)) == -1) /// len of the word
			break ;
		s_re[j++] = ft_strsub(*str, i, i_lenw);
		i += i_lenw;
	}
	s_re[j] = NULL;
	return (s_re);
}