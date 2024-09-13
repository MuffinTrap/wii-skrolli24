#include "mgdl-model.h"
#include <mgdl/mgdl-opengl.h>

void Model::AddTexturedMesh(Mesh* meshIn, gdl::Image* imageIn)
{
	meshes.push_back(meshIn);
	textures.push_back(imageIn);
}
void Model::AddTexture(gdl::Image* imageIn)
{
	textures.push_back(imageIn);
}

void Model::Draw(int textureId)
{
	glEnable(GL_TEXTURE_2D);
	for(size_t i = 0; i < meshes.size(); i++)
	{
		if (textureId>= 0 && textureId < (int)textures.size())
		{
			glBindTexture(GL_TEXTURE_2D, textures[textureId]->GetTextureId());
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]->GetTextureId());
		}
		meshes[i]->DrawImmediate();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


