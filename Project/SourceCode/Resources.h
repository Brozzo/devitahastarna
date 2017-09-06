#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <memory>
#include <array>

namespace NResources
{
	const std::string DVHPath( getenv("DVH_PATH") ); //Gets the path to the DVH base-directory from the environment variable DVH_PATH.
	const std::string ResourcesPath( DVHPath + "/Project/Resources/" );
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

namespace NMusic
{
	using namespace NResources;
	const std::string MusicPath( ResourcesPath + "Music/" );
	enum class EMusic
	{
		MAIN_THEME,
		NUM_OF_MUSIC,
	};
	const std::string& GetFullPath( EMusic music );
}

namespace NSounds
{
	using namespace NResources;
	const std::string SoundsPath( ResourcesPath + "Sounds/" );
	enum class ESounds
	{
		TEST_SOUND,
		NUM_OF_SOUNDS,
	};
	const std::string& GetFullPath( ESounds sound );
}
