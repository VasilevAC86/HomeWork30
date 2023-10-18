# include <iostream>
#include<fstream>
#include<string>

bool record_file(std::string message, std::string path); // Функция добавления записи в файл с проверкой открытия файла (для задачи 1)
bool overwrite(std::string my_path, std::string my_text); // Функция замены содержимого файла с проверкой существования файла по пути my_path (для задачи 2)
void print_file(std::string my_path); // Процедура посимвольного вывода в консоль информации из файла (для задачи 2)

int main() {
	// Задача 1. Работа с файлом
	std::cout << "\033[91mTask 1. Working with a file\033[0m\n\n";
	std::string message; // Переменная для хранения вводимой пользователем строки	
	std::string path = "text.txt";// Относительный путь к файлу "text.txt"
	//std::string key{"end"};
	do { // Цикл записи строк в файл, пока не будет введена строка "end" или "END" или "End"
		std::cout << "Enter a string -> ";
		std::getline(std::cin, message);
		if (record_file(message, path))
			std::cout << "\n\033[93mThe string added to file successfully.\033[0m\n";
		else
			std::cout << "\n\033[95mError opening file!\033[0m\n";
	} while (message != "end");
	std::ifstream in; // Объект для чтения информации из файла
	in.open(path, std::ios::in); // Открываем файл для чтения
	if (in.is_open()) {
		std::cout << "\n\033[93mThe file is open for reading.\nFile contents:\033[0m\n\n";
		message.clear(); // Чистим переменную для последующей записи в неё информации из файла
		std::string str; // Переменная для построчного считывания информации из файла
		while (std::getline(in, str)) // Удаляем файл
			message += str + '\n';
		in.close(); 
		std::cout << message;
	}
	else
		std::cout << "\033[94mError opening file!\033[0m\n";
	if (remove(path.c_str()) == 0)
		std::cout << "\n\033[92mFile deleted!\033[0m\n\n";
	else
		std::cout << "\n\033[95mFile deletion error!\033[0m\n\n";

	// Задача 2. Замена содержимого файла
	std::cout << "\033[91mTask 2. Replacing file contents\033[0m\n\n\033[93mEnter the path to file -> \033[0m";
	std::string my_path; // Переменная для хранения пути к файлу
	std::string my_Text; // Переменная для хранения нового текста, который будет перезаписан в файл
	std::cin >> my_path;
	std::cout << "\033[93mEnter the string you want to replace the contents of the file with -> \033[0m";
	std::cin.ignore();
	std::getline(std::cin, my_Text);
	if (overwrite(my_path, my_Text)) {
		std::cout << "\n\n\033[92mFile overwritten successfully.\033[0m";
		print_file(my_path); // Если пользователь захочет, то он выведет содержимое файла
	}
	else
		std::cout << "\n\033[95mFile not foud!\033[0m\n";

	return 0;
}

bool record_file(std::string message, std::string path) {
	std::fstream in_and_out; // Объект для записи/вывода данных в/из файла
	in_and_out.open(path, std::ios::app); // Открываем файл для добаления записи в конец файла (если файла нет, то он будет создан)
	if (in_and_out.is_open()) {
		in_and_out << message << '\n'; // Записываем в файл строку и переводим курсор на соедующую строку
		in_and_out.close();
		return true;
	}
	return false;
}

bool overwrite(std::string my_path, std::string my_text) {
	std::ifstream in; // Создаём объект для чтения файла
	in.open(my_path, std::ios::in); // Открываем объект по пути my_path только для чтения
	if (in.is_open()) {		
		in.close(); // Закрываем файл, проверка доступности файла выполнена
		std::cout << "\n\033[92mFile found!!!";
		print_file(my_path); // Если пользователь захочет, то он выведет содержимое файла				
		std::ofstream out; // Создаем объект для перезаписи файла
		out.open(my_path, std::ios::out); // Открываем объект по пути my_path для перезаписи
		if (out.is_open()) {
			out << my_text << '\n';
			out.close();
			return true;
		}		
	} // Если файл не получилось открыть, то 
	return false;
}

void print_file(std::string my_path) {	
	std::cout << "\n\033[93mDo you want to view the contents of the file?\033[0m\nPress \033[93m1\033[0m to YES or press \033[93many other key\033[0m to NO\nYour choose -> ";
	char my_Choise; // Переменная для хранения выбора пользователя
	std::cin >> my_Choise;
	if (my_Choise == '1') {
		std::string contents; // Строка для хранения информации из файла
		char sym; // Переменная для посимвольного считывания информации из файла
		std::ifstream in; // Объект для чтения информации из файла
		in.open(my_path, std::ios::in); // Открываем файл для чтения
		if (in.is_open()) {
			std::cout << "\n\033[93mThe file is open.\nFile contents:\033[0m\n";
			while (in.get(sym))
				contents += sym;
			std::cout << contents;
		}
		else
			std::cout << "\033[94mError opening file!\033[0m\n";
		in.close();
	}
}
