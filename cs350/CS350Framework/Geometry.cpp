///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Geometry.hpp"
#include "DebugDraw.hpp"
#include "Application.hpp"


float DistFromPlane(const Vector3& point, const Vector3& normal, float planeDistance)
{
  //compute the vector from plane's point to poi
  Math::Vector3 vectorToPoint = point - (normal * planeDistance);

  //project this vector on to the normal to find the distance from the plane
  return vectorToPoint.Dot(normal);
}

Vector3 ProjectPointOnPlane(const Vector3& point, const Vector3& normal, float planeDistance)
{
  float distFromPlane = DistFromPlane(point, normal, planeDistance);
  
  //subtract normal * distance from plane to get our projected point
  return point - (distFromPlane * normal);
}

bool BarycentricCoordinates(const Vector3& point, const Vector3& a, const Vector3& b,
                            float& u, float& v, float epsilon)
{
  
  if(a != b)
  {
    Math::Vector3 ba = a - b;
    float baLen = ba.Length();
    
    Math::Vector3 normal = ba / baLen;
    u = normal.Dot(point - b) / baLen;
    v = 1.0f - u;

    if(u == Math::Clamp(u, -epsilon, 1.0f + epsilon))
    {
      if(v == Math::Clamp(v, -epsilon, 1.0f + epsilon))
      {
        return true;
      }
    }
  }
  return false;
}

bool BarycentricCoordinates(const Vector3& point, const Vector3& a, const Vector3& b, const Vector3& c,
                            float& u, float& v, float& w, float epsilon)
{
  if((a != b) && (a != c) && (b != c))
  {

    Math::Vector3 v0 = point - c;
    Math::Vector3 v1 = a - c;
    Math::Vector3 v2 = b - c;

    float aCramer = v1.Dot(v1);
    float bCramer = v2.Dot(v1);
    float cCramer = bCramer;
    float dCramer = v2.Dot(v2);

    float eCramer = v0.Dot(v1);
    float fCramer = v0.Dot(v2);


    Math::Matrix2 uTop;
    uTop[0][0] = eCramer; uTop[1][0] = fCramer;
    uTop[0][1] = bCramer; uTop[1][1] = dCramer;


    Math::Matrix2 vTop;
    vTop[0][0] = aCramer; vTop[1][0] = cCramer;
    vTop[0][1] = eCramer; vTop[1][1] = fCramer;


    Math::Matrix2 botMat;
    botMat[0][0] = aCramer; botMat[1][0] = cCramer;
    botMat[0][1] = bCramer; botMat[1][1] = dCramer;

    float botDet = botMat.Determinate();
    u = uTop.Determinate() / botDet;
    v = vTop.Determinate() / botDet;
    w = 1.0f - u - v;

    if(u == Math::Clamp(u, -epsilon, 1.0f + epsilon))
    {
      if(v == Math::Clamp(v, -epsilon, 1.0f + epsilon))
      {
        if(w == Math::Clamp(w, -epsilon, 1.0f + epsilon))
        {
          return true;
        }
      }
    }

  }

  

  return false;
}

IntersectionType::Type PointPlane(const Vector3& point, const Vector4& plane, float epsilon)
{
  Math::Vector3 normal = Math::Vector3(plane.x, plane.y, plane.z);

  float distFromPlane = DistFromPlane(point, normal, plane.w);

  if(distFromPlane < -epsilon)
  {
    return IntersectionType::Outside;
  }

  if(distFromPlane > epsilon)
  {
    return IntersectionType::Inside;
  }

  return IntersectionType::Coplanar;

}

bool PointSphere(const Vector3& point, const Vector3& sphereCenter, float sphereRadius)
{
  return (sphereCenter - point).LengthSq() <= (sphereRadius * sphereRadius);
}

bool PointAabb(const Vector3& point, const Vector3& aabbMin, const Vector3& aabbMax)
{
  Math::Vector3 pointInside = point;
  pointInside.x = Math::Clamp(pointInside.x, aabbMin.x, aabbMax.x);
  pointInside.y = Math::Clamp(pointInside.y, aabbMin.y, aabbMax.y);
  pointInside.z = Math::Clamp(pointInside.z, aabbMin.z, aabbMax.z);

  return pointInside == point;
}

bool RayPlane(const Vector3& rayStart, const Vector3& rayDir,
              const Vector4& plane, float& t, float epsilon)
{
  ++Application::mStatistics.mRayPlaneTests;
  Math::Vector3 normal(plane.x, plane.y, plane.z);
  float dist = DistFromPlane(rayStart, normal, plane.w);
  float dirDotNorm = rayDir.Dot(normal);
  bool retVal = false;
  if(dist < 0.0f)
  {
    if(dirDotNorm > epsilon)
    {
      // it collides
      retVal = true;
    }
  }
  else if(dist > 0.0f)
  {
    if(dirDotNorm < -epsilon)
    {
      // it collides
      retVal = true;
    }
  }

  //protect against div by zero
  if(dirDotNorm > 0.0f)// if it's greater than zero, then our distance will be negative
  {
    t = -dist / dirDotNorm;
  }
  else if(dirDotNorm < 0.0f)//if it's less, our distance will be positive (but dot will be negative)
  {
    t = dist / -dirDotNorm;
  }
  return retVal;
}

bool RayTriangle(const Vector3& rayStart, const Vector3& rayDir,
                 const Vector3& triP0, const Vector3& triP1, const Vector3& triP2,
                 float& t, float triExpansionEpsilon)
{
  ++Application::mStatistics.mRayTriangleTests;
  Math::Vector3 normal = (triP1 - triP0).Cross(triP2 - triP0).Normalized();
  if(RayPlane(rayStart, rayDir, Math::Vector4(normal.x, normal.y, normal.z, normal.Dot(triP0)), t))
  {
    Math::Vector3 pointOnPlane = (rayDir * t) + rayStart;
    Math::Vector3 barycentric;
    return BarycentricCoordinates(pointOnPlane, triP0, triP1, triP2, barycentric.x, barycentric.y, barycentric.z, triExpansionEpsilon);
  }
  return false;
}

bool RaySphere(const Vector3& rayStart, const Vector3& rayDir,
               const Vector3& sphereCenter, float sphereRadius,
               float& t)
{
  ++Application::mStatistics.mRaySphereTests;
  //project sphere center on to line
  Math::Vector3 sphereVec = sphereCenter - rayStart;
  float floatingPointEpsilon = 0.0001f;
  float tClosestToRay = sphereVec.Dot(rayDir);
  if(tClosestToRay >= 0.0f)
  {
    Math::Vector3 pointClosestToSphere = rayStart + (rayDir * tClosestToRay);
    
    if((sphereCenter - pointClosestToSphere).LengthSq() <= (sphereRadius * sphereRadius))
    {
      //may be inside sphere, so we must calculate the length of ray that is inside the sphere and subtract
      //we can use cosine for this.
      //                                             adjacent                           hypotenuse
      float lenInSphere;
      if((sphereCenter - pointClosestToSphere).LengthSq() > floatingPointEpsilon)
      {
        lenInSphere = Math::ArcCos((sphereCenter - pointClosestToSphere).Length() / sphereRadius);
      }
      else
      {
        lenInSphere = sphereRadius;
      }
      //since raydir should be unit length, we can simply subtract this from our closest t
      //we max to make sure that we don't subtract past the start of the ray
      t = Math::Max(tClosestToRay - lenInSphere, 0.0f);
      return true;
    }
  }
  return false;
}

bool RayAabb(const Vector3& rayStart, const Vector3& rayDir,
             const Vector3& aabbMin, const Vector3& aabbMax, float& t)
{
  ++Application::mStatistics.mRayAabbTests;
  
  if(PointAabb(rayStart, aabbMin, aabbMax))
  {
    t = 0.0f;
    return true;
  }

  std::vector<float> tVals;
  std::vector<Plane> planes;
  if(rayDir.x)
  {
    planes.emplace_back(Plane(Math::Vector3(aabbMin.x / Math::Abs(aabbMin.x), 0.0f, 0.0f), aabbMin));
    planes.emplace_back(Plane(Math::Vector3(aabbMax.x / Math::Abs(aabbMax.x), 0.0f, 0.0f), aabbMax));
    tVals.emplace_back(FLT_MAX);
    tVals.emplace_back(FLT_MAX);
  }
  else
  {
    if(Math::Clamp(rayStart.x, aabbMin.x, aabbMax.x) != rayStart.x)
    {
      return false;
    }
  }
  if(rayDir.y)
  {
    planes.emplace_back(Plane(Math::Vector3(0.0f, aabbMin.y / Math::Abs(aabbMin.y), 0.0f), aabbMin));
    planes.emplace_back(Plane(Math::Vector3(0.0f, aabbMax.y / Math::Abs(aabbMax.y), 0.0f), aabbMax));
    tVals.emplace_back(FLT_MAX);
    tVals.emplace_back(FLT_MAX);
  }
  else
  {
    if(Math::Clamp(rayStart.y, aabbMin.y, aabbMax.y) != rayStart.y)
    {
      return false;
    }
  }
  if(rayDir.z)
  {
    planes.emplace_back(Plane(Math::Vector3(0.0f, 0.0f, aabbMin.z / Math::Abs(aabbMin.z)), aabbMin));
    planes.emplace_back(Plane(Math::Vector3(0.0f, 0.0f, aabbMax.z / Math::Abs(aabbMax.z)), aabbMax));
    tVals.emplace_back(FLT_MAX);
    tVals.emplace_back(FLT_MAX);
  }
  else
  {
    if(Math::Clamp(rayStart.z, aabbMin.z, aabbMax.z) != rayStart.z)
    {
      return false;
    }
  }

  for(int i = 0; i < planes.size(); i += 2)
  {
    RayPlane(rayStart, rayDir, planes[i].mData, tVals[i]);
    RayPlane(rayStart, rayDir, planes[i + 1].mData, tVals[i + 1]);

    //we dot with positive plane axis to get the desired component
    if(rayDir.Dot(Math::Vector3(planes[i + 1].mData.x, planes[i + 1].mData.y, planes[i + 1].mData.z)) < 0.0f)
    {
      std::swap(tVals[i], tVals[i + 1]);
    }
  }

  float tmin = -FLT_MAX;
  float tmax = FLT_MAX;


  for(int i = 0; i < tVals.size(); i += 2)
  {
    tmin = Math::Max(tmin, tVals[i]);
    tmax = Math::Min(tmax, tVals[i + 1]);
  }
  


  //tmin should be start of our collision
  if(tmin < tmax)
  {
    if(tmin > 0.0f)
    {
      t = tmin;
      return true;
    }
  }
  
  return false;
}

IntersectionType::Type PlaneTriangle(const Vector4& plane, 
                                     const Vector3& triP0, const Vector3& triP1, const Vector3& triP2,
                                     float epsilon)
{
  ++Application::mStatistics.mPlaneTriangleTests;
  /******Student:Assignment1******/
  Warn("Assignment1: Required function un-implemented");
  return IntersectionType::NotImplemented;
}

IntersectionType::Type PlaneSphere(const Vector4& plane,
                                   const Vector3& sphereCenter, float sphereRadius)
{
  ++Application::mStatistics.mPlaneSphereTests;
  
  float distFromPlane = DistFromPlane(sphereCenter, Math::Vector3(plane.x, plane.y, plane.z), plane.w);

  if(distFromPlane > sphereRadius)
  {
    return IntersectionType::Inside;
  }
  if(distFromPlane < -sphereRadius)
  {
    return IntersectionType::Outside;
  }
  return IntersectionType::Overlaps;
}

IntersectionType::Type PlaneAabb(const Vector4& plane,
                                 const Vector3& aabbMin, const Vector3& aabbMax)
{
  ++Application::mStatistics.mPlaneAabbTests;
  /******Student:Assignment1******/
  Warn("Assignment1: Required function un-implemented");
  return IntersectionType::NotImplemented;
}

IntersectionType::Type FrustumTriangle(const Vector4 planes[6],
                                       const Vector3& triP0, const Vector3& triP1, const Vector3& triP2,
                                       float epsilon)
{
  ++Application::mStatistics.mFrustumTriangleTests;
  /******Student:Assignment1******/
  Warn("Assignment1: Required function un-implemented");
  return IntersectionType::NotImplemented;
}

IntersectionType::Type FrustumSphere(const Vector4 planes[6],
                                     const Vector3& sphereCenter, float sphereRadius, size_t& lastAxis)
{
  ++Application::mStatistics.mFrustumSphereTests;
  /******Student:Assignment1******/
  Warn("Assignment1: Required function un-implemented");
  return IntersectionType::NotImplemented;
}

IntersectionType::Type FrustumAabb(const Vector4 planes[6],
                                   const Vector3& aabbMin, const Vector3& aabbMax, size_t& lastAxis)
{
  ++Application::mStatistics.mFrustumAabbTests;
  /******Student:Assignment1******/
  Warn("Assignment1: Required function un-implemented");
  return IntersectionType::NotImplemented;
}

bool SphereSphere(const Vector3& sphereCenter0, float sphereRadius0,
                  const Vector3& sphereCenter1, float sphereRadius1)
{
  ++Application::mStatistics.mSphereSphereTests;
  return (sphereCenter1 - sphereCenter0).LengthSq() < 
    ((sphereRadius0 + sphereRadius1)*(sphereRadius0 + sphereRadius1));
}

bool AabbAabb(const Vector3& aabbMin0, const Vector3& aabbMax0,
              const Vector3& aabbMin1, const Vector3& aabbMax1)
{
  ++Application::mStatistics.mAabbAabbTests;
  /******Student:Assignment1******/
  Warn("Assignment1: Required function un-implemented");
  return false;
}
