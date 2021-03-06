/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:35:30 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/25 17:25:10 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			ssl_commands(char *s)
{
	ft_puter("ft_ssl: Error: '");
	ft_puter(s);
	ft_puter("' is an invalid command.\n\n");
	ft_puter("Standart commands:\n\n");
	ft_puter("Message Digest commands:\nmd5\n\n");
	ft_puter("Cipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\
		\ndes3\ndes3-ecb\ndes3-cbc\n\n");
}

unsigned char	*ft_strj(unsigned char *s1, unsigned char *s2, int i1, int j1)
{
	int				i;
	int				j;
	unsigned char	*res;

	res = (unsigned char *)malloc(i1 + j1 + 1);
	j = -1;
	i = -1;
	while (++i < i1)
		res[i] = s1[i];
	while (++j < j1)
		res[i++] = s2[j];
	res[i] = '\0';
	return (res);
}

unsigned char	*ft_read(int op, int len, int *i)
{
	unsigned char	*str;
	unsigned char	buf[len + 1];
	unsigned char	*s;
	int				j;

	str = (unsigned char *)malloc(1);
	*str = '\0';
	*i = 0;
	while ((j = read(op, buf, len)))
	{
		s = ft_strj(str, buf, *i, j);
		*i += j;
		free(str);
		str = s;
	}
	return (str);
}

int				file_er(int i[2], int o[2], char **argv)
{
	if (i[0] < 0 || o[0] < 0)
	{
		ft_puter("ft_ssl: ");
		ft_tolower(argv[1]);
		ft_puter(argv[1]);
		write(2, ": ", 2);
	}
	if (i[0] == -1)
	{
		open(argv[i[1] + 1], O_RDONLY);
		ft_puter(argv[i[1] + 1]);
		write(2, ": ", 2);
		ft_puter(strerror(errno));
		write(2, "\n", 1);
		return (1);
	}
	else if (o[0] == -1)
	{
		ft_puter(argv[o[1] + 1]);
		write(2, ": ", 2);
		ft_puter(strerror(errno));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

int				main(int argc, char *argv[])
{
	if (argc < 2)
		ft_puter("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		if (!ft_scmp(argv[1], "base64"))
			base64(argv);
		else if (!ft_scmp(argv[1], "des") || !ft_scmp(argv[1], "des-ecb"))
			des_ecb(argv);
		else if (!ft_scmp(argv[1], "des-cbc"))
			des_cbc(argv);
		else if (!ft_scmp(argv[1], "des3") || !ft_scmp(argv[1], "des3-ecb"))
			des3_ecb(argv);
		else if (!ft_scmp(argv[1], "des3-cbc"))
			des3_cbc(argv);
		else if (!ft_scmp(argv[1], "md5"))
			md_main(argv, &md5_e);
		else if (!ft_scmp(argv[1], "sha256"))
			md_main(argv, &sha256_e);
		else
			ssl_commands(argv[1]);
	}
	return (0);
}
