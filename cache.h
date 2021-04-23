#include<bitset>
#include<cmath>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int address_size = 20;

class CacheSimulator
{
private:
	int _set_num;
	int _set_line_num;
	int _block_size;

	int _cache_line_num;
	int _cache_line_size;
	int _cache_size;
	int _valid_pos;

	int _address_offset_size;
	int _address_index_size;
	int _address_tag_size;

	bitset<64>* _cache;

public:
	CacheSimulator(int set_num, int set_line_num,int block_size);
	~CacheSimulator();
	void cacheSimulate(string file);
	bool Hit(bitset<20>);
	void cache2CPU();
	void memory2Cache(bitset<20> address);
	int replaceLineSel(bitset<20> address);
	int setLineSel();
};