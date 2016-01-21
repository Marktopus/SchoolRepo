///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "DebugDraw.hpp"

#include "Application.hpp"
#include "Main/Support.hpp"
#include "Math/MathFunctions.hpp"

#define ShowDebugDrawWarnings true

DebugDrawer* gDebugDrawer = new DebugDrawer();

//-----------------------------------------------------------------------------DebugShape
DebugShape::DebugShape()
{
  mColor = Vector4(.6f);
  mMask = (unsigned int)-1;
  mTimer = 0;
  mOnTop = false;
  mTransform.SetIdentity();
}

DebugShape& DebugShape::Color(const Vector4& color)
{
  mColor = color;
  return *this;
}

DebugShape& DebugShape::OnTop(bool state)
{
  mOnTop = state;
  return *this;
}

DebugShape& DebugShape::Time(float time)
{
  mTimer = time;
  return *this;
}

DebugShape& DebugShape::SetMaskBit(int bitIndex)
{
  mMask = 1 << bitIndex;
  return *this;
}

DebugShape& DebugShape::SetTransform(const Matrix4& transform)
{
  mTransform = transform;
  return *this;
}

//-----------------------------------------------------------------------------DebugDrawer
DebugDrawer::DebugDrawer()
{
  mActiveMask = (unsigned int)-1;
  mApplication = NULL;
}

void DebugDrawer::Update(float dt)
{
  std::vector<DebugShape> newShapes;
  for(size_t i = 0; i < mShapes.size(); ++i)
  {
    DebugShape& shape = mShapes[i];
    shape.mTimer -= dt;

    // If the shape still has time left then add it to the list of shapes to keep drawing,
    // anything that has a timer that ran out will not be in the new list
    if(shape.mTimer >= 0)
      newShapes.push_back(shape);
  }

  mShapes.swap(newShapes);
}

void DebugDrawer::Draw()
{
  for(size_t i = 0; i < mShapes.size(); ++i)
  {
    DebugShape& shape = mShapes[i];

    // If the shape doesn't have one of the active mask bits set then don't draw it
    if((shape.mMask & mActiveMask) == 0)
      continue;
    
    // If this shape always draws on top then disable depth testing
    if(shape.mOnTop)
      glDisable(GL_DEPTH_TEST);


    // Decompose the matrix to set the gl transform (too lazy to properly transform the matrix between formats)
    float radians;
    Vector3 scale, translation, axis;
    Matrix3 rotationMat;
    shape.mTransform.Decompose(&scale, &rotationMat, &translation);
    Math::ToAxisAngle(Math::ToQuaternion(rotationMat), &axis, &radians);
    glPushMatrix();
    // Set the transform
    glTranslatef(translation.x, translation.y, translation.z);
    glRotatef(Math::RadToDeg(radians), axis.x, axis.y, axis.z);
    glScalef(scale.x, scale.y, scale.z);

    glBegin(GL_LINES);
    glColor3fv(shape.mColor.array);

    // Draw all of the line segments of this shape
    for(size_t j = 0; j < shape.mSegments.size(); ++j)
    {
      LineSegment& segment = shape.mSegments[j];

      glVertex3fv(segment.mStart.array);
      glVertex3fv(segment.mEnd.array);
    }

    glEnd();
    glPopMatrix();

    // Make sure to re-enable depth testing
    if(shape.mOnTop)
      glEnable(GL_DEPTH_TEST);
  }
}

DebugShape& DebugDrawer::GetNewShape()
{
  mShapes.push_back(DebugShape());
  return mShapes.back();
}

//helpers
std::vector<LineSegment> makeCircle(Math::Vec3Param center, Math::Vector3 forward, float radius, unsigned sides = 40)
{
  Math::Vector3 right;
  Math::Vector3 up = Math::Vector3(0.0f, 1.0f, 0.0f);
  Math::GenerateOrthonormalBasis(forward, &up, &right);

  std::vector<Math::Vector3> points;
  Math::Vector3 toAdd;
  

  float angle = Math::cTwoPi / float(sides);
  float it = 0.0f;
  
  while(it < Math::cTwoPi)
  {
    points.push_back(center + (radius * (Math::Vector3(up)*Math::Cos(it) + Math::Vector3(right)*Math::Sin(it))));
    it += angle;
  }

  std::vector<LineSegment> result;

  for(it = 1; it < points.size(); ++it)
  {
    result.push_back(LineSegment(points[it - 1], points[it]));
  }
  result.push_back(LineSegment(points[it - 1], points[0]));

  return result;
  
}


DebugShape& DebugDrawer::DrawPoint(const Vector3& point)
{
  return DrawSphere(Sphere(point, 0.1f));
}

DebugShape& DebugDrawer::DrawLine(const LineSegment& line)
{
  DebugShape& shape = GetNewShape();
  shape.mSegments.push_back(line);
  
  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

std::vector<LineSegment> makeRay(const Ray& ray, float t)
{
  std::vector<LineSegment> result;
  Math::Vector3 endPoint = ray.mStart + (ray.mDirection * t);
  const float goldenRatio = 1.61803398875f;
  
  Math::Vector3 right;
  Math::Vector3 up;
  Math::GenerateOrthonormalBasis(ray.mDirection, &up, &right);

  Math::Vector3 circleCenter = endPoint - ray.mDirection * goldenRatio * goldenRatio * 0.2f;
  float radius = 0.5f * goldenRatio * 0.2f;


  result = makeCircle(circleCenter, ray.mDirection, radius);

  //connecting segments

  result.push_back(LineSegment(circleCenter + right * radius, endPoint));
  result.push_back(LineSegment(circleCenter - right * radius, endPoint));
  result.push_back(LineSegment(circleCenter + up * radius, endPoint));
  result.push_back(LineSegment(circleCenter - up * radius, endPoint));

  result.push_back(LineSegment(ray.mStart, endPoint));

  return result;
}

DebugShape& DebugDrawer::DrawRay(const Ray& ray, float t)
{
  DebugShape& shape = GetNewShape();
  shape.mSegments = makeRay(ray, t);

  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

DebugShape& DebugDrawer::DrawSphere(const Sphere& sphere)
{
  // To access the camera's position for the horizon disc calculation use mApplication->mCamera.mTranslation
  DebugShape& shape = GetNewShape();
  int it;

  std::vector<LineSegment> segments[4];

  segments[0] = makeCircle(sphere.mCenter, Math::Vector3(1.0f, 0.0f, 0.0f), sphere.mRadius);

  
  segments[1] = makeCircle(sphere.mCenter, Math::Vector3(0.0f, 1.0f, 0.0f), sphere.mRadius);


  segments[2] = makeCircle(sphere.mCenter, Math::Vector3(0.0f, 0.0f, 1.0f), sphere.mRadius);


  //horizon circle
  Math::Vector3 dVec = sphere.mCenter - mApplication->mCamera.mTranslation;
  Math::Vector3 dVecNorm = dVec.Normalized();
  float radSquared = sphere.mRadius * sphere.mRadius;
  float lLen = Math::Sqrt(dVec.LengthSq() - radSquared);
  float rPrime = (sphere.mRadius * lLen) / dVec.Length();
  float z = radSquared - (rPrime * rPrime);
  Math::Vector3 newCenter = mApplication->mCamera.mTranslation + (dVec - (dVecNorm * z));
  
  segments[3] = makeCircle(newCenter, dVecNorm, rPrime);

  for(int i = 0; i < 4; ++i)
  {
    shape.mSegments.insert(shape.mSegments.end(), segments[i].begin(), segments[i].end());
  }

  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

DebugShape& DebugDrawer::DrawAabb(const Aabb& aabb)
{
  DebugShape& shape = GetNewShape();
  Math::Vector3 min = aabb.GetMin();
  Math::Vector3 max = aabb.GetMax();
  //make the other 4 points
  Math::Vector3 minPlusX(max.x, min.y, min.z);
  Math::Vector3 minPlusY(min.x, max.y, min.z);
  Math::Vector3 minPlusZ(min.x, min.y, max.z);

  Math::Vector3 maxMinusX(min.x, max.y, max.z);
  Math::Vector3 maxMinusY(max.x, min.y, max.z);
  Math::Vector3 maxMinusZ(max.x, max.y, min.z);



  shape.mSegments.push_back(LineSegment(min, minPlusX));
  shape.mSegments.push_back(LineSegment(min, minPlusY));
  shape.mSegments.push_back(LineSegment(min, minPlusZ));
  
  shape.mSegments.push_back(LineSegment(max, maxMinusX));
  shape.mSegments.push_back(LineSegment(max, maxMinusY));
  shape.mSegments.push_back(LineSegment(max, maxMinusZ));

  shape.mSegments.push_back(LineSegment(maxMinusX, minPlusY));
  shape.mSegments.push_back(LineSegment(maxMinusZ, minPlusY));
  shape.mSegments.push_back(LineSegment(minPlusX, maxMinusY));
  shape.mSegments.push_back(LineSegment(minPlusZ, maxMinusY));

  shape.mSegments.push_back(LineSegment(maxMinusX, minPlusZ));
  shape.mSegments.push_back(LineSegment(maxMinusZ, minPlusX));


  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

DebugShape& DebugDrawer::DrawTriangle(const Triangle& triangle)
{
  DebugShape& shape = GetNewShape();

  shape.mSegments.push_back(LineSegment(triangle.mPoints[0], triangle.mPoints[1]));
  shape.mSegments.push_back(LineSegment(triangle.mPoints[1], triangle.mPoints[2]));
  shape.mSegments.push_back(LineSegment(triangle.mPoints[2], triangle.mPoints[0]));
  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

DebugShape& DebugDrawer::DrawPlane(const Plane& plane, float sizeX, float sizeY)
{
  DebugShape& shape = GetNewShape();
  Math::Vector3 right;
  Math::Vector3 up;
  Math::GenerateOrthonormalBasis(plane.GetNormal(), &up, &right);
  
  Math::Vector3 center = plane.GetNormal() * plane.mData.w;

  shape.mSegments = makeRay(Ray(center, plane.GetNormal()), (sizeX + sizeY)/2.0f);

  shape.mSegments.push_back(LineSegment(center - (up * (sizeY / 2.0f)), center - (right * (sizeX / 2.0f))));
  shape.mSegments.push_back(LineSegment(center - (up * (sizeY / 2.0f)), center + (right * (sizeX / 2.0f))));
  shape.mSegments.push_back(LineSegment(center + (up * (sizeY / 2.0f)), center - (right * (sizeX / 2.0f))));
  shape.mSegments.push_back(LineSegment(center + (up * (sizeY / 2.0f)), center + (right * (sizeX / 2.0f))));

  
  

  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

DebugShape& DebugDrawer::DrawQuad(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3)
{
  DebugShape& shape = GetNewShape();

  shape.mSegments.push_back(LineSegment(p0, p1));
  shape.mSegments.push_back(LineSegment(p1, p2));
  shape.mSegments.push_back(LineSegment(p2, p3));
  shape.mSegments.push_back(LineSegment(p3, p0));
  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}

enum PlaneIndex
{
  LeftBottomNear,
  RightBottomNear,
  RightTopNear,
  LeftTopNear,
  LeftBottomFar,
  RightBottomFar,
  RightTopFar,
  LeftTopFar

};

DebugShape& DebugDrawer::DrawFrustum(const Frustum& frustum)
{
  DebugShape& shape = GetNewShape();
  
  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftBottomNear], frustum.mPoints[RightBottomNear]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftTopNear], frustum.mPoints[RightTopNear]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftBottomFar], frustum.mPoints[RightBottomFar]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftTopFar], frustum.mPoints[RightTopFar]));

  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftBottomNear], frustum.mPoints[LeftBottomFar]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[RightBottomNear], frustum.mPoints[RightBottomFar]));

  shape.mSegments.push_back(LineSegment(frustum.mPoints[RightTopNear], frustum.mPoints[RightTopFar]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftTopNear], frustum.mPoints[LeftTopFar]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftBottomNear], frustum.mPoints[LeftTopNear]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[RightBottomNear], frustum.mPoints[RightTopNear]));

  shape.mSegments.push_back(LineSegment(frustum.mPoints[LeftBottomFar], frustum.mPoints[LeftTopFar]));
  shape.mSegments.push_back(LineSegment(frustum.mPoints[RightBottomFar], frustum.mPoints[RightTopFar]));
  
  ///******Student:Assignment2******/
  //WarnIf(ShowDebugDrawWarnings, "Assignment2: Required function un-implemented");
  return shape;
}
