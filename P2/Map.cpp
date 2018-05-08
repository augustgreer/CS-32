#include "Map.h"

Map::Map()
{
	head = nullptr;
	tail = nullptr;
	m_size = 0;
}

Map::~Map()		//Map destructor
{
	Node* p = head;		//create an active pointer p
	while (p != nullptr)	//loop through list (if Map is empty, the destructor does nothing)
	{
		Node* n = p->next;		//create a pointer to hold p's next for when p is deleted
		delete p;
		p = n;			//iterate p to the next node
	}
}

Map::Map(const Map& mapRef)
{
	m_size = 0;		//constructor
	head = nullptr;
	tail = nullptr;

	for (int i = 0; i < mapRef.size(); i++)
	{
		KeyType key;
		ValueType value;

		mapRef.get(i, key, value);
		insert(key, value);
	}
	/*Node* h2 = mapRef.head;		//ptr to top of Map being copied
	if (h2 != nullptr)			//at beggining, make sure copy map has nodes
	{
		{
			head = new Node;			//allocate new
			head->m_key = h2->m_key;	//set the member variables of the new node to corresponding node of copy map
			head->m_value = h2->m_value;
			head->prev = nullptr;
		}
		h2 = mapRef.head->next;		//iterate copy map ptr
		Node* h1 = head;			//create new map ptr
		while (h2 != nullptr)		//loops until end of copy map
		{
			h1->next = new Node;		//new node in new map
			h1->next->prev = h1;		//set the prev to ptr ahead before iterating the ptr
			h1 = h1->next;				//iterate new map ptr
			h1->m_key = h2->m_key;		//set the member variables of the new node to corresponding node of copy map
			h1->m_value = h2->m_value;
			h1->next = nullptr;			//set next to null in case this is the last node (will be overwritten later if necessary)
			if (h2->next == nullptr)
				tail = h1;
			h2 = h2->next;				//iterate copy map ptr
		}
	}
}
*/
	//excess code
	//after writing all the functions, I realized there were much easier way to implement
}
Map& Map::operator=(const Map& mapRef)
{
	Map holder(mapRef);		//this should create another mapRef using the copy constructor
	swap(holder);			//and swap this and the map holder without messing with the actual mapRef
	/*Node* p;		//create an active pointer p
	p = head;
	while (p != nullptr)	//loop through list (if Map is empty, the destructor does nothing)
	{
		Node* n = p->next;		//create a pointer to hold p's next for when p is deleted
		delete p;
		p = n;			//iterate p to the next node
	}
	
	return Map(mapRef);   //call the copy constructor and return the newly copied map
	*/
	//excess code
	//after writing all the functions, I realized there were much easier way to implement
	return *this;
}

bool Map::empty() const
{
	if (m_size == 0)
		return true;
	else
		return false;
	/*
	if (head == nullptr)		//a nullptr indicates emptiness
		return true;
	else
		return false;			//if there are nodes, it's not empty
		*/
}

int Map::size() const
{
	/*
	int size = 0;
	Node* p = head;			//create a ptr to top of Map
	while (p != nullptr)	//go through all nodes
	{
		size++;				//iterate size
		p = p->next;		//iterate the ptr
	}
	return size;		//return how many loops were completed (note: an empty map will skip the while loop and still return 0 because size was initialized to zero)
	*/
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (contains(key))	//make sure the node doesn't already exist
		return false;

	if (empty())		//special case for when the map is empty
	{
		head = new Node;
		tail = head;
		head->pair.m_key = key;
		head->pair.m_value = value;
		head->next = nullptr;
		head->prev = nullptr;
		m_size++;
	}

	//this will add a new node to the end of the map if it isn't already in the map
	else
	{
		Node*p = tail;
		tail->next = new Node;
		tail = tail->next;
		tail->pair.m_key = key;
		tail->pair.m_value = value;
		tail->next = nullptr;
		tail->prev = p;
		m_size++;
	}

	return true;
	/*Node* p = head;
	while (p != nullptr)
	{
		if (p->pair.m_key == key)
			return false;
		if (p->next == nullptr)
			break;
		p = p->next;
	}
	p->next = new Node;
	p->next->pair.m_key = key;
	p->next->pair.m_value = value;
	p->next->prev = p;
	p->next->next = nullptr;
	tail = p->next;
	return true;*/
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->pair.m_key == key)
		{
			p->pair.m_value = value;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (!update(key, value))
		insert(key, value);
	return true;
}

bool Map::erase(const KeyType& key)
{
	//simple checks before running loops
	if (!contains(key) || m_size == 0) //doesn't contain/ empty
		return false;

	Node* p = head;

	if (m_size == 1)	//this catches when the Map holds one node because it could dereference nullptr below otherwise 
	{
		m_size--;
		delete head;
		head = nullptr;
		tail = nullptr;
		return true;
	}

	while (p != nullptr)
	{
		if (p->pair.m_key == key)		//if there's a match
		{
			if (p == head)				//special case when the match is the first node
			{
				head = p->next;
				head->prev = nullptr;
				delete p;
			}
			else if (p == tail)				//special case when the match is the last node
			{
				tail = p->prev;
				tail->next = nullptr;
				delete p;
			}
			else						//case when the match is surrounded by other nodes
			{
				p->prev->next = p->next;
				p->next->prev = p->prev;
				delete p;
			}
			m_size--;			//decrement the size after a delete
			return true;
		}
		else
			p = p->next;
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	Node* p = head;

	while (p != nullptr)		//loop until the end
	{
		if (p->pair.m_key == key)	//if there's a match, true
			return true;
		else
			p = p->next;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	/*if (!contains(key))
		return false;
*/
	Node* p = head;
	while (p != nullptr)
	{
		if (p->pair.m_key == key)
		{
			value = p->pair.m_value;
			return true;
		}
		else
			p = p->next;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= size())	//if the ith element doesn't exist
		return false;
	else
	{
		Node* p = head;
		for (int count = 0; count < i; count++)	//loop until ith position (note: the zero'th element will skip this and properly set the parameter to the first Node's value)
			p = p->next;
		key = p->pair.m_key;
		value = p->pair.m_value;
	}
	return true;
}

void Map::swap(Map& other)		//this will run the same # of statements no matter the size of each Map
{
	int tempSize = m_size;		//swap sizes
	m_size = other.m_size;
	other.m_size = tempSize;

	Node* tempHead = head;	//swap head pointer
	head = other.head;
	other.head = tempHead;

	Node* tempTail = tail;		//swap tail pointer
	tail = other.tail;
	other.tail = tempTail;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
	result = m1;
	bool returnValue = true;
	for (int i = 0; i < m2.size(); i++)	//loop through the size of m1 (we can't say result.size() because it will change as we update it)
	{
		KeyType key;				//create variables to store pairs currently under investigation for m2
		ValueType value;
		m2.get(i, key, value);
		if (result.contains(key))
		{
			ValueType value2;			//variable for value in m1 under investigation
			result.get(key, value2);

			if (value != value2)
			{
				result.erase(key);
				returnValue = false;
			}
		}
		else
			result.insert(key, value);
	}
	return returnValue;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	result = m1;
	for (int i = 0; i < m1.size(); i++)	//loop through the size of m1 (we can't say result.size() because it will change as we update it)
	{
		KeyType key;				//create variables to store pairs currently under investigation for m2
		ValueType value;
		m2.get(i, key, value);
		if (result.contains(key))	//if result has the same key as m2, subtract it from result
		{
			result.erase(key);
		}
	}
}