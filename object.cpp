#include "object.h"

object::object(obj_file &File, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color)
{

	//vec3 Position(0.0f, 0.0f, 0.0f);
	//vec3 Scale(1.0f, 1.0f, 1.0f);
	//vec3 Rotation(0.0f, 180.0f, 0.0f);

	SetInitialModel(Position, Scale, Rotation);

	struct cb
	{
		XMMATRIX MVP;
		XMMATRIX Model;
		XMFLOAT4 AmbientLight;
		XMFLOAT3 LightPosition;

	} VS_Input;

	// NOTE(Cristoffer): Store vertex data.
	for(auto const &Vert : File.Vertices)
	{
		vertex Vertex;

		Vertex.Position = vec3(Vert.x, Vert.y, Vert.z);
		Vertex.Color = Color;
		Vertex.Normal = vec3(0.5f, 0.5f, 0.5f);

		Vertices.push_back(Vertex);
	}

	// NOTE(Cristoffer): Store the normals.
	for(auto const &Vertex : File.Normals)
	{
		Normals.push_back(Vertex);
	}
	
	// NOTE(Cristoffer): Fill the normal vertices based on mapped index.
	for(auto const Element : File.FaceIndices)
	{
		uint32 VertexIndex = Element.Position;
		uint32 NormalIndex = Element.Normal;

		Vertices.at(VertexIndex).Normal = Normals.at(NormalIndex);
	}

	// NOTE(Cristoffer): Vertex indicies for index buffer.
	for(auto const &Indicies : File.FaceIndices)
	{
		Indices.push_back(Indicies.Position);
	}

	Shader = new shader(L"vehicle_vs.cso", L"vehicle_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	Shader->AddInputElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->CommitInputElements();

	Texture = nullptr;

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), (uint32)Vertices.size(), DYNAMIC);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint32), (uint32)Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(cb));
}

void object::Draw(camera &Camera)
{
	struct cb
	{
		XMMATRIX MVP;
		XMMATRIX Model;
		XMFLOAT4 AmbientLight;
		XMFLOAT3 LightPosition;

	} VS_Input;

	VS_Input.MVP = XMMatrixTranspose(Model * XMMATRIX(Camera.GetViewMatrix()) * XMMATRIX(Camera.GetProjectionMatrix()));
	VS_Input.Model = XMMatrixTranspose(Model);
	VS_Input.AmbientLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//VS_Input.LightPosition = XMFLOAT3(Camera.GetPositionX(), Camera.GetPositionY(), Camera.GetPositionZ());
	VS_Input.LightPosition = XMFLOAT3(light_source::Position.x, 
									  light_source::Position.y, 
									  light_source::Position.z);

	//Texture->Bind();
	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}