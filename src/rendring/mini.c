/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:07:10 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/23 20:07:12 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    double ratio;
    Vector3 color;
} Light;

typedef struct {
    double ratio;
    Vector3 color;
} AmbientLight;

typedef struct {
    double radius;
    Vector3 center;
    Vector3 color;
} Sphere;

typedef struct {
    Vector3 normal;
    Vector3 point;
    Vector3 color;
} Plane;

// Function to calculate the dot product of two vectors
double dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to calculate the length of a vector
double length(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Function to normalize a vector
Vector3 normalize(Vector3 v) {
    double len = length(v);
    Vector3 result = {v.x / len, v.y / len, v.z / len};
    return result;
}

// Function to calculate the color of a pixel based on intersections and lighting
Vector3 calculate_pixel_color(Ray ray, Sphere sphere, Plane plane, Light light, AmbientLight ambient_light) {
    Vector3 pixel_color = {0.0, 0.0, 0.0};
    double t;

    if (intersect_sphere(ray, sphere, &t)) {
        Vector3 point = {
            ray.origin.x + t * ray.direction.x,
            ray.origin.y + t * ray.direction.y,
            ray.origin.z + t * ray.direction.z
        };
        Vector3 normal = normalize({point.x - sphere.center.x, point.y - sphere.center.y, point.z - sphere.center.z});
        Vector3 ambient = {
            ambient_light.ratio * ambient_light.color.x,
            ambient_light.ratio * ambient_light.color.y,
            ambient_light.ratio * ambient_light.color.z
        };

        Vector3 light_dir = normalize({light.origin.x - point.x, light.origin.y - point.y, light.origin.z - point.z});
        double dot_product = dot(light_dir, normal);
        if (dot_product < 0) dot_product = 0;
        Vector3 diffuse = {
            light.ratio * light.color.x * dot_product,
            light.ratio * light.color.y * dot_product,
            light.ratio * light.color.z * dot_product
        };

        pixel_color.x = sphere.color.x * (ambient.x + diffuse.x);
        pixel_color.y = sphere.color.y * (ambient.y + diffuse.y);
        pixel_color.z = sphere.color.z * (ambient.z + diffuse.z);
    } else if (intersect_plane(ray, plane, &t)) {
        Vector3 point = {
            ray.origin.x + t * ray.direction.x,
            ray.origin.y + t * ray.direction.y,
            ray.origin.z + t * ray.direction.z
        };
        Vector3 normal = normalize(plane.normal);
        Vector3 ambient = {
            ambient_light.ratio * ambient_light.color.x,
            ambient_light.ratio * ambient_light.color.y,
            ambient_light.ratio * ambient_light.color.z
        };

        Vector3 light_dir = normalize({light.origin.x - point.x, light.origin.y - point.y, light.origin.z - point.z});
        double dot_product = dot(light_dir, normal);
        if (dot_product < 0) dot_product = 0;
        Vector3 diffuse = {
            light.ratio * light.color.x * dot_product,
            light.ratio * light.color.y * dot_product,
            light.ratio * light.color.z * dot_product
        };

        pixel_color.x = plane.color.x * (ambient.x + diffuse.x);
        pixel_color.y = plane.color.y * (ambient.y + diffuse.y);
        pixel_color.z = plane.color.z * (ambient.z + diffuse.z);
    }

    return pixel_color;
}

// Function to render the image
void render_image(Scene scene, int image_width, int image_height) {
    Vector3 image[image_width][image_height];
    Vector3 direction;

    // Calculate the direction vector for each pixel from the camera
    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            double ndc_x = (2.0 * x) / image_width - 1.0;
            double ndc_y = 1.0 - (2.0 * y) / image_height;

            direction.x = ndc_x * tan(scene.camera.fov / 2.0);
            direction.y = ndc_y * tan(scene.camera.fov / 2.0);
            direction.z = 1.0; // Assuming camera is pointing along the positive z-axis

            Ray ray;
            ray.origin = scene.camera.position;
            ray.direction = normalize(direction);

            // Calculate the color of the pixel based on intersections and lighting
            Vector3 pixel_color = calculate_pixel_color(ray, scene.objects[0].sphere, scene.objects[1].plane,
                                                        scene.light, scene.ambient_light);

            // Store the pixel color in the image
            image[x][y] = pixel_color;
        }
    }

    // Display or save the image
    // ...
}
