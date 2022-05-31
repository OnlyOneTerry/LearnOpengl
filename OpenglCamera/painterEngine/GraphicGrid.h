#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class GraphicItemBase;

class GraphicGrid
{
public:
	GraphicGrid(float width,float height,unsigned int row, unsigned int col, std::string vsPath, std::string fsPath, glm::vec3 origin, glm::vec3 color);
	~GraphicGrid();
	void generateLine(glm::vec3 begin, glm::vec3 end,std::string vsPath,std::string fsPath,glm::vec3 color);
	std::vector<GraphicItemBase*>& getLineVec();
	void addLine(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
private:
	std::vector<GraphicItemBase*> line_vec_;
};

