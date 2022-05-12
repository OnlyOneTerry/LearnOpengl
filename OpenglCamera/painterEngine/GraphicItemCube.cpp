#include "GraphicItemCube.h"

GraphicItemCube::GraphicItemCube(std::string vertexPath, std::string fragmentPath)
	:GraphicItemBase(vertexPath, fragmentPath)
{

}

GraphicItemCube::~GraphicItemCube()
{

}

void GraphicItemCube::initVAOVBO()
{
	if (_vertices.size() < 1) return;
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	//绑定当前VAO
	glBindVertexArray(_VAO);
	//绑定VBO到当前VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	//GPU开辟空间并传入数据
	glBufferData(GL_ARRAY_BUFFER,_vertices.size()*sizeof(float), &_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
void GraphicItemCube::drawCall()
{
	//激活shader
	_shader->use();
	//激活要启用的VAO
	glBindVertexArray(_VAO);
	//drawCall
	int cubePointsNum = _vertices.size()/3;
	glDrawArrays(GL_TRIANGLES, 0, cubePointsNum);
	//std::cout << "draw Cube......" << cubePointsNum << std::endl;
}