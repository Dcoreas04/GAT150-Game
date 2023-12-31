#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Core/Math/Color.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/ModelRenderComponent.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
bool SpaceGame::Initialize()
{
	// create font / text object
	m_font = kiko::g_resourceM.Get<kiko::Font>("arcadeclassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(kiko::g_resourceM.Get<kiko::Font>("arcadeclassic.ttf", 24));
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(kiko::g_resourceM.Get<kiko::Font>("arcadeclassic.ttf", 24));
	m_titleText->Create(kiko::g_renderer, "AZTEROIDS", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(kiko::g_resourceM.Get<kiko::Font>("arcadeclassic.ttf", 24));
	m_gameoverText->Create(kiko::g_renderer, "GAME OVER", kiko::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<kiko::Text>(kiko::g_resourceM.Get<kiko::Font>("arcadeclassic.ttf", 24));
	m_timerText->Create(kiko::g_renderer, "TIMER", kiko::Color{ 1, 1, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 6 });
		player->m_tag = "Player";
		player->m_game = this;

		// Create Components
		std::unique_ptr<kiko::ModelRenderComponent> component = std::make_unique<kiko::ModelRenderComponent>();
		component->m_model = kiko::g_resourceM.Get<kiko::Model>("ship.txt", kiko::g_renderer);
		player->AddComponents(std::move(component));
		
		auto physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
		physicsComponent->m_damping = 0.0f;
		player->AddComponents(std::move(physicsComponent));

		m_scene->Add(std::move(player));
		}
	m_state = eState::Game;
	break;
	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3});
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
			component->m_texture = kiko::g_resourceM.Get<kiko::Texture>("Ship_2_C_Small.png", kiko::g_renderer);
			enemy->AddComponents(std::move(component));
			m_scene->Add(std::move(enemy));
		}
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), {1, 1, 1, 1});
	m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer & renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}

	m_timerText->Draw(renderer, 400, 40);
	m_scoreText->Draw(renderer, 40, 20);
	m_scene->Draw(renderer);
}
