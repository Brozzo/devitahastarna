#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <array>

namespace NResources
{
	const std::string ResourcesPath( "../../Resources/" );
}

namespace NImages
{
	using namespace NResources;
	const std::string ImagesPath( ResourcesPath + "Images/" );
	enum class EImages
	{
		TEST_IMAGE,
		PLAYER,
		NUM_OF_IMAGES,
	};
	const std::string& GetFullPath( EImages image );
}

namespace NTextures
{
	using namespace NImages;
	extern std::array< std::unique_ptr<sf::Texture>, size_t( EImages::NUM_OF_IMAGES ) > Textures;
	sf::Texture* GetTexture( EImages image );
	void CreateTextures();
}