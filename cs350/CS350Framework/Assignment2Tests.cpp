#include "Application.hpp"
#include "Shapes.hpp"
#include "Geometry.hpp"
#include "Math/Utilities.hpp"
#include "DebugDraw.hpp"
#include "Components.hpp"
#include "SimpleNSquared.hpp"
#include "UnitTests.hpp"

void DebugDrawingPoints1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  gDebugDrawer->DrawPoint(Vector3(0, 0, 0));
  gDebugDrawer->DrawPoint(Vector3(1, 0, 0));
  gDebugDrawer->DrawPoint(Vector3(0, 1, 0));
  gDebugDrawer->DrawPoint(Vector3(0, 0, 1));
}

void DebugDrawingLines1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  gDebugDrawer->DrawLine(LineSegment(Vector3(0, 0, 0), Vector3(1, 0, 0)));
  gDebugDrawer->DrawLine(LineSegment(Vector3(0, 0, 0), Vector3(0, 1, 0)));
  gDebugDrawer->DrawLine(LineSegment(Vector3(0, 0, 0), Vector3(0, 0, 1)));
}

void DebugDrawingRays1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  gDebugDrawer->DrawRay(Ray(Vector3(0, 0, 0), Vector3(1, 0, 0)), 5.0f);
  gDebugDrawer->DrawRay(Ray(Vector3(0, 0, 0), Vector3(0, 1, 0)), 5.0f);
  gDebugDrawer->DrawRay(Ray(Vector3(0, 0, 0), Vector3(0, 0, 1)), 5.0f);
}

void DebugDrawingSpheres1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  gDebugDrawer->DrawSphere(Sphere(Vector3(0.577812f, 0.776177f, -0.602959f), 0.464431f));
  gDebugDrawer->DrawSphere(Sphere(Vector3(0.207284f, -6.23721f, -1.81981f), 4.92792f));
  gDebugDrawer->DrawSphere(Sphere(Vector3(-1.47537f, -3.06628f, 5.96103f), 4.30209f));
  gDebugDrawer->DrawSphere(Sphere(Vector3(0.429898f, 0.439505f, -3.27661f), 2.48084f));
  gDebugDrawer->DrawSphere(Sphere(Vector3(-4.36159f, -2.82456f, 3.94174f), 2.29526f));
}

void DebugDrawingAabbs1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  gDebugDrawer->DrawAabb(Aabb(Vector3(-0.403611f, -1.15883f, 0.148383f), Vector3(9.11458f, -1.08467f, 1.5852f)));
  gDebugDrawer->DrawAabb(Aabb(Vector3(-4.35473f, 3.87758f, -5.91895f), Vector3(-1.90989f, 5.3357f, 5.60585f)));
  gDebugDrawer->DrawAabb(Aabb(Vector3(0.964619f, -8.42168f, -2.07626f), Vector3(2.97204f, -1.10177f, 0.241842f)));
  gDebugDrawer->DrawAabb(Aabb(Vector3(-4.96121f, -0.145595f, -5.8373f), Vector3(-3.95404f, 0.285578f, -3.56056f)));
  gDebugDrawer->DrawAabb(Aabb(Vector3(2.04614f, 0.412525f, -0.525727f), Vector3(6.36345f, 5.07618f, 1.69215f)));
}

void DebugDrawingTriangles1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  gDebugDrawer->DrawTriangle(Triangle(Vector3(0, 0, 0), Vector3(1, 1, 0), Vector3(1, 1, 1)));
}

void DebugDrawingPlanes1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  Plane plane(Vector3(0.0665589f, -0.520518f, -0.851253f), Vector3(0.577812f, 0.776177f, -0.602959f));
  gDebugDrawer->DrawPlane(plane, 3, 4);
}

void DebugDrawingQuads1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  Vector3 p0 = Vector3(-2.18192f, -1.94761f, 0.846782f);
  Vector3 p1 = Vector3(-2.18192f, 3.30789f, -2.36682f);
  Vector3 p2 = Vector3(3.33754f, 3.49997f, -2.0527f);
  Vector3 p3 = Vector3(3.33754f, -1.75554f, 1.1609f);
  gDebugDrawer->DrawQuad(p0, p1, p2, p3);
}

void DebugDrawingFrustum1(const std::string& testName, int debuggingIndex, FILE* file = NULL)
{
  Frustum frustum;
  frustum.Set(Vector3(-2.0169f, -9.57391f, -1.3047f), Vector3(2.42922f, -9.57391f, -1.3047f), Vector3(2.42922f, -2.83268f, -1.3047f), Vector3(-2.0169f, -2.83268f, -1.3047f), Vector3(-0.94259f, -8.4996f, -2.31514f), Vector3(1.3549f, -8.4996f, -2.31514f), Vector3(1.3549f, -3.90699f, -2.31514f), Vector3(-0.94259f, -3.90699f, -2.31514f));
  gDebugDrawer->DrawFrustum(frustum);
}

void RegisterDebugDrawingPointsTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingPoints1, list);
}

void RegisterDebugDrawingLinesTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingLines1, list);
}

void RegisterDebugDrawingRaysTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingRays1, list);
}

void RegisterDebugDrawingSpheresTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingSpheres1, list);
}

void RegisterDebugDrawingAabbsTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingAabbs1, list);
}

void RegisterDebugDrawingTrianglesTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingTriangles1, list);
}

void RegisterDebugDrawingPlanesTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingPlanes1, list);
}

void RegisterDebugDrawingQuadsTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingQuads1, list);
}

void RegisterDebugDrawingFrustumTests(AssignmentUnitTestList& list)
{
  DeclareSimpleUnitTest(DebugDrawingFrustum1, list);
}

void InitializeAssignment2Tests()
{
  mTestFns.push_back(AssignmentUnitTestList());
  AssignmentUnitTestList& list = mTestFns[1];
  
  // Add Debug Drawing Tests
  RegisterDebugDrawingPointsTests(list);
  RegisterDebugDrawingLinesTests(list);
  RegisterDebugDrawingRaysTests(list);
  RegisterDebugDrawingSpheresTests(list);
  RegisterDebugDrawingAabbsTests(list);
  RegisterDebugDrawingTrianglesTests(list);
  RegisterDebugDrawingPlanesTests(list);
  RegisterDebugDrawingQuadsTests(list);
  RegisterDebugDrawingFrustumTests(list);
}
