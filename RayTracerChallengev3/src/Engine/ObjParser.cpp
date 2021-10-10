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
		std::vector<Triangle*> triangles;

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
				std::vector<Triangle*> temp = processFace(words, vertices);
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
				// TODO
			}
			else if (words[0] == "vt")
			{
				//std::cout << "\n Processing vertex texture..." << "\t" << *iter;
				// TODO
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

	std::vector<Triangle*> ObjParser::fanTriangulation(const std::vector<Point4*>& vertices) const
	{
		std::vector<Triangle*> triangles{};

		for (int index = 1; index < vertices.size() - 1; index++)
		{
			Triangle* t = new Triangle(*vertices[0], *vertices[index], *vertices[index + 1]);
			triangles.push_back(t);
		}

		return triangles;
	}

	std::vector<Triangle*> ObjParser::processFace(const std::vector<std::string>& words, const std::vector<Point4*>& vertices) const
	{
		std::vector<Triangle*> triangles{};

		if (words.size() == 4)
		{
			// line in triangle format of "f 1 2 3"

			int index1 = processFaceVertexInfo(words[1])[0];
			int index2 = processFaceVertexInfo(words[2])[0];
			int index3 = processFaceVertexInfo(words[3])[0];
			Triangle* t = new Triangle(*vertices[index1], *vertices[index2], *vertices[index3]);
			triangles.push_back(t);			
		}
		else
		{
			// line in triangulate polygonal format of "f 1 2 3 4 5"

			// get verts in polygon
			std::vector<Point4*> verts{};
			for (int i = 1; i < words.size(); i++)
			{
				int index = processFaceVertexInfo(words[i])[0];
				verts.push_back(vertices[index]);
			}

			// perform fan triangulation on them and get back a vector of triangles
			std::vector<Triangle*> temp = fanTriangulation(verts);
			for (auto t : temp) triangles.push_back(t);
		}

		return triangles;
	}

	std::vector<int> ObjParser::processFaceVertexInfo(const std::string& vertexInfo) const
	{
		std::vector<int> indices{};
		
		if (vertexInfo.find('/') == std::string::npos)
		{
			// face definition is in format "f 1 2 3" so vertexInfo is simple the index of the vertex
			indices.push_back(std::stoi(vertexInfo) - 1);
		}
		else
		{
			// face definition is in format "f 1/1/1 2/2/2 3/3/3" so vertexInfo is vertexIndex/textureIndex/normalIndex
			
			// replace / with space
			std::string noSlash = vertexInfo;
			std::replace(noSlash.begin(), noSlash.end(), '/', ' ');
			
			std::vector<std::string> values = splitStringOnSpace(noSlash);
			indices.push_back(std::stoi(values[0]) - 1); // vertex index
			indices.push_back(std::stoi(values[1]) - 1); // texture index
			indices.push_back(std::stoi(values[2]) - 1); // normal index
		}
		
		return indices;
	}
}