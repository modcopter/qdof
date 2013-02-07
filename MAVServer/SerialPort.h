#include <string>

#include <boost/iostreams/stream.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;

class SerialPort {
public:
	SerialPort(std::string name, unsigned int baudrate)
			: m_io_service(), m_serial_port(m_io_service) {
	}

	SerialPort() : m_io_service(), m_serial_port(m_io_service) {}

	SerialPort(SerialPort &c) : m_io_service(), m_serial_port(m_io_service) {
		this->m_baud = c.m_baud;
		this->m_name = c.m_name;
	}

	void open() {
		m_serial_port.open(m_name);
	}

	void open(std::string name = "", unsigned int baudrate = 0) {
		if (name == "") name = m_name; else m_name = name;
		if (baudrate = 0) baudrate = m_baud; else m_baud = baudrate;

		m_serial_port.open(m_name);
		m_serial_port.set_option(boost::asio::serial_port::baud_rate(m_baud));
	}

	bool is_open() {
		return m_serial_port.is_open();
	}

	void writeByte(uint8_t b) {
		uint8_t bytes[1] = {b};
		m_serial_port.write_some(boost::asio::buffer(bytes, 1));
	}

	void writeString(std::string str) {
		m_serial_port.write_some(boost::asio::buffer(str.c_str(), str.size()));
	}

	void writeString(char *str, int len) {
		m_serial_port.write_some(boost::asio::buffer(str, len));
	}

	uint8_t readByte() {
		uint8_t buf[1];
		m_serial_port.read_some(boost::asio::buffer(buf, 1));
		return buf[0];
	}

	int readBytes(uint8_t buf[], int maxlen) {
		return m_serial_port.read_some(boost::asio::buffer(buf, maxlen));		
	}

	serial_port &getSerialPort() {return m_serial_port;}

private:
	std::string m_name;
	unsigned int m_baud;

	io_service m_io_service;
	serial_port m_serial_port;
};