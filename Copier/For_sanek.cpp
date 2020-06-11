// For_sanek.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <locale>
#include <codecvt>

void read_file(std::string filename, std::vector<int>& numbers) {
	std::ifstream file_with_numbers;
	file_with_numbers.open(filename);

	while (!file_with_numbers.eof()) {
		int i;
		file_with_numbers >> i;
		numbers.push_back(i);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// Path with needed files
    std::cout << "Введите путь до папки с фотографиями:\n";
	std::string path;
	std::cin >> path;

	// Path with needed folder
	std::cout << "Введите путь до папки, в которую будут загружены выбранные файлы:\n";
	std::string folder;
	std::cin >> folder;

	// File with numbers
	std::cout << "Введите название файла с номерами фотографий полностью (вместе с .txt):\n";
	std::string file;
	std::cin >> file;

	std::vector<int> numbers;
	read_file(file, numbers);
	for (auto a : numbers) {
		std::string path_getted = path + "\\*" + std::to_string(a) + ".CR2";
		std::wstring w_path(path_getted.begin(), path_getted.end());

		WIN32_FIND_DATAW wfd;
		HANDLE const hFind = FindFirstFileW(w_path.c_str(), &wfd);
		setlocale(LC_ALL, "");

		if (INVALID_HANDLE_VALUE != hFind)
		{
			do
			{
				std::wcout << &wfd.cFileName[0] << std::endl;
			} while (NULL != FindNextFileW(hFind, &wfd));

			FindClose(hFind);
		}
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
		std::string file_name = converter.to_bytes(&wfd.cFileName[0]);

		std::string folder_input = folder + "\\" + file_name;
		std::wstring w_folder(folder_input.begin(), folder_input.end());

		std::string path_absolute = path + "\\" + file_name;
		std::wstring w_path_absolute(path_absolute.begin(), path_absolute.end());

		if (CopyFile(w_path_absolute.c_str(), w_folder.c_str(), FALSE)) {
			std::cout << "File " + std::to_string(a) + " copied successful!" << std::endl;
		}
		else {
			std::cout << "Copy of file " + std::to_string(a) + " failed!" << std::endl;
		}
	}
	system("PAUSE");
	return 0;
}
