#include"cache.h"

using namespace std;

char file[20] = "traceijk.txt";

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

	/*SetAssociateFIFO t1(8,32);
	t1.cacheSimulate();
	cout << endl;
	SetAssociateFIFO t2(8, 32);
	t2.cacheSimulate();
	cout << endl;
	SetAssociateFIFO t3(8, 128);
	t3.cacheSimulate();
	cout << endl;*/
	//SetAssociateRandom t2(2, 8);
	//t2.cacheSimulate();
	//cout << endl;
	//SetAssociateLRU t4(8, 4);
	//t4.cacheSimulate();

	/*for (int size = 8; size <= 128; size *= 4) {
		cout<< " size " << size << endl;
		for (int line = 16; line <= 256; line *= 4) {
			DirectMap t1(line,size);
			cout << "DirectMap  " << " line " << line << endl;
			t1.cacheSimulate();
			for (int set = 2; set <= 8; set *= 2) {
				SetAssociateLRU t3(set, line / set,size);
				cout << "SetAssoLRU  " << " line  " << line << " set " << set << endl;
				t3.cacheSimulate();
			}
			SetAssociateLRU t5(1, line,size);
			cout << "fullSetAssoLRU  " << " line  " << line  << endl;
			t5.cacheSimulate();
			cout << "**********" << endl;
		}
		cout << "---------------------" << endl;
	}*/
	for (int size = 8; size <= 32; size *= 4) {
		cout << " random and size " << size << endl;
		for (int line = 64; line <= 64; line *= 4) {
			for (int set = 8; set <= 8; set *= 2) {
				SetAssociateRandom t2(set, line/set,size);
				cout << "SetAssoRan  " << " line  " << line << " set " << set << endl;
				t2.cacheSimulate();
			}
			SetAssociateRandom t4(1, line,size);
			cout << "fullSetAssoRan  " << " line  " << line << endl;
			t4.cacheSimulate();
			cout << "**********" << endl;
		}
		cout << "---------------------" << endl;
	}
	for (int size = 8; size <= 32; size *= 4) {
		cout << " fifo and size " << size << endl;
		for (int line = 16; line <= 64; line *= 4) {
			for (int set = 2; set <= 8; set *= 2) {
				SetAssociateFIFO t2(set, line / set, size);
				cout << "SetAssociateFIFO  " << " line  " << line << " set " << set << endl;
				t2.cacheSimulate();
			}
			SetAssociateFIFO t4(1, line, size);
			cout << "SetAssociateFIFO  " << " line  " << line << endl;
			t4.cacheSimulate();
			cout << "**********" << endl;
		}
		cout << "---------------------" << endl;
	}
}
