/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:50:12 by hahadiou          #+#    #+#             */
/*   Updated: 2023/07/23 18:50:13 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double ratio;
    int r, g, b;
} Color;

typedef struct {
    double x, y, z;
} Vector3;

typedef struct {
    char type;
    Color color;
    Vector3 position;
    double diameter;
    double height;
    Vector3 orientation;
} Object;

typedef struct {
    double ratio;
    Color color;
} AmbientLight;

typedef struct {
    Vector3 position;
    double fov;
    Vector3 orientation;
} Camera;

typedef struct {
    Vector3 position;
    double ratio;
    Color color;
} Light;

typedef struct {
    AmbientLight ambient_light;
    Camera camera;
    Light light;
    Object* objects;
    int num_objects;
} Scene;

// Helper function to parse color information
Color parse_color(char* color_str) {
    Color color;
    sscanf(color_str, "%d,%d,%d", &color.r, &color.g, &color.b);
    return color;
}

// Helper function to parse vector information
Vector3 parse_vector(char* vector_str) {
    Vector3 vector;
    sscanf(vector_str, "%lf,%lf,%lf", &vector.x, &vector.y, &vector.z);
    return vector;
}

// Function to parse the scene description file and create the scene
Scene parse_scene_description(const char* filename) {
    Scene scene;
    scene.num_objects = 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open the file '%s'\n", filename);
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char type;
        if (sscanf(line, "%c ", &type) == 1) {
            switch (type) {
                case 'A': // Ambient lighting
                    sscanf(line, "%*c %lf %d,%d,%d", &scene.ambient_light.ratio,
                           &scene.ambient_light.color.r, &scene.ambient_light.color.g, &scene.ambient_light.color.b);
                    break;
                case 'C': // Camera
                    sscanf(line, "%*c %lf,%lf,%lf %lf,%lf,%lf %lf",
                           &scene.camera.position.x, &scene.camera.position.y, &scene.camera.position.z,
                           &scene.camera.orientation.x, &scene.camera.orientation.y, &scene.camera.orientation.z,
                           &scene.camera.fov);
                    break;
                case 'L': // Light
                    sscanf(line, "%*c %lf,%lf,%lf %lf %d,%d,%d",
                           &scene.light.position.x, &scene.light.position.y, &scene.light.position.z,
                           &scene.light.ratio, &scene.light.color.r, &scene.light.color.g, &scene.light.color.b);
                    break;
                case 'sp': // Sphere
                case 'pl': // Plane
                case 'cy': // Cylinder
                    if (scene.num_objects == 0) {
                        scene.objects = (Object*)malloc(sizeof(Object));
                    } else {
                        scene.objects = (Object*)realloc(scene.objects, (scene.num_objects + 1) * sizeof(Object));
                    }

                    Object object;
                    object.type = type;
                    sscanf(line, "%*c %lf,%lf,%lf %lf %d,%d,%d %lf,%lf,%lf %lf %lf,%lf,%lf",
                           &object.position.x, &object.position.y, &object.position.z,
                           &object.diameter, &object.color.r, &object.color.g, &object.color.b,
                           &object.orientation.x, &object.orientation.y, &object.orientation.z,
                           &object.height);

                    scene.objects[scene.num_objects++] = object;
                    break;
                default:
                    printf("Error: Unknown type identifier '%c'\n", type);
                    fclose(file);
                    exit(1);
            }
        }
    }

    fclose(file);
    return scene;
}

// Function to free memory used by the scene objects
void free_scene(Scene scene) {
    free(scene.objects);
}

int main() {
    Scene scene = parse_scene_description("scene.rt");

    // Use the parsed scene data for rendering or further processing

    free_scene(scene);

    return 0;
}
