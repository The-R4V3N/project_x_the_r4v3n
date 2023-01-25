#include "signals.h"

CAN_signals::CAN_signals() {
    // constructor implementation
}

float CAN_signals::get_temperature() {
    return m_temperature;
}

void CAN_signals::set_temperature(float newValue) {
    m_temperature = newValue;
}

float CAN_signals::get_humidity() {
    return m_humidity;
}

void CAN_signals::set_humidity(float newValue) {
    m_humidity = newValue;
}

private:
float m_temperature;
float m_humidity;
