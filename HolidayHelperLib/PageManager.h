#pragma once
#include "Common.h"
#include "Page.h"

namespace HolidayHelper::Presentation
{

	class PageManager
	{
	public:
		PageManager() {};
		void AddPage(string PageName, shared_ptr<Page> pPageObj);
		shared_ptr<Page> GetPage(string PageName);

	private:

		map<string, shared_ptr<Page>> m_PageDictionary;
	};
}