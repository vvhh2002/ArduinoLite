#include "Arduino.h"

static int8_t adc_gpios[] = {
    21, -1, 22, -1, 20, -1, -1, -1, -1, -1,
    -1, -1, 25, 24, 26, 23, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 28, 29, 27, -1, -1,
    -1, -1, 14, 15, 16, 17, 10, 11, 12, 13,
};

static adc_bits_width_t adc_resolution = ADC_WIDTH_BIT_12;


uint16_t analogRead(uint8_t pin)
{
    if (pin >= 40 || adc_gpios[pin] == -1) {
        return 0;
    } else if (adc_gpios[pin] < 20) {
        adc1_channel_t channel = (adc1_channel_t)(adc_gpios[pin] - 10);
        adc1_config_width(adc_resolution);
        adc1_config_channel_atten(channel, ADC_ATTEN_DB_11);
        return adc1_get_raw(channel);
    } else {
        adc2_channel_t channel = (adc2_channel_t)(adc_gpios[pin] - 20);
        int value = 0;
        adc2_config_channel_atten(channel, ADC_ATTEN_DB_11);
        adc2_get_raw((adc2_channel_t)channel, adc_resolution, &value);
        return value;
    }
}

void analogReadResolution(uint8_t bits)
{
    if (bits >= 9 && bits <= 12) {
        adc_resolution = (adc_bits_width_t)(bits - 9);
    }
}

void analogWrite(uint8_t pin, uint16_t val)
{

}

void attachInterrupt(uint8_t interrupt, void (*userFunc)(void), int mode, void *arg)
{

}

void detachInterrupt(uint8_t interrupt)
{

}

inline void interrupts()
{
    //
}

inline void noInterrupts()
{
    //
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    timeout += micros();
    while (timeout < micros() && digitalRead(pin) == state);
    while (timeout < micros()) {
        if (digitalRead(pin) == state) {
            unsigned long pulse_start = micros();
            while (timeout < micros() && digitalRead(pin) == state);
            return micros() - pulse_start;
        }
    }
    return 0;
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return pulseIn(pin, state, timeout);
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
    uint8_t output = 0;

    for (int i = 0; i < 8; i++) {
        digitalWrite(clockPin, HIGH);
        if (bitOrder == LSBFIRST){
            output |= digitalRead(dataPin) << i;
        } else {
            output |= digitalRead(dataPin) << (7 - i);
        }
        digitalWrite(clockPin, LOW);
    }

    return output;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
    for (int i = 0; i < 8; i++){
        if (bitOrder == LSBFIRST){
            digitalWrite(dataPin, (value & (1 << i)) ? HIGH : LOW);
        } else {
            digitalWrite(dataPin, (value & (1 << (7 - i))) ? HIGH : LOW);
        }
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

inline long random(long max)
{
    return random(0, max);
}

inline long random(long min, long max)
{
    long value = min;
    do {
        value = esp_random();
    } while (value < min || value > max);
    return value;
}

inline void randomSeed(long seed)
{
}

template <typename T, typename U, typename V>
inline T constrain(T amt, U low, V high)
{
    return max(min(amt, high), low);
}

template <typename T>
inline T map(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <typename T, typename U>
inline T max(T a, U b)
{
    return std::max(a, (T)b);
}

template <typename T, typename U>
inline T min(T a, U b)
{
    return std::min(a, (T)b);
}

template <typename T>
inline long round(T n)
{
    return ((n) >= 0 ? (long)((n) + 0.5) : (long)((n)-0.5));
}
