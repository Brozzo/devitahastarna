#include "Resources.h"

#include <cassert>
#include <array>
#include <string>


std::unique_ptr<CResources> CResources::_pInstance = nullptr;

bool LoadOrOpenFromFile( sf::Music & Object, const std::string & File )
{
	return Object.openFromFile( File );
}
