#pragma once

namespace RayTracer
{
	struct ObjParseResult
	{
		int numLinesIgnored;		
		Group* defaultGroup;

		ObjParseResult() : numLinesIgnored(0) { defaultGroup = new Group(); }
	};

	struct FaceData
	{
		int* vertexIndex;
		int* textureVertexIndex;
		int* vertexNormalIndex;

		FaceData() 
		{
			vertexIndex = 0;
			textureVertexIndex = 0;
			vertexNormalIndex = 0;
		}
		/*~FaceData() 
		{ 
			delete vertexIndex; 
			delete textureVertexIndex; 
			delete vertexNormalIndex; 
		}*/
	};

	class ObjParser
	{			
	public:		
		ObjParser() {}

		ObjParseResult& parse(const std::string& filename) const;
		
		std::vector<std::string> splitStringOnSpace(std::string text) const;

		std::vector<IShape*> fanTriangulation(const std::vector<Point4*>& vertices, const std::vector<Point4*>& vertexNormals) const;

		std::vector<IShape*> processFace(const std::vector<std::string>& words, const std::vector<Point4*>& vertices, const std::vector<Point4*>& vertexNormals) const;
		
		FaceData processFaceData(const std::string& vertexInfo) const;
	};
}