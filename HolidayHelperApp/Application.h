#pragma once
#include <HolidayHelperLib/Common.h>
#include <HolidayHelperLib/DataManager.h>
#include <HolidayHelperLib/PageManager.h>
#include <HolidayHelperLib/User.h>

using HolidayHelper::Data::DataManager;
using HolidayHelper::Presentation::PageManager;

class Application
{
public:
	Application();

	//Set the application parameters (Usually just the parameters to main from the runtime)
	void SetParams(int argc, char** argv);

	//Runs the main body of the application
	int Run();

private:

	//Loads data from disk into the data manager
	bool LoadDataStore();

	//Stores the data manager back to disk
	void SaveDataStore();

	//Sets up the pages in the page manager
	void SetupPages();

	void AddDefaultData();

	map<int, string> m_Params;
	map<string, string> m_Options;

	//Data manager is shared_ptr so that it can be passed around to other components of the application in a memory safe way
	std::shared_ptr<DataManager> m_DataManager;
	std::unique_ptr<PageManager> m_PageManager;

};