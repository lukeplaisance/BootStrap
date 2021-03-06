#pragma once
#include <Application.h>
#include <vector>
#include <Transform.h>
#include "MeshRenderer.h"
#include "Shader.h"
#include "Texture.h"


class RenderingGeometryApp :public Application
{
public:

	MeshRenderer* mesh;
	Shader* shader;
	Transform* m_transform;
	Texture* texture;
	
	unsigned int m_program;

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	RenderingGeometryApp();
	~RenderingGeometryApp();

	std::vector<glm::vec4> GenHalfCircle(int np, int radius);

	void GenSphere(int radius, int np, int nm);

	std::vector<unsigned int> GenIndices(unsigned int np, unsigned int nm);

	std::vector<glm::vec4> RotatePoints(std::vector<glm::vec4> points, 
										unsigned int numMeridians);

	std::vector<MeshRenderer::Vertex> GenCube(std::vector<MeshRenderer::Vertex> vertices);

	std::vector<unsigned int> genCubeIndices();

	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

