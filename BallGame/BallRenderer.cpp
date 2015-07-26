#include "BallRenderer.h"

void BallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (_program == nullptr){
		_program = std::make_unique<Engine::GLSLProgram>();
		_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
		_program->addAttribute("vertexPosition");
		_program->addAttribute("vertexColor");
		_program->addAttribute("vertexUV");
		_program->linkShaders();
	}
	_program->use();
	spriteBatch.begin();

	GLint textureUniform = _program->getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	GLint pUniform = _program->getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	for (auto& ball : balls){
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
			ball.radius * 2.0f, ball.radius * 2.0f);
		spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, ball.color);
	}

	spriteBatch.end();
	spriteBatch.renderBatch();

	_program->unuse();
}

void MomentumBallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix){
	glClearColor(0.0f, 0.1f, 0.5f, 1.0f);
	if (_program == nullptr){
		_program = std::make_unique<Engine::GLSLProgram>();
		_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
		_program->addAttribute("vertexPosition");
		_program->addAttribute("vertexColor");
		_program->addAttribute("vertexUV");
		_program->linkShaders();
	}
	_program->use();
	spriteBatch.begin();

	GLint textureUniform = _program->getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	GLint pUniform = _program->getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	for (auto& ball : balls){
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
			ball.radius * 2.0f, ball.radius * 2.0f);
		Engine::Color color;
		GLubyte colorVal = (GLubyte)(glm::clamp(glm::length(ball.velocity) * ball.mass * 12.0f, 0.0f, 255.0f));
		color.r = colorVal;
		color.g = colorVal;
		color.b = colorVal;
		color.a = colorVal;
		spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, color);
	}

	spriteBatch.end();
	spriteBatch.renderBatch();

	_program->unuse();
}

VelocityBallRenderer::VelocityBallRenderer(int screenWidth, int screenHeight) : _screenWidth(screenWidth), _screenHeight(screenHeight){
	
}

void VelocityBallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (_program == nullptr){
		_program = std::make_unique<Engine::GLSLProgram>();
		_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
		_program->addAttribute("vertexPosition");
		_program->addAttribute("vertexColor");
		_program->addAttribute("vertexUV");
		_program->linkShaders();
	}
	_program->use();
	spriteBatch.begin();

	GLint textureUniform = _program->getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	GLint pUniform = _program->getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	for (auto& ball : balls){
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
			ball.radius * 2.0f, ball.radius * 2.0f);
		Engine::Color color;
		float mult = 100.0f;
		GLubyte colorVal = (GLubyte)(glm::clamp(ball.velocity.x * mult, 0.0f, 255.0f));
		color.r = 128.0f;
		color.g = (GLubyte)((ball.position.x / _screenWidth) * 255.0f);
		color.b = (GLubyte)((ball.position.y / _screenHeight) * 255.0f);
		color.a = colorVal;
		spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, color);
	}

	spriteBatch.end();
	spriteBatch.renderBatch();

	_program->unuse();
}