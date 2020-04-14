#pragma once
#include <vector>

using std::vector;
using std::initializer_list;

template <typename T> class DataSet : public vector<T>
{
public:
	DataSet<T>() {}
	DataSet<T>(initializer_list<T> _ilist) : vector<T>(_ilist) {}

	DataSet<T> Where(bool(*Func)(T));
	template <typename rT> DataSet<rT> Select(rT(*Func)(T))
	{
		DataSet<rT> returnData;

		for (auto Item : (*this))
		{
			returnData.push_back(Func(Item));
		}

		return returnData;
	}


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
