#pragma once
#include <vector>
#include "Vector3.h"

using std::vector;

struct Spline
{
	vector<Vector3> controPoints;

	size_t getNbPoints() const { return controPoints.size(); }
	Vector3 compute(size_t index, float t) const;
};

