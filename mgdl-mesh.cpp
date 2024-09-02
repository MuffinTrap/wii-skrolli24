#include "mgdl-mesh.h"
#include <mgdl/mgdl-opengl.h>
#include <mgdl/mgdl-assert.h>

bool Mesh::LoadFile(std::string fbxFile)
{
	// Right handed for OpenGL
	// Y is up
	ufbx_load_opts opts = {};
	opts.target_axes = ufbx_axes_right_handed_y_up;
	opts.target_unit_meters = 1.0f;
	ufbx_error error;
	scene = ufbx_load_file(fbxFile.c_str(), &opts, &error);
	gdl_assert_printf(scene != nullptr, "Cannot load fbx: %s\n", error.description.data);

	for (ufbx_node* node : scene->nodes)
	{
		printf("%s\n", node->name.data);
		// try to get the mesh of this node
		mesh = node->mesh;
	}
	printf("Mesh loaded\n");
	return true;
}

void Mesh::DrawImmediate(MeshDrawMode mode)
{
	if (mode == Textured)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	for (ufbx_face face : mesh->faces)
	{
		if (mode == Lines)
		{
			glBegin(GL_LINE_LOOP);
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		for(uint32_t corner = 0; corner < face.num_indices; corner++)
		{
			uint32_t index = face.index_begin + corner;
			ufbx_vec3 position = mesh->vertex_position[index];
			ufbx_vec3 normal = mesh->vertex_normal[index];
			ufbx_vec2 uv = mesh->vertex_uv[index];
			glVertex3f(position.x, position.y, position.z);
			if (mode == Textured)
			{
				glNormal3f(normal.x, normal.y, normal.z);
				//flipeti flip
				float y = uv.y;
				y -= 1.0f;
				y *= -1.0f;
				glTexCoord2f(uv.x, y);
			}
		}
		if (mode == Lines)
		{
			glEnd();
		}
	}
	if (mode == Textured)
	{
		glEnd();
	}
}


Mesh::~Mesh()
{
	if (scene != nullptr)
	{
		ufbx_free_scene(scene);
	}
}


