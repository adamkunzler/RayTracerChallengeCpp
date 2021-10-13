#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	ObjParseResult& ObjParser::parse(const std::string& filename) const
	{		
		ObjParseResult* result = new ObjParseResult();
		result->defaultGroup = new Group();
		
		std::vector<Point4*> vertices;
		std::vector<Point4*> textureCoords;
		std::vector<Point4*> vertexNormals;
		std::vector<IShape*> triangles; // Triangle or SmoothTriangle

		//
		// read all the lines from the obj file
		//
		std::vector<std::string> lines{};
		std::ifstream file(filename);
		std::string line;
		while (std::getline(file, line))
		{
			lines.push_back(line);			
		}

		//
		// process each line
		//
		Group* g = 0;
		for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); iter++)
		{
			// split line into words
			std::vector<std::string> words = splitStringOnSpace(*iter);
			if (words.size() == 0) continue;

			if (words[0] == "v")
			{
				//std::cout << "\n Processing vertex..." << "\t" << *iter;
				double x = std::stod(words[1]);
				double y = std::stod(words[2]);
				double z = std::stod(words[3]);
				vertices.push_back(new Point4(x, y, z));
			}
			else if (words[0] == "f")
			{				
				//std::cout << "\n Processing face..." << "\t" << *iter;
				std::vector<IShape*> temp = processFace(words, vertices, vertexNormals);
				if (g == 0)
				{
					for (auto t : temp) result->defaultGroup->addChild(t);
				}
				else
				{
					for (auto t : temp) g->addChild(t);
				}
			}
			else if (words[0] == "g")
			{
				//std::cout << "\n Processing group..." << "\t" << *iter;
				g = new Group();
				result->defaultGroup->addChild(g);
			}
			else if (words[0] == "vn")
			{
				//std::cout << "\n Processing vertex normal..." << "\t" << *iter;
				double x = std::stod(words[1]);
				double y = std::stod(words[2]);
				double z = std::stod(words[3]);
				vertexNormals.push_back(new Point4(x, y, z));
			}
			else if (words[0] == "vt")
			{
				//std::cout << "\n Processing texture coords..." << "\t" << *iter;
				double x = std::stod(words[1]);
				double y = std::stod(words[2]);
				double z = std::stod(words[3]);
				textureCoords.push_back(new Point4(x, y, z));
			}
			else 
			{
				//std::cout << "\n Ignoring line..." << "\t" << *iter;
				result->numLinesIgnored++;
			}
			
			/*for (const auto& str : words)
			{
				std::cout << str << std::endl;
			}*/
		}
				
		for (auto p : vertices) delete p;		
		vertices.clear();

		for (auto p : triangles) delete p;		
		triangles.clear();

		return *result;
	}

	std::vector<std::string> ObjParser::splitStringOnSpace(std::string text) const
	{
		std::vector<std::string> words{};

		std::istringstream ss(text);
		std::string word;
		while (ss >> word)
		{
			words.push_back(word);
		}

		return words;
	}

	std::vector<IShape*> ObjParser::fanTriangulation(const std::vector<Point4*>& vertices, const std::vector<Point4*>& vertexNormals) const
	{
		std::vector<IShape*> triangles{};

		bool hasVertexNormals = vertices.size() == vertexNormals.size();
		for (int index = 1; index < vertices.size() - 1; index++)
		{
			if (hasVertexNormals && allowSmoothTriangles)
			{
				SmoothTriangle* t = new SmoothTriangle(
					*vertices[0], *vertices[index], *vertices[index + 1],
					*vertexNormals[0], *vertexNormals[index], *vertexNormals[index + 1]
				);
				triangles.push_back(t);
			}
			else
			{
				Triangle* t = new Triangle(*vertices[0], *vertices[index], *vertices[index + 1]);
				triangles.push_back(t);
			}			
		}

		return triangles;
	}

	std::vector<IShape*> ObjParser::processFace(
		const std::vector<std::string>& words, 
		const std::vector<Point4*>& vertices,
		const std::vector<Point4*>& vertexNormals) const
	{
		std::vector<IShape*> triangles{};

		if (words.size() == 4)
		{
			// line in triangle format of "f 1 2 3"

			FaceData f1 = processFaceData(words[1]);
			FaceData f2 = processFaceData(words[2]);
			FaceData f3 = processFaceData(words[3]);

			int index1 = *f1.vertexIndex;
			int index2 = *f2.vertexIndex;
			int index3 = *f3.vertexIndex;

			if (*processFaceData(words[1]).vertexNormalIndex == 0 || !allowSmoothTriangles)
			{
				Triangle* t = new Triangle(*vertices[index1], *vertices[index2], *vertices[index3]);
				triangles.push_back(t);
			}
			else
			{
				int n1 = *processFaceData(words[1]).vertexNormalIndex;
				int n2 = *processFaceData(words[2]).vertexNormalIndex;
				int n3 = *processFaceData(words[3]).vertexNormalIndex;

				SmoothTriangle* t = new SmoothTriangle(
					*vertices[index1], *vertices[index2], *vertices[index3], 
					*vertexNormals[n1], *vertexNormals[n2], *vertexNormals[n3]
				);
				triangles.push_back(t);
			}
			
		}
		else
		{
			// line in triangulate polygonal format of "f 1 2 3 4 5"

			// get verts in polygon
			std::vector<Point4*> verts{};
			std::vector<Point4*> vertNorms{};
			for (int i = 1; i < words.size(); i++)
			{
				FaceData f = processFaceData(words[i]);
				verts.push_back(vertices[*f.vertexIndex]);

				if (*f.vertexNormalIndex != 0)
				{
					vertNorms.push_back(vertexNormals[*f.vertexNormalIndex]);
				}
			}

			// perform fan triangulation on them and get back a vector of triangles
			std::vector<IShape*> temp = fanTriangulation(verts, vertNorms);
			for (auto t : temp) triangles.push_back(t);
		}

		return triangles;
	}

	FaceData ObjParser::processFaceData(const std::string& vertexInfo) const
	{				
		// vertexInfo is the "1/1/1" in "f 1/1/1 2/2/2 3/3/3" or "1" in "f 1 2 3"
		FaceData data;
		
		if (vertexInfo.find('/') == std::string::npos)
		{
			// face definition is in format "f 1 2 3" so vertexInfo is simple the index of the vertex
			data.vertexIndex = new int(std::stoi(vertexInfo) - 1);
		}
		else if (vertexInfo.find("//") == std::string::npos)
		{
			// face definition is in format "f 1/1/1 2/2/2 3/3/3" so vertexInfo is vertexIndex/textureIndex/normalIndex

			// replace / with space
			std::string noSlash = vertexInfo;
			std::replace(noSlash.begin(), noSlash.end(), '/', ' ');

			std::vector<std::string> values = splitStringOnSpace(noSlash);
			data.vertexIndex = new int(std::stoi(values[0]) - 1);
			data.textureVertexIndex = new int(std::stoi(values[1]) - 1); 
			data.vertexNormalIndex = new int(std::stoi(values[2]) - 1); 
		}
		else
		{
			// face definition is in format "f 1//1 2//2 3//3" so vertexInfo is vertextIndex//normalIndex
			
			// replace / with space
			std::string noSlash = vertexInfo;
			std::replace(noSlash.begin(), noSlash.end(), '/', ' ');

			std::vector<std::string> values = splitStringOnSpace(noSlash);
			data.vertexIndex = new int(std::stoi(values[0]) - 1);
			data.vertexNormalIndex = new int(std::stoi(values[1]) - 1);
		}
		
		return data;
	}
}