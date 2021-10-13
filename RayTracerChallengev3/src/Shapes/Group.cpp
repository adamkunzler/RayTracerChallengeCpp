#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{

	Vector4 Group::localNormalAt(const Point4& localPoint, const Intersection& i) const
	{
		// groups don't have normals and this should never be called
		throw;
	}

	void Group::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{		
		if (!bounds.intersectBy(localRay)) return;
		
		for (std::vector<IShape*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
		{
			(*iter)->intersectBy(localRay, intersections);
		}		
	}

	void Group::addChild(IShape* shape)
	{
		shape->parent = this;
		children.push_back(shape);

		bounds = localBounds();
	}

	// TODO cache this
	BoundingBox Group::localBounds() const
	{
		BoundingBox bb;

		for (std::vector<IShape*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
		{
			BoundingBox childBox = (*iter)->parentSpaceBoundsOf();
			bb.addBoundingBox(childBox);
		}

		return BoundingBox(bb.min, bb.max);
	}
	void Group::partitionChildren(std::vector<IShape*>& left, std::vector<IShape*>& right)
	{
		BoundingBox bbLeft;
		BoundingBox bbRight;
		localBounds().splitBounds(bbLeft, bbRight);

		// divy up children into the bounding boxes they fit in		
		std::vector<IShape*> stayInGroup;
		for (std::vector<IShape*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
		{
			BoundingBox childBounds = (*iter)->parentSpaceBoundsOf();
			if (bbLeft.containsBoundingBox(childBounds))
			{
				// fits in the left bounding box
				left.push_back(*iter);
			}
			else if (bbRight.containsBoundingBox(childBounds))
			{
				// fits in the right bounding box
				right.push_back(*iter);
			}
			else
			{
				// didn't fit in left or right...will stay in group
				stayInGroup.push_back(*iter);
			}
		}

		// clear children and re-add stayInGroup as children
		children.clear();
		for (auto iter = stayInGroup.begin(); iter != stayInGroup.end(); iter++)
		{
			children.push_back(*iter);
		}
	}

	void Group::makeSubGroup(std::vector<IShape*> shapes)
	{
		Group* g = new Group();
		std::copy(shapes.begin(), shapes.end(), std::back_inserter(g->children));
		addChild(g);
	}

	void Group::divide(const int& threshold)
	{
		if (threshold <= children.size())
		{
			std::vector<IShape*> leftChildren{};
			std::vector<IShape*> rightChildren{};
			partitionChildren(leftChildren, rightChildren);

			if (leftChildren.size() > 0) makeSubGroup(leftChildren);
			if (rightChildren.size() > 0) makeSubGroup(rightChildren);
		}

		
		for (auto iter = children.begin(); iter != children.end(); iter++)
		{
			(*iter)->divide(threshold);
		}
	}

	void Group::setMaterial(const Material& material)
	{
		for (auto iter = children.begin(); iter != children.end(); iter++)
		{
			if (Group* g = dynamic_cast<Group*>(*iter))
			{
				g->setMaterial(material);
			}
			else
			{
				(*iter)->material = material;
			}
		}
	}
}