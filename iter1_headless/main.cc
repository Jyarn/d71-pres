#include <cmath>
#include <stdlib.h>
#include <unistd.h>

#define G 6.67e-11

typedef struct {
    double x, y;
} Vector;

typedef struct {
    Vector velocity, position, acceleration;
    double mass;
} Particle;

typedef struct {
    int n_particles;
    int n_steps;
    double time_step;
    int seed;
    int screen_x, screen_y;
    int obj_x_max, obj_y_max;
    int object_radius;
    double smoothing;
    int render_after_n_frames;
} Simulator_Params;

double
norm(Vector i)
{
    return std::sqrt(i.x*i.x + i.y*i.y);
}

void
one_step(Particle* particles, const Simulator_Params* params)
{
    for (int i = 0; i < params->n_particles; i++) {
        particles[i].acceleration.x = 0;
        particles[i].acceleration.y = 0;
        for (int j = 0; j < params->n_particles; j++) {
            if (i != j) {
                Particle part_i = particles[i];
                Particle part_j = particles[j];
                double mass = part_j.mass;

                Vector r;
                r.x = part_j.position.x - part_i.position.x;
                r.y = part_j.position.y - part_i.position.y ;

                double r_norm = norm(r) + params->smoothing;
                double r_norm_cubed = r_norm * r_norm * r_norm;

                particles[i].acceleration.x += G * mass * r.x / r_norm_cubed;
                particles[i].acceleration.y += G * mass * r.y / r_norm_cubed;
            }
        }
    }

    for (int i = 0; i < params->n_particles; i++) {
        particles[i].velocity.x += params->time_step * particles[i].acceleration.x;
        particles[i].velocity.y += params->time_step * particles[i].acceleration.y;

        particles[i].position.x += params->time_step * particles[i].velocity.x;
        particles[i].position.y += params->time_step * particles[i].velocity.y;
    }
}

int
main(void)
{
    Simulator_Params params = {
        .n_particles = 2000,
        .time_step = 0.1,
        .seed = 1000,
        .screen_x = 500,
        .screen_y = 500,
        .obj_x_max = 500,
        .obj_y_max = 500,
        .object_radius = 10,
        .smoothing = 1,
        .render_after_n_frames = 50,
    };

    srand(params.seed);
    Particle* particles = new Particle[params.n_particles];

    for (int i = 0; i < params.n_particles; i++) {
        particles[i].position.x = rand() % params.obj_x_max - (double)params.obj_x_max / 2 + (double)params.screen_x / 2;
        particles[i].position.y = rand() % params.obj_y_max - (double)params.obj_y_max / 2 + (double)params.screen_y / 2;
        particles[i].mass = rand();
    }

    int i = 0;
    for (int i = 0; i < 10000; i++)
        one_step(particles, &params);

    return 0;
}
