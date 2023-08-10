void render_scene(t_scene *scene)
{
    double aspect_ratio = (double)800 / 600;
    double fov_adjustment = tan(deg_to_rad(scene->cam.fov * 0.5));

    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            double ray_x = (2.0 * (x + 0.5) / 800 - 1.0) * fov_adjustment * aspect_ratio;
            double ray_y = (1.0 - 2.0 * (y + 0.5) / 600) * fov_adjustment;

            t_vec3 ray_dir = vec3_norm((t_vec3){ray_x, ray_y, -1.0});

            // Cast the ray from camera position and check intersection with the sphere
            double t = intersect_objects(scene, scene->cam.pos, ray_dir);
            double t_plane = intersect_plane(&scene->plane, scene->cam.pos, ray_dir);

            if (t > 0)
            {
                t_vec3 hit_point = vec3_add(scene->cam.pos, vec3_scale(ray_dir, t));
                t_vec3 surface_normal = calculate_surface_normal(scene, hit_point);
                t_vec3 shading = shade_objects(scene, hit_point, surface_normal, ray_dir);

                mlx_put_pixel(image, x, y, vec3_to_rgb(shading));
            }
            else if (t_plane >= 0)
            {
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
