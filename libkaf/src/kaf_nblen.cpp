int	kaf_nblen(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		nb *= -1;
	else
	{
		while (nb > 0)
		{
			nb /= 10;
			i++;
		}
	}
	return (i);
}
