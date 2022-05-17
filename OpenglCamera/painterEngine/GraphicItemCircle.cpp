#include "GraphicItemCircle.h"

GraphicItemCircle::GraphicItemCircle(std::string vertexPath, std::string fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath, fragmentPath, color)
{

}

GraphicItemCircle::~GraphicItemCircle()
{

}

void GraphicItemCircle::initVAOVBO()
{
	buildCircleFaceVertices(vertices_);

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, float_vertices_.size() * sizeof(float), &float_vertices_[0], GL_STATIC_DRAW);

	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//���� ����
	//glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(TVertex),(void*)offsetof(TVertex, TVertex::Normal));
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PL::TVertex), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//����ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

std::vector<PL::TVertex> GraphicItemCircle::getUnitCircleVertices()
{
	const float PI = 3.1415926f;
	float sectorStep = 2 * PI / sector_count_;
	float sectorAngle = 0.0f;

	glm::vec3 position;
	glm::vec3 normal;
	PL::TVertex tVertex;

	std::vector<PL::TVertex> unitCircleVertices;
	for (int i = 0; i <= sector_count_; i++)
	{
		sectorAngle = i * sectorStep;
		position.x = pier_radius_ * cos(sectorAngle);
		position.y = 0.0f;
		position.z = pier_radius_ * sin(sectorAngle);

		glm::vec4 tempPos = glm::vec4(position,1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		//ʹ��glm::translate
		trans = glm::translate(trans, pier_origin_);
		//ʹ��glm::rotate �Ե����任
		trans = glm::rotate(trans, glm::radians(rotate_angle), pier_rotate_axis_);
		tempPos = trans * tempPos;

		position.x = tempPos.x;
		position.y = tempPos.y;
		position.z = tempPos.z;

		normal.x = cos(sectorAngle);
		normal.y = 0.0f;
		normal.z = sin(sectorAngle);

		tVertex.Position = position;
		tVertex.Normal = normal;
		unitCircleVertices.push_back(tVertex);
	}
	return unitCircleVertices;
}
void GraphicItemCircle::buildCircleFaceVertices(std::vector<PL::TVertex>& vertices)
{
	vertices_.clear();
	std::vector<PL::TVertex> unitVertices = getUnitCircleVertices();
	// ��ȡԲ�ܵ�����
	std::vector<PL::TVertex> vctTop;

	PL::TVertex tVertex;
	for (int i = 0; i < unitVertices.size(); ++i)
	{
		tVertex.Position = unitVertices[i].Position;
		tVertex.Normal = unitVertices[i].Normal;
		vctTop.push_back(tVertex);
	}

	//��������ε�ƽ�Բ��
	glm::vec3 position;
	for (int i = 0; i < vctTop.size() - 1; ++i)
	{
		glm::vec3 position(0.0f, 0.0f, 0.0f);
		glm::vec3 normal(0.0f, 1.0f, 0.0f);
		glm::vec4 tempPos1 = glm::vec4(position, 1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		//ʹ��glm::translate
		trans = glm::translate(trans, pier_origin_);
		tempPos1 = trans * tempPos1;
		position.x = tempPos1.x;
		position.y = tempPos1.y;
		position.z = tempPos1.z;

		tVertex.Position = position;
		tVertex.Normal = normal;
		vertices.push_back(tVertex);
		std::cout<<"1 -------" <<"x is : " << tVertex.Position.x << "y is : " << tVertex.Position.y << "z is: " << tVertex.Position.z << std::endl;
		tVertex.Position = vctTop[i].Position;
		vertices.push_back(tVertex);
		std::cout<< "2 -------" <<"x is : " << tVertex.Position.x << "y is : " << tVertex.Position.y << "z is: " << tVertex.Position.z << std::endl;
		tVertex.Position = vctTop[i + 1].Position;
		vertices.push_back(tVertex);
		std::cout<< "3 -------" <<"x is : " << tVertex.Position.x << "y is : " << tVertex.Position.y << "z is: " << tVertex.Position.z << std::endl;
		
	}
	float_vertices_.clear();
	for (int i = 0; i < vertices.size(); i++)
	{
		float_vertices_.push_back(vertices[i].Position.x);
		float_vertices_.push_back(vertices[i].Position.y);
		float_vertices_.push_back(vertices[i].Position.z);
		//float_vertices_.push_back(vertices[i].Normal.x);
		//float_vertices_.push_back(vertices[i].Normal.y);
		//float_vertices_.push_back(vertices[i].Normal.z);
	}

	std::cout << "size is -----------" << vertices.size() << std::endl;
}
void GraphicItemCircle::drawCall()
{
	//����shader
	shader_->use();
	//����Ҫ���õ�VAO
	glBindVertexArray(vao_);
	int Num = float_vertices_.size()/3;
	glDrawArrays(GL_TRIANGLES, 0, Num);
	//std::cout << "vao is ------" << vao_ << std::endl;
}

void GraphicItemCircle::setOrgin(glm::vec3 origin)
{
	pier_origin_ = origin;
}
