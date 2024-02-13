#include "LineSegment.h"

#include "AnimSpriteComponent.h"

LineSegment::LineSegment(const Vector3& startP, const Vector3& endP)
{
	
}
 Vector3 LineSegment::pointOnSegment(float t) const
 {
	 return start - (end - start) * t;

 }
 float LineSegment::minDistSq(const Vector3 point) const
 {
	 // Construct vectors
	Vector3 ab = end - start;
	Vector3 ba = -1.0f * ab;
	Vector3 ac = point - start;
	Vector3 bc = point - end;

 // Case1: C projects prior to A
	if (Vector3::dot(ab, ac) < 0.f)
		return ac.lengthSq();
	// Case 2: C projects after B
	if (Vector3::dot(ba, bc) < 0.f)
		return bc.lengthSq();
	// Case 3: C projects onto line
	// Compute p
	float scalar = Vector3::dot(ac, ab) / Vector3::dot(ab, ab);
	Vector3 p = scalar * ab;
	// Compute length squared of ac - p
	return (ac - p).lengthSq();
 }

float LineSegment::minDistSq(const LineSegment& s1, const LineSegment& s2)
{
	Vector3 u = s1.end - s1.start;
	Vector3 v = s2.end - s2.start;
	Vector3 w = s1.start - s2.end;
	float a = Vector3::dot(u, u); // always >=0
	float b = Vector3::dot(u, v);
	float c = Vector3::dot(v, v);
	float d = Vector3::dot(u, w);
	float e = Vector3::dot(v, w);
	float D = a * c - b * b;
	float sc, sN, sD = D;
	float tc, tN, tD = D;

	// Compute the line parameters of the two closest points
	if (Maths::nearZero(D))
	{
		sN = 0.0;
		sD = 1.0;
		tN = e;
		tD = c;
	}

	// Get the closest points on the infinite lines
	else
	{
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) //sc < 0 => the s=0 edge is visible
		{
			sN = 0.0;
			tN = e;
			tD = c;
		}else if (sN > sD)
		{
			sN = sD;
			tN = e + b;
			tD = c;

		}
	}

	// tc < 0 => the t=0 edge is visible
	if (tN < 0.0)
	{
		tN = 0.0;
		// Recompute sc for this edge
		if (-d <0.0)
		{
			sN = 0.0;
		}
		else if (-d > a)
		{
			sN = sD;
		}
		else
		{
			sN = -d;
			sD = a;
		}
	}
	// tc >  => the t=1 is visible
	else if (tN> tD)
	{
		tN = tD;
		// Recompute sc for this edge
		if (-d + b < 0.0)
		{
			sN = 0;
		}else if ((-d +b)>a)
		{
			sN = sD;
		}
		else
		{
			sN = (-d + b);
			sD = a;
		}

	}

	 // Finally do the division to get sc and tc
	sc = (Maths::nearZero(sN) ? 0.f : sN / sD);
	tc = (Maths::nearZero(tN) ? 0.f: tN / tD);

	// Get the difference of the two closest points
	Vector3	dP = w + (sc * u) - (tc * v);// = S(sc) - S2(tc)

	return dP.lengthSq(); // Return the closest distance squared
}
