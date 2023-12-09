#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>

size_t writeCallback(char* buf, size_t size, size_t nmemb, std::string* userdata) {
	if (userdata == nullptr)
		return 0;

	userdata->append(buf, size * nmemb);
	return size * nmemb;
}

namespace Requests {
	std::string getIP() {
		CURL* curl = curl_easy_init();

		std::string ipData;

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ipData);

			CURLcode res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				std::cerr << "Error trying to get IP: " << curl_easy_strerror(res) << std::endl;
				ipData = "Unknown";
			}

			curl_easy_cleanup(curl);
		}

		return ipData;
	}

	void sendRequest(const char* webhook_url, const char *message) {
		CURL* curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, webhook_url);

			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);

			CURLcode res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				std::cerr << "Error trying to send data: " << curl_easy_strerror(res) << std::endl;
			}

			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
		}

		std::cout << webhook_url << std::endl;
	}
}