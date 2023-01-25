#ifndef SIGNALS_H
#define SIGNALS_H

class CAN_signals {
public:
	CAN_signals();
	float get_temperature();
	void set_temperature(float newValue);
	float get_humidity();
	void set_humidity(float newValue);

private:
	float m_temperature;
	float m_humidity;
};
#endif
