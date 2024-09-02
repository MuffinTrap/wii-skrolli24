#pragma once

#include <string>
#include "ufbx.h"

enum MeshDrawMode
{
	Textured,
	Lines
};

class Mesh
{
public:
	bool LoadFile(std::string fbxFile);
	void DrawImmediate(MeshDrawMode mode);
	~Mesh();
	ufbx_scene* scene = nullptr;
	ufbx_mesh* mesh = nullptr;

};
