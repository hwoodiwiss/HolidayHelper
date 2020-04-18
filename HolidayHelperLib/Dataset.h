#pragma once
#include "ISerializable.h"
#include <vector>

using std::vector;
using std::initializer_list;

namespace HolidayHelper::Data
{
	template <typename T> class DataSet : public vector<T>
	{
	public:
		DataSet<T>() {}
		DataSet<T>(initializer_list<T> _ilist) : vector<T>(_ilist) {}

		DataSet<T> Where(bool(*Func)(T));
		template <typename rT> DataSet<rT> Select(rT(*Func)(T));
		T First();

	private:
	};

	template<typename T>
	inline DataSet<T> DataSet<T>::Where(bool(*Func)(T))
	{
		DataSet<T> returnData;

		for (auto Item : (*this))
		{
			if (Func(Item)) returnData.push_back(Item);
		}

		return returnData;
	}

	template<typename T>
	inline T DataSet<T>::First()
	{
		if (*this->size() > 0)
			return this[0];

		throw new std::exception("Array Index out of Bounds!");
	}

	template<typename T>
	template<typename rT>
	inline DataSet<rT> DataSet<T>::Select(rT(*Func)(T))
	{
		DataSet<rT> returnData;

		for (auto Item : (*this))
		{
			returnData.push_back(Func(Item));
		}

		return returnData;
	}

}