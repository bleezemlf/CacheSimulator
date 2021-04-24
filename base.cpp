#include"cache.h"

using namespace std;

CacheSimBase::CacheSimBase(int set_num, int set_line_num, int data_size = 4) :
	_set_num(set_num),
	_set_line_num(set_line_num),
	_data_size(data_size),
	_hit_num(0),
	_cnt(0)

{
	_cache_line_num = set_num * set_line_num;

	_address_offset_size = int(log2(data_size));
	_address_index_size = int(log2(_set_num));
	_address_tag_size = address_size - _address_offset_size - _address_index_size;

	//_cache_line_size = 1 + _address_tag_size + 8 * data_size;
	_cache_line_size = 1 + _address_tag_size;
	_cache_size = _cache_line_num * _cache_line_size;

	_valid_pos = _cache_line_size - 1;

}

CacheSimBase::~CacheSimBase()
{

}

void CacheSimBase::cacheSimulate()
{
	ifstream in_file;
	char t1[20];
	in_file.open("traceijk.txt", ios::in);

	while (!in_file.eof()){
		if (_cnt == 100000)
			break;
		in_file.getline(t1, 13);
		if (t1[0] == '0')
			continue;
		unsigned int t2 = strtoul(t1 + 2, nullptr, 16);
		bitset<20> t3(t2);
		_address = t3;
		_index = 0;
		for (int i = _address_offset_size; i < _address_offset_size + _address_index_size; i++)
			_index += _address[i] * pow(2, i - _address_offset_size);
		_tag = 0;
		for (int i = _address_offset_size + _address_index_size; i < address_size; i++)
			_tag += _address[i] * pow(2, i - _address_offset_size - _address_index_size);
		if (Hit()) {
			_hit_num++;
			_cnt++;
			cache2CPU();
		}
		else{
			_cnt++;
			memory2Cache();
		}
	}
	in_file.close();
	cout << "hit:" << _hit_num << " " << "total:" << _cnt << " "
		<< "rate:" << float(_hit_num) / _cnt << endl << endl;
}