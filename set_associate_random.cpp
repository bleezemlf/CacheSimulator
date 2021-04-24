#include"cache.h"
using namespace std;
SetAssociateRandom::SetAssociateRandom(int set_num, int set_line_num, int data_size):
	CacheSimBase(set_num,set_line_num,data_size)
{
	_cache = new bitset<64>[_cache_line_num];
	for (int i = 0; i < _cache_line_num; i++)
		_cache[i][_valid_pos] = 0;
}

SetAssociateRandom::~SetAssociateRandom()
{
	delete[] _cache;
}

bool SetAssociateRandom::Hit()
{
	int t1 = _index * _set_line_num;
	bool t2 = false;
	for (int i = t1; i < t1 + _set_line_num; i++) {
		if (_cache[i][_valid_pos] == 0) {
			continue;
		}
		for (int j = address_size - 1, k = _valid_pos - 1; 
			j > address_size - 1 - _address_tag_size;
			j--, k--) 
		{
			t2 = true;
			if (_address[j] == _cache[i][k])
				continue;
			else {
				t2 = false;
				break;
			}
		}
		if (t2 == true)
			break;
	}
	return t2;
}

void SetAssociateRandom::cache2CPU()
{
	//cout << "hit" << endl;
}

void SetAssociateRandom::memory2Cache()
{
	//cout << "miss" << endl;
	int replace_line = replaceLineSel();
	if (_cache[replace_line][_valid_pos] == 0)
		_cache[replace_line][_valid_pos] = 1;

	for (int i = _valid_pos - 1, j = address_size - 1; 
			i > _valid_pos - 1 - _address_tag_size;
			i--, j--)
		_cache[replace_line][i] = _address[j];
}

int SetAssociateRandom::replaceLineSel()
{
	static default_random_engine random(time(0));
	static uniform_int_distribution<int> dis1(0, _set_line_num - 1);
	int t1 = 0;
	t1 = dis1(random) + _index * _set_line_num;
	return t1;
}

void SetAssociateRandom::test()
{
	vector<bitset<20> >address_vec;
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10000));
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