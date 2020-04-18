#include "Page.h"
#include "Input.h"

using HolidayHelper::Utils::Input;

namespace HolidayHelper::Presentation
{
	string Page::ExecutePage(string prevPage, string ApplicationHeader, shared_ptr<DataManager> appDataStore, shared_ptr<User>& currentUser)
	{
		system("cls");
		cout << ApplicationHeader << endl;
		if (currentUser != nullptr)
		{
			cout << "User: " << currentUser->GetUsername() << endl << "Type: " << currentUser->GetUserTypeString() <<  endl;
		}
		return Execute(prevPage, appDataStore, currentUser);
	}

	void Page::AddPageAction(int key, string value)
	{
		m_PageActions.insert(pair<int, string>(key, value));
	}

	bool Page::IsLoggedIn(shared_ptr<User> currentUser)
	{
		if (currentUser != nullptr && currentUser->GetUserType() > 0)
		{
			return true;
		}

		return false;
	}

	int Page::GetUserPageAction()
	{
		int UserOption = INT_MIN;
		while (m_PageActions.find(UserOption) == m_PageActions.end())
		{
			cout << "Please enter an option:" << endl;
			UserOption = Input::GetUserInt();

			if (m_PageActions.find(UserOption) == m_PageActions.end())
			{
				cout << "Invalid Option!" << endl;
			}
		}

		return UserOption;
	}

}
