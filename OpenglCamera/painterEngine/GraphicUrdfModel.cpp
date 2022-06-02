#include "GraphicUrdfModel.h"
#include "GraphicItemStl.h"
#include <iostream>
#include <string>
#include <fstream>



GraphicUrdfModel::GraphicUrdfModel(display_utils::ModelType mType)
	:GraphicModel(mType)
{

}


GraphicUrdfModel::~GraphicUrdfModel()
{

}

void GraphicUrdfModel::loadModel(std::string filePath, std::string vsPath, std::string fsPath)
{
	char* path = (char*)filePath.c_str();
	std::string xmlstr =  readFileIntoString(path);

	UrdfParser::getInstance().parseUrdf(xmlstr,model_);

	for (int i=0; i < model_.link_array.size(); i++)
	{
		//std::cout << "link name is -----------" << model_.link_array[i].name << std::endl;

#if 0
		std::vector<urdf::Collision> collision_array = model_.link_array[i].collision_array;
		for (int c = 0; c < collision_array.size(); c++)
		{
			    std::string colorStr = collision_array[c].material.color;
			    glm::vec3 color = { 1.0f,1.0f,1.0f };
			    float alpha = 1.0f;
			    getColorAndAphaFromString(colorStr, color, alpha);
			    
			    GraphicItemStl* stlItem = new GraphicItemStl(vsPath, fsPath, color);
			    glm::mat4 model = glm::mat4(1.0f);
			    model = glm::translate(model, glm::vec3(-5.0f+1.0f*i, 3.0f, 0.0f));
			    stlItem->setLightColor(glm::vec3(1.0f, 0.1f, 0.0f));
			    stlItem->setLightPos(glm::vec3(10.0f, 4.0f, 0.0f));
			    stlItem->setModelmatrix(model);
			    std::string replaceStr = "package://";
			    
			    
			    int length = collision_array[c].geometry.mesh.filename.length();
			    std::string filePath = collision_array[c].geometry.mesh.filename.substr(replaceStr.size(),length);
			    std::string resultPath = package_dir_ + filePath;
			    stlItem->setStlFilePath(resultPath);
			    stlItem->initVAOVBO();
			    stl_vec_.push_back(stlItem);
			    stl_name_map_.insert(make_pair(stlItem,model_.link_array[i].name));
			
		}
#endif
		std::vector<urdf::Visual> visual_array = model_.link_array[i].visual_array;
		for (int v = 0; v < visual_array.size(); v++)
		{

			    std::string colorStr = visual_array[v].material.color;
			    
			    glm::vec3 color = {1.0f,1.0f,1.0f};
			    float alpha = 1.0f;
			    getColorAndAphaFromString(colorStr,color,alpha);
			    
			    GraphicItemStl* stlItem = new GraphicItemStl(vsPath, fsPath, color);
			    glm::mat4 model = glm::mat4(1.0f);
			    model = glm::translate(model, glm::vec3(-5.0f+1.0f*i, 1.0f, 0.0f));
			    stlItem->setModelmatrix(model);
			    stlItem->setLightColor(glm::vec3(1.0f, 0.1f, 0.0f));
			    stlItem->setLightPos(glm::vec3(10.0f, 4.0f, 0.0f));
			    
			    std::string replaceStr = "package://";
			    int length = visual_array[v].geometry.mesh.filename.length();
			    std::string filePath = visual_array[v].geometry.mesh.filename.substr(replaceStr.size(), length);
			    std::string resultPath = package_dir_ + filePath;
			    stlItem->setStlFilePath(resultPath);
			    stlItem->initVAOVBO();
			    stl_vec_.push_back(stlItem);
			    stl_name_map_.insert(make_pair(stlItem, model_.link_array[i].name));
			
		}

	}
	

	//组装机械臂
	//1.求各个机械臂的矩
	std::map< GraphicItemBase*, std::string>::iterator iter = stl_name_map_.begin();


#if 0
	glm::mat4 model = glm::mat4(1.0f);
	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "base_link")
		{
			//std::cout << "line name is ----- base_link" << std::endl;
			glm::vec3 rpy = { -1.57f,0.0f,0.0f };
			//父类坐标系的x,y,z
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(baseCoordinate_.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(baseCoordinate_.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ,rpy.z, glm::vec3(baseCoordinate_.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			model = model * rotate;
			std::cout << "hard coding --------base_link" << std::endl;
			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					std::cout << model[m][n] << " ";
					if (n == 3)
					{
						std::cout << "\n" << std::endl;
					}
				}
			}
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	
	}
	glm::mat4 baseModel = model;
	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "base")
		{
			//std::cout << "line name is ----- base" << std::endl;
			glm::vec3 rpy = { -0.0f,0.0f,0.0f };
			glm::vec3 Coordinate = baseModel * glm::vec4(baseCoordinate_, 1.0f);
			//父类坐标系的x,y,z
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			baseModel = baseModel * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(baseModel);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}

	}


	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "link_1")
		{
			//std::cout << "line name is ----- link_1" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX,rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY,rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ,rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;

			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.78f));
			model = model * rotate;
			std::cout << "hard coding --------link_1" << std::endl;
			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					std::cout << model[m][n] << " ";
					if (n == 3)
					{
						std::cout << "\n" << std::endl;
					}
				}
			}
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}


	glm::mat4 link2Model = glm::mat4(1.0f);
	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "link_2")
		{
			//std::cout << "line name is ----- link_2" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX,rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			link2Model = glm::translate(model, glm::vec3(0.32f, 0.0f, 0.0f));
			link2Model = link2Model * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(link2Model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}

	glm::mat4 cylinderModel = glm::mat4(1.0f);

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "cylinder")
		{
			//std::cout << "line name is ----- cylinder" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			cylinderModel = glm::translate(model, glm::vec3(-0.349f, -0.194f, -0.142f));
			cylinderModel = cylinderModel * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(cylinderModel);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}

	glm::mat4 pistonModel = glm::mat4(1.0f);

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "piston")
		{
			//std::cout << "line name is ----- piston" << std::endl;
			glm::vec3 Coordinate = cylinderModel * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.2089f,0.0f,-1.57f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			pistonModel = glm::translate(cylinderModel, glm::vec3(0.0f, 0.0f, 0.0f));
			pistonModel = pistonModel * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(pistonModel);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}

	}

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{

		if (iter->second == "link_3")
		{
			//std::cout << "line name is ----- link_3" << std::endl;
			glm::vec3 Coordinate = link2Model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ,rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			model = glm::translate(link2Model, glm::vec3(0.0f, 0.0f, 1.28f));
			model = model * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}

	}

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "link_4")
		{
			//std::cout << "line name is ----- link_4" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY,rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.2f));
			model = model * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{

		if (iter->second == "link_5")
		{
			//std::cout << "line name is ----- link_5" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			model = glm::translate(model, glm::vec3(1.5925f, 0.0f, 0.0f));
			model = model * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "link_6")
		{
			//std::cout << "line name is ----- link_6" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,0.0f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
			model = model * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}

	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		if (iter->second == "too10")
		{
			//std::cout << "line name is ----- tool0" << std::endl;
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			glm::vec3 rpy = { 0.0f,1.57f,0.0f };
			glm::mat4 rotateX = glm::mat4(1.0f);
			rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(Coordinate.x, 0, 0));
			glm::mat4 rotateY = glm::mat4(1.0f);
			rotateY = glm::rotate(rotateY,rpy.y, glm::vec3(Coordinate.y, 0, 0));
			glm::mat4 rotateZ = glm::mat4(1.0f);
			rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(Coordinate.z, 0, 0));
			glm::mat4 rotate = rotateX * rotateY*rotateZ;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = model * rotate;
			dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(model);
			dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
			break;
		}
	}
#endif
	
	createTreeNodes();
	urdf::TFTreeNodeData* root = createTFTree();
	
	for (iter = stl_name_map_.begin(); iter != stl_name_map_.end(); iter++)
	{
		std::stack<urdf::TFTreeNodeData*> stack;
		getPathNodesByKey(root, iter->second,stack);
		glm::mat4 trans = glm::mat4(1.0f);
		getNodeMatrix(trans,stack);
		dynamic_cast<GraphicItemBase*>(iter->first)->setModelmatrix(trans);
		dynamic_cast<GraphicItemBase*>(iter->first)->setVisible(true);
	}
}

void GraphicUrdfModel::stringSplit(const std::string& str, const std::string& splits, std::vector<std::string>& res)
{
	if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	std::string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}

void GraphicUrdfModel::getColorAndAphaFromString(std::string clrStr, glm::vec3 & color, float & alpha)
{
	std::vector<std::string> resStrVec ;
	stringSplit(clrStr, " ", resStrVec);
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	alpha = 1.0f;
	
	if (resStrVec.size() == 4)
	{
		r = atof(resStrVec[0].c_str());
		g = atof(resStrVec[1].c_str());
		b = atof(resStrVec[2].c_str());
		alpha = atof(resStrVec[3].c_str());
	}
	//std::cout << "resStrVec size is :   " << r <<" " <<g <<" "<< b<< std::endl;
	 color = glm::vec3(r, g, b);
}

void GraphicUrdfModel::getVec3FromString(std::string clrStr, glm::vec3 & value)
{
	std::vector<std::string> resStrVec;
	stringSplit(clrStr, " ", resStrVec);
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;

	if (resStrVec.size() == 3)
	{
		r = atof(resStrVec[0].c_str());
		g = atof(resStrVec[1].c_str());
		b = atof(resStrVec[2].c_str());
	}

	value = glm::vec3(r, g, b);
}


std::string GraphicUrdfModel::readFileIntoString(char* filename)
{
  std::ifstream ifile(filename);
  //将文件读取到ostringstream对象buf中
  std::ostringstream buf;
  char ch;
  while (buf && ifile.get(ch))
  {
  	buf.put(ch);
  }
  //返回与流对象buf关联的字符串
  return buf.str();
}

urdf::TFTreeNodeData * GraphicUrdfModel::createTFTree()
{
	//最后一个添加的即是基座
	urdf::TFTreeNodeData* root = node_vec_.back();
	for (int i = 0; i < node_vec_.size(); i++)
	{
		for (int j = 0; j < node_vec_.size(); j++)
		{
			if (node_vec_[i]->name == node_vec_[j]->parentName)
			{
				node_vec_[i]->childNodeDatas.push_back(node_vec_[j]);
			}
		}
	}

	return root;
}

void GraphicUrdfModel::createTreeNodes()
{
	for (int i = 0; i < model_.joint_array.size(); i++)
	{
		urdf::TFTreeNodeData* node = new urdf::TFTreeNodeData;
		node->name = model_.joint_array[i].child_link_name;
		node->parentName = model_.joint_array[i].parent_link_name;

		glm::vec3 axis = { 0.0f,0.0f,0.0f };
		getVec3FromString(model_.joint_array[i].axis,axis);
		node->axis = axis;
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
		node->coordinate = Coordinate;
		glm::vec3 rpy = { 0.0f,0.0f,0.0f };
		getVec3FromString(model_.joint_array[i].origin.rotation_str, rpy);
		glm::vec3 position = {0.0f,0.0f,0.0f};
		getVec3FromString(model_.joint_array[i].origin.xyz_str, position);
		std::cout << "link name is ----"<< node->name << std::endl;
		std::cout << "rpy is ----"<< rpy.x<<" "<<rpy.y <<" "<<rpy.z<< std::endl;
		std::cout << "position is ----"<< position.x<<" "<< position.y <<" "<< position.z<< std::endl;
		calcTransformMatrix(model, rpy, Coordinate, position);
		
		for (int m = 0; m < 4; m++)
		{
			for (int n = 0; n < 4; n++)
			{
				std::cout << model[m][n] << " ";
				if (n == 3)
				{
					std::cout << "\n" << std::endl;
				}
			}
		}

		node->matMatrix = model;
		node->limit = model_.joint_array[i].limit;
		node_vec_.push_back(node);
	}
	//创建基座节点
	std::vector<int> indexVec;
	for (int i = 0; i < model_.joint_array.size(); i++)
	{
		if (model_.joint_array[i].parent_link_name == "base_link")
		{
			urdf::TFTreeNodeData* node = new urdf::TFTreeNodeData;
			node->name = model_.joint_array[i].parent_link_name;
			glm::vec3 axis = { 1.0f,1.0f,1.0f };
			getVec3FromString(model_.joint_array[i].axis, axis);
			node->axis = axis;
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 Coordinate = model * glm::vec4(baseCoordinate_, 1.0f);
			node->coordinate = Coordinate;
			glm::vec3 rpy = { -1.57f,0.0f,0.0f };
			glm::vec3 position = { 0.0f,0.0f,0.0f };
			calcTransformMatrix(model, rpy, Coordinate, position);
			std::cout << "link name is ----" << node->name << std::endl;
			std::cout << "rpy is ----" << rpy.x << " " << rpy.y << " " << rpy.z << std::endl;
			std::cout << "position is ----" << position.x << " " << position.y << " " << position.z << std::endl;
			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					std::cout << model[m][n] << " ";
					if (n == 3)
					{
						std::cout << "\n" << std::endl;
					}
				}
			}

			node->matMatrix = model;
			node->limit = model_.joint_array[i].limit;
			node_vec_.push_back(node);
			break;
	   }
	 
	}

}

void GraphicUrdfModel::calcTransformMatrix(glm::mat4& model,glm::vec3 rpy,glm::vec3 coor,glm::vec3 position)
{
	glm::mat4 rotateX = glm::mat4(1.0f);
	rotateX = glm::rotate(rotateX, rpy.x, glm::vec3(coor.x, 0, 0));
	glm::mat4 rotateY = glm::mat4(1.0f);
	rotateY = glm::rotate(rotateY, rpy.y, glm::vec3(coor.y, 0, 0));
	glm::mat4 rotateZ = glm::mat4(1.0f);
	rotateZ = glm::rotate(rotateZ, rpy.z, glm::vec3(coor.z, 0, 0));
	glm::mat4 rotate = rotateX * rotateY*rotateZ;
	model = glm::translate(model, position);
	model = model * rotate;
}

void GraphicUrdfModel::getNodeMatrix(glm::mat4 & model, std::stack<urdf::TFTreeNodeData*> stack)
{
	while (!stack.empty())
	{
		model = stack.top()->matMatrix*model;
		stack.pop();
	}
}


std::vector<GraphicItemBase*>& GraphicUrdfModel::getStlVec()
{
	return stl_vec_;
}

void GraphicUrdfModel::setPackageDir(std::string dir)
{
	package_dir_ = dir;
}

bool GraphicUrdfModel::getPathNodesByKey(urdf::TFTreeNodeData * node, std::string targetName, std::stack<urdf::TFTreeNodeData*>& stack)
{
	bool b = false;
	if (node != nullptr) {
		std::cout << "push name -------" << node->name << std::endl;
		stack.push(node);
		if (node->name == targetName) { return true; }
		std::vector<urdf::TFTreeNodeData*> childrens = node->childNodeDatas;

		for (int i = 0; i < childrens.size(); i++) {
			b = getPathNodesByKey(childrens[i], targetName, stack);
			if (b) {
				break;
			}
		}

		if (!b) {
			stack.pop();
		}
	}
	return b;
}


