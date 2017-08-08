#pragma once

#include <SFML/System/Vector2.hpp>

#include <memory>
#include <utility>

namespace sf
{
	class Sprite;
}
class CShip
{
public:
	struct SEngine
	{
		sf::Vector2f _RelativePosition;
		sf::Vector2f _RelativeForce;
	};
	static SEngine BaseEngine( const CShip& Ship );
	static SEngine LeftFrontEngine( const CShip& Ship );
	static SEngine RightFrontEngine( const CShip& Ship );
	static SEngine LeftBackEngine( const CShip& Ship );
	static SEngine RightBackEngine( const CShip& Ship );

	CShip::~CShip();
	void								Update();

	void								SetSprite( std::unique_ptr<sf::Sprite> pSprite );
	const sf::Sprite*					GetSprite() const { return _pSprite.get(); }

	void								SetPosition( float x, float y ) { _Position.x = x; _Position.y = y; }
	void								SetPosition( const sf::Vector2f& Position ) { _Position = Position; }
	void								Accelerate( const sf::Vector2f& VelocityChange ) { _VelocityIncrease += VelocityChange; }
	const sf::Vector2f&					GetPosition() const { return _Position; }

	void								SetRotation( float vRotation ) { _vRotation = vRotation; }
	void								AccelerateRotation( float vRotationSpeedChange ) { _vRotationSpeedIncrease += vRotationSpeedChange; }
	float								GetRotation() const { return _vRotation; }

	void								UseEngine( const SEngine& Engine );

	sf::Vector2f						GetPhysicsRectangle() const { return _PhysicsRectangle; }
private:
	std::unique_ptr<sf::Sprite>			_pSprite;
	sf::Vector2f						_PhysicsRectangle; // For rotational inertia
	sf::Vector2f						_Position;
	sf::Vector2f						_Velocity;
	sf::Vector2f						_VelocityIncrease;
	float								_vRotation = 0.0f;
	float								_vRotationSpeed = 0.0f;
	float								_vRotationSpeedIncrease = 0.0f;
};