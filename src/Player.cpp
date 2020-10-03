#include "Player.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/ThermalDetonator.png", "detonator");
	
	auto size = TextureManager::Instance()->getTextureSize("detonator");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("detonator", x, y, 0, 255, true);
}

void Player::update(float deltaTime)
{
	glm::vec2 pos = getTransform()->position;

	getRigidBody()->velocity += Util::limitMagnitude(getRigidBody()->acceleration, currentSpeed());

	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
	slow();
	SetSprint(false);
}

void Player::clean()
{

}

float Player::currentAcceleration()
{
	return m_sprintFlag ? RUN_ACCELERATION : WALK_ACCELERATION;
}

float Player::currentSpeed()
{
	return m_sprintFlag ? RUN_SPEED : WALK_SPEED;
}

void Player::moveLeft() {
	getRigidBody()->acceleration.x -= currentAcceleration();
}

void Player::moveRight() {
	getRigidBody()->acceleration.x += currentAcceleration();
}

void Player::moveUp() {
	getRigidBody()->acceleration.y -= currentAcceleration();
}

void Player::moveDown() {
	getRigidBody()->acceleration.y += currentAcceleration();
}

void Player::slow()
{
	getRigidBody()->acceleration *= 0.5f;
	getRigidBody()->velocity *= 0.8f;
}

void Player::stop()
{
	getRigidBody()->acceleration = { 0.0f, 0.0f };
	getRigidBody()->velocity = { 0.0f, 0.0f };
}

float Player::checkDistance(GameObject* pGameObject) {
	return Util::distance(getTransform()->position, pGameObject->getTransform()->position);
}

