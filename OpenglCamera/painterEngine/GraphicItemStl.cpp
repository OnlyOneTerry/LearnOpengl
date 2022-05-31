#include "GraphicItemStl.h"

GraphicItemStl::GraphicItemStl(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color )
	:GraphicItemBase(vertexPath,fragmentPath,color)
{

}

GraphicItemStl::~GraphicItemStl()
{

}

void GraphicItemStl::setStlFilePath(std::string path)
{
	file_path_ = path;
}

void GraphicItemStl::initVAOVBO()
{
	urdf::STLDocument stlDoc;
	openBinary(file_path_, stlDoc);

	if (float_vertices_.size() < 1) return;

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	glBufferData(GL_ARRAY_BUFFER, float_vertices_.size() * sizeof(float), &float_vertices_[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//设置法线属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void GraphicItemStl::drawCall()
{
	if (!visible_) return;
	//激活shader
	shader_->use();
	//绘制模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//激活要启用的VAO
	glBindVertexArray(vao_);
	int Num = float_vertices_.size() / 3;
	glDrawArrays(GL_TRIANGLES, 0, Num);
}

bool GraphicItemStl::openBinary(const std::string &p_FileName, urdf::STLDocument &p_STLDocument)
{
	p_STLDocument.clear();
	FILE *fp;
	int numFacet;
	int error = fopen_s(&fp, p_FileName.c_str(), "rb");
	float normal[3];
	float point1[3];
	urdf::STLDocument::STLPoint stlPoint;
	urdf::STLDocument::STLFacet stlFacet;
	if (0 == error)//成功打开文件
	{
		fseek(fp, STL_LABEL_SIZE, SEEK_SET);//跳过开头
		fread(&numFacet, sizeof(int), 1, fp);//读取facet的数目
		for (int facetIndex = 0; facetIndex < numFacet; ++facetIndex)
		{
			unsigned short attr; //用来储存属性,实际上把这个值丢弃了
			fread(normal, sizeof(float), 3, fp);//读取facet的法向量
			stlFacet.m_Normal = normal;
			for (int i = 0; i < 3; ++i)
			{
				fread(point1, sizeof(float), 3, fp);//读取vertex
				stlFacet.m_PointList[i] = point1;
				stlPoint = point1;
				p_STLDocument.m_VertexList.push_back(stlPoint);

				float_vertices_.push_back(stlPoint.x);
				float_vertices_.push_back(stlPoint.y);
				float_vertices_.push_back(stlPoint.z);

				float_vertices_.push_back(stlFacet.m_Normal.x);
				float_vertices_.push_back(stlFacet.m_Normal.y);
				float_vertices_.push_back(stlFacet.m_Normal.z);
			}
			fread(&attr, sizeof(unsigned short), 1, fp);//读取属性
			p_STLDocument.m_FacetList.push_back(stlFacet);
		}
	}
	else {
		std::cout << "failed to open filed....." << std::endl;
	}
	fclose(fp);

	//std::cout << "point size is : " << p_STLDocument.m_VertexList.size() << std::endl;
	//std::cout << "face size is : " << p_STLDocument.m_FacetList.size() << std::endl;

	return true;
}
