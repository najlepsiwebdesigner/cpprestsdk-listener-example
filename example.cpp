#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>  
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <boost/format.hpp>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace web::http::experimental::listener;
using namespace std;

std::string read_file(std::string filename) {
	ifstream inFile;
	inFile.open(filename);

	std::stringstream strStream;
	strStream << inFile.rdbuf();
	string str = strStream.str();
	return str;
}

boost::format get_template(std::string filename) {
	std::string content = read_file(filename);
	boost::format con = boost::format(content);
	return con;
}

int main(int argc, char* argv[])
{
	http_listener listener("http://localhost:12345");

	int count = 0;

	listener.support(methods::GET, [count] (http_request request) mutable {
		std::cout << "GET "<< request.request_uri().to_string() << std::endl;

		// tu si ziskam get parametre
		auto http_get_vars = uri::split_query(request.request_uri().query());

		// takto sa parsuju parametre	
		auto param_end = http_get_vars.find("end");
		if (param_end != end(http_get_vars)) {
			auto request_name = param_end->second;
			std::cout << "Received \"end\": " << request_name << endl;
		}

		auto param_start = http_get_vars.find(U("start"));
		if (param_start != end(http_get_vars)) {
			auto request_name = param_start->second;
			std::cout << "Received \"start\": " << request_name << endl;
		}


		boost::format tpl = get_template("index.html");
		tpl % "Page rendered: " % count;
		count++;

		request.reply(status_codes::OK, U(boost::str(tpl)),U("text/html"));
	});	

	listener.open().wait();
	std::cout << "Web server started on: " << listener.uri().to_string() << std::endl;
	
	while(true) {
		this_thread::sleep_for(chrono::milliseconds(2000));
	}

	std::cout << "Terminating JSON listener." << endl;
	listener.close().wait();

    return 0;
}
