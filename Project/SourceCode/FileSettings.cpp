
#include "FileSettings.h"

#include <fstream>
#include <iostream>



std::string NFileSettings::ResoursePath; // = [...]/Resources/


void NFileSettings::SetUpSettings()
{
	bool firstIteration = true;
	while (true)
	{
		std::ifstream input;
		input.open("file_settings.txt");
		if (input.is_open())
		{
			input >> NFileSettings::ResoursePath;
		}
		input.close();
		std::string path_confirmed = "PATH_CONFIRMED";
		std::string fileName = "PATH_CONFIRMATION.txt";
		std::string str;
		std::string path;
		input.open(NFileSettings::ResoursePath + fileName);
		if (input.is_open())
		{
			input >> str;
		}
		input.close();
		if (str == path_confirmed)
		{
			if (!firstIteration)
			{
				std::cout << "\n\nResource folder set up correctly. You should not have to do this again :)\n\n";
			}
			return;
		}

		if (firstIteration)
		{
			std::cout << "You haven't set up your resource folder path or it has been moved.\n"
				<< "Please write where you have your resources folder, relative to this program\n"
				<< "Example1: Project/Resources/\n"
				<< "Example2: ../../Resources/\n"
				<< "\nEnter your path here: ";
		}
		else
		{
			std::cout << "\nThe path you entered: " << NFileSettings::ResoursePath << " is invalid. Please try again:\n";
		}
		std::cin >> path;
		if ( path.size() > 0 && path[path.size() - 1] != '/')
		{
			path.push_back('/');
		}
		std::ofstream output;
		output.open("file_settings.txt");
		output << path;
		output.close();
		firstIteration = false;
	}
	return;
}
