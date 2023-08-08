#pragma once
#include "PhysicsComponents.h"
namespace kiko
{
	class EnginePhysicsComponent : public Physics
	{
	public:
		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
	};


}