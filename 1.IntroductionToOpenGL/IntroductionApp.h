#pragma once
#define GLM_FORCE_SWIZZLE
#include "Application.h"
#include <glm/glm/glm.hpp>


struct Transform;

class CameraApp :	public Application
{
public:
	CameraApp();
	~CameraApp();
	Transform* modelTransform;
	glm::mat4 model;
	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

