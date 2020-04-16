#pragma once
#include "ISerializable.h"
#include "SerializableVector.h"
#include <vector>

using std::vector;
using std::initializer_list;
using HolidayHelper::Persistence::SerializableVector;

namespace HolidayHelper::Data
{
	template <typename T> class DataSet : public vector<T>
	{
	public:
		DataSet<T>() {}
		DataSet<T>(initializer_list<T> _ilist) : vector<T>(_ilist) {}

		DataSet<T> Where(bool(*Func)(T));
		template <typename rT> DataSet<rT> Select(rT(*Func)(T));
		


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