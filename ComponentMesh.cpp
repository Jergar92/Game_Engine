#include "ComponentMesh.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui\imgui.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"


ComponentMesh::ComponentMesh(GameObject* my_go) :Component(my_go)
{

	component_name = "Mesh";
	type = MESH;
}


ComponentMesh::~ComponentMesh()
{
}
void ComponentMesh::SetupMesh()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

}

void ComponentMesh::InspectorUpdate()
{
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen);
	ImGui::Checkbox("Enabled##enable_active", &enable);
	if (node_open)
	{
		
			ImGui::Text("Vertices:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", num_vertices);

			ImGui::Text("Indices:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", num_indices);

			ImGui::Checkbox("Bounding Box##show_bb", &show_bounding_box);

		ImGui::TreePop();

	}
}
void ComponentMesh::SetData(const std::vector<Vertex>& set_vertices, const std::vector<uint>& set_indices, const int num_ver, const int num_ind)
{
	vertices = set_vertices;
	indices = set_indices;
	num_vertices = num_ver;
	num_indices = num_ind;
	SetupMesh();
}
const std::vector<Vertex>& ComponentMesh::GetVertices()
{
	return vertices;
}
const std::vector<uint>& ComponentMesh::GetIndices()
{
	return indices;
}
const uint ComponentMesh::GetVertexBuffer()
{
	return VBO;
}
const uint ComponentMesh::GetElementBuffer()
{
	return EBO;
}
void ComponentMesh::GenerateBoudingBox()
{
	bounding_box.SetNegativeInfinity();
	for (int i = 0; i < vertices.size(); i++)
	{	
		bounding_box.Enclose(vertices[i].position);
	}
}
void ComponentMesh::SetAABB(const AABB set_bounding_box)
{
	bounding_box = set_bounding_box;
}
void ComponentMesh::Update()
{

	GenerateBoudingBox();

	if (show_bounding_box)
		RenderBoundingBox();


}

void ComponentMesh::RenderBoundingBox()
{
	//--- pos z
	glBegin(GL_LINES);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.maxPoint.y, bounding_box.maxPoint.z);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.minPoint.y, bounding_box.maxPoint.z);

	glVertex3f(bounding_box.minPoint.x, bounding_box.minPoint.y, bounding_box.maxPoint.z);
	glVertex3f(bounding_box.minPoint.x, bounding_box.maxPoint.y, bounding_box.maxPoint.z);
	glEnd();
	//--- pos x
	glBegin(GL_LINES);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.minPoint.y, bounding_box.maxPoint.z);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.minPoint.y, bounding_box.minPoint.z);

	glVertex3f(bounding_box.maxPoint.x, bounding_box.maxPoint.y, bounding_box.minPoint.z);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.maxPoint.y, bounding_box.maxPoint.z);
	glEnd();

	//---- pos y
	glBegin(GL_LINES);
	glVertex3f(bounding_box.minPoint.x, bounding_box.maxPoint.y, bounding_box.maxPoint.z);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.maxPoint.y, bounding_box.maxPoint.z);

	glVertex3f(bounding_box.maxPoint.x, bounding_box.maxPoint.y, bounding_box.minPoint.z);
	glVertex3f(bounding_box.minPoint.x, bounding_box.maxPoint.y, bounding_box.minPoint.z);
	glEnd();

	//--- neg z
	glBegin(GL_LINES);
	glVertex3f(bounding_box.minPoint.x, bounding_box.minPoint.y, bounding_box.minPoint.z);
	glVertex3f(bounding_box.minPoint.x, bounding_box.maxPoint.y, bounding_box.minPoint.z);

	glVertex3f(bounding_box.maxPoint.x, bounding_box.maxPoint.y, bounding_box.minPoint.z);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.minPoint.y, bounding_box.minPoint.z);
	glEnd();

	//--- neg y
	glBegin(GL_LINES);
	glVertex3f(bounding_box.minPoint.x, bounding_box.minPoint.y, bounding_box.minPoint.z);
	glVertex3f(bounding_box.maxPoint.x, bounding_box.minPoint.y, bounding_box.minPoint.z);

	glVertex3f(bounding_box.maxPoint.x, bounding_box.minPoint.y, bounding_box.maxPoint.z);
	glVertex3f(bounding_box.minPoint.x, bounding_box.minPoint.y, bounding_box.maxPoint.z);
	glEnd();

	//--- neg x
	glBegin(GL_LINES);
	glVertex3f(bounding_box.minPoint.x, bounding_box.minPoint.y, bounding_box.minPoint.z);
	glVertex3f(bounding_box.minPoint.x, bounding_box.minPoint.y, bounding_box.maxPoint.z);

	glVertex3f(bounding_box.minPoint.x, bounding_box.maxPoint.y, bounding_box.maxPoint.z);
	glVertex3f(bounding_box.minPoint.x, bounding_box.maxPoint.y, bounding_box.minPoint.z);
	glEnd();
}
