/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:48:56 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/07 16:49:49 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <strings.h>
# include <limits.h>
# include "minirt.h"


# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl    t_gnl;
typedef t_gnl           t_line;
typedef t_gnl           t_read;

struct s_gnl
{
    char    *buf;
    int     size;
    int     pos;
};

static void	free_buffer(t_read *prb)
{
	if (prb->buf != NULL)
	{
		free(prb->buf);
		prb->buf = NULL;
	}
}

static char	*ft_realloc(t_line *line)
{
	char	*new_buf;
	size_t	new_size;

	new_size = line->size + 1;
	new_buf = malloc((new_size + 1) * sizeof(char));
	if (line->buf)
	{
		if (new_buf)
			memcpy(new_buf, line->buf, line->size);
		free(line->buf);
	}
	line->buf = new_buf;
	line->size = new_size;
	return (new_buf);
}

static int	read_file(int fd, t_read *reserve)
{
	if (!reserve->buf)
		reserve->buf = malloc(BUFFER_SIZE);
	if (reserve->pos >= reserve->size)
	{
		reserve->size = read(fd, reserve->buf, BUFFER_SIZE);
		if (reserve->size < 1)
			return (0);
		reserve->pos = 0;
	}
	return (reserve->buf[reserve->pos++]);
}

static int	put_line(t_line *line, char c)
{
	if (line->pos >= line->size)
	{
		if (ft_realloc(line) == NULL)
			return (0);
	}
	line->buf[line->pos++] = c;
	if (c == '\n')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	int				c;
	t_line			line;
	static t_read	reserve;

	if (fd < 0)
		return (0);
	line.buf = 0;
	line.pos = 0;
	line.size = 0;
	while (1)
	{
		c = read_file(fd, &reserve);
		if (c == 0)
			break ;
		if (put_line(&line, c) == 0)
			break ;
	}
	if (line.pos == 0)
		free_buffer(&reserve);
	else
		line.buf[line.pos] = 0;
	return (line.buf);
}


typedef struct 	s_scene		t_scene;
typedef struct 	s_set		t_set;
typedef struct 	s_cam		t_cam;
typedef struct	s_vec3		t_vec3;
typedef struct	s_am_light	t_am_light;
typedef struct	s_light		t_light;
typedef struct	s_object	t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_plane		t_plane;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_cam
{
	bool	set;
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	pos_initial;
	t_vec3	dir_initial;
	int		fov;
};

struct s_am_light
{
	bool	set;
	double	brightness;
	t_vec3	color;
};

struct s_light
{
	double	set;
	t_vec3	pos;
	double	ratio;
	t_vec3	color;
};

struct s_sphere	
{
	t_vec3		center;
	double		radius;
	t_vec3		color;
	double		set;
	t_sphere	*next;
};

struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
	double	set;
	t_plane	*next;
};

struct s_cylinder
{
    t_vec3 		center;
    t_vec3 		axis;
    double 		diameter;
    double		height;
    t_vec3 		color;
    double 		set;
	t_cylinder	*next;
};

struct s_object
{
	t_sphere	*sp_lst;
	t_cylinder	*cy_lst;
	t_plane		*pl_lst;
};

struct s_scene
{
	t_object	object;
	int			width;
    int			height;
    t_am_light 	amb;
    t_cam 		cam;
    t_light 	light;
    t_sphere 	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
};

typedef struct s_mlx
{
	mlx_image_t		*image;
	mlx_t			*mlx;
}	t_mlx;

typedef struct s_data
{
	t_mlx	*mlx;
	t_scene	*scene;	
}	t_data;

int	ft_array_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		++len;
	return (len);
}

void	stod(char *s, double *res)
{
	int	i;

	i = 0;
	if ( s[1] && (s[0] == '+' || s[0] == '-' ) )
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '.')
		{
			dprintf(2, "Inv Number\n");
			exit (1);
		}
		i++;
	}
	*res = atof(s);
	if (s[0] == '+' || s[0] == '-')
		s = s + 1;
}

void	stoi(char *s, int min, int max, int *res)
{
	int	i;

	i = 0;
	if (s[0] && (s[0] == '+' || s[0] == '-'))
		i++;
	while (s[i])
	{
		// if (!ft_isdigit(s[i])) // TODO : to be modified and check the error
		// {
		// 	dprintf(2, "Inv Number stoi : %s\n", s);
		// 	exit (1);
		// }
		i++;
	}
	*res = ft_atoi(s);
	if (*res < min || *res > max)
		exit (1);
}

void	parse_vec3(char *s, t_vec3 *vec3)
{
	char	**split;

	split = ft_split(s, ',');
	if (split == NULL)
		dprintf(2, "Inv Memory\n");
	stod(split[0], &(*vec3).x);
	stod(split[1], &(*vec3).y);
	stod(split[2], &(*vec3).z);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_norm(t_vec3 a)
{
	double	alpha;

	alpha = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return ((t_vec3){alpha * a.x, alpha * a.y, alpha * a.z});
}

void	parse_cam(t_scene *scene, char **split)
{
	t_vec3	look_at;
	
	if (scene->cam.set)
		dprintf(2, "Parsing Error in Camera\n");
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	parse_vec3(split[1], &(scene->cam.pos));
	// printf("vec3: spt %s\n", split[1]);
	scene->cam.pos_initial = scene->cam.pos;
	parse_vec3(split[2], &look_at);
	// printf("vec3: spt %s\n", split[2]);
	scene->cam.dir = vec3_norm(vec3_sub(look_at, scene->cam.pos));
	scene->cam.dir_initial = scene->cam.dir;
	stoi(split[3], 1, 179, &(scene->cam.fov));
	scene->cam.set = true;
}

void	parse_color(char *s, t_vec3 *color)
{
	char	**split;
	int		primary;

	split = ft_split(s, ',');
	if (split == NULL)
	{
		dprintf(2, "Inv Memory");
		exit (1);
	}
	primary = 0;
	if (ft_array_len(split) != 3)
	{
		dprintf(2, "Inv number of args\n");
		exit (1);
	}
	stoi(split[0], 0, 255, &primary);
	(*color).x = (double)primary / 255.0;
	stoi(split[1], 0, 255, &primary);
	(*color).y = (double)primary / 255.0;
	stoi(split[2], 0, 255, &primary);
	(*color).z = (double)primary / 255.0;
}

t_vec3	color_scale(double f, t_vec3 c1)
{
	return ((t_vec3){f * c1.x, f * c1.y, f * c1.z});
}

void	parse_amb(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 3)
		dprintf(2, "Invalid Number of args in param : %s\n", split[0]);
	stod(split[1], &(scene->amb.brightness));
	parse_color(split[2], &(scene->amb.color));
	scene->amb.color = color_scale(scene->amb.brightness, scene->amb.color);
	scene->amb.set = true;
}

void	parse_light(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	parse_vec3(split[1], &(scene->light.pos));
	stod(split[2], &(scene->light.ratio));
	parse_color(split[3], &(scene->light.color));
	scene->light.color = color_scale(scene->light.ratio, scene->light.color);
	scene->light.set = true;
}

t_sphere *create_sphere_node() {

	t_sphere *new_node = (t_sphere *)malloc(sizeof(t_sphere));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

void add_sphere_to_back(t_sphere **lst, t_sphere *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_sphere *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	parse_sphere(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	t_sphere *new_sphere = create_sphere_node();
	// add_sphere_to_back(&(scene->object.sp_lst));
	parse_vec3(split[1], &(new_sphere->center));
	stod(split[2], &(new_sphere->radius));
	parse_color(split[3], &(new_sphere->color));
	new_sphere->radius = new_sphere->radius / 2.0;
	new_sphere->set = true;
	add_sphere_to_back(&(scene->object.sp_lst), new_sphere);
	// if (scene->object.sp_lst == NULL)
    //     scene->object.sp_lst = new_sphere;
    // else
    // {
    //     t_sphere *current = scene->object.sp_lst;
    //     while (current->next != NULL)
    //         current = current->next;
    //     current->next = new_sphere;
    // }
}

void	parse_plane(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	parse_vec3(split[1], &(scene->plane.point));
	parse_vec3(split[2], &(scene->plane.normal));
	parse_color(split[3], &(scene->plane.color));
	scene->plane.set = true;
}

void	parse_cylinder(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 6)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	parse_vec3(split[1], &(scene->cylinder.center));
	parse_vec3(split[2], &(scene->cylinder.axis));
	stod(split[3], &(scene->cylinder.diameter));
	stod(split[4], &(scene->cylinder.height));
	parse_color(split[5], &(scene->cylinder.color));
	scene->cylinder.set = true;
}

void	parse_ids(t_scene *scene, char **split)
{
	if (!strcmp(split[0], "C"))
		parse_cam(scene, split);
	else if (!strcmp(split[0], "A"))
		parse_amb(scene, split);
	else if (!strcmp(split[0], "L"))
		parse_light(scene, split);
	else if (!strcmp(split[0], "sp"))
		parse_sphere(scene, split);
	else if (!strcmp(split[0], "pl"))
		parse_plane(scene, split);
	else if (!strcmp(split[0], "cy"))
		parse_cylinder(scene, split);
	else
		dprintf(2, "Invalid Id\n");
}

int	parse_scene(t_scene *scene, char *filename)
{
	int		fd;
	char	*line[2];
	char	**split;

	// TODO : check for valid extension
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "Error opening file\n");
		return (1);
	}
	while (-42)
	{
		line[0] = get_next_line(fd);
		if (line[0] == NULL)
			break ;
		line[1] = ft_strtrim(line[0], " \t");
		// printf("Line--> : %s\n", line[1]);
		split = ft_split(line[1], ' ');
		if (split == NULL)
		{
			dprintf(2, "Inv Memeory\n");
			exit (1);
		}
		if (split[0])
		{
			// printf("split--> : %s\n", split[0]);
		}
		parse_ids(scene, split);
	}
	return (0);
}

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

unsigned int mlx_rgb(int red, int green, int blue)
{
    // Ensure RGB components are within the range [0, 255]
    red = (red < 0) ? 0 : (red > 255) ? 255 : red;
    green = (green < 0) ? 0 : (green > 255) ? 255 : green;
    blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;

    // Create the 32-bit color value (8 bits for each component)
    return (red << 16) | (green << 8) | blue;
}

double deg_to_rad(double degrees)
{
    return (degrees * M_PI / 180.0);
}

mlx_t*	mlx;
static mlx_image_t* image;

int	vec3_to_rgb(t_vec3 color)
{
    int r = (int)(255.999 * color.x);
    int g = (int)(255.999 * color.y);
    int b = (int)(255.999 * color.z);
    
    return (r << 16) | (g << 8) | b;
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;
    
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec3 vec3_scale(t_vec3 vec, double scalar)
{
    return (t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

// Function to calculate the intersection of a ray with the sphere
double intersect_sphere(t_sphere *sphere, t_vec3 ray_origin, t_vec3 ray_dir)
{
    t_vec3 oc = vec3_sub(ray_origin, sphere->center);
    double a = vec3_dot(ray_dir, ray_dir);
    double b = 2.0 * vec3_dot(oc, ray_dir);
    double c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (-1.0); // No intersection
    else
    {
        double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
        return fmin(t1, t2);
    }
}

// double intersect_objects(t_scene *scene, t_vec3 ray_origin, t_vec3 ray_dir) {
//     double t_sphere = intersect_sphere(scene->object.sp_lst, ray_origin, ray_dir);
// 	return (t_sphere);
// }

double intersect_objects(t_scene *scene, t_vec3 ray_origin, t_vec3 ray_dir)
{
    double closest_t = -1.0;

    // Iterate through the linked list and find the closest intersection
    t_sphere *current_sphere = scene->object.sp_lst;
    while (current_sphere != NULL)
    {
        double t = intersect_sphere(current_sphere, ray_origin, ray_dir);
        if (t > 0 && (closest_t < 0 || t < closest_t))
            closest_t = t;
        current_sphere = current_sphere->next;
    }

    // Similar checks for other objects

    return (closest_t);
}

// Function to calculate the length of a 3D vector
double vec3_length(t_vec3 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3 shade_object(t_scene *scene, t_light *light, t_vec3 hit_point, t_vec3 surface_normal, t_vec3 ray_dir)
{
    // Calculate light direction and distance to the light source
    t_vec3 light_dir = vec3_norm(vec3_sub(light->pos, hit_point));
    double light_distance = vec3_length(vec3_sub(light->pos, hit_point));

    // Check for shadows by casting a ray from the hit point to the light source
    bool in_shadow = false;
    // for (int i = 0; i < num_objects_in_scene; i++)
	// {
        // Check for intersection between the hit point and the object
        double t = intersect_objects(scene, hit_point, light_dir);
        if (t > 0 && t < light_distance) 
		{
            in_shadow = true;
            // break;
        }
    // }

    // Calculate ambient and diffuse lighting components
    t_vec3 ambient = vec3_scale(scene->amb.color, scene->amb.brightness);
    t_vec3 diffuse = (in_shadow) ? (t_vec3){0, 0, 0} : color_scale(light->ratio * fmax(0.0, vec3_dot(surface_normal, light_dir)), scene->object.sp_lst->color);

    // Combine ambient and diffuse lighting for shading
    t_vec3 shading = vec3_add(ambient, diffuse);

    return (shading);
}

t_vec3 shade_objects(t_scene *scene, t_vec3 hit_point, t_vec3 surface_normal, t_vec3 ray_dir)
{
    t_vec3 shading = (t_vec3){0, 0, 0};

    // Iterate through the linked list and shade each object
    t_sphere *current_sphere = scene->object.sp_lst;
    while (current_sphere != NULL)
    {
        if (vec3_length(vec3_sub(hit_point, current_sphere->center)) <= current_sphere->radius)
            shading = vec3_add(shading, shade_object(scene, &scene->light, hit_point, surface_normal, ray_dir));
        current_sphere = current_sphere->next;
    }

    // Similar shading for other objects

    return (shading);
}

t_vec3 calculate_surface_normal(t_scene *scene, t_vec3 hit_point)
{
    t_vec3 surface_normal = vec3_sub(hit_point, scene->object.sp_lst->center);
    return vec3_norm(surface_normal);
}

// Function to shade the cylinder object
t_vec3 shade_cylinder(t_scene *scene, t_light *light, t_vec3 hit_point, t_vec3 ray_dir) {
    t_vec3 surface_normal = vec3_norm(vec3_sub(hit_point, scene->cylinder.center));
    t_vec3 shading = shade_object(scene, light, hit_point, surface_normal, ray_dir);
    return (shading);
}

void render_scene(t_scene *scene)
{
	printf("----------------<Rendering Scene>----------------\n");	
	
	/************************************************************/

    double aspect_ratio = (double)800 / 600;
	printf("width | height: %d\t%d\n", 800, 600);
	printf("aspect_ratio: %f\n", aspect_ratio);
    double fov_adjustment = tan(deg_to_rad(scene->cam.fov * 0.5));

	printf("fov: %f\n", fov_adjustment);
	
    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            double ray_x = (2.0 * (x + 0.5) / 800 - 1.0) * fov_adjustment * aspect_ratio;
            double ray_y = (1.0 - 2.0 * (y + 0.5) / 600) * fov_adjustment;

            t_vec3 ray_dir = vec3_norm((t_vec3){ray_x, ray_y, -1.0}); // Assuming camera looks towards -Z

            // Cast the ray from camera position and check intersection with the sphere
            double t = intersect_objects(scene, scene->cam.pos, ray_dir);
			// Cast the ray from the camera position and check intersection with the plane
            // double t_plane = intersect_plane(&scene->plane, scene->cam.pos, ray_dir);
            // if (t > 0)
				// printf("t---->%f\n", t);
			// Cast the ray from camera position and check intersection with the cylinder
            // double t_cylinder = intersect_cylinder(&scene->cylinder, scene->cam.pos, ray_dir);
            // if (t_cylinder >= 0)
			// {
            //     // Intersection with the cylinder occurred, set pixel color using shading function
            //     t_vec3 hit_point = vec3_add(scene->cam.pos, vec3_scale(ray_dir, t_cylinder));
            //     t_vec3 shading = shade_cylinder(scene, &scene->light, hit_point, ray_dir);
            //     mlx_put_pixel(image, x, y, vec3_to_rgb(shading));
			// }
			if (t > 0 )
            {
				 // Intersection occurred, set pixel color to the object's shading
                t_vec3 hit_point = vec3_add(scene->cam.pos, vec3_scale(ray_dir, t));
                t_vec3 surface_normal = calculate_surface_normal(scene, hit_point);
				t_vec3 shading = shade_objects(scene, hit_point, surface_normal, ray_dir);

                mlx_put_pixel(image, x, y, vec3_to_rgb(shading));
            }
			else
			{
				mlx_put_pixel(image, x, y, vec3_to_rgb(scene->amb.color));
			}
        }
    }
}

t_scene	scene;

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	// printf("%d\n", image->instances[0].x);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
    {
        scene.light.pos.y += 2.0;
		render_scene(&scene);
        // image->instances[0].y -= 5;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
		scene.light.pos.y -= 2.0;
		render_scene(&scene);
		// image->instances[0].y += 5;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
		// image->instances[0].x += 5;
		scene.light.pos.x -= 2.0;
		render_scene(&scene);
    }
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    {
		// image->instances[0].x += 5;
		scene.light.pos.x += 2.0;
		render_scene(&scene);
    }
}

void create_scene(t_scene *scene, char *filename)
{
    bzero(scene, sizeof(t_scene));
    printf("-----PARSING FILE----: %s\n", filename);
    printf("\n\n");
    
	mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracing", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	
	mlx_loop_hook(mlx, ft_hook, mlx);
	
    parse_scene(scene, filename);

    // // Allocate memory for the image
    // scene->image = (unsigned int**)malloc(600 * sizeof(unsigned int*));
    // for (int y = 0; y < 600; y++)
    // {
    //     scene->image[y] = (unsigned int*)malloc(800 * sizeof(unsigned int));
    //     for (int x = 0; x < 800; x++)
    //     {
    //         // Set initial color to black
    //         scene->image[y][x] = mlx_rgb(0, 0, 0);
    //     }
    // }
}

int main(int ac, char **av)
{
	// t_scene	scene;

	if (ac != 2)
		return (1);
	create_scene(&scene, av[1]);
	render_scene(&scene);

	printf("\n");
	printf("cam_pos_in: %f\n", scene.cam.pos_initial.x);
	printf("cam_pos_in: %f\n", scene.cam.pos_initial.y);
	printf("cam_pos_in: %f\n", scene.cam.pos_initial.z);
	
	printf("\n");
	
	printf("amb_light: %f\n", scene.amb.color.x);
	printf("amb_light: %f\n", scene.amb.color.y);
	printf("amb_light: %f\n", scene.amb.color.z);
	
	printf("\n");

	printf("light_pos: %f\n", scene.light.pos.x);
	printf("light_pos: %f\n", scene.light.pos.y);
	printf("light_pos: %f\n", scene.light.pos.z);
	
	printf("\n");

	printf("light_color: %f\n", scene.light.color.x);
	printf("light_color: %f\n", scene.light.color.y);
	printf("light_color: %f\n", scene.light.color.z);

	printf("\n");
	
	printf("sphere_center: %f\n", scene.sphere.center.x);
	printf("sphere_center: %f\n", scene.sphere.center.y);
	printf("sphere_center: %f\n", scene.sphere.center.z);
	
	printf("\n");
	
	printf("sphere_radius: %f\n", scene.sphere.radius);
	
	printf("\n");
	
	printf("plane_coords: %f\n", scene.plane.point.x);
	printf("plane_coords: %f\n", scene.plane.point.y);
	printf("plane_coords: %f\n", scene.plane.point.z);
	
	printf("\n");

	printf("plane_normal: %f\n", scene.plane.normal.x);
	printf("plane_normal: %f\n", scene.plane.normal.y);
	printf("plane_normal: %f\n", scene.plane.normal.z);
	
	printf("\n");
	
	printf("sphere_color: %f\n", scene.sphere.color.x);
	printf("sphere_color: %f\n", scene.sphere.color.y);
	printf("sphere_color: %f\n", scene.sphere.color.z);

	printf("\n");
	
	printf("plane_color: %f\n", scene.plane.color.x);
	printf("plane_color: %f\n", scene.plane.color.y);
	printf("plane_color: %f\n", scene.plane.color.z);
	
	printf("\n");
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	return (0);
}
