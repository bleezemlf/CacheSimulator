#include"cache.h"

using namespace std;

CacheSimBase::CacheSimBase(int set_num, int set_line_num, int data_size = 4) :
	_set_num(set_num),
	_set_line_num(set_line_num),
	_data_size(data_size)

{
	_cache_line_num = set_num * set_line_num;

	_address_offset_size = int(log2(data_size));
	_address_index_size = int(log2(_set_num));
	_address_tag_size = address_size - _address_offset_size - _address_index_size;

	_cache_line_size = 1 + _address_tag_size + 8 * data_size;
	_cache_size = _cache_line_num * _cache_line_size;

	_valid_pos = _cache_line_size - 1;

}

CacheSimBase::~CacheSimBase()
{

}


