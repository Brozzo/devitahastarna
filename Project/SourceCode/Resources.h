#pragma once

#include "FileSettings.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <memory>
#include <array>

template<typename SFMLObject_t>
bool LoadOrOpenFromFile( SFMLObject_t& Object, const std::string& File )
{
	return Object.loadFromFile( File );
}
bool LoadOrOpenFromFile( sf::Music& Object, const std::string& File );

template<typename EResourceType, typename SFMLObject_t>
class CResourceStorage
{
	constexpr static size_t NUM_OF = static_cast<size_t>(EResourceType::NUM_OF);
public:
	CResourceStorage( const std::string& FolderName, const std::array< std::string, NUM_OF >& FileNames )
	{
		for ( size_t i = 0; i < NUM_OF; ++i )
		{
			_CompletePaths[i] = NFileSettings::ResoursePath + FolderName + FileNames[i];

			_SFMLObjects[i].reset( new SFMLObject_t() );
			LoadOrOpenFromFile( *_SFMLObjects[i], _CompletePaths[i] );
		}
	}
	SFMLObject_t& GetSFMLObject( EResourceType tag ) const
	{
		const size_t nIndex = static_cast<size_t>(tag);
		//assert( nIndex < NUM_OF && nIndex >= 0 );
		return *_SFMLObjects[nIndex];
	}
	SFMLObject_t& AccessSFMLObject( EResourceType tag ) const
	{
		const size_t nIndex = static_cast<size_t>(tag);
		//assert( nIndex < NUM_OF && nIndex >= 0 );
		return *_SFMLObjects[nIndex];
	}
private:
	std::array< std::string, NUM_OF > _CompletePaths;
	std::array< std::unique_ptr<SFMLObject_t>, NUM_OF > _SFMLObjects;
};

namespace NImages
{
	enum class EImages
	{
		TEST_IMAGE,
		PLAYER,
		NUM_OF,
	};
	static const std::array< std::string, size_t( EImages::NUM_OF ) > FileNames
	{
		"image.png",
		"ship.png",
	};
}
namespace NMusic
{
	enum class EMusic
	{
		MAIN_THEME,
		NUM_OF,
	};
	static const std::array< std::string, size_t( EMusic::NUM_OF ) > FileNames
	{
		"main_theme.ogg",
	};
}
namespace NSounds
{
	enum class ESounds
	{
		TEST_SOUND,
		NUM_OF,
	};
	static const std::array< std::string, size_t( ESounds::NUM_OF ) > FileNames
	{
		"bubbling.wav",
	};
}

class CResources
{
private:
	CResources() {}
public:
	static void InitializeInstance() { _pInstance.reset( new CResources() ); }

	static sf::Texture& AccessTexture( NImages::EImages tag ) { return _pInstance->_Images.AccessSFMLObject( tag ); }
	static sf::Music& AccessMusic( NMusic::EMusic tag ) { return _pInstance->_Music.AccessSFMLObject( tag ); }
	static sf::SoundBuffer& AccessSound( NSounds::ESounds tag ) { return _pInstance->_Sounds.AccessSFMLObject( tag ); }
private:
	static std::unique_ptr<CResources> _pInstance;

	CResourceStorage<NImages::EImages, sf::Texture> _Images { "Images/", NImages::FileNames };
	CResourceStorage<NMusic::EMusic, sf::Music> _Music { "Music/", NMusic::FileNames };
	CResourceStorage<NSounds::ESounds, sf::SoundBuffer> _Sounds { "Sounds/", NSounds::FileNames };
};



