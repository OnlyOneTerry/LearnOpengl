#include "GraphicItemCube.h"

GraphicItemCube::GraphicItemCube(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath, fragmentPath,color)
{

}

GraphicItemCube::~GraphicItemCube()
{

}

void GraphicItemCube::initVAOVBO()
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

	//绘制模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void GraphicItemCube::drawCall()
{
	//激活shader
	shader_->use();
	//激活要启用的VAO
	glBindVertexArray(vao_);
	//drawCall
	int cubePointsNum = float_vertices_.size()/3;
	glDrawArrays(GL_TRIANGLES, 0, cubePointsNum);
}