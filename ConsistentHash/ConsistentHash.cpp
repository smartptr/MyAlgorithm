#include <map>
#include <string>
#include <iostream>

#include "consistentHash.h"

struct SdbmHash
{
	size_t operator()(const char* str) const
	{
		size_t hash = 0;
		int c;
		while((c = *str++))
			hash = c + (hash << 6) + (hash << 16) - hash;
		return hash;
	}
};

//cache sever class
class CacheSever
{
public:
	typedef std::map<std::string, std::string> StringMap;
	void put(const std::string& key, const std::string& value)
	{
		cache_[key] = value;
	}
	std::string Get(const std::string& key)const
	{
		std::string value;
		StringMap::const_iterator it = cache_.find(key);
		if(it != cache_.end())
			value = it->second;
		return value;
	}
	void remove(const std::string& key)
	{
		StringMap::iterator it = cache_.find(key);
		if(it != cache_.end())
			cache_.erase(it);
	}

private:
	StringMap cache_;
};

int main()
{
	typedef std::map<std::string, CacheSever> SeverMap;
	SeverMap sever;
	ConsistentHash::HashRing<std::string, std::string, SdbmHash> ring(10, SdbmHash());
	//cache severs
	sever["127.0.0.1"] = CacheSever();
	sever["192.168.0.213"] = CacheSever();
	sever["168.152.143.2"] = CacheSever();
	// add cache hash
	for (SeverMap::const_iterator it = sever.begin(); it != sever.end(); ++it)
	{
		std::cout << "Adding " << it->first << " with hash: " << ring.AddNode(it->first) << std::endl;
	}
	//store data
	const char* fruits[] = {"apple", "peer", "banana", "orange", "cherry", "apricot"};
	const char* color[] = {"red", "green", "yellow", "orange", "black", "pink"};
	//std::cout <<   sizeof(fruits) << std::endl;
	const unsigned int numfruits = sizeof(fruits) / sizeof(numfruits);
	//store
	for (unsigned int f = 0; f < numfruits; ++f)
	{
		std::string host = ring.GetNode(fruits[f]);
		std::cout << "Storing: " << fruits[f]  << " on sever: " << host << std::endl;
		sever[host].put(fruits[f], color[f]);
	}
    //read it back
	for (unsigned int f = 0; f < numfruits; ++f)
	{
		std::string host = ring.GetNode(fruits[f]);
		std::string color1 = sever[host].Get(fruits[f]);
		std::cout << "Found: " << fruits[f]  << " on sever: " << host << " (" << color1 << ")" << std::endl;
	}
	system("pause");
	return 0;
}
