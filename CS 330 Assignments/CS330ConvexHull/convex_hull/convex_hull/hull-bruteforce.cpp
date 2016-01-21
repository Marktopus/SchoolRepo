#include "hull-bruteforce.h"
#include <cfloat>//max negative float

bool Point::operator==(Point const& arg2) const
{
  return (x == arg2.x) && (y == arg2.y);
}

std::ostream& operator<< (std::ostream& os, Point const& p)
{
  os << "(";
  os << p.x;
  os << " , ";
  os << p.y;
  os << ") ";
  return os;
}

std::istream& operator>> (std::istream& os, Point & p)
{
  os >> p.x;
  os >> p.y;
  return os;
}

float find_projection_scalar(const Point& point, const Point& dirOrigin, const Point& dir)
{
  //(u.v)/(u.u) * u
  //we got rid of the multplication by u so we could just return dot product
  float uDotV = ((point.x - dirOrigin.x) * dir.x) + ((point.y - dirOrigin.y) * dir.y);
  float uDotU = (dir.x * dir.x) + (dir.y * dir.y);
  
  return (uDotU) ? (uDotV/uDotU) : 0.0f;
}

int find_support_brute_force(std::vector< Point > const& points, const Point& dir, const Point& origin)
{
  float largest = -FLT_MAX;
  float comparator = 0.0f;
  int sizeOfPoints = static_cast<int>(points.size());
  int toReturn = -1;
  for (int i = 0; i < sizeOfPoints; ++i)
  {
    comparator = find_projection_scalar(points[i], origin, dir);
    if (comparator > largest)
    {
      largest = comparator;
      toReturn = i;
    }
  }
  return toReturn;
}

std::set<int> hullBruteForce(std::vector< Point > const& points)
{
  std::set<int> hull;
  if (points.empty())
  {
    return hull;
  }
  Point lineNormal = { -1.0f, 0.0f };
  Point origin = { 0.0f, 0.0f };
  Point line;
  int leastX = find_support_brute_force(points, lineNormal, origin);
  if (leastX == -1)
  {
    return hull;
  }
  hull.insert(leastX);
  int pointsSize = points.size();
  bool sameSide;
  int sign = 0; //false is negative, true is positive
  float projectionScalar;
  for (int pointIter = 0; pointIter < pointsSize - 1; ++pointIter) // for all points
  {
    for (int pointIter2 = pointIter + 1; pointIter2 < pointsSize; ++pointIter2) // for all points not including those compared
    {
      sameSide = true;
      line.x = points[pointIter2].x - points[pointIter].x;
      line.y = points[pointIter2].y - points[pointIter].y;
      lineNormal = line;
      if (!line.x && !line.y)
      {
        continue;
      }
      
      std::swap(lineNormal.x, lineNormal.y);
      lineNormal.y = -lineNormal.y;
      sign = 0;
      for (int pivotIter = 0; (pivotIter < pointsSize) && sameSide; ++pivotIter)
      {
        projectionScalar = find_projection_scalar(points[pivotIter], points[pointIter], lineNormal);
        switch (sign)
        {
          case -1:
            if (projectionScalar > 0.0f)
            {
              sameSide = false;
            }
            break;
          case 0:
            if (projectionScalar < 0.0f)
            {
              sign = -1;
            }
            else if (projectionScalar > 0.0f)
            {
              sign = 1;
            }
            break;
          case 1:
            if (projectionScalar < 0.0f)
            {
              sameSide = false;
            }
            break;
          
        }
      }
      if (sameSide)
      {
        hull.insert(pointIter);
        hull.insert(pointIter2);
      }
    }
  }
  return hull;
}


std::vector<int> hullBruteForce2(std::vector< Point > const& points)
{
  std::vector<int> returnVal;
  if (points.empty())
  {
    return returnVal;
  }
  std::set<int> indices = hullBruteForce(points);
  for (std::set<int>::iterator it = indices.begin(); it != indices.end(); ++it)
  {
    returnVal.push_back(*it);
  }

  Point lineNormal;
  Point line;
  int pointsSize = returnVal.size();
  float projectionScalar;
  int pointIter = 0;
  int pointIter2 = pointIter + 1;
  while (pointIter2 < pointsSize)
  {
    line.x = points[returnVal[pointIter2]].x - points[returnVal[pointIter]].x;
    line.y = points[returnVal[pointIter2]].y - points[returnVal[pointIter]].y;
    lineNormal = line;
    std::swap(lineNormal.x, lineNormal.y);
    lineNormal.x = -lineNormal.x;
    for (int pivotIter = 0; pivotIter < pointsSize; ++pivotIter)
    {
      projectionScalar = find_projection_scalar(points[returnVal[pivotIter]], points[returnVal[pointIter]], lineNormal);
      if (projectionScalar < 0.0f)//it's not on the right side(not counter clockwise)
      {
        std::swap(returnVal[pointIter2], returnVal[pivotIter]);
        //resetting for the next loop
        --pointIter;
        --pointIter2;
        break;
      }
    }
    ++pointIter;
    ++pointIter2;
  }

  return returnVal;
}

