#include "newMap.h"
#include <cstdlib>
#include <iostream>

Map::Map() // Create an empty map (i.e., one with no key/value pairs)
{
	m_currentSize = 0;
	m_maximumSize = DEFAULT_MAX_ITEMS;
	m_pairs = new Pair[m_maximumSize];
}

Map::Map(int size)
{
	if (size < 0)
	{
		std::cout << "error: desired size must not be negative" << std::endl;
		exit(1);
	}
	else
	{
		m_currentSize = 0;
		m_maximumSize = size;
		m_pairs = new Pair[m_maximumSize];
	}
}

Map::~Map()
{
	delete []m_pairs;	//deletes the entire array
}

Map::Map(const Map& mapRef)
{
	m_currentSize = mapRef.size();
	m_maximumSize = mapRef.m_maximumSize;
	m_pairs = new Pair[m_maximumSize];
	for (int i = 0; i < m_maximumSize; i++)
	{
		m_pairs[i] = mapRef.m_pairs[i];
	}
}

Map& Map::operator=(const Map& mapRef)
{
	delete[]m_pairs;
	m_currentSize = mapRef.size();
	m_maximumSize = mapRef.m_maximumSize;
	m_pairs = new Pair[m_maximumSize];
	for (int i = 0; i < m_maximumSize; i++)
	{
		m_pairs[i] = mapRef.m_pairs[i];
	}
	return *this;
}



bool Map::empty() const  // Return true if the map is empty, otherwise false.
{
	if (0 == m_currentSize)
		return true;
	else
		return false;
}
int Map::size() const    // Return the number of key/value pairs in the map.
{
	return m_currentSize;
}
bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
	if (contains(key) || m_currentSize == m_maximumSize)
		return false;
	m_pairs[m_currentSize].m_key = key;
	m_pairs[m_currentSize].m_value = value;
	m_currentSize++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	for (int i = 0; i < m_currentSize; i++)
	{
		if (m_pairs[i].m_key == key)
		{
			m_pairs[i].m_value = value;
			return true;
		}
	}
	return false;
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
	if (!update(key, value))
	{
		if (!insert(key, value))
			return false;
	}
	return true;
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	for (int i = 0; i < m_currentSize; i++)
	{
		if (m_pairs[i].m_key == key)
		{
			m_pairs[i].m_key = m_pairs[m_currentSize - 1].m_key;
			m_pairs[i].m_value = m_pairs[m_currentSize - 1].m_value;
			m_currentSize--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	for (int i = 0; i < m_currentSize; i++)
	{
		if (m_pairs[i].m_key == key)
			return true;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	for (int i = 0; i < m_currentSize; i++)
	{
		if (m_pairs[i].m_key == key)
		{
			value = m_pairs[i].m_value;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
	if (0 <= i && i < this->size())
	{
		key = m_pairs[i].m_key;
		value = m_pairs[i].m_value;
		return true;
	}
	return false;
}

void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
	Map mapHolder = *this;	//this will execute through maxSize because of the implementation of the copy constructor
	*this = other;			//this will also execute through maxSize because of the implementation of the assignment operator
	other = mapHolder;		//^Same^ (assignment operator)
}