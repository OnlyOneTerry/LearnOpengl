#include "GraphicGrid.h"
#include"GraphicItemLine.h"

GraphicGrid::GraphicGrid(float width, float height, unsigned int row, unsigned int col, std::string vsPath, std::string fsPath,glm::vec3 origin, glm::vec3 color)
{
	glm::vec3 p1 = { -width / 2.0,origin.y,-height / 2.0 };
	glm::vec3 p2 = { width / 2.0, origin.y,-height / 2.0 };
	glm::vec3 p3 = { width / 2.0, origin.y, height / 2.0 };
	glm::vec3 p4 = { -width / 2.0,origin.y, height / 2.0 };

	//生成x方向直线
	float deltaZ = height / row;
	std::cout << "deltaZ is :" << deltaZ << std::endl;
	//p1--------------------->p2
	for (int i = 0; i <= row; i++)
	{
		glm::vec3 pBegin = { p1.x,p1.y,p1.z + deltaZ*i };
		glm::vec3 pEnd   = { p2.x,p2.y,p2.z + deltaZ*i };
		std::cout << " pBegin : " << pBegin.x << " " << pBegin.y << " " << pBegin.z << std::endl;
		std::cout << " pEnd : " << pEnd.x << " " << pEnd.y << " " << pEnd.z << std::endl;
		//generateLine(pBegin, pEnd,vsPath,fsPath,color);
	}

	//生成z方向直线
	//p1---------------------->p4
	float deltaX = width / col;
	for (int i = 0; i <= col; i++)
	{
		glm::vec3 pBegin = { p1.x + deltaX * i,p1.y,p1.z };
		glm::vec3 pEnd   = { p4.x + deltaX * i,p4.y,p4.z };
		std::cout << " pBegin : " << pBegin.x << " " << pBegin.y << " " << pBegin.z << std::endl;
		std::cout << " pEnd : " << pEnd.x << " " << pEnd.y << " " << pEnd.z << std::endl;
		//generateLine(pBegin, pEnd, vsPath, fsPath, color);
	}

	std::cout << "deltaX is :" << deltaX << std::endl;
}

GraphicGrid::~GraphicGrid()
{
	for (int i = 0; i < line_vec_.size(); i++)
	{
		if (line_vec_[i])
		{
			delete line_vec_[i];
		}
	}
}

void GraphicGrid::generateLine(glm::vec3 begin, glm::vec3 end, std::string vsPath, std::string fsPath ,glm::vec3 color)
{
	std::vector<float> lineVertices;
	lineVertices.push_back(begin.x);
	lineVertices.push_back(begin.y);
	lineVertices.push_back(begin.z);
	lineVertices.push_back(end.x);
	lineVertices.push_back(end.y);
	lineVertices.push_back(end.z);

	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath, color);
	lineItem->setVertexData(lineVertices);
	lineItem->initVAOVBO();
	line_vec_.push_back(lineItem);
}

std::vector<GraphicItemBase*>& GraphicGrid::getLineVec()
{
	return line_vec_;
	// TODO: 在此处插入 return 语句
}

void GraphicGrid::addLine(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath, color);
	lineItem->setVertexData(vertexData);
	lineItem->initVAOVBO();
	line_vec_.push_back(lineItem);
}
