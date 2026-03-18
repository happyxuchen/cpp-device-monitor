#include <cassert>
#include <iostream>
#include "../include/parser.h"

int main()
{
    std::string msg = "DEVICE:sensor1;TEMP:40;PRESSURE:113;STATUS:OK";

    auto data = parse_message(msg);

    assert(data["DEVICE"] == "sensor1");
    assert(data["TEMP"] == "40");
    assert(data["PRESSURE"] == "113");
    assert(data["STATUS"] == "OK");
    assert(has_required_fields(data));

    int temp = 0;
    int pressure = 0;

    assert(safe_to_int(data["TEMP"], temp));
    assert(safe_to_int(data["PRESSURE"], pressure));
    assert(temp == 40);
    assert(pressure == 113);

    std::cout << "All parser tests passed.\n";
    return 0;
}