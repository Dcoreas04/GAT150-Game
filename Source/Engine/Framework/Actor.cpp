#include "Actor.h"
#include "Framework/Components/RendererComponent.h"
namespace kiko
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components)
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(kiko::Renderer& renderer)
	{
		// if (m_model) m_model->Draw(renderer, m_transform);
		for (auto& component : m_components)
		{
			RendererComponent* rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent)
			{
				rendererComponent->Draw(renderer);
			}
		}
	}
	void Actor::AddComponents(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}
