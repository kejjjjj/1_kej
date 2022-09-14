#include "pch.h"

void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
	float angle;
	static float sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);

	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);

	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward) {
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if (right) {
		right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
		right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
		right[2] = -1 * sr * cp;
	}
	if (up) {
		up[0] = (cr * sp * cy + -sr * -sy);
		up[1] = (cr * sp * sy + -sr * cy);
		up[2] = cr * cp;
	}
}
void vectoangles(const vec3_t value1, vec3_t angles) {
	float forward;
	float yaw, pitch;

	if (value1[1] == 0 && value1[0] == 0) {
		yaw = 0;
		if (value1[2] > 0) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if (value1[0]) {
			yaw = (atan2(value1[1], value1[0]) * 180 / M_PI);
		}
		else if (value1[1] > 0) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if (yaw < 0) {
			yaw += 360;
		}

		forward = sqrt(value1[0] * value1[0] + value1[1] * value1[1]);
		pitch = (atan2(value1[2], forward) * 180 / M_PI);
		if (pitch < 0) {
			pitch += 360;
		}
	}

	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = 0;
}
void VectorsToAngles(vec3_t src, vec3_t dst, vec3_t outA)
{
	vec3_t out;
	VectorSubtract(dst, src, out);
	vectoangles(out, outA);
}
void vector_scale(vec3_t vector, float scale, vec3_t out) {
	out[0] = vector[0] *= scale;
	out[1] = vector[1] *= scale;
	out[2] = vector[2] *= scale;

	//return Vec3{ vector[0], vector[1], vector[2] };
}
float vector_scaleComponent(float index, float scale) {
	return index *= scale;
}
float vector_addComponent(float index, float amount) {
	return index += amount;
}
void vector_add(vec3_t veca, vec3_t vecb, vec3_t out)
{
	out[0] = veca[0] += vecb[0];
	out[1] = veca[1] += vecb[1];
	out[2] = veca[2] += vecb[2];

	//return Vec3{ veca[0], veca[1], veca[2] };
}
void AnglesToForward(vec3_t angles, vec3_t origin, float scale, vec3_t out)
{
	vec3_t forwardAngles = { angles[0], angles[1], angles[2] };

	AngleVectors(angles, forwardAngles, NULL, NULL);
	vector_scale(forwardAngles, scale, out); //vec[i] * scale

	vector_add(forwardAngles, origin, out); //vec[i] + GetEye()[0]

	//return scaled;
}
void AnglesToRight(vec3_t angles, vec3_t origin, float scale, vec3_t out)
{
	vec3_t rightAngles = { angles[0], angles[1], angles[2] };

	AngleVectors(angles, NULL, rightAngles, NULL);
	vector_scale(rightAngles, scale, out); //vec[i] * scale

	vector_add(rightAngles, origin, out); //vec[i] + GetEye()[1]

	//return scaled;
}
void AnglesToUp(vec3_t angles, vec3_t origin, float scale, vec3_t out)
{
	vec3_t upAngles = { angles[0], angles[1], angles[2] };

	AngleVectors(angles, NULL, NULL, upAngles);
	vector_scale(upAngles, scale, out); //vec[i] * scale

	vector_add(upAngles, origin, out); //vec[i] + GetEye()[2]

	//return scaled;
}
float AngleNormalizePI(float angle)
{
	angle = fmodf(angle + (float)M_PI, 2 * (float)M_PI);
	return angle < 0 ? angle + (float)M_PI : angle - (float)M_PI;
}
float AngleNormalize360(float angle) {
	return (360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535);
}
float AngleNormalize180(float angle) {
	angle = AngleNormalize360(angle);
	if (angle > 180.0) {
		angle -= 360.0;
	}
	return angle;
}

float AngleDelta(float angle1, float angle2) {
	return AngleNormalize180(angle1 - angle2);
}
vec_t VectorNormalize(vec3_t v) {
	float length, ilength;

	length = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	length = sqrt(length);

	if (length) {
		ilength = 1 / length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}

	return length;
}

vec_t VectorNormalize2(const vec3_t v, vec3_t out) {
	float length, ilength;

	length = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	length = sqrt(length);

	if (length) {
		ilength = 1 / length;
		out[0] = v[0] * ilength;
		out[1] = v[1] * ilength;
		out[2] = v[2] * ilength;
	}
	else {
		VectorClear(out);
	}

	return length;

}
void VectorInverse(vec3_t v) {
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}
