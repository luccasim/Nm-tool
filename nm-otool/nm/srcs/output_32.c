/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:52:36 by luccasim          #+#    #+#             */
/*   Updated: 2016/11/22 16:52:38 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	check_option(uint32_t *addr, char *symbol)
{
	char	*opt;

	opt = ft_options_sglt();
	if (opt)
	{
		if (ft_strchr(opt, 'u') && ft_strchr(opt, 'U'))
			return (SUCCESS);
		if (ft_strchr(opt, 'u'))
		{
			if (*symbol != 'U')
				return (SUCCESS);
			*addr = 0;
			*symbol = 0;
		}
		if (ft_strchr(opt, 'j'))
		{
			*addr = 0;
			*symbol = 0;
		}
		if (ft_strchr(opt, 'U') && *symbol == 'U')
			return (SUCCESS);
	}
	return ((*symbol == '-') ? SUCCESS : FAIL);
}

int			output_32(void *l, char *st, t_list *sl)
{
	char				s;
	uint32_t			v;
	uint32_t			addr;
	uint32_t			name;
	struct nlist		*list;

	list = (struct nlist*)l;
	addr = 1;
	v = list->n_value;
	s = symbol_type(list->n_value, list->n_sect, list->n_type, sl);
	name = 1;
	if (check_option(&addr, &s) == SUCCESS)
		return (SUCCESS);
	if (addr)
		addr = (s != 'U') ? ft_printf("%.8llx ", v) : ft_printf("%8s ", "");
	if (s)
		ft_printf("%c ", s);
	if (name)
		ft_printf("%s\n", st + list->n_un.n_strx);
	return (SUCCESS);
}
