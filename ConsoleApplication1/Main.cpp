// infix_iterator.h 
// 
// Lifted from Jerry Coffin's 's prefix_ostream_iterator 
#if !defined(INFIX_ITERATOR_H_) 
#define  INFIX_ITERATOR_H_ 
#include <ostream> 
#include <iterator> 
template <class T,
	class charT = char,
	class traits = std::char_traits<charT> >
	class infix_ostream_iterator :
	public std::iterator<std::output_iterator_tag, void, void, void, void>
{
	std::basic_ostream<charT, traits> *os;
	charT const* delimiter;
	bool first_elem;
public:
	typedef charT char_type;
	typedef traits traits_type;
	typedef std::basic_ostream<charT, traits> ostream_type;
	infix_ostream_iterator(ostream_type& s)
		: os(&s), delimiter(0), first_elem(true)
	{}
	infix_ostream_iterator(ostream_type& s, charT const *d)
		: os(&s), delimiter(d), first_elem(true)
	{}
	infix_ostream_iterator<T, charT, traits>& operator=(T const &item)
	{
		// Here's the only real change from ostream_iterator: 
		// Normally, the '*os << item;' would come before the 'if'. 
		if (!first_elem && delimiter != 0)
			*os << delimiter;
		*os << item;
		first_elem = false;
		return *this;
	}
	infix_ostream_iterator<T, charT, traits> &operator*() {
		return *this;
	}
	infix_ostream_iterator<T, charT, traits> &operator++() {
		return *this;
	}
	infix_ostream_iterator<T, charT, traits> &operator++(int) {
		return *this;
	}
};
#endif 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

int main(int argc, char* argv[])
{

	string x;

	// argv[0] is not interesting, since it's just your program's path.
	for (int i = 1; i < argc; ++i)
	{

		vector<string> path_dirs;
		vector<string> temp_levels;
		vector<string> levels;
		vector<string> engrams;
		vector<string> output_lines;

		path_dirs = split(argv[i], '/');
		string file_name = path_dirs[path_dirs.size() - 1];
		file_name = split(file_name, '.')[0];
		cout << "File [1]: " << file_name << endl << endl;

		ifstream file(argv[i]);
		string line;
		if (getline(file, line))
		{
			//cout << line << endl;
			temp_levels = split(line, '(');
			temp_levels = split(temp_levels[1], ')');
			temp_levels = split(temp_levels[0], ',');
		}

		for each(string line in temp_levels)
		{
			string level_num;
			level_num = split(line, '=')[1];
			levels.push_back(level_num);
		}

		if (getline(file, line))
		{
			//skip line
		}

		while (getline(file, line))
		{
			//cout << line << endl;
			string engram_num;
			engram_num = split(line, '=')[1];
			engrams.push_back(engram_num);
		}

		for (int x = 0; x < levels.size(); x++)
		{
			string temp_line;
			temp_line = to_string(x) + ";" + levels[x] + ";" + engrams[x];
			output_lines.push_back(temp_line);
		}

		ofstream output_file(file_name + ".csv");
		infix_ostream_iterator<std::string> output_iterator(output_file, "\n");
		copy(output_lines.begin(), output_lines.end(), output_iterator);
	}
	return 0;
}