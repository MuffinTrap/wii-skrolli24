#pragma once

#include <vector>

#include "mgdl-mesh.h"
#include <mgdl/mgdl-image.h>

// Model can contain multiple
// meshes and their textures
// Model also knows where it is?

class Model
{
public:
	void AddTexturedMesh(Mesh* meshIn, gdl::Image* imageIn);
	void Draw();
	std::vector<Mesh*> meshes;
	std::vector<gdl::Image*> textures;

};