#include"cache.h"
using namespace std;

SetAssociateLRU::SetAssociateLRU(int set_num, int set_line_num, int data_size) :
	CacheSimBase(set_num, set_line_num, data_size)
{
	_replace_line = 0;
	_cache = new bitset<64>[_cache_line_num];
	for (int i = 0; i < _cache_line_num; i++)
		_cache[i][_valid_pos] = 0;

	_LRU_q = new int[_cache_line_num];
	for (int i = 0; i < _cache_line_num; i++)
		_LRU_q[i] = 0;
}

SetAssociateLRU::~SetAssociateLRU()
{
	delete[] _cache;
	delete[] _LRU_q;
}

bool SetAssociateLRU::Hit()
{
	int t1 = _index * _set_line_num;
	bool t2 = false;
	for (int i = t1; i < t1 + _set_line_num; i++) {
		_replace_line = i;
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

void SetAssociateLRU::cache2CPU()
{
	//cout << "hit" << endl;
	int t1 = _index * _set_line_num;
	for (int i = t1; i < t1 + _set_line_num; i++)
		_LRU_q[i]++;
	_LRU_q[_replace_line] = 0;
}

void SetAssociateLRU::memory2Cache()
{
	//cout << "miss" << endl;
	int replace_line = replaceLineSel();
	int t1 = _index * _set_line_num;
	for (int i = t1; i < t1 + _set_line_num; i++)
		_LRU_q[i]++;
	_LRU_q[_replace_line] = 0;

	if (_cache[replace_line][_valid_pos] == 0)
		_cache[replace_line][_valid_pos] = 1;

	if (write_policy == 1)
		if (_cache[_replace_line][_dirty_pos] == 1)
			cache2Mem();

	for (int i = _valid_pos - 1, j = address_size - 1;
		i > _valid_pos - 1 - _address_tag_size;
		i--, j--)
	{
		_cache[replace_line][i] = _address[j];
	}
}

void SetAssociateLRU::CPU2Cache()
{
	_cache[_replace_line][_dirty_pos] = 1;
}

void SetAssociateLRU::cache2Mem()
{
	_cache[_replace_line][_dirty_pos] = 0;
}

void SetAssociateLRU::CPU2Cache2Mem()
{

}

int SetAssociateLRU::replaceLineSel()
{
	int t1 = _index * _set_line_num;
	_replace_line = t1;
	int max = _LRU_q[t1];
	for (int i = t1; i < t1 + _set_line_num; i++) {
		if (max < _LRU_q[i]) {
			max = _LRU_q[i];
			_replace_line = i;
		}
	}
	
	return _replace_line;
}

void SetAssociateLRU::test()
{
	vector<bitset<20> >address_vec;
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10004));
	address_vec.push_back(bitset<20>(0x10008));
	address_vec.push_back(bitset<20>(0x1000c));
	address_vec.push_back(bitset<20>(0x10004));
	address_vec.push_back(bitset<20>(0x10008));
	address_vec.push_back(bitset<20>(0x10010));
	address_vec.push_back(bitset<20>(0x10000));
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
		//cout << _LRU_q[0] << " " << _LRU_q[1] << " " << _LRU_q[2] << " " << _LRU_q[3] << endl;
	}
}