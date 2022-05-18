#include "GraphicItemSphere.h"
 float PI = 3.14159;
GraphicItemSphere::GraphicItemSphere(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath, fragmentPath, color)
{

}

GraphicItemSphere::~GraphicItemSphere()
{

}

void GraphicItemSphere::initVAOVBO()
{
	generateSphereVertices();
	generateSphereVerticesIndex();

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER,vbo_);
	glBufferData(GL_ARRAY_BUFFER, float_vertices_.size() * sizeof(float), &float_vertices_[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(int), &indices_[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void GraphicItemSphere::drawCall()
{
	shader_->use();
	glBindVertexArray(vao_);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, x_segements_*y_segements_ * 6, GL_UNSIGNED_INT, 0);
}

void GraphicItemSphere::generateSphereVertices()
{

	for (int y = 0; y <= y_segements_; y++)
	{
		for (int x = 0; x <= x_segements_; x++)
		{
			float xSegment = (float)x / (float)x_segements_;
			float ySegment = (float)y / (float)y_segements_;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			glm::vec4 tempPos;
			tempPos.x = xPos;
			tempPos.y = yPos;
			tempPos.z = zPos;
			tempPos.w = 1.0f;

			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, origin_);

			tempPos = trans * tempPos;

			float_vertices_.push_back(tempPos.x);
			float_vertices_.push_back(tempPos.y);
			float_vertices_.push_back(tempPos.z);

			//float_vertices_.push_back(xPos);
			//float_vertices_.push_back(yPos);
			//float_vertices_.push_back(zPos);
			//std::cout << " x is : " << xPos << " y is :" << yPos << " z is :" << zPos << std::endl;
		}
	}
}

void GraphicItemSphere::generateSphereVerticesIndex()
{
	//生成球的Indices
	for (int i = 0; i < y_segements_; i++)
	{
		for (int j = 0; j < x_segements_; j++)
		{
			indices_.push_back(i * (x_segements_ + 1) + j);
			indices_.push_back((i + 1) * (x_segements_ + 1) + j);
			indices_.push_back((i + 1) * (x_segements_ + 1) + j + 1);
			indices_.push_back(i* (x_segements_ + 1) + j);
			indices_.push_back((i + 1) * (x_segements_ + 1) + j + 1);
			indices_.push_back(i * (x_segements_ + 1) + j + 1);
		}
	}
}

void GraphicItemSphere::setOrigin(glm::vec3 origin)
{
	origin_ = origin;
}
