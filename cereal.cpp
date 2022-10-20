#include <iostream>
#include <fstream>			// ofstream, ifstream
#include <algorithm>		// for_each
#include <string>

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

using namespace std;

struct DataStruct
{
	int nA;
	int nB;
	double dC;
	vector<string> vString;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(nA, nB, dC, vString);
	}
};

void DataPrint(DataStruct data)
{
	printf("data1 : nA(%d), nB(%d), dC(%f), vString(", data.nA, data.nB, data.dC);
	for_each(data.vString.begin(), data.vString.end(), [](string& str) {
		printf("%s ", str.c_str());
		});
	printf(")\n");
}

int main(void)
{
	// 데이터 출력
	ofstream out("cereal.dat", ios::binary);
	{
		cereal::BinaryOutputArchive oArchives(out);

		DataStruct data1;
		{
			data1.nA = 1;
			data1.nB = 2;
			data1.dC = 3.3;
			data1.vString.push_back("test");
			data1.vString.push_back("시험중");
		}
		DataStruct data2;
		{
			data2.nA = 10;
			data2.nB = 20;
			data2.dC = 30.3;
			data2.vString.push_back("안녕");
			data2.vString.push_back("Hi~~");
			data2.vString.push_back("福");
		}

		oArchives(data1, data2);
		out.close();
	}

	// 데이터 입력
	ifstream in("cereal.dat", ios::binary);
	{
		cereal::BinaryInputArchive iArchives(in);

		DataStruct data1;
		DataStruct data2;
		iArchives(data1, data2);

		DataPrint(data1);
		DataPrint(data2);

		in.close();
	}

	//pause();

	return 0;
}