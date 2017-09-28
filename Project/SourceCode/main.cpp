#include "Program.h"
#include "Resources.h"
#include "FileSettings.h"

int main()
{
	NFileSettings::SetUpSettings();
	CResources::InitializeInstance();

	CProgram Program( sf::VideoMode( 1024, 720 ), "DVH", sf::Style::Titlebar | sf::Style::Close ); //Not sure if this is correct, but it works :P
	Program.Run();

	return 0;
}
