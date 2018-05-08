#include "Map.h"
#include "CarMap.h"
#include <iostream>


	CarMap::CarMap()       // Create an empty car map.
	{
		Map m_carMap;
	}

	bool CarMap::addCar(std::string license)
		// If a car with the given license plate is not currently in the map, 
		// and there is room in the map, add an entry for that car recording
		// that it has 0 gallons of gas in it, and return true.  Otherwise,
		// make no change to the map and return false.
	{
		if (m_carMap.insert(license, 0))
			return true;
		else
			return false;
	}

	double CarMap::gas(std::string license) const
		// If a car with the given license plate is in the map, return the
		// number of gallons of gas in its tank; otherwise, return -1.
	{
		double a;
		if (m_carMap.get(license, a))
			return a;
		else
			return -1;
		
	}
	bool CarMap::addGas(std::string license, double gallons)
		// If no car with the given license plate is in the map or if
		// gallons is negative, make no change to the map and return
		// false.  Otherwise, increase the number of gallons of gas in the
		// indicated car by the gallons parameter and return true.
	{
		if (!m_carMap.contains(license) || gallons < 0)
			return false;
		else
		{
			m_carMap.update(license, (gas(license) + gallons));
			return true;
		}
	}

	bool CarMap::useGas(std::string license, double gallons)
		// If no car with the given license plate is in the map or if
		// gallons is negative or if gallons > gas(), make no change to the
		// map and return false.  Otherwise, decrease the number of gallons
		// of gas in the indicated car by the gallons parameter and return
		// true.
	{
		if (!m_carMap.contains(license) || gallons < 0 || gallons > gas(license))
			return false;
		else
		{
			m_carMap.update(license, (gas(license) - gallons));
			return true;
		}
	}

	int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
	{
		return m_carMap.size();
	}

	void CarMap::print() const
		// Write to cout one line for every car in the map.  Each line
		// consists of the car's license plate, followed by one space,
		// followed by the number of gallons in that car's tank.  Write
		// no other text.
	{
		for (int i = 0; i < m_carMap.size(); i++)
		{
			std::string lic;
			double gals;
			m_carMap.get(i, lic, gals);
			std::cout << lic << " " << gals << std::endl;
		}
	}