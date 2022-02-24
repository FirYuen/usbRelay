#include "CppLinuxSerial/SerialPort.hpp"
#include <iostream>
using namespace mn::CppLinuxSerial;
std::string stringToHex(std::string source);

int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		std::cout << "use " << argv[0] << " 0 to open relay" << std::endl;
		std::cout << "use " << argv[0] << " 1 to close relay" << std::endl;
		return 0;
	}

	// Create serial port object and open serial port at 57600 buad, 8 data bits, no parity bit, and one stop bit (8n1)
	SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	// Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
	serialPort.SetTimeout(-1); // Block when reading until any data is received
	serialPort.Open();

	std::string hex = "";

	switch (atoi(argv[1]))
	{
	case 0:
		hex = "A00101A2";
		std::cout << "ON"<< std::endl;
		break;
	case 1:
		hex = "A00100A1";
		std::cout << "OFF"<< std::endl;
		break;
	default:
		std::cout << "use " << argv[0] << " 0 to open relay" << std::endl;
		std::cout << "use " << argv[0] << " 1 to close relay" << std::endl;
		return 0;
		break;
	}

	// Generating message
	std::string result = stringToHex(hex);

	// Write some ASCII data
	// serialPort.Write("\xA0\x01\x01\xA2\r");
	serialPort.Write(result);
	// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	// std::string readData;
	// serialPort.Read(readData);

	// Close the serial port
	serialPort.Close();
	return 0;
}

std::string stringToHex(std::string source)
{

	std::basic_string<uint8_t> bytes;

	for (size_t i = 0; i < source.length(); i += 2)
	{
		uint16_t byte;

		std::string nextbyte = source.substr(i, 2);

		std::istringstream(nextbyte) >> std::hex >> byte;

		bytes.push_back(static_cast<uint8_t>(byte));
	}

	std::string result(begin(bytes), end(bytes));
	return result;
}