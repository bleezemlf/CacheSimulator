#include"cache.h"

using namespace std;

CacheSimulator::CacheSimulator(int set_num, int set_line_num,int block_size = 4):
	_set_num(set_num),
	_set_line_num(set_line_num),
	_block_size(block_size)

	/*_cache_line_num(set_num* set_line_num),
	_address_offset_size(int(log2(block_size))),
	_address_index_size(int(log2(_cache_line_num))),
	_address_tag_size(address_size - _address_index_size - _address_tag_size),
	_cache_line_size(1 + _address_tag_size + 8 * block_size),
	_cache_size(_cache_line_num* _cache_line_size)*/

{
	_cache_line_num = set_num * set_line_num;

	_address_offset_size = int(log2(block_size));
	_address_index_size = int(log2(_cache_line_num));
	_address_tag_size = address_size - _address_index_size - _address_tag_size;
	
	_cache_line_size = 1 + _address_tag_size + 8 * block_size;
	_cache_size = _cache_line_num * _cache_line_size;

	_valid_pos = _cache_line_size - 1;

	_cache = new bitset<64>[_cache_line_num];
	for (int i = 0; i < _cache_line_num; i++)
		_cache[i][_valid_pos] = 0;
}

CacheSimulator::~CacheSimulator()
{
	delete[] _cache;
}

bool CacheSimulator::Hit(bitset<20> address)
{
	int index = 0;
	for (int i = _address_offset_size; i < _address_offset_size + _address_index_size; i++)
		index += address[i] * pow(2, i - _address_offset_size);

	int t1 = index * _set_line_num;
	for (int i = t1; i < t1 + _set_line_num; i++) {
		for (int j = address_size - 1, k = _valid_pos - 1; j > address_size - 1 - _address_tag_size; j--, k--) {
			if (address[j] == _cache[i][k])
				continue;
			else 
				return false;
		}			
	}
	return true;
}

int CacheSimulator::setLineSel()
{
	////
	return 0;
}

int CacheSimulator::replaceLineSel(bitset<20> address)
{
	int index = 0;
	for (int i = _address_offset_size; i < _address_offset_size + _address_index_size; i++)
		index += address[i] * pow(2, i - _address_offset_size);
	return index + setLineSel();
}

void CacheSimulator::cache2CPU()
{
	cout << "hit" << endl;
}

void CacheSimulator::memory2Cache(bitset<20> address)
{
	cout << "miss" << endl;
	int replace_line = replaceLineSel(address);
	if (_cache[replace_line][_valid_pos] == 0)
		_cache[replace_line][_valid_pos] == 1;
	
	for (int i = _valid_pos - 1, j = address_size - 1; i > _valid_pos - 1 - _address_tag_size; i--, j--)
		_cache[replace_line][i] = address[j];

}

void CacheSimulator::cacheSimulate(string file)
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
	vector<bitset<20> >address_vec;
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10004));
	address_vec.push_back(bitset<20>(0x10008));
	address_vec.push_back(bitset<20>(0x1000c));
	address_vec.push_back(bitset<20>(0x10000));
	address_vec.push_back(bitset<20>(0x10010));
	address_vec.push_back(bitset<20>(0x10014));
	address_vec.push_back(bitset<20>(0x1000c));

	for (auto& addr : address_vec) {
		if (Hit(addr))
			cache2CPU();
		else
			memory2Cache(addr);
	}

}

int main()
{
	CacheSimulator cache1(4, 1);
	cache1.cacheSimulate("file");
}
