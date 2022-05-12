#include "GraphicItemLine.h"

GraphicItemLine::GraphicItemLine(std::string vertexPath, std::string fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath, fragmentPath,color)
{

}

GraphicItemLine::~GraphicItemLine()
{

}

void GraphicItemLine::initVAOVBO()
{
	if (_vertices.size() < 1) return;
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	//绑定当前VAO
	glBindVertexArray(_VAO);
	//绑定VBO到当前VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	//GPU开辟空间并传入数据
	glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(float), &_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void GraphicItemLine::drawCall()
{
	//std::cout << "draw Line......" << _VAO << std::endl;
	_shader->use();
	glBindVertexArray(_VAO);
	glDrawArrays(GL_LINES, 0, 2);
}
