#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <Renderer/Texture.h>
#include <Renderer/Renderer.cpp>

using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

template <typename T>
void print(const std::string& s, const T& container)
{
	std::cout << s << std::endl;
		for (auto element : container)
		{
			std::cout << element << " ";
		}
	std::cout << std::endl;
}
void print_arg(int count, ...)
{
	va_list args;

	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}

void zero(int x)
{
	x = 0;
}

int main(int argc, char* argv[])
{
	print_arg(3, "hello", "world", "goodbye");

	INFO_LOG("Hello World");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();

	// create game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// main game loop
	bool quit = false;
	while (!quit)
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(kiko::g_renderer);
		}

		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;
}