#include "mgdl-mesh.h"
#include <mgdl/mgdl-opengl.h>
#include <mgdl/mgdl-assert.h>
#include <glm/glm.hpp>

bool Mesh::LoadFile(std::string fbxFile)
{
	// Right handed for OpenGL
	// Y is up
	ufbx_load_opts opts = {};
	opts.target_axes = ufbx_axes_right_handed_y_up;
	opts.target_unit_meters = 1.0f;
	ufbx_error error;
	printf("Reading fbx file %s\n", fbxFile.c_str());
	scene = ufbx_load_file(fbxFile.c_str(), &opts, &error);
	gdl_assert_printf(scene != nullptr, "Cannot load fbx: %s\n", error.description.data);

	for (ufbx_node* node : scene->nodes)
	{
		printf("Found node %s\n", node->name.data);
		// try to get the mesh of this node
		mesh = node->mesh;
	}
	printf("Mesh loaded\n");
	return true;
}

ufbx_vec3 Mesh::GetVertex(size_t index)
{
	return mesh->vertex_position[index];
}
void Mesh::DrawImmediate(MeshDrawMode mode)
{
	if (mode == Textured)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	for(ufbx_face face : mesh->faces)
	{
		if (mode == Lines)
		{
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		for(uint32_t corner = 0; corner < face.num_indices; corner++)
		{
			uint32_t index = face.index_begin + corner;
			ufbx_vec3 position = mesh->vertex_position[index];
			if (mode == Textured)
			{
				ufbx_vec3 normal = mesh->vertex_normal[index];
				ufbx_vec2 uv = mesh->vertex_uv[index];
				glNormal3f(normal.x, normal.y, normal.z);
				//flipeti flip
				float y = uv.y;
				y -= 1.0f;
				y *= -1.0f;
				glTexCoord2f(uv.x, y);
			}

			// NOTE!
			// This must be last since GX needs to know
			// what data goes to vertex before sending the position
			glVertex3f(position.x, position.y, position.z);
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
static void Quad(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d)
{
	glVertex3f(d.x, d.y, d.z);
	glVertex3f(c.x, c.y, c.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(a.x, a.y, a.z);
}

void Mesh::DrawQuad()
{
	glBegin(GL_QUADS);
	glm::vec3 bl = {-0.5f, 0.0f, -0.5f};
	glm::vec3 br = {0.5f, 0.0f, -0.5f};
	glm::vec3 fl = {-0.5f, 0.0f, 0.5f};
	glm::vec3 fr = {0.5f, 0.0f, 0.5f};
	Quad(fl, fr, br, bl);
	glEnd();
}

void Mesh::DrawBox()
{
	float height = 0.5f;
	glm::vec3 bl = {-0.5f, -0.5f, -0.5f};
	glm::vec3 br = {0.5f, -0.5f, -0.5f};
	glm::vec3 fl = {-0.5f, -0.5f, 0.5f};
	glm::vec3 fr = {0.5f, -0.5f, 0.5f};

	glm::vec3 tbl = {-0.5f, height, -0.5f};
	glm::vec3 tbr = {0.5f, height, -0.5f};
	glm::vec3 tfl = {-0.5f, height, 0.5f};
	glm::vec3 tfr = {0.5f, height, 0.5f};

	/*
	glm::vec3 R = {1.0f, 0.0f, 0.0f};
	glm::vec3 U = {0.0f, 1.0f, 0.0f};
	glm::vec3 F = {0.0f, 0.0f, 0.001f};
	*/

	glBegin(GL_QUADS);
		// left side
		Quad(bl, tbl, tfl, fl);
		// front
		Quad(fl, tfl, tfr, fr);
		// right
		Quad(fr, tfr, tbr, br);
		// back
		Quad(br, tbr, tbl, bl);
		// Top
		Quad(tfl, tbl, tbr, tfr);
		// Bottom
		Quad(fl, bl, br, fr);
	glEnd();
}



