#include "ComponentMesh.h"
#include "Glew\include\GL\glew.h"
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

	if (indices.size() != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
		//set bind buffer glBindBuffer to 0
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ComponentMesh::InspectorUpdate()
{
	
	uint flags = ImGuiTreeNodeFlags_DefaultOpen|ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(),flags,&enable);
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
const std::vector<Vertex>& ComponentMesh::GetVertices()const
{
	return vertices;
}
const std::vector<uint>& ComponentMesh::GetIndices()const
{
	return indices;
}
const uint ComponentMesh::GetVertexBuffer()const
{
	return VBO;
}
const uint ComponentMesh::GetElementBuffer()const
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

AABB ComponentMesh::GetBoundingBox() const
{
	return bounding_box;
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

bool ComponentMesh::SaveComponent(JSONConfig & config) const
{
	bool ret = true;
	config.SetInt(type, "Type");
	config.SetBool(my_go->GetUID(), "GameObject UID");
	config.SetBool(enable, "Enable");

	//save the path of the mesh.frog
	return ret;
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
