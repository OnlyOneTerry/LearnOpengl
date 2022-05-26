#include "GraphicItemBase.h"


GraphicItemBase::GraphicItemBase(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color)
{
	shader_ = new Shader(vertexPath.c_str(), fragmentPath.c_str());
	shader_->use();
	shader_->setVec3("color", color);
}

GraphicItemBase::~GraphicItemBase()
{
	if (shader_)
		delete shader_;
	shader_ = nullptr;
}


void GraphicItemBase::setVertexData(std::vector<display_utils::TVertex>& vertexs)
{
	vertices_ = vertexs;
}

void GraphicItemBase::setVertexData(std::vector<float>& vertexs)
{
	float_vertices_ = vertexs;
}

void GraphicItemBase::setApha(float apha)
{
	apha_ = apha;
	if (shader_)
	{
		shader_->setFloat("apha", apha_);//TODO: 着色器添加apha值
	}
}

void GraphicItemBase::useShader()
{
	if (shader_)
	{
		shader_->use();
	}
}

glm::mat4 GraphicItemBase::getModelMatrix()
{
	return model_;
}

void GraphicItemBase::setModelmatrix(glm::mat4 model)
{
	model_ = model;
}

void GraphicItemBase::setLightPos(glm::vec3 lightpos)
{
	lightPos_ = lightpos;
}

void GraphicItemBase::setViewPos(glm::vec3 viewPos)
{
	viewPos_ = viewPos;
}

void GraphicItemBase::setLightColor(glm::vec3 lightColor)
{
	lightColor_ = lightColor;
}

glm::vec3 GraphicItemBase::getLightPos()
{
	return lightPos_;
}
glm::vec3 GraphicItemBase::getViewPos()
{
	return viewPos_;
}
glm::vec3 GraphicItemBase::getLightColor()
{
	return lightColor_;
}

void GraphicItemBase::setShaderMat4(std::string name, glm::mat4 value)
{
	if (shader_)
	{
		shader_->setMat4(name, value);
	}
}

void GraphicItemBase::setShaderVec3(std::string name, glm::vec3 value)
{
	if (shader_)
	{
		shader_->setVec3(name, value);
	}
}