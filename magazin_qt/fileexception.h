#include <string>
using std::string;
class File_Error {
private:
	string msg;
public:
	File_Error(string msg) {
		this->msg = msg;
	};
	string get_message() {
		return msg;
	};


};
