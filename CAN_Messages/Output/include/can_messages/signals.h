#ifndef SIGNALS_H
#define SIGNALS_H

#include<sstream>
#include<string>
class CAN_signals
{
	public: 
		CAN_signals();
		/*
		get temperature
		*/
		std::string get_temperature();
		/*
		set temperature
		*/
		std::string set_temperature(float newValue);
		/*
		get humidity
		*/
		std::string get_humidity();
		/*
		set humidity
		*/
		std::string set_humidity(uint8_t newValue);

	private: 
		uint8_t m_startMsgId;
		uint8_t m_temperatureGetMsgId;
		uint8_t m_temperatureSetMsgId;
		uint8_t m_humidityGetMsgId;
		uint8_t m_humiditySetMsgId;
};

#endif /* SIGNALS_H */
