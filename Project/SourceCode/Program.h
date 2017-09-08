#pragma once

#include "Ship.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <memory>
#include <array>

namespace sf
{
	class RenderWindow;
}
class CProgram
{
public:
	template<typename... T>
	CProgram( T... t );

	void													SetSFWindow( std::unique_ptr<sf::RenderWindow> pNewWindow );
	std::unique_ptr<sf::RenderWindow>						ReleaseSFWindow();

	void													Run();
private:
	void													HandleInput();
	void													HandleKeyPressed( const sf::Event::KeyEvent& event );
	void													HandleKeyReleased( const sf::Event::KeyEvent& event );

	void													Update();

	std::unique_ptr<sf::RenderWindow>						_pSFWindow;
	std::array< bool, sf::Keyboard::KeyCount >				_PressedKeys;
	CShip													_Player;
	sf::Music*												_pMusic = nullptr;
	sf::Sound												_PlayerSound;
};

template<typename ...T>
CProgram::CProgram( T ...t )
	: _pSFWindow( std::make_unique<sf::RenderWindow>( t... ) )
{
	_PressedKeys.fill( false );
}
