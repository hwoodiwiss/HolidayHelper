#include "Application.h"
#include <HolidayHelperLib/User.h>
#include <HolidayHelperLib/DataManager.h>
#include <HolidayHelperLib/Page.h>
#include <HolidayHelperLib/Location.h>
#include <HolidayHelperLib/Activity.h>

//Application Page Types
#include "WelcomePage.h"
#include "CreateUserPage.h"
#include "LoginPage.h"
#include "LogoutPage.h"
#include "AdminMainPage.h"
#include "MainPage.h"
#include "PreviousEstimatePage.h"
#include "NewEstimatePage.h"
#include "ManageCustomersPage.h"
#include "ManageLocationsPage.h"
#include "ManageUsersPage.h"

#include <fstream>




using ifstream = std::ifstream;
using ofstream = std::ofstream;
using std::cout;
using std::cin;
using HolidayHelper::Presentation::Page;
using HolidayHelper::Presentation::PageManager;
using HolidayHelper::Data::Activity;
using HolidayHelper::Data::Location;
namespace fs = std::filesystem;

const string ApplicationHeader = R"(
                      ___
                      \\ \
                       \\ `\
    ___                 \\  \
   |    \                \\  `\
   |_____\                \    \
   |______\                \    `\
   |       \                \     \
   |      __\__---------------------------------._.
 __|---~~~__o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_[][\__
|___                         /~      )                \__
    ~~~---..._______________/      ,/_________________/
                           /      /
                          /     ,/
                         /     /
                        /    ,/
                       /    /
                      //  ,/
                     //  /
                    // ,/
                   //_/
               _  _      _                              _                      _     ___  
  /\  /\ ___  | |(_)  __| |  __ _  _   _    /\  /\ ___ | | _ __    ___  _ __  / |   / _ \ 
 / /_/ // _ \ | || | / _` | / _` || | | |  / /_/ // _ \| || '_ \  / _ \| '__| | |  | | | |
/ __  /| (_) || || || (_| || (_| || |_| | / __  /|  __/| || |_) ||  __/| |    | | _| |_| |
\/ /_/  \___/ |_||_| \__,_| \__,_| \__, | \/ /_/  \___||_|| .__/  \___||_|    |_|(_)\___/ 
                                   |___/                  |_|                             
)";


Application::Application()
{
	m_DataManager = nullptr;
}


void Application::SetParams(int argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		string fullParam = string(argv[i]);

		//Pushes the raw parameter string to the parameters vector
		m_Params.insert(std::pair<int, string>(i, fullParam));

		size_t eqIndex = fullParam.find('=');

		//If there's no equals, this is just a parameter, not an option, skip to next
		if (eqIndex == -1)
		{
			continue;
		}

		string optName = fullParam.substr(0, eqIndex);

		//Specify Ui64 to surpress "Potential overflow" warning. Honestly overkill.
		string optValue = fullParam.substr(eqIndex + 1Ui64);

		//Push option key-value pair to the options map
		m_Options.insert(std::pair<string, string>(optName, optValue));

	}
}

//Application Run takes on the role of main
int Application::Run()
{
	//Initialise data and page managers
	m_DataManager = shared_ptr<DataManager>(new DataManager());
	m_PageManager = unique_ptr<PageManager>(new PageManager());
	shared_ptr<User> appUser = nullptr;

	//Loads data from disk into DataManager
	if (!LoadDataStore())
	{
		if (m_DataManager->FindUser("Administrator") == nullptr)
		{
			//If the default admin doesn't exist, create it
			GUID Id;
			if (CoCreateGuid(&Id) != S_OK)
			{
				//Something has gone very wrong
				return -1;
			}

			auto DefaultUser = shared_ptr<User>(new User(Id, "Administrator", "admin", true, UserType::UT_ADMIN));
			m_DataManager->AddUser(DefaultUser);
		}

		AddDefaultData();
		
	}

	//Setup application pages
	SetupPages();

	//Gets the welcome page from the page manager, this is the entrypoint page to the core systems pages
	shared_ptr<Page> currPageObj = m_PageManager->GetPage("Welcome");

	//Vars to store the names of the next and previous pages
	string nextPage;
	string prevPage = "";
	while (currPageObj != nullptr)
	{
		//Temporary storage for next page so that we can assign it to prev page after executing the next page
		//This is necesary as the prevPage is used to gave an avenue to navigate "back" in a page
		string prevNextPage = nextPage;

		//Execute the current page and store the result in next page
		nextPage = currPageObj->ExecutePage(prevPage, ApplicationHeader, m_DataManager, appUser);

		//Set prevPage to the value of prevNextPage, for use next iteration
		prevPage = prevNextPage;

		//Set the current page object to the page with the name that was returned from executing the previous page
		//Will return nullptr if no page is found or if nextPage is empty
		currPageObj = m_PageManager->GetPage(nextPage);
	}

	//After the core page loop ends, store contents of the data manager back to disk
	SaveDataStore();

	return 0;
}

bool Application::LoadDataStore()
{
	//Load application data from the filesystem
	std::error_code relPathError;
	auto curr = fs::current_path();
	fs::path pathDataStore = fs::absolute(fs::path(L".\\HolidayHelper.data"), relPathError);

	if (std::filesystem::exists(pathDataStore))
	{
		m_DataManager->Load(pathDataStore);
	}
	else
	{
		//Create default empty file if it doesn't exist
		ofstream outStream(pathDataStore.c_str(), std::ios::binary);
		outStream.close();
		
		//Set the update path for internal updates
		m_DataManager->SetUpdatePath(pathDataStore);

		return false;
	}

	return true;
}

void Application::SaveDataStore()
{
	//Load application data from the filesystem
	std::error_code relPathError;
	auto curr = fs::current_path();
	fs::path pathDataStore = fs::absolute(fs::path(L".\\HolidayHelper.data"), relPathError);

	m_DataManager->Save(pathDataStore);
}

void Application::SetupPages()
{
	m_PageManager->AddPage("Welcome", shared_ptr<Page>(new WelcomePage()));
	m_PageManager->AddPage("Login", shared_ptr<Page>(new LoginPage()));
	m_PageManager->AddPage("CreateUser", shared_ptr<Page>(new CreateUserPage()));
	m_PageManager->AddPage("Logout", shared_ptr<Page>(new LogoutPage()));
	m_PageManager->AddPage("Main", shared_ptr<Page>(new MainPage()));
	m_PageManager->AddPage("AdminMain", shared_ptr<Page>(new AdminMainPage()));
	m_PageManager->AddPage("PreviousEstimate", shared_ptr<Page>(new PreviousEstimatePage()));
	m_PageManager->AddPage("NewEstimate", shared_ptr<Page>(new NewEstimatePage()));
	m_PageManager->AddPage("ManageCustomers", shared_ptr<Page>(new ManageCustomersPage()));
	m_PageManager->AddPage("ManageUsers", shared_ptr<Page>(new ManageUsersPage()));
	m_PageManager->AddPage("ManageLocations", shared_ptr<Page>(new ManageLocationsPage()));
}

void Application::AddDefaultData()
{
	shared_ptr<Location> Florida = Location::Create("Florida", 1300.0f, 4);
	shared_ptr<Location> Paris = Location::Create("Paris", 600.0f, 2);
	shared_ptr<Location> Milan = Location::Create("Milan", 950.0f, 2);
	shared_ptr<Location> Tokyo = Location::Create("Tokyo", 1800.0f, 4);

	//Anonymous vector notation, it's clean, it makes me happy.
	m_DataManager->AddLocations({ Florida, Paris, Milan, Tokyo });

	auto ThemePark = Activity::Create("Theme Park", 80.0f, false);
	m_DataManager->AddActivity(ThemePark, { Florida, Paris, Tokyo });

	auto GuidedTour = Activity::Create("Guided Tours", 35.0f, false);
	m_DataManager->AddActivity(GuidedTour, { Paris, Milan, Tokyo });

	auto SkyDiving = Activity::Create("Sky Diving", 110.0f, false);
	m_DataManager->AddActivity(SkyDiving, { Florida });

	m_DataManager->Update();
}
