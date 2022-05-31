#pragma once

#include <learnopengl/shader.h>
#include <vector>
#include <string>
#include "../common/commonDef.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class GraphicItemBase
{
public:
	GraphicItemBase(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	virtual ~GraphicItemBase();
	void setVertexData(std::vector<display_utils::TVertex>& vertexs);
	void setVertexData(std::vector<float>& vertexs);
	void setApha(float apha);
	void setShaderMat4(std::string name, glm::mat4 value);
	void setShaderVec3(std::string name, glm::vec3 value);
	virtual void initVAOVBO() = 0;
	virtual void drawCall() = 0;
	virtual void useShader();
	glm::mat4 getModelMatrix();
	void setModelmatrix(glm::mat4 model);
	void setLightPos(glm::vec3 lightpos);
	void setViewPos(glm::vec3 viewPos);
	void setLightColor(glm::vec3 lightColor);
	glm::vec3 getLightPos();
	glm::vec3 getViewPos();
	glm::vec3 getLightColor();

	void setVisible(bool visible);
protected:
	// ≥ı ºªØVAO
    unsigned int vbo_, vao_,ebo_;
	Shader* shader_;
	std::vector<display_utils::TVertex> vertices_;
	std::vector<float> float_vertices_;
	std::vector<int>   indices_;
	float apha_ = 1.0f;
	glm::mat4 model_ = glm::mat4(1.0f);
	glm::vec3 lightPos_ = glm::vec3(5.0f,1.0f,0.0f);
	glm::vec3 viewPos_ = glm::vec3(0.0f,0.0f,3.0f);
	glm::vec3 lightColor_ = glm::vec3(1.0f,0.0f,0.0f);
	bool visible_ = true;
};

