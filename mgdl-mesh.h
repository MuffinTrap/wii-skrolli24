#pragma once

#include <string>
#include <mgdl/mgdl-types.h>

#include "ufbx.h"

class Mesh
{
public:
	bool LoadFile(std::string fbxFile);
	void DrawImmediate();
	ufbx_vec3 GetVertex(size_t index);
	~Mesh();
	ufbx_scene* scene = nullptr;
	ufbx_mesh* mesh = nullptr;

	static void DrawQuad();
	static void DrawBox();

};
