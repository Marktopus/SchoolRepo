///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "SimpleNSquared.hpp"
#include "Math\Utilities.hpp"
#include "DebugDraw.hpp"
#include "Geometry.hpp"

//-----------------------------------------------------------------------------NSquaredSpatialPartition
NSquaredSpatialPartition::NSquaredSpatialPartition()
{
  mType = SpatialPartitionTypes::NSquared;
}

void NSquaredSpatialPartition::CreateProxy(Proxy& proxy, SpatialPartitionData& data)
{
  // Doing this lazily (and bad, but it's n-squared...).
  // Just store as the proxy what the client data is so we can look it up later.
  proxy.mProxy = data.mClientData;
  mData.push_back(data.mClientData);
}

void NSquaredSpatialPartition::UpdateProxy(Proxy& proxy, SpatialPartitionData& data)
{
  // Nothing to do here, update doesn't do anything
}

void NSquaredSpatialPartition::RemoveProxy(Proxy& proxy)
{
  // Find the proxy data and remove it
  for(size_t i = 0; i < mData.size(); ++i)
  {
    if(mData[i] == proxy.mProxy)
    {
      mData[i] = mData.back();
      mData.pop_back();
      break;
    }
  }
}

void NSquaredSpatialPartition::DebugDraw(int level, const Math::Matrix4& transform, const Vector4& color, int bitMask)
{
  // Nothing to debug draw
}

void NSquaredSpatialPartition::CastRay(const Ray& ray, CastResults& results)
{
  // Add everything
  for(size_t i = 0; i < mData.size(); ++i)
  {
    CastResult result;
    result.mClientData = mData[i];
    results.AddResult(result);
  }
}

void NSquaredSpatialPartition::CastFrustum(const Frustum& frustum, CastResults& results)
{
  // Add everything
  for(size_t i = 0; i < mData.size(); ++i)
  {
    CastResult result;
    result.mClientData = mData[i];
    results.AddResult(result);
  }
}

void NSquaredSpatialPartition::SelfQuery(QueryResults& results)
{
  // Add everything
  for(size_t i = 0; i < mData.size(); ++i)
  {
    for(size_t j = i + 1; j < mData.size(); ++j)
    {
      results.AddResult(QueryResult(mData[i], mData[j]));
    }
  }
}

void NSquaredSpatialPartition::GetDataFromProxy(const Proxy& proxy, SpatialPartitionData& data) const
{
  data.mClientData = proxy.mProxy;
}

void NSquaredSpatialPartition::FilloutData(std::vector<SpatialPartitionQueryData>& results) const
{
  for(size_t i = 0; i < mData.size(); ++i)
  {
    SpatialPartitionQueryData data;
    data.mClientData = mData[i];
    results.push_back(data);
  }
}

//-----------------------------------------------------------------------------BoundingSphereSpatialPartition
BoundingSphereSpatialPartition::BoundingSphereSpatialPartition()
{
  mType = SpatialPartitionTypes::NSquaredSphere;
}

void BoundingSphereSpatialPartition::CreateProxy(Proxy& proxy, SpatialPartitionData& data)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::UpdateProxy(Proxy& proxy, SpatialPartitionData& data)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::RemoveProxy(Proxy& proxy)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::DebugDraw(int level, const Math::Matrix4& transform, const Vector4& color, int bitMask)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::CastRay(const Ray& ray, CastResults& results)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::CastFrustum(const Frustum& frustum, CastResults& results)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::SelfQuery(QueryResults& results)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingSphereSpatialPartition::FilloutData(std::vector<SpatialPartitionQueryData>& results) const
{
  Warn("Assignment2: Required function un-implemented");
}

//-----------------------------------------------------------------------------BoundingAabbSpatialPartition
BoundingAabbSpatialPartition::BoundingAabbSpatialPartition()
{
  mType = SpatialPartitionTypes::NSquaredAabb;
}

void BoundingAabbSpatialPartition::CreateProxy(Proxy& proxy, SpatialPartitionData& data)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::UpdateProxy(Proxy& proxy, SpatialPartitionData& data)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::RemoveProxy(Proxy& proxy)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::DebugDraw(int level, const Math::Matrix4& transform, const Vector4& color, int bitMask)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::CastRay(const Ray& ray, CastResults& results)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::CastFrustum(const Frustum& frustum, CastResults& results)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::SelfQuery(QueryResults& results)
{
  Warn("Assignment2: Required function un-implemented");
}

void BoundingAabbSpatialPartition::FilloutData(std::vector<SpatialPartitionQueryData>& results) const
{
  Warn("Assignment2: Required function un-implemented");
}
