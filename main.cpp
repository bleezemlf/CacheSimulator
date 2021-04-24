#include"cache.h"

using namespace std;

char file[20] = "traceijk.txt";

/*
CacheSimulator::CacheSimulator(int set_num, int set_line_num, int replace_policy = 0, int block_size = 4) :
	_set_num(set_num),
	_set_line_num(set_line_num),
	_block_size(block_size)

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

	_fifo_q = new int[_set_num];
	for (int i = 0; i < _set_num; i++) {
		_fifo_q[i] = 0;
	}
}

CacheSimulator::~CacheSimulator()
{
	delete[] _cache;
	delete[] _fifo_q;
}

bool CacheSimulator::Hit()
{
	int t1 = _index * _set_line_num;
	for (int i = t1; i < t1 + _set_line_num; i++) {
		for (int j = address_size - 1, k = _valid_pos - 1; j > address_size - 1 - _address_tag_size; j--, k--) {
			if (_address[j] == _cache[i][k])
				continue;
			else 
				return false;
		}			
	}
	return true;
}

int CacheSimulator::replaceLineSel()
{
	 
}

void CacheSimulator::cache2CPU()
{
	cout << "hit" << endl;
}

void CacheSimulator::memory2Cache()
{
	cout << "miss" << endl;
	int replace_line = replaceLineSel();
	if (_cache[replace_line][_valid_pos] == 0)
		_cache[replace_line][_valid_pos] == 1;
	
	for (int i = _valid_pos - 1, j = address_size - 1; i > _valid_pos - 1 - _address_tag_size; i--, j--)
		_cache[replace_line][i] = _address[j];

}

void CacheSimulator::cacheSimulate(string file)
{
	
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
*/

int main()
{
	/*DirectMap t1(32);
	t1.test();
	cout << endl;
	SetAssociateRandom t2(2, 8);
	t2.test();
	cout << endl;
	SetAssociateFIFO t3(1, 4);
	t3.test();
	cout << endl;
	SetAssociateLRU t4(1, 4);
	t4.test();*/

	for (int size = 8; size <= 128; size *= 4) {
		cout<< " size " << size << endl;
		for (int line = 16; line <= 256; line *= 4) {
			DirectMap t1(line);
			cout << "DirectMap  " << " line " << line << endl;
			t1.cacheSimulate();
			for (int set = 2; set <= 8; set *= 2) {
				SetAssociateLRU t3(line / set, set);
				cout << "SetAssoLRU  " << " line  " << line << " set " << set << endl;
				t3.cacheSimulate();
			}
			SetAssociateLRU t5(1, line);
			cout << "fullSetAssoLRU  " << " line  " << line  << endl;
			t5.cacheSimulate();
			cout << "**********" << endl;
		}
		cout << "---------------------" << endl;
	}
	for (int size = 8; size <= 128; size *= 4) {
		cout << " random and size " << size << endl;
		for (int line = 16; line <= 256; line *= 4) {
			for (int set = 2; set <= 8; set *= 2) {
				SetAssociateRandom t2(line / set, set);
				cout << "SetAssoRan  " << " line  " << line << " set " << set << endl;
				t2.cacheSimulate();
			}
			SetAssociateRandom t4(1, line);
			cout << "fullSetAssoRan  " << " line  " << line << endl;
			t4.cacheSimulate();
		}
		cout << "---------------------" << endl;
	}
}
