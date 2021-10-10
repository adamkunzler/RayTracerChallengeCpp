#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstddef>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <thread>
#include <atomic>

#include "../src/Utils.h"

#include "../src/DataStructs/Color.h"
#include "../src/DataStructs/Vector4.h"
#include "../src/DataStructs/Point4.h"
#include "../src/DataStructs/Matrix4x4.h"
#include "../src/DataStructs/BoundingBox.h"

#include "../src/Patterns/IPattern.h"
#include "../src/Patterns/CheckerPattern.h"
#include "../src/Patterns/StripePattern.h"
#include "../src/Patterns/GradientPattern.h"
#include "../src/Patterns/RingPattern.h"

#include "../src/Geometry/PointLight.h"
#include "../src/Geometry/Intersection.h"
#include "../src/Geometry/Ray.h"
#include "../src/Geometry/Material.h"
#include "../src/Geometry/Computation.h"

#include "../src/Engine/SceneConfig.h"
#include "../src/Engine/Camera.h"
#include "../src/Engine/Canvas.h"
#include "../src/Engine/World.h"

#include "../src/Shapes/IShape.h"
#include "../src/Shapes/Group.h"
#include "../src/Shapes/Sphere.h"
#include "../src/Shapes/Cube.h"
#include "../src/Shapes/Cylinder.h"
#include "../src/Shapes/Plane.h"
#include "../src/Shapes/Triangle.h"

#include "../src/Engine/Engine.h"
#include "../src/Engine/Scene.h"
#include "../src/Engine/ObjParser.h"

#include "../src/tests/_testHarness.h"

#endif