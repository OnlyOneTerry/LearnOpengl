#include "GraphicItemLine.h"

GraphicItemLine::GraphicItemLine(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath, fragmentPath,color)
{

}

GraphicItemLine::~GraphicItemLine()
{

}

void GraphicItemLine::initVAOVBO()
{
	if (float_vertices_.size() < 1) return;
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	//绑定当前VAO
	glBindVertexArray(vao_);
	//绑定VBO到当前VAO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	//GPU开辟空间并传入数据
	glBufferData(GL_ARRAY_BUFFER, float_vertices_.size()*sizeof(float), &float_vertices_[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void GraphicItemLine::drawCall()
{
	shader_->use();
	glBindVertexArray(vao_);
	int num = float_vertices_.size() / 3;
	glDrawArrays(GL_LINE_LOOP, 0, num);
	//std::cout << "vao is ------" << vao_ << std::endl;
}
