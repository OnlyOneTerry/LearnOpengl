#pragma once
#include "../common/urdfDef.h"
#include "tinyxml.h"
#include <iostream>

class UrdfParser
{
public:
	~UrdfParser();
	static UrdfParser getInstance();
	void parseUrdf(const std::string& xml_string,urdf::RobotModel& model);

	void parseLink(urdf::Link& link, TiXmlElement* config);
	bool parseCollision(urdf::Collision& collision, TiXmlElement* config);
	bool parseVisual(urdf::Visual& vis, TiXmlElement * config);
	bool parseMaterial(urdf::Material&material, TiXmlElement * config);
	urdf::Geometry parseGeometry(TiXmlElement* g);
	bool parseMesh(urdf::Mesh& mesh, TiXmlElement* m);
	bool parseOrigin(urdf::Origin& origin, TiXmlElement* xml);

	bool parseJoint(urdf::Joint& joint, TiXmlElement* config);
	bool parseJointLimits(urdf::JointLimits& jl, TiXmlElement* config);
	double strToDouble(std::string str);
private:
	UrdfParser();

};

