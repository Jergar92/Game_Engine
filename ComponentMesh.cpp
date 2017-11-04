#include "ComponentMesh.h"
#include "Application.h"

#include "Glew\include\GL\glew.h"
#include "imgui\imgui.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"


ComponentMesh::ComponentMesh(GameObject* my_go) :Component(my_go)
{
	UID = App->GenerateRandom();
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
	if (indices.size() % 3 != 0)
	{
		LOG("ERROR is Not multiple of 3!");
		debug_normals_succes = false;
	}
	else {
		glGenBuffers(1, &vertex_normals_id);
		glGenBuffers(1, &surface_normals_id);

		std::vector<float3> vertex_normals;
		std::vector<float3> surface_normals;
		//vertex normal loop
		for (uint i = 0; i < indices.size(); i++)
		{
			int indice_number = indices[i];
			vertex_normals.push_back(vertices[indice_number].position);
			vertex_normals.push_back(vertices[indice_number].position + vertices[indice_number].normals);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_id);
		glBufferData(GL_ARRAY_BUFFER, vertex_normals.size() * sizeof(float3), &vertex_normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//surface normal loop
		for (uint i = 0; i < indices.size(); i += 3)
		{
			float3 vertexA = vertices[indices[i]].position;
			float3 vertexB = vertices[indices[i + 1]].position;
			float3 vertexC = vertices[indices[i + 2]].position;

			float3 edge1 = vertexB - vertexA;
			float3 edge2 = vertexC - vertexA;
			float3 surface_normal = Cross(edge1, edge2);
			surface_normal.Normalize();


			float3 center_point(
				((vertexA.x + vertexB.x + vertexC.x) / 3),
				((vertexA.y + vertexB.y + vertexC.y) / 3),
				((vertexA.z + vertexB.z + vertexC.z) / 3));

			surface_normals.push_back(center_point);
			surface_normals.push_back(center_point + surface_normal);
		}

		glBindBuffer(GL_ARRAY_BUFFER, surface_normals_id);
		glBufferData(GL_ARRAY_BUFFER, surface_normals.size() * sizeof(float3), &surface_normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

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

			ImGui::Checkbox("Bounding Box AABB##show_bb", &show_bounding_boxAABB);
			ImGui::Checkbox("Bounding Box OBB##show_bb", &show_bounding_boxOBB);

		ImGui::TreePop();

	}
}
void ComponentMesh::CleanUp()
{
	vertices.clear();
	indices.clear();
}
void ComponentMesh::SetData(const std::vector<Vertex>& set_vertices, const std::vector<uint>& set_indices, const int num_ver, const int num_ind)
{
	vertices = set_vertices;
	indices = set_indices;
	num_vertices = num_ver;
	num_indices = num_ind;
	SetupMesh();
	GenerateBoudingBox();
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
const uint ComponentMesh::GetVertexNormalID() const
{
	return vertex_normals_id;
}
const uint ComponentMesh::GetSurfaceNormalID() const
{
	return surface_normals_id;
}
const bool ComponentMesh::GetDrawMesh() const
{
	return draw_mesh;
}
void ComponentMesh::GenerateBoudingBox()
{
	bounding_box.SetNegativeInfinity();
	for (int i = 0; i < vertices.size(); i++)
	{	
		bounding_box.Enclose(vertices[i].position);
	}
}

void ComponentMesh::DrawMesh(bool show)
{
	draw_mesh = show;
}

const bool ComponentMesh::GetDebugNormal() const
{
	return debug_normals_succes;
}

AABB ComponentMesh::GetBoundingBox() const
{
	return bounding_box;
}

int ComponentMesh::GetUID() const
{
	return UID;
}

void ComponentMesh::SetAABB(const AABB set_bounding_box)
{
	bounding_box = set_bounding_box;
}
void ComponentMesh::Update()
{
	if (show_bounding_boxAABB)
	{
		RenderBoundingBoxAABB();
	}
	else if (show_bounding_boxOBB)
	{
		RenderBoundingBoxOBB();
	}
		
}

bool ComponentMesh::SaveComponent(JSONConfig & config) const
{
	bool ret = true;
	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetInt(UID, "Mesh UID");

	config.SetBool(enable, "Enable");

	//save the path of the mesh.frog
	return ret;
}

bool ComponentMesh::LoadComponent(const JSONConfig & config)
{
	bool ret = true;

	UID = config.GetInt("Mesh UID");

	std::string id_name = std::to_string(UID);
	App->importer->LoadMesh(id_name.c_str(), this);
	enable= config.GetBool( "Enable");

	return ret;
}

void ComponentMesh::RenderBoundingBoxAABB()const
{
	
	glBegin(GL_LINES);
		for (uint i = 0; i < 12; i++)
		{
			glVertex3f(bounding_box.Edge(i).a.x, bounding_box.Edge(i).a.y, bounding_box.Edge(i).a.z);
			glVertex3f(bounding_box.Edge(i).b.x, bounding_box.Edge(i).b.y, bounding_box.Edge(i).b.z);
		}
		glEnd();

}

void ComponentMesh::RenderBoundingBoxOBB()const
{
	OBB box = my_go->GetBoundingBox();
	glBegin(GL_LINES);
	for (uint i = 0; i < 12; i++)
	{
		glVertex3f(box.Edge(i).a.x, box.Edge(i).a.y, box.Edge(i).a.z);
		glVertex3f(box.Edge(i).b.x, box.Edge(i).b.y, box.Edge(i).b.z);
	}
	glEnd();
}
