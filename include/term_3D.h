/* Compiler Directives ...... */
#ifndef TERM_3D__H
#define TERM_3D__H
/* Structures ............... */
struct Vec3 {
	float x, y, z;
};
struct Tri {
	struct Vec3 p[3];
};
struct Mat4x4 {
	float m[4][4];
};
/* Functions ................ */
void multiply_mat4x4_vec3(struct Vec3 i, float m[4][4], struct Vec3 * o)
{
	o->x = i.x * m[0][0] + i.y * m[0][1] + i.z * m[0][2] + m[0][3];
	o->y = i.x * m[1][0] + i.y * m[1][1] + i.z * m[1][2] + m[1][3];
	o->z = i.x * m[2][0] + i.y * m[2][1] + i.z * m[2][2] + m[2][3];
	float w = i.x * m[3][0] + i.y * m[3][1] + i.z * m[3][2] + m[3][3];
	if (w != 0.0f) { o->x /= w; o->y /= w; o->z /= w; }
}
#endif // TERM_3D__H
/* .......................... */