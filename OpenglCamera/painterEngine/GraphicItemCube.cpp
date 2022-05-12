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
	//�󶨵�ǰVAO
	glBindVertexArray(_VAO);
	//��VBO����ǰVAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	//GPU���ٿռ䲢��������
	glBufferData(GL_ARRAY_BUFFER,_vertices.size()*sizeof(float), &_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
void GraphicItemCube::drawCall()
{
	//����shader
	_shader->use();
	//����Ҫ���õ�VAO
	glBindVertexArray(_VAO);
	//drawCall
	int cubePointsNum = _vertices.size()/3;
	glDrawArrays(GL_TRIANGLES, 0, cubePointsNum);
	//std::cout << "draw Cube......" << cubePointsNum << std::endl;
}