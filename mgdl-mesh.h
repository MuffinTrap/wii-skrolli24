#pragma once

#include <string>
#include <mgdl/mgdl-types.h>
#include <glm/glm.hpp>


#include "ufbx.h"

class Mesh
{
public:
	bool LoadFile(std::string fbxFile);
	void DrawImmediate();
	ufbx_vec3 GetVertex(size_t index);
	~Mesh();
	ufbx_scene* scene = nullptr;
	ufbx_mesh* mesh1;
	ufbx_mesh* mesh2;

	static void DrawQuad();
	static void DrawBox();
private:
	glm::vec3 mesh2Offset; // For the PC monitor
	void DrawMesh(ufbx_mesh* mesh);

};
