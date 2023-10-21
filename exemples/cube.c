/* Include Standard Libraries */
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/term_canvas.h"
#include "../include/term_3D.h"
/* Entry Point .............. */
int main(void)
{
	struct Canvas canvas = new_canvas((struct SIZE){ 240, 160 });
	set_terminal_mode();
	float a = 0.0f;
	struct Tri mesh[12] = {
		// SOUTH
		(struct Tri){
			(struct Vec3){ 0.0f, 0.0f, 0.0f },
			(struct Vec3){ 0.0f, 1.0f, 0.0f },
			(struct Vec3){ 1.0f, 1.0f, 0.0f },
		},
		(struct Tri){
			(struct Vec3){ 0.0f, 0.0f, 0.0f },
			(struct Vec3){ 1.0f, 1.0f, 0.0f },
			(struct Vec3){ 1.0f, 0.0f, 0.0f },
		},
		// EAST
		(struct Tri){
			(struct Vec3){ 1.0f, 0.0f, 0.0f },
			(struct Vec3){ 1.0f, 1.0f, 0.0f },
			(struct Vec3){ 1.0f, 1.0f, 1.0f },
		},
		(struct Tri){
			(struct Vec3){ 1.0f, 0.0f, 1.0f },
			(struct Vec3){ 1.0f, 1.0f, 1.0f },
			(struct Vec3){ 1.0f, 0.0f, 1.0f },
		},
		// NORTH
		(struct Tri){
			(struct Vec3){ 1.0f, 0.0f, 1.0f },
			(struct Vec3){ 1.0f, 1.0f, 1.0f },
			(struct Vec3){ 0.0f, 1.0f, 1.0f },
		},
		(struct Tri){
			(struct Vec3){ 1.0f, 0.0f, 1.0f },
			(struct Vec3){ 0.0f, 1.0f, 1.0f },
			(struct Vec3){ 0.0f, 0.0f, 1.0f },
		},
		// WEST
		(struct Tri){
			(struct Vec3){ 0.0f, 0.0f, 1.0f },
			(struct Vec3){ 0.0f, 1.0f, 1.0f },
			(struct Vec3){ 0.0f, 1.0f, 0.0f },
		},
		(struct Tri){
			(struct Vec3){ 0.0f, 0.0f, 1.0f },
			(struct Vec3){ 0.0f, 1.0f, 0.0f },
			(struct Vec3){ 0.0f, 0.0f, 1.0f },
		},
		// TOP
		(struct Tri){
			(struct Vec3){ 0.0f, 1.0f, 0.0f },
			(struct Vec3){ 0.0f, 1.0f, 1.0f },
			(struct Vec3){ 1.0f, 1.0f, 1.0f },
		},
		(struct Tri){
			(struct Vec3){ 0.0f, 1.0f, 0.0f },
			(struct Vec3){ 1.0f, 1.0f, 1.0f },
			(struct Vec3){ 1.0f, 1.0f, 0.0f },
		},
		// BOTTOM
		(struct Tri){
			(struct Vec3){ 1.0f, 0.0f, 1.0f },
			(struct Vec3){ 0.0f, 0.0f, 1.0f },
			(struct Vec3){ 0.0f, 0.0f, 0.0f },
		},
		(struct Tri){
			(struct Vec3){ 1.0f, 0.0f, 1.0f },
			(struct Vec3){ 0.0f, 0.0f, 0.0f },
			(struct Vec3){ 1.0f, 0.0f, 0.0f },
		},
	};
	struct Tri tri_projected;
	struct Tri tri_rotatedx;
	struct Tri tri_rotatedy;
	struct Tri tri_rotatedz;
	for (size_t j = 0; j < 60; ++j) {
		float matrix[4][4] = {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		float rot_x[4][4] = {
			{ 1.0f, 0.0f,                       0.0f,                      0.0f },
			{ 0.0f, cosf(a * (M_PI / 180.0f)),  sinf(a * (M_PI / 180.0f)), 0.0f },
			{ 0.0f, -sinf(a * (M_PI / 180.0f)), cosf(a * (M_PI / 180.0f)), 0.0f },
			{ 0.0f, 0.0f,                       0.0f,                      1.0f },
		};
		float rot_z[4][4] = {
			{ cosf(a * (M_PI / 180.0f)),  sinf(a * (M_PI / 180.0f)), 0.0f, 0.0f },
			{ -sinf(a * (M_PI / 180.0f)), cosf(a * (M_PI / 180.0f)), 0.0f, 0.0f },
			{ 0.0f, 0.0f,                       1.0f,                      1.0f },
			{ 0.0f, 0.0f,                       0.0f,                      1.0f },
		};
		wprintf(L"\033[H\n");
		clear_canvas(canvas, DEFAULT, DEFAULT, 0);
		for (int i = 0; i < 12; ++i) {
			multiply_mat4x4_vec3(mesh[i].p[0], rot_z, &tri_rotatedz.p[0]);
			multiply_mat4x4_vec3(mesh[i].p[1], rot_z, &tri_rotatedz.p[1]);
			multiply_mat4x4_vec3(mesh[i].p[2], rot_z, &tri_rotatedz.p[2]);
			
			multiply_mat4x4_vec3(tri_rotatedz.p[0], rot_x, &tri_rotatedy.p[0]);
			multiply_mat4x4_vec3(tri_rotatedz.p[1], rot_x, &tri_rotatedy.p[1]);
			multiply_mat4x4_vec3(tri_rotatedz.p[2], rot_x, &tri_rotatedy.p[2]);
			
			multiply_mat4x4_vec3(tri_rotatedy.p[0], matrix, &tri_projected.p[0]);
			multiply_mat4x4_vec3(tri_rotatedy.p[1], matrix, &tri_projected.p[1]);
			multiply_mat4x4_vec3(tri_rotatedy.p[2], matrix, &tri_projected.p[2]);
			
			// for (size_t k = 0; k < 3; ++k) {
				// set_pixel(canvas, (struct Vec2){ floorf(tri_projected.p[k].x * 20.0f + (canvas.width / 2)), floorf(tri_projected.p[k].y * 20.0f + (canvas.height / 2)) }, CANVAS_TINT_FILL);
			// }
			draw_wire_frame_triangle(canvas, (struct Vec2){ floorf(tri_projected.p[0].x * 30.0f + (canvas.width / 2)), floorf(tri_projected.p[0].y * 30.0f + (canvas.height / 2)) },
											 (struct Vec2){ floorf(tri_projected.p[1].x * 30.0f + (canvas.width / 2)), floorf(tri_projected.p[1].y * 30.0f + (canvas.height / 2)) },
											 (struct Vec2){ floorf(tri_projected.p[2].x * 30.0f + (canvas.width / 2)), floorf(tri_projected.p[2].y * 30.0f + (canvas.height / 2)) },
											 DEFAULT, DEFAULT, CANVAS_TINT_FILL);
			// wprintf(L"tri_projected.p[0].x * 10.0f + (canvas.width / 2) = %f, tri_projected.p[0].y * 10.0f + (canvas.height / 2) = %f\n", floorf(tri_projected.p[0].x * 10.0f + (canvas.width / 2)), floorf(tri_projected.p[0].y * 10.0f + (canvas.height / 2)));
			// wprintf(L"tri_projected.p[1].x * 10.0f + (canvas.width / 2) = %f, tri_projected.p[1].y * 10.0f + (canvas.height / 2) = %f\n", floorf(tri_projected.p[1].x * 10.0f + (canvas.width / 2)), floorf(tri_projected.p[1].y * 10.0f + (canvas.height / 2)));
			// wprintf(L"tri_projected.p[2].x * 10.0f + (canvas.width / 2) = %f, tri_projected.p[2].y * 10.0f + (canvas.height / 2) = %f\n", floorf(tri_projected.p[2].x * 10.0f + (canvas.width / 2)), floorf(tri_projected.p[2].y * 10.0f + (canvas.height / 2)));
		}
		draw_canvas(canvas);
		a += 10.0f;
	}
	wprintf(L"\033[0m");
	wprintf(L"[ DBG ] Program Ended\n");
	free_canvas(canvas);
	return 0;
}
/* .......................... */
