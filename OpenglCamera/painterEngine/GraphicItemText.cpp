#include "GraphicItemText.h"
#include<ft2build.h>
#include FT_FREETYPE_H

GraphicItemText::GraphicItemText(std::string & vertexPath, std::string & fragmentPath, glm::vec3 color) :
	GraphicItemBase(vertexPath, fragmentPath, color)
{
	color_ = color;
}

GraphicItemText::~GraphicItemText()
{

}

void GraphicItemText::initEnv()
{
	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		//return -1;
	}

	// find path to font
	std::string font_name = std::string("D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/resources/fonts/Antonio-Bold.ttf");
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		//return -1;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		//return -1;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			display_utils::Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
			};
			characters_.insert(std::pair<char, display_utils::Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void GraphicItemText::initVAOVBO()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GraphicItemText::drawCall()
{
	shader_->use();
	glm::mat4  projection = glm::ortho(0.0f, static_cast<float>(scr_width_), 0.0f, static_cast<float>(scr_height_));
	shader_->setMat4("projection", projection);
	renderText(*shader_, text_, x_, y_,scale_, color_);
}

void GraphicItemText::setText(std::string txt)
{
	text_ = txt;
}

void GraphicItemText::setOriginPos(float x, float y)
{
	x_ = x;
	y_ = y;
}

void GraphicItemText::setScale(float scale)
{
	scale_ = scale;
}

void GraphicItemText::setWidthandHeight(int width, int height)
{
	scr_width_ = width;
	scr_height_ = height;
}

void GraphicItemText::renderText(Shader & shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
	shader.use();
	shader.setVec3("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao_);

	//iterate through all characters
	std::string::const_iterator c = text.begin();
	for (; c != text.end(); c++)
	{
		display_utils::Character ch = characters_[*c];

		float xpos = x + ch.Bearing.x*scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y)*scale;

		float w = ch.Size.x*scale;
		float h = ch.Size.y*scale;

		//update VBO for each character
		float verteices[6][4] =
		{
			{xpos,ypos + h,0.0,0.0f},
			{xpos,ypos,    0.0f,1.0f},
			{xpos + w,ypos, 1.0f,1.0f},

			{xpos,ypos + h,0.0f,0.f},
			{ xpos + w,ypos, 1.0f,1.0f},
			{xpos + w,ypos + h,1.0f,0.0f}
		};

		//render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		//update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verteices), verteices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6)*scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
