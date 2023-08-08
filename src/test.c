// ... (Previous code)

struct s_light
{
    bool set;
    t_vec3 pos;
    double ratio;
    t_vec3 color;
    t_light *next;
};

// ... (Other structures and functions)

// Function to create a new light node
t_light *create_light_node()
{
    t_light *new_node = (t_light *)malloc(sizeof(t_light));
    if (new_node == NULL)
        return NULL;
    new_node->next = NULL;
    return new_node;
}

// Function to add a new light to the back of the light list
void add_light_to_back(t_light **lst, t_light *new_node)
{
    if (*lst == NULL)
        *lst = new_node;
    else
    {
        t_light *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

// Function to parse light data from split and add to the scene's light list
void parse_light(t_scene *scene, char **split)
{
    if (ft_array_len(split) != 4)
        dprintf(2, "Invalid Number of args in param %s: ", split[0]);
    t_light *new_light = create_light_node();
    parse_vec3(split[1], &(new_light->pos));
    stod(split[2], &(new_light->ratio));
    parse_color(split[3], &(new_light->color));
    new_light->color = color_scale(new_light->ratio, new_light->color);
    new_light->set = true;
    add_light_to_back(&scene->light, new_light);
}

// ... (Other parsing functions)

// Function to calculate shading from multiple light sources
t_vec3 shade_objects(t_scene *scene, t_vec3 hit_point, t_vec3 surface_normal, t_vec3 ray_dir)
{
    t_vec3 shading = (t_vec3){0, 0, 0};

    // Iterate through the linked list and shade each object
    t_sphere *current_sphere = scene->object.sp_lst;
    while (current_sphere != NULL)
    {
        if (vec3_length(vec3_sub(hit_point, current_sphere->center)) <= current_sphere->radius)
            shading = vec3_add(shading, shade_object(scene, scene->light, hit_point, surface_normal, ray_dir));
        current_sphere = current_sphere->next;
    }

    // Iterate through the linked list of lights and calculate shading from each light
    t_light *current_light = scene->light;
    while (current_light != NULL)
    {
        t_vec3 light_shading = shade_object(scene, current_light, hit_point, surface_normal, ray_dir);
        shading = vec3_add(shading, light_shading);
        current_light = current_light->next;
    }

    // Similar shading for other objects

    return shading;
}

// ... (Other functions)

// Main rendering loop
void render_scene(t_scene *scene)
{
    // ... (Previous rendering code)

    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            // ... (Previous ray tracing code)

            // Cast the ray from camera position and check intersection with objects
            double t = intersect_objects(scene, scene->cam.pos, ray_dir);
            // Cast the ray from camera position and check intersection with plane
            double t_plane = intersect_plane(&scene->plane, scene->cam.pos, ray_dir);

            if (t > 0)
            {
                // Intersection occurred, set pixel color to the object's shading
                t_vec3 hit_point = vec3_add(scene->cam.pos, vec3_scale(ray_dir, t));
                t_vec3 surface_normal = calculate_surface_normal(scene, hit_point);
                t_vec3 shading = shade_objects(scene, hit_point, surface_normal, ray_dir);
                mlx_put_pixel(image, x, y, vec3_to_rgb(shading));
            }
            else if (t_plane >= 0)
            {
                // Intersection with a plane occurred, set pixel color using shading function
                t_vec3 hit_point = vec3_add(scene->cam.pos, vec3_scale(ray_dir, t_plane));
                t_vec3 surface_normal = scene->plane.normal;
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

int main()
{
    // ... (Previous main function code)

    // Initialize the scene
    t_scene scene;
    init_scene(&scene);

    // Parse scene data from a file
    parse_scene(&scene, "scene.txt");

    // Render the scene
    render_scene(&scene);

    // ... (Previous main function code)

    return 0;
}
