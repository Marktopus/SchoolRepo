#include "closestpair.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <utility>

enum PointOrg
{
  Horizontal,
  Vertical,
  SamePoint,
  Count
};

float DistFromCenter(const Point& lhs, float center, PointOrg org)
{
  switch (org)
  {
    case Horizontal:
      return abs(lhs.x - center);
      break;
    case Vertical:
      return abs(lhs.y - center);
      break;
    default:
      return 0.0f;
  }
  
}

PointOrg CheckAllPoints(std::vector< int > const& indices, std::vector< Point > const& points)
{
  bool vert = true;
  bool horiz = true;
  for (unsigned i = 0, j = 1; j < indices.size(); ++i, ++j)
  {
    if (points[indices[i]].x != points[indices[j]].x)
    {
      horiz = false;
    }
    else if (points[indices[i]].y != points[indices[j]].y)
    {
      vert = false;
    }
  }
  if (!horiz)
  {
    return Horizontal;
  }
  else if (!vert)
  {
    return Vertical;
  }
  else
  {
    return SamePoint;
  }
}

Point operator-(const Point& rhs, const Point& lhs)
{
  Point returnVal;
  returnVal.x = (rhs.x - lhs.x);
  returnVal.y = (rhs.y - lhs.y);
  return returnVal;
}

float LengthSq(const Point& rhs)
{
  return (rhs.x * rhs.x) + (rhs.y * rhs.y);
}

float Length(const Point& rhs)
{
  return sqrt(LengthSq(rhs));
}

std::ostream& operator<< (std::ostream& os, Point const& p) {
	os << "(" << p.x << " , " << p.y << ") ";
	return os;
}

std::istream& operator>> (std::istream& os, Point & p) {
	os >> p.x >> p.y;
	return os;
}

////////////////////////////////////////////////////////////////////////////////
float closestPair_aux(std::vector< int > const& indices, std::vector< Point > const& points);

////////////////////////////////////////////////////////////////////////////////
float closestPair ( std::vector< Point > const& points ) {
	unsigned size = points.size();

	//std::cerr << "closestPair_aux " << size << " points:";
	//for(int i=0;i<size;++i) { std::cerr << points[i] << " "; } std::cerr << std::endl;

	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();
  std::vector< int > indices;
  for (unsigned i = 0; i < points.size(); ++i)
  {
    indices.push_back(static_cast<int>(i));
  }
	return closestPair_aux( indices, points );
}

////////////////////////////////////////////////////////////////////////////////
float closestPair_aux(std::vector< int > const& indices, std::vector< Point > const& points) 
{
  PointOrg org = CheckAllPoints(indices, points);
  
  unsigned size = indices.size();

	//std::cerr << "closestPair_aux ";
	//for(int i=0;i<size;++i) { std::cerr << points[ indices[i] ] << " "; } std::cerr << std::endl;
  //find center
  float center = 0.0f;
  for (unsigned i = 0; i < indices.size(); ++i)
  {
    switch (org)
    {
      case Horizontal:
        center += points[indices[i]].x;
        break;
      case Vertical:
        center += points[indices[i]].y;
        break;
      case SamePoint:
        center += 0.0f;
        break;
      default:
        break;
    }
    
  }
  center /= static_cast<float>(indices.size());

  std::vector<int> left;
  std::vector<int> right;
  float curPoint = 0.0f;
  for (unsigned i = 0; i < indices.size(); ++i)
  {
    switch (org)
    {
      case Horizontal:
        curPoint = points[indices[i]].x;
        break;
      case Vertical:
        curPoint = points[indices[i]].y;
        break;
      case SamePoint:
        curPoint = 0.0f;
        break;
      default:
        break;
    }
    if (curPoint < center)
    {
      left.push_back(indices[i]);
    }
    else
    {
      right.push_back(indices[i]);
    }
  }

	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();

  float leftVal = closestPair_aux(left, points);
  float rightVal = closestPair_aux(right, points);
  float min_dist = std::min(leftVal, rightVal);

  for (unsigned i = 0; i < left.size(); ++i)
  {
    float newLeftVal = 0.0f;
    switch (org)
    {
      case Horizontal:
        newLeftVal = points[left[i]].x;
        break;
      case Vertical:
        newLeftVal = points[left[i]].y;
        break;
      case SamePoint:
        newLeftVal = 0.0f;
        break;
      default:
        break;
    }
    if (abs(newLeftVal - center) < min_dist)
    {
      for (unsigned j = 0; j < right.size(); ++j)
      {
        float newRightVal = 0.0f;
        switch (org)
        {
          case Horizontal:
            newRightVal = points[right[j]].x;
            break;
          case Vertical:
            newRightVal = points[right[j]].y;
            break;
          case SamePoint:
            newLeftVal = 0.0f;
            break;
          default:
            break;
        }
        if (abs(newRightVal - center) < min_dist)
        {
          float newLen = Length(points[left[i]] - points[right[j]]);
          if (newLen < min_dist)
          {
            min_dist = newLen;
          }
        }
      }
    }
  }

	return min_dist;
}

