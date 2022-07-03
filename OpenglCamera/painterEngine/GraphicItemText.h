#pragma once
#include "GraphicItemBase.h"
#include <map>
#include <string>
class GraphicItemText:public GraphicItemBase
{
public:
	GraphicItemText(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~GraphicItemText();
	void initEnv();
	void renderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
	void initVAOVBO();
	void drawCall();
	void setText(std::string txt);
	void setOriginPos(float x, float y);
	void setScale(float scale);
	void setWidthandHeight(int width, int height);
private:
	//�����ı����
	std::map<GLchar, display_utils::Character> characters_;
	std::string text_="opengl";//Ҫ���ƶ��ı�
	float x_ = 0;
	float y_ = 0;//���Ƶ����
	float scale_ = 1;//���ű���
	glm::vec3 color_ = {0.5f,0.5f,0.5f};
	int scr_width_ = 800;
	int scr_height_ = 600;
};