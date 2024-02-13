#include "Spline.h"


Vector3 Spline::compute(size_t index, float t) const
{
	if (index >= controPoints.size())
		return controPoints.back();
	if (index == 0)
		return controPoints[index];
	if (index + 2 >= controPoints.size())
		return controPoints[index];

	Vector3 p0 = controPoints[index - 1];
	Vector3 p1 = controPoints[index];
	Vector3 p2 = controPoints[index + 1];
	Vector3 p3 = controPoints[index + 2];
	// Compute position according to Catmull-Rom equation
	Vector3 position = 0.5f * ((2.0f * p1) + (-1.0f * p0 + p2) * t + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t + (-1.0f * p0 + 3.0f * p1 - 3.0f * p1 - 3.0f * p2 + p3) * t * t * t);
	return position;
}
