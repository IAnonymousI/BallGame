#pragma once

#include <memory>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLProgram.h>
#include "Ball.h"

class BallRenderer {
public:
    virtual void renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix);
protected:
	std::unique_ptr<Engine::GLSLProgram> _program = nullptr;
};

class MomentumBallRenderer : public BallRenderer{
public:
	virtual void renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix) override;
};

class VelocityBallRenderer : public BallRenderer{
public:
	VelocityBallRenderer(int screenWidth, int screenHeight);
	virtual void renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix) override;

private:
	int _screenWidth, _screenHeight;
};