#pragma once
#include <utils\utils.h>

#include <GLM\vec4.hpp>

class Mesh 
{
public:
	Mesh(const cstr& path);
	~Mesh();
	void draw();
public:
	REGISTER_READ_ONLY_PROPERTY(const cstr&, filename);
	REGISTER_READ_ONLY_PROPERTY(uint, vbo_vertices);
	REGISTER_READ_ONLY_PROPERTY(uint, vbo_normals);
	REGISTER_READ_ONLY_PROPERTY(uint, ibo_elements);
public:
	REGISTER_PROPERTY(std::vector<glm::vec4>,	vertices);
	REGISTER_PROPERTY(std::vector<glm::vec3>,	normals);
	REGISTER_PROPERTY(std::vector<ushort>,		elements);
private:
	cstr filename;
	std::vector<glm::vec4>	vertices;
	std::vector<glm::vec3>	normals;
	std::vector<ushort>		elements;
	uint vbo_vertices = 0, vbo_normals = 0, ibo_elements = 0;
private:
	void bind();
};