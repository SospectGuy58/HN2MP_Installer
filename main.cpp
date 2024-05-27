#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <Windows.h>
#pragma comment(lib, "urlmon.lib")

#define PAKDOWNLOADLINK "http://kkskorv2.dx.am/HN2MP/Download.php"
#define PATCH_OFFSET 0xAD5F63
#define PATCH 0x85

int main(int argc, char* argv[]) {
	if (argc < 2)
	{
		std::cout << "Path to HN2 was not entered" << std::endl;
		exit(1);
	}

	std::string PathToHN2 = argv[1];
	PathToHN2 += "/HelloNeighbor2/";

	std::string PathToPak = PathToHN2 + "Content/Paks/zz_HN2MP_p.pak";
	std::replace(PathToPak.begin(), PathToPak.end(), '/', '\\');

	std::cout << "Downloading HN2MP to the following path, please wait:" << std::endl << PathToPak << std::endl;
	URLDownloadToFileA(NULL, std::string(PAKDOWNLOADLINK).c_str(), PathToPak.c_str(), 0, NULL);
	std::cout << "HN2MP successfully downloaded, patching HN2 binary" << std::endl;

	std::ofstream FILE_HelloNeighbor2Binary(PathToHN2 + "Binaries/Win64/HelloNeighbor2-Win64-Shipping.exe",
		std::ios::out | std::ios::in);

	if (!FILE_HelloNeighbor2Binary.good())
	{
		std::cout << "There was an error finding the HN2 binary" << std::endl;
		exit(2);
	}

	FILE_HelloNeighbor2Binary.seekp(PATCH_OFFSET, std::ios::beg);
	FILE_HelloNeighbor2Binary.put(PATCH);
	FILE_HelloNeighbor2Binary.close();

	std::cout << "HN2 binary successfully patched" << std::endl;

	return 0;
}
