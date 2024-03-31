t_vec3	vector_fmax(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3)
	{
		.x = fmax(v1.x, v2.x),
		.y = fmax(v1.y, v2.y),
		.z = fmax(v1.z, v2.z)
	};
}

t_vec3	vector_fmin(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3)
	{
		.x = fmin(v1.x, v2.x),
		.y = fmin(v1.y, v2.y),
		.z = fmin(v1.z, v2.z)
	};
}

void	ray_mv_to_pool(t_list **pool, t_list **ray_list)
{
	t_list	*cur;

	cur = *ray_list;
	while (cur)
	{
		if (*((t_ray *)(cur->content))->next)
		{
			ray_mv_to_pool(pool, ((t_ray *)(cur->content))->next);
			*((t_ray *)(cur->content))->next = NULL;
		}
		cur = cur->next;
	}
	 
	lst_mv_all_to_pool(pool, ray_list, ray_clean);
}