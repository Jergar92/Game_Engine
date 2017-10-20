#include "ComponentMesh.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui\imgui.h"


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
void ComponentMesh::GuiUpdate()
{
}
void ComponentMesh::InspectorUpdate()
{
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	if (node_open)
	{

		ImGui::TreePop();

	}
}
void ComponentMesh::SetData(const std::vector<Vertex>& set_vertices, const std::vector<uint>& set_indices)
{
	vertices = set_vertices;
	indices = set_indices;
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
void ComponentMesh::Update()
{
	

}
