#include "GraphicItemCube.h"

GraphicItemCube::GraphicItemCube(std::string vertexPath, std::string fragmentPath, glm::vec3 color)
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
	//�󶨵�ǰVAO
	glBindVertexArray(vao_);
	//��VBO����ǰVAO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	//GPU���ٿռ䲢��������
	glBufferData(GL_ARRAY_BUFFER, float_vertices_.size()*sizeof(float), &float_vertices_[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//����ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void GraphicItemCube::drawCall()
{
	//����shader
	shader_->use();
	//����Ҫ���õ�VAO
	glBindVertexArray(vao_);
	//drawCall
	int cubePointsNum = float_vertices_.size()/3;
	glDrawArrays(GL_TRIANGLES, 0, cubePointsNum);
}