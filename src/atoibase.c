/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoibase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:33:00 by olskor            #+#    #+#             */
/*   Updated: 2023/03/21 04:22:33 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int	check_base(char *base)
{
	int			i;
	int			j;

	i = -1;
	while (base[++i])
	{
		j = -1;
		while (base[++j])
		{
			if (base[i] == base[j] && i != j)
				return (0);
		}
	}
	return (1);
}

static int	check_nbr(char *nbr_b, char *base)
{
	int			i;
	int			j;
	int			match;

	i = -1;
	match = 0;
	while (nbr_b[++i])
	{
		j = -1;
		while (base[++j])
		{
			if (nbr_b[i] == base[j])
				match = 1;
		}
		if (match != 1)
			return (0);
		match = 0;
	}
	return (1);
}

static int	ft_get_number(char *nbr_b, char *base)
{
	int			i;
	int			j;
	int			nbr;

	i = 0;
	nbr = 0;
	while (nbr_b[i])
	{
		if (nbr_b[i] == '-')
			i++;
		j = 0;
		while (base[j] && base[j] != nbr_b[i])
			j++;
		if (base[j] != '\0')
		{
			nbr = nbr * ft_strlen(base) + j;
		}
		i++;
	}
	return (nbr);
}

int	ft_atoibase(char *nbr_b, char *base)
{
	int			nbr;

	nbr = 0;
	if (nbr_b == NULL || base == NULL)
		return (0);
	if (check_nbr(nbr_b, base) == 0 || check_base(base) == 0)
		return (0);
	nbr = ft_get_number(nbr_b, base);
	if (nbr_b[0] == '-')
		nbr = -nbr;
	return (nbr);
}

int	atoibaseskip(char *nbr, t_map *map)
{
	int	i;
	int	atoi;

	i = 0;
	while (nbr[i] && nbr[i] != ',')
		i++;
	if (nbr[i++] == ',')
	{
		if (nbr[i++] == '0')
		{
			if (nbr[i++] == 'x')
			{
				atoi = ft_atoibase((nbr + i), "0123456789ABCDEF");
				if (atoi == 0)
					atoi = ft_atoibase((nbr + i), "0123456789abcdef");
				if (atoi == 0)
					atoi = 16777215;
				map->tri = 1;
				return (atoi);
			}
		}
	}
	return (16777215);
}
