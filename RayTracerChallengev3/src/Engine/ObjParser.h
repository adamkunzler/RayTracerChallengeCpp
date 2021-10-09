#pragma once

namespace RayTracer
{
	struct ObjParseResult
	{
		int numLinesIgnored;		
		Group* defaultGroup;

		ObjParseResult() : numLinesIgnored(0) {}
	};

	class ObjParser
	{			
	public:		
		ObjParser() {}

		ObjParseResult& parse(const std::string& filename) const;
		
		std::vector<std::string> splitStringOnSpace(std::string text) const;

		std::vector<Triangle*> fanTriangulation(const std::vector<Point4*>& vertices) const;

		std::vector<Triangle*> processFace(const std::vector<std::string>& words, const std::vector<Point4*>& vertices) const;
		
		std::vector<int> processFaceVertexInfo(const std::string& vertexInfo) const;
	};
}