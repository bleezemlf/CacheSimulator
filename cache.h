#include<bitset>
#include<cmath>
#include<fstream>
#include<iostream>
#include<random>
#include<string>
#include<vector>
using namespace std;

const int address_size = 20;
const int write_policy = 1;

class CacheSimBase
{
protected:
	int _set_num;
	int _set_line_num;
	int _data_size;

	int _cache_line_num;
	int _cache_line_size;
	int _cache_size;
	int _valid_pos;
	int _dirty_pos;

	int _tag;
	int _index;

	bitset<20> _address;
	int _address_offset_size;
	int _address_index_size;
	int _address_tag_size;

	int _hit_num;
	int _w_hit_num;
	int _cnt;
	int _w_cnt;
public:
	CacheSimBase(int set_num, int set_line_num, int data_size);
	~CacheSimBase();

	virtual bool Hit() = 0;
	virtual void cache2CPU() = 0;
	virtual void memory2Cache() = 0;
	virtual int replaceLineSel() = 0;
	void cacheSimulate();

	virtual void CPU2Cache() = 0;
	virtual void CPU2Cache2Mem() = 0;
	virtual void cache2Mem() = 0;

};


//直接映射采取顺序结构的cache
class DirectMap :public CacheSimBase
{
private:
	bitset<1024>* _cache;
public:
	DirectMap(int set_num, int data_size = 4);
	~DirectMap();
	bool Hit();
	void cache2CPU();
	void memory2Cache();
	int replaceLineSel() { return _index; }
	void CPU2Cache();
	void CPU2Cache2Mem();
	void cache2Mem();
	//void cacheSimulate();
	void test();
};
//组相联采取各种不同的cache结构

class SetAssociateRandom:public CacheSimBase
{
private:
	bitset<64>* _cache;
	int _replace_line;
public:
	SetAssociateRandom(int set_num, int set_line_num, int data_size = 4);
	~SetAssociateRandom();
	bool Hit();
	void cache2CPU();
	void memory2Cache();
	int replaceLineSel();
	void CPU2Cache();
	void CPU2Cache2Mem();
	void cache2Mem();
	//void cacheSimulate();
	void test();
};

class SetAssociateFIFO :public CacheSimBase
{
private:
	bitset<64>* _cache;
	int* _fifo_q;
	int _replace_line;
public:
	SetAssociateFIFO(int set_num, int set_line_num, int data_size = 4);
	~SetAssociateFIFO();
	bool Hit();
	void cache2CPU();
	void memory2Cache();
	void CPU2Cache();
	void CPU2Cache2Mem();
	void cache2Mem();
	int replaceLineSel();
	//void cacheSimulate();
	void test();
};

class SetAssociateLRU :public CacheSimBase
{
private:
	bitset<64>* _cache;
	int* _LRU_q;
	int _replace_line;
public:
	SetAssociateLRU(int set_num, int set_line_num, int data_size = 4);
	~SetAssociateLRU();
	bool Hit();
	void cache2CPU();
	void memory2Cache();
	int replaceLineSel();
	void CPU2Cache();
	void CPU2Cache2Mem();
	void cache2Mem();
	//void cacheSimulate();
	void test();
};