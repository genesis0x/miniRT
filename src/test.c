typedef struct s_object
{
    char type; // Type identifier for the object ('s' for sphere, 'p' for plane, 'c' for cylinder)
    void *data; // Pointer to the specific object data (t_sphere*, t_plane*, t_cylinder*)
    struct s_object *next; // Pointer to the next object in the linked list
} t_object;

struct s_scene
{
    int width;
    int height;
    t_am_light amb;
    t_cam cam;
    t_light light;
    t_object *objects; // Linked list of objects in the scene
};

// ... (other code remains the same)

void parse_ids(t_scene *scene, char **split)
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

void parse_sphere(t_scene *scene, char **split)
{
    // ... (parse sphere parameters and create t_sphere object)

    t_sphere *sphere = malloc(sizeof(t_sphere));
    sphere->center = center;
    sphere->radius = radius;
    sphere->color = color;
    sphere->set = true;

    // Create a new object node and add it to the linked list
    t_object *new_object = malloc(sizeof(t_object));
    new_object->type = 's';
    new_object->data = sphere;
    new_object->next = scene->objects;
    scene->objects = new_object;
}

void parse_plane(t_scene *scene, char **split)
{
    // ... (parse plane parameters and create t_plane object)

    t_plane *plane = malloc(sizeof(t_plane));
    plane->point = point;
    plane->normal = normal;
    plane->color = color;
    plane->set = true;

    // Create a new object node and add it to the linked list
    t_object *new_object = malloc(sizeof(t_object));
    new_object->type = 'p';
    new_object->data = plane;
    new_object->next = scene->objects;
    scene->objects = new_object;
}

void parse_cylinder(t_scene *scene, char **split)
{
    // ... (parse cylinder parameters and create t_cylinder object)

    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    cylinder->center = center;
    cylinder->axis = axis;
    cylinder->diameter = diameter;
    cylinder->height = height;
    cylinder->color = color;
    cylinder->set = true;

    // Create a new object node and add it to the linked list
    t_object *new_object = malloc(sizeof(t_object));
    new_object->type = 'c';
    new_object->data = cylinder;
    new_object->next = scene->objects;
    scene->objects = new_object;
}

// ... (other parsing functions and main loop)

void cleanup_scene(t_scene *scene)
{
    // Free the memory allocated for the linked list of objects
    t_object *current = scene->objects;
    while (current != NULL)
    {
        t_object *temp = current;
        current = current->next;
        if (temp->type == 's')
            free(temp->data); // Free t_sphere object
        else if (temp->type == 'p')
            free(temp->data); // Free t_plane object
        else if (temp->type == 'c')
            free(temp->data); // Free t_cylinder object
        free(temp); // Free object node
    }
}
