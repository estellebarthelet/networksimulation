#include "network.h"
#include "random.h"

#include <algorithm>
#include <iostream>
// PEUT ON REMPLACER VALUES.SIZE() PAR SIZE() PARTOUT????

void Network::resize(const size_t &n)
{
	values.resize(n);
	RNG.normal(values);
}



bool Network::add_link(const size_t& n1, const size_t& n2)
{
	if(n1 == n2 or n1 >= values.size() or n2 >= values.size())
		return false;
	else{
				links.insert(std::make_pair(n1, n2));
				links.insert(std::make_pair(n2, n1));
				return true;
	} 
}



size_t Network::random_connect(const double& mean_deg)
{
	links.clear();

	size_t linksNb(0);
	std::mt19937 rng;
	std::uniform_int_distribution<> unif(0, values.size()-1);
	
	for(size_t i=0; i<values.size(); ++i)
	{
		size_t degree(RNG.poisson(mean_deg));

		for(size_t j=1; j<= degree; ++j)
		{
			while(not add_link(i, unif(rng))) continue;
			++linksNb;
		}
	}

	return linksNb;
}



size_t Network::set_values(const std::vector<double>& val)
{
	values.clear();
	values = val;
	return size();
}



size_t Network::size() const
{
	return values.size();
}



size_t Network::degree(const size_t &_n) const
{
	return links.count(_n);
}


double Network::value(const size_t &_n) const
{
	return values[_n];
}



std::vector<double> Network::sorted_values() const
{
	std::vector<double> res (values);
	std::sort(res.begin(), res.end(), std::greater<double>());
	return res;
}


std::vector<size_t> Network::neighbors(const size_t& n) const
{
	std::vector<size_t> neighbors;
	
	if(n < values.size())
	{
		auto l = links.find(n);
		while(l->first == n){
			neighbors.push_back(l->second);
			++l;
		}
	}
	
	return neighbors;
}
bool Network::linkAlreadyExists(const size_t& n1, const size_t& n2){
	for(auto l : links){
			if((l.first == n1 or l.first == n2) and (l.second == n1 or l.second == n2)) //checks if links exists
				return true;
	}
	return false;
}