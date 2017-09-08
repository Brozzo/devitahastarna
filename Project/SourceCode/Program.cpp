#include "Program.h"
#include "Resources.h"

#include <iostream>
#include <cmath>


void CProgram::SetSFWindow( std::unique_ptr<sf::RenderWindow> pNewWindow )
{
	_pSFWindow = std::move( pNewWindow );
}

std::unique_ptr<sf::RenderWindow> CProgram::ReleaseSFWindow()
{
	return std::move( _pSFWindow );
}

void CProgram::Run()
{
	_Player.SetSprite( std::make_unique<sf::Sprite>( CResources::AccessTexture( NImages::EImages::PLAYER ) ) );
	_Player.SetPosition( 100, 100 );
	_Player.SetRotation( 10.0f );
	_pMusic = &CResources::AccessMusic( NMusic::EMusic::MAIN_THEME );
	_pMusic->setLoop(true);
	_pMusic->play();
	_PlayerSound.setBuffer( CResources::AccessSound( NSounds::ESounds::TEST_SOUND ) );
	_PlayerSound.setLoop(true);
	_PlayerSound.play();
	sf::Clock clock;
	clock.restart();
	long long nNextTick = clock.getElapsedTime().asMicroseconds();
	while ( _pSFWindow && _pSFWindow->isOpen() )
	{
		constexpr long long nMicrosecondsPerTick = 1000000 / 240;
		long long time = clock.getElapsedTime().asMicroseconds();
		if ( time < nNextTick )
			sf::sleep( sf::microseconds( nNextTick - time ) );
		else
			nNextTick = time;
		nNextTick += nMicrosecondsPerTick;

		HandleInput();
		Update();
	}
}

void CProgram::HandleInput()
{
	sf::Event event;
	while ( _pSFWindow->pollEvent( event ) )
	{
		switch ( event.type )
		{
		case sf::Event::Closed:
			_pSFWindow->close();
			break;
		case sf::Event::KeyPressed:
			HandleKeyPressed( event.key );
			break;
		case sf::Event::KeyReleased:
			HandleKeyReleased( event.key );
			break;
		default:
			break;
		}
	}
}

void CProgram::HandleKeyPressed( const sf::Event::KeyEvent& event )
{
	if ( 0 <= event.code && event.code < sf::Keyboard::KeyCount ) //C: Some weird keys has code -1.
		_PressedKeys[event.code] = true;
}
void CProgram::HandleKeyReleased( const sf::Event::KeyEvent& event )
{
	if ( 0 <= event.code && event.code < sf::Keyboard::KeyCount )
		_PressedKeys[event.code] = false;
}

void CProgram::Update()
{
	sf::Vector2f ScreenCenter = { float( _pSFWindow->getSize().x ), float( _pSFWindow->getSize().y ) };
	ScreenCenter *= 0.5f;
	sf::Vector2f PlayerToCenter = ScreenCenter - _Player.GetPosition();
	float velocity = sqrt(_Player.GetVelocity().x * _Player.GetVelocity().x + _Player.GetVelocity().y * _Player.GetVelocity().y);
	
	if ( _PressedKeys[sf::Keyboard::S] )
	{
		_Player.UseEngine( _Player.BaseEngine( _Player ) );
		if ( _PlayerSound.getStatus() != 2 )
			_PlayerSound.play();
	}
	else
	{
		_PlayerSound.pause();
	}
	if ( _PressedKeys[sf::Keyboard::A] )
	{
		_Player.UseEngine( _Player.LeftBackEngine( _Player ) );
	}
	if ( _PressedKeys[sf::Keyboard::D] )
	{
		_Player.UseEngine( _Player.RightBackEngine( _Player ) );
	}
	if ( _PressedKeys[sf::Keyboard::Q] )
	{
		_Player.UseEngine( _Player.LeftFrontEngine( _Player ) );
	}
	if ( _PressedKeys[sf::Keyboard::E] )
	{
		_Player.UseEngine( _Player.RightFrontEngine( _Player ) );
	}
	if ( _PressedKeys[sf::Keyboard::Space] )
	{
		_Player.Accelerate( PlayerToCenter * 0.0001f );
	}
	if ( _PressedKeys[sf::Keyboard::O] )
	{
		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done)
		{
			std::cout << "error!";
		}

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "error!";
		}
	}
	if ( _PressedKeys[sf::Keyboard::P] )
	{
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect("192.168.1.166", 53000);
		if (status != sf::Socket::Done)
		{
			std::cout << "error!";
		}
	}

	_Player.Update();

	_pMusic->setPitch( velocity / 10.0f + 1 );

	std::vector<const sf::Sprite*> Sprites;
	if ( const sf::Sprite* pPlayerSprite = _Player.GetSprite() )
	{
		Sprites.push_back( pPlayerSprite );
	}

	_pSFWindow->clear();
	for ( const sf::Sprite* pSprite : Sprites )
	{
		_pSFWindow->draw( *pSprite );
	}
	_pSFWindow->display();
}
