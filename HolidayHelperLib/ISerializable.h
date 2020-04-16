#pragma once
#include <iostream>
#include "Common.h"

namespace HolidayHelper::Persistence
{

	//Abstract interface for serializing objects to disk
	class DllExport ISerializable
	{
	public:

		//Pure virtual functions that have to be overloaded in derived classes
		virtual std::ostream& Serialize(std::ostream& os) = 0;
		virtual std::istream& Deserialize(std::istream& is) = 0;

		//virtual std::ostream& Serialize(map<string, string>& om) = 0;
		//virtual std::istream& Deserialize(map<string, string>& im) = 0;

		//Out stream operator, allows operator based stream interaction for ISerializabe objects
		friend std::ostream& operator <<(std::ostream& os, ISerializable& outObj)
		{
			//This will call the ISerializable::Serialize as defined in a derived object
			return outObj.Serialize(os);
		}

		//In stream operator, allows operator based stream interaction for ISerializabe objects
		friend std::istream& operator >>(std::istream& is, ISerializable& inObj)
		{
			//This will call the ISerializable::Deserialize as defined in a derived object
			return inObj.Deserialize(is);
		}

	protected:

		//Helper function for properly reading in a string from istream
		inline std::string InStreamToString(std::istream& in);


	};
}