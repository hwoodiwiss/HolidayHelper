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
		DataSet<T>(vector<T>&& Copy) : vector<T>(Copy) {}
		DataSet<T>(initializer_list<T> _ilist) : vector<T>(_ilist) {}

		T First();
		template <typename Lambda> DataSet<T> Where(Lambda const&lambda);
		template <typename rT> DataSet<rT> Select(rT(*Func)(T));
		bool Contains(const T& Val);
		

	private:
	};


	template<typename T>
	inline T DataSet<T>::First()
	{
		if (this->size() > 0)
			return this->at(0);

		throw new std::exception("Array Index out of Bounds!");
	}


	template<typename T>
	template<typename Lambda>
	inline DataSet<T> DataSet<T>::Where(Lambda const& lambda)
	{
		DataSet<T> returnData;

		for (auto Item : (*this))
		{
			if (lambda(Item) == true) returnData.push_back(Item);
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

	template<typename T>
	inline bool DataSet<T>::Contains(const T& Val)
	{
		for (auto Item : (*this))
		{
			if (Item == Val)
				return true;
		}

		return false;
	}

}