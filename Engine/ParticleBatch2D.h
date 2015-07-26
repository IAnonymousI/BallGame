#pragma once

#include <functional>
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "Vertex.h"
#include "GLTexture.h"

namespace Engine{

	class Particle2D{
	public:

		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		Color color;
		float life = 0.0f;
		float width = 0.0f;

	};

	inline void defaultUpdate(Particle2D& particle, float deltaTime){
		particle.position += particle.velocity * deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc = defaultUpdate);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

		void addParticle(const glm::vec2& position, const glm::vec2& velocity, Color& color, float width);

	private:
		int findFreeParticle();

		std::function<void(Particle2D&, float)> _updateFunc;
		float _decayRate = 0.1f;
		Particle2D* _particles = nullptr;
		int _maxParticles = 0;
		int _lastFreeParticle = 0;
		GLTexture _texture;
	};

}