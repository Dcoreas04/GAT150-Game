#pragma once
#include "RendererComponent.h"
#include "Renderer/Texture.h"
namespace kiko
{
	class SpriteComponent : public RendererComponent
	{
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		
	public:
		res_t<Texture> m_texture;
	};


}