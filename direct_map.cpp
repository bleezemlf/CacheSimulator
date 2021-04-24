#include"cache.h"
using namespace std;

DirectMap::DirectMap(int set_num, int data_size) :CacheSimBase(set_num, 1, data_size)
{
	_cache = new bitset<64>[_cache_line_num];
	for (int i = 0; i < _cache_line_num; i++)
		_cache[i][_valid_pos] = 0;
}

DirectMap::~DirectMap()
{
	delete[] _cache;
}

bool DirectMap:: Hit()
{
	int t1 = _index;
	if (_cache[_index][_valid_pos] == 0)
		return false;
	for (int j = address_size - 1, k = _valid_pos - 1; j > address_size - 1 - _address_tag_size; j--, k--) {
		if (_address[j] == _cache[t1][k])
			continue;
		else
			return false;
	}
	return true;
}

void DirectMap::cache2CPU()
{
	cout << "hit" << endl;
}

void DirectMap::memory2Cache()
{
	cout << "miss" << endl;
	if (_cache[_index][_valid_pos] == 0)
		_cache[_index][_valid_pos] = 1;

	for (int i = _valid_pos - 1, j = address_size - 1; i > _valid_pos - 1 - _address_tag_size; i--, j--)
		_cache[_index][i] = _address[j];
}

void DirectMap::cacheSimulate(string file)
{
	/*
	char raw_address[13];
	ifstream ifs;
	ifs.open(file, ios::in);
	while (!ifs.eof()){
		ifs.getline(raw_address, 13);
		////raw_address -> bitset<20> address
		bitset<20> address;
		if (Hit(address))
			cache2CPU();
		else
			memory2Cache(address);
	}
	ifs.close();
	*/


}

void DirectMap::test()
{
	vector<bitset<20> >address_vec;
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10004));
	address_vec.push_back(bitset<20>(0x10008));
	address_vec.push_back(bitset<20>(0x1000c));
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10014));
	address_vec.push_back(bitset<20>(0x1000c));
	for (auto& addr : address_vec) {
		_address = addr;
		_index = 0;
		for (int i = _address_offset_size; i < _address_offset_size + _address_index_size; i++)
			_index += _address[i] * pow(2, i - _address_offset_size);
		_tag = 0;
		for (int i = _address_offset_size + _address_index_size; i < address_size; i++)
			_tag += _address[i] * pow(2, i - _address_offset_size - _address_index_size);
		if (Hit())
			cache2CPU();
		else
			memory2Cache();
	}
}