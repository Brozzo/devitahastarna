#include "Program.h"
#include "Resources.h"

int main()
{
	NTextures::CreateTextures();

	CProgram Program( sf::VideoMode( 1600, 950 ), "DVH" );
	Program.Run();

	return 0;
}
