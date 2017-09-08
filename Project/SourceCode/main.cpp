#include "Program.h"
#include "Resources.h"
#include "FileSettings.h"

int main()
{
	NFileSettings::SetUpSettings();
	CResources::InitializeInstance();

	CProgram Program( sf::VideoMode( 1000, 800 ), "DVH", sf::Style::Titlebar + sf::Style::Close ); //Not sure if this is correct, but it works :P
	Program.Run();

	return 0;
}
