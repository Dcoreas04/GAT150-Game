#pragma once
#include "Component.h"

namespace kiko
{
	class RendererComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}