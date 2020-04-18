#pragma once
#include "Common.h"
#include "Page.h"

namespace HolidayHelper::Presentation
{

	class DllExport PageManager
	{
	public:
		PageManager() {};
		void AddPage(string PageName, shared_ptr<Page> pPageObj);
		void SetApplicationHeader(string ApplicationHeader) { m_ApplicationHeader = ApplicationHeader; }
		shared_ptr<Page> GetPage(string PageName);

	private:

		map<string, shared_ptr<Page>> m_PageDictionary;
		string m_ApplicationHeader;
	};
}