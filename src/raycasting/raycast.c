/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/26 22:54:38 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

static void	ft_put_pixel(mlx_image_t *images, int j, int i, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 125;
	mlx_put_pixel(images, j, i, colour);
}


//need to know which side it hit the wall, for the textures.
static void	ft_draw_ray(t_rays *ray, t_data *data, int x)
{
	int		y;
	int		min_y;
	int		max_y;

	// here we use pythagoras to calculate the final actual length of the ray.
	//we 
	y = (int)sqrt(pow(data->px - ray->x, 2) + pow(data->py - ray->y, 2));
	//this i just copied, it for scaling, but i didnt try different things to see what might be better.
	y = HEIGHT / y;
	min_y = -y / 2 + HEIGHT / 2;
	if (min_y < 0)
		min_y = 0;
	max_y = y / 2 + HEIGHT / 2;
	if (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < min_y)
			ft_put_pixel(data->image, x, y, data->ceiling);
		else if (y >= min_y && y <= max_y)
			mlx_put_pixel(data->image, x, y, 0xFF0000FF);
		else if (y > max_y)
			ft_put_pixel(data->image, x, y, data->floor);
		y++;
	}
}

static void	ft_straight_ray(t_data *data, t_rays *ray, int dir_x, int dir_y)
{
	//this does the same as our ft_new_xy and ft_ray_cast function
	//but because it is a straigth line, we dont need cos/sin/tan.
	//and we can just add up by 1
	//this could be a better function, maybe ill rewrite it later.
	ray->x_dir = dir_x;
	ray->y_dir = dir_y;
	ray->dx = dir_x;
	ray->dy = dir_y;
	ray->end_x = (int)(data->px / CELL_SIZE);
	ray->end_y = (int)(data->py / CELL_SIZE);
	ray->x = data->px;
	ray->y = data->py;
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
	{
		ray->x += ray->x_dir;
		ray->y += ray->y_dir;
		ray->end_x = (int)((data->px - ray->x) / CELL_SIZE);
		ray->end_x = (int)((data->py - ray->y) / CELL_SIZE);
	}
}

static void	ft_new_xy(t_rays *ray, double angle)
{
	//here we make sure we check every x and y axis the ray crosses.
	//this is also done in dda and other ray_cast algos.
	//i just use a different way, so this might be a miscalculation is made.
	
	//first i set dx and dy=(difference of x and difference of y).
	//so the current x or y minus the rounded down end_x or end_y.
	//so if we are a at x=1 and y=2 in the map. our ray_x could be 1 * CELL_SIZE + 1/CELL_SIZE
	//so then dx would be 1/CELL_SIZE.
	ray->dx = ray->x - (ray->end_x * CELL_SIZE);
	ray->dy = ray->y - (ray->end_y * CELL_SIZE);
	//we know the direction, so we know which why (+x or -x) we need to go to get to our new x_axis.
	//in the example above, if x_dir=1 we need the go to x=2, so our dx needs to be CELL_SIZE-(old_dx).
	//so in this case it would be CELL_SIZE - 1/CELL_SIZE
	if (ray->x_dir == 1)
		ray->dx = CELL_SIZE - ray->dx;
	if (ray->y_dir == 1)
		ray->dy = CELL_SIZE - ray->dy;
	//then we check, with the margin, if the difference is to small, so that we just want consider it on the line already.
	if (ray->dy < MARGIN)
		ray->dy = CELL_SIZE;
	if (ray->dx < MARGIN)
		ray->dx = CELL_SIZE;
	//here we are going to calculate the hyptonus(so the ray). and see if the distance to the next y is bigger than the distance to the next x
	//we want to choose the shortest. cause otherwise you migth skip a axis.
	//depending on the step you choose, you can calculate the corresponding x or y value.
	//so if the dx step results in a shorter ray(thus the x-axis being the closest or the one next in line)
	//we can use the same angle together with the dx, to get the new ray->y.
	// the (* PI /180) is to transfer the angle from degrees to radians, because cos/sin/tan use radian in the math.h header.
	// we do the dx and dy *x_dir and *y_dir, to substract or add depending on the direction we are going.
	if (ray->dx / cos(angle * PI / 180) <= ray->dy / sin(angle * PI / 180))
	{
		ray->x += ray->dx * ray->x_dir;
		ray->y += (ray->dx * tan(angle * PI / 180)) * ray->y_dir;
	}
	else
	{
		ray->y += ray->dy * ray->y_dir;
		ray->x += (ray->dy / tan(angle * PI / 180)) * ray->x_dir;
	}
	//here we recalculate the rounded up/down value of the new ray_x and ray_y, so we can check the end_x and end_y in our map.
	ray->end_x = (int)(ray->x / CELL_SIZE);
	ray->end_y = (int)(ray->y / CELL_SIZE);
}

static void	ft_ray_cast(double angle, t_rays *ray, t_data *data)
{
	//to see the ray, which should go from the players position in the given angles direction
	//i first transfer the angle to the corresponding angle in 0 to 90 quadrant of the radian circle.
	//this way we can see every ray as a triangle, where the ray_line is the hypothonus 
	//hypothonus = (de schuine en langste zijde van een driehoek, waar 1 hoek 90 grade is, dit is bij ons altijd het geval)
	if (angle > 270)
		angle = 360 - angle;
	if (angle > 180)
		angle -= 180;
	if (angle > 90)
		angle = 180 - angle;
	//i set ray->x and ray->y to the start postion of our player.
	ray->x = data->px;
	ray->y = data->py;
	//i set ray->end_x and ray->end_y to the starting coordinates in our map
	ray->end_x = (int)(data->px / CELL_SIZE);
	ray->end_y = (int)(data->py / CELL_SIZE);
	//we loop, until the end_x and end_y in our map corresponds to someting else then a '0'
	//this should always be a '1', but i just '0' just to be sure.
	//and i check if our end_x and end_y are in range.
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
		ft_new_xy(ray, angle);
}

static void	ft_ray_calc(double angle, t_data *data, int x)
{
	t_rays	ray;

	//first we check if the angle is 90/180/270/360/0. 
	//because we are working with doubles, we use a margin to
	//check if we are close enough to the angle.
	//we use a different function to check straight lines,
	//to avoid dividing by 0.
	if (fabs(angle - 90.0) < MARGIN)
		ft_straight_ray(data, &ray, 0, -1);
	else if (fabs(angle - 180.0) < MARGIN)
		ft_straight_ray(data, &ray, -1, 0);
	else if (fabs(angle - 270.0) < MARGIN)
		ft_straight_ray(data, &ray, 0, 1);
	else if (fabs(angle - 360.0) < MARGIN || angle < MARGIN)
		ft_straight_ray(data, &ray, 1, 0);
	else
	{
		//here we set the directions depending on the angle.
		//you can search for radians and angles, to see how the radian circle
		//looks like, this is how i see to angles in our program.
		if (angle > 90 && angle < 270)
			ray.x_dir = -1;
		else
			ray.x_dir = 1;
		if (angle > 180 && angle < 360)
			ray.y_dir = 1;
		else
			ray.y_dir = -1;
		ft_ray_cast(angle, &ray, data);
	}
	//after these functions we will have the data we need to draw the collum of the x coordinate in the screenwindow.
	ft_draw_ray(&ray, data, x);
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	double	angle;
	double	step;

	//instead of using the CELL_SIZE, we could also just use doubles, this way we might be less outof range in calculations
	//transfering to doubles is not a big task.
	x = 0;
	angle = data->fov + (ANGLE / 2);
	if (angle > 360)
		angle -= 360;
	step = ANGLE / (WIDTH - 1);
	while (x < WIDTH)
	{
		ft_ray_calc(angle, data, x);
	 	angle -= step;
	 	if (angle <= 0.0)
	 		angle += 360;
		x++;
	}
	return (OK);
}
