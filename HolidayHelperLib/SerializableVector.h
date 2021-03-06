#pragma once
#include <vector>
#include <type_traits>
#include "Common.h"
#include "ISerializable.h"
#include "Dataset.h"

using HolidayHelper::Data::DataSet;
using namespace HolidayHelper::Data;

namespace HolidayHelper::Persistence
{

	//Note that this converts the type to always be stored internally as shared pointers
	template<typename T> class SerializableVector : public DataSet<shared_ptr<T>>, public ISerializable
	{
		//Fails compilation if this container is used for a class that does not inherit ISerializable
		static_assert(std::is_base_of<ISerializable, T>::value, "T must inherit from ISerialiazable");
	public:
		SerializableVector() : DataSet<shared_ptr<T>>() {}

		std::ostream& Serialize(std::ostream& out)
		{
			size_t size = this->size();
			out.write(reinterpret_cast<char*>(&size), sizeof(size_t));
			for (size_t i = 0; i != size; i++)
			{
				out << *(this->at(i));
			}

			return out;
		}

		std::istream& Deserialize(std::istream& in)
		{
			size_t numElements = 0;
			in.read(reinterpret_cast<char*>(&numElements), sizeof(size_t));
			//Resize once to avoid reallocations at capacity boundaries
			this->resize(numElements);
			for (size_t index = 0; index < numElements; index++)
			{
				shared_ptr<T> currItem = shared_ptr<T>(new T());
				in >> *currItem;
				this->at(index) = currItem;
			}

			return in;
		}
	};

}