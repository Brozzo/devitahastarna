#include "Resources.h"

#include <cassert>
#include <array>
#include <string>

using namespace NImages;

const std::string& NImages::GetFullPath( EImages image )
{
	static const std::array< std::string, size_t( EImages::NUM_OF_IMAGES ) > Paths
	{
		ImagesPath + "image.png",
		ImagesPath + "ship.png",
	};
	assert( size_t( image ) < Paths.size() );
	return Paths[size_t( image )];
}

std::array< std::unique_ptr<sf::Texture>, size_t( EImages::NUM_OF_IMAGES ) > NTextures::Textures;

sf::Texture* NTextures::GetTexture( EImages image )
{
	assert( size_t( image ) < Textures.size() );
	return Textures[size_t( image )].get();
}

void NTextures::CreateTextures()
{
	Textures[size_t( EImages::TEST_IMAGE )] = std::make_unique<sf::Texture>();
	Textures[size_t( EImages::TEST_IMAGE )]->loadFromFile( GetFullPath( EImages::TEST_IMAGE ) );

	Textures[size_t( EImages::PLAYER )] = std::make_unique<sf::Texture>();
	Textures[size_t( EImages::PLAYER )]->loadFromFile( GetFullPath( EImages::PLAYER ) );
}
