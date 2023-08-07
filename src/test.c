// Add this structure definition for planes
typedef struct s_plane {
    t_vec3 point;
    t_vec3 normal;
    t_vec3 color;
    bool set;
} t_plane;

// Modify your t_scene structure to include a plane object
typedef struct s_scene {
    // ... other fields ...
    t_plane plane;
    // ... other fields ...
} t_scene;

// Modify your parsing_plane function to correctly parse plane information
void parse_plane(t_scene *scene, char **split) {
    // ... existing parsing logic ...

    parse_vec3(split[1], &(scene->plane.point));
    parse_vec3(split[2], &(scene->plane.normal));
    parse_color(split[3], &(scene->plane.color));
    scene->plane.set = true;
}

// Implement an intersection test function for planes
double intersect_plane(t_plane *plane, t_vec3 ray_origin, t_vec3 ray_dir) {
    double denominator = vec3_dot(plane->normal, ray_dir);
    if (fabs(denominator) > 1e-6) {
        t_vec3 point_to_plane = vec3_sub(plane->point, ray_origin);
        double t = vec3_dot(point_to_plane, plane->normal) / denominator;
        if (t >= 0) {
            return t;
        }
    }
    return -1.0; // No intersection
}

// Modify your shade_objects function to include shading for planes
t_vec3 shade_objects(t_scene *scene, t_vec3 hit_point, t_vec3 surface_normal, t_vec3 ray_dir) {
    // ... existing shading logic ...

    // Iterate through the linked list and shade each object, including planes
    t_sphere *current_sphere = scene->object.sp_lst;
    while (current_sphere != NULL) {
        // ... existing shading logic ...
        current_sphere = current_sphere->next;
    }

    // Shade the plane if it's set
    if (scene->plane.set) {
        t_vec3 shading = shade_object(scene, &scene->light, hit_point, surface_normal, ray_dir);
        return shading;
    }

    // ... existing shading logic ...
}

// Modify your render_scene function to include planes in the rendering loop
void render_scene(t_scene *scene) {
    // ... existing rendering logic ...

    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 800; x++) {
            // ... existing ray casting logic ...

            double t = intersect_objects(scene, scene->cam.pos, ray_dir);
            double t_plane = intersect_plane(&scene->plane, scene->cam.pos, ray_dir);

            if (t > 0) {
                // Intersection with other objects occurred
                // ... existing shading and rendering logic ...
            } else if (t_plane >= 0) {
                // Intersection with a plane occurred, set pixel color using shading function
                t_vec3 hit_point = vec3_add(scene->cam.pos, vec3_scale(ray_dir, t_plane));
                t_vec3 surface_normal = scene->plane.normal; // Plane's normal is its surface normal
                t_vec3 shading = shade_objects(scene, hit_point, surface_normal, ray_dir);
                mlx_put_pixel(image, x, y, vec3_to_rgb(shading));
            } else {
                // No intersection, set pixel color to ambient color
                mlx_put_pixel(image, x, y, vec3_to_rgb(scene->amb.color));
            }
        }
    }
}
