#include <iostream>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {

    // первый запрос для получения внещнего ip адреса

    httplib::Client cli1("https://whatsmyip.dev");
    auto result = cli1.Get("/api/ip");

    json data = json::parse(result->body);

    std::cout << data << '\n';

    std::string ip = data["addr"];

    // второй запрос для получения приблизительных координат

    std::string request = "/json/" + ip;

    httplib::Client cli2("http://ip-api.com");
    result = cli2.Get(request);

    data = json::parse(result->body);

    std::cout << data << '\n';

    auto latitude = to_string(data["lat"]);
    auto longtitude = to_string(data["lon"]);

    // третий запрос для получения информации о погоде

    request = "/v1/forecast?latitude=" + latitude + "&longitude=" + longtitude + "&current_weather=true";

    httplib::Client cli3("https://api.open-meteo.com");
    result = cli3.Get(request);

    data = json::parse(result->body);

    std::cout << "Температура в данный момент: " << data["current_weather"]["temperature"] << '\n';

    return 0;
}
