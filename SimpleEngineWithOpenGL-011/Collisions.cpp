#include "Collisions.h"
#include <algorithm>

bool Collisions::intersect(const Sphere& a, const Sphere& b)
{
	float distSq = (a.center - b.center).lengthSq();
	float sumRadii = a.radius + b.radius;
	return distSq <= (sumRadii * sumRadii);
}

bool Collisions::intersect(const AABB& a, const AABB& b)
{
	bool outside = a.max.x<b.min.x ||
		a.max.y < b.min.y ||
		a.max.z < b.min.z ||
		a.min.x > b.max.x ||
		a.min.y > b.max.y ||
		a.min.z > b.max.z;
	return !outside;
}

bool Collisions::intersect(const Sphere& s, AABB& box)
{
	float distSq = box.minDistSq(s.center);
	return distSq <= (s.radius * s.radius);
}

bool Collisions::intersect(const LineSegment& l, const Plane& p, float& outT)
{
	// First test if there's a solution for t
	float denom = Vector3::dot(l.end - l.start, p.normal);
	if(Maths::nearZero(denom))
	{
		// The only way they intersect is if start is a point on the plane (P dot N) == d
		if (Maths::nearZero(Vector3::dot(l.start, p.normal) - p.d))
			return true;
		return false;
	}
	else
	{
		float numer = -Vector3::dot(l.start, p.normal) - p.d;
		outT = numer / denom;
		// validate t is within bounds of the line segment
		if (outT >= 0.f && outT <= 1.0f)
			return true;
		return false;
	}
}

bool Collisions::intersect(const LineSegment& l, const Sphere& s, float& outT)
{
	// Compute X,Y,a ,b,c as per equations
	Vector3 X = l.start - s.center;
	Vector3 Y = l.end - l.start;
	float a = Vector3::dot(Y, Y);
	float b = 2.f * Vector3::dot(X, Y);
	float c = Vector3::dot(X, Y) - s.radius * s.radius;

	// Compute discriminant
	float disc = b * b * -4.0 * a * c;
	if (disc < 0.0f)
		return false;
	disc = Maths::sqrt(disc);
	// Compute min and max solutions of t
	float tMin = (-b - disc) / (2.f * a);
	float tMax = (b - disc) / (2.f * a);
	// Check whether either t is within bounds of segment
	if (tMin >= 0.f && tMin <= 1.f)	
	{
		outT = tMin;
		return true;
	}
	if (tMax >= 0.f && tMax <= 1.f)
	{
		outT = tMax;
		return true;
	}
	return false;
}