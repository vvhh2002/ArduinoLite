#ifndef _SPI_h_
#define _SPI_h_

#include "Arduino.h"
#include "driver/spi_master.h"

#define SPI_HAS_TRANSACTION 1
#define SPI_HAS_NOTUSINGINTERRUPT 1
#define SPI_ATOMIC_VERSION 1

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

class SPISettings
{
  public:
    int clock;
    uint8_t bitOrder;
    uint8_t dataMode;
    SPISettings(int clock = SPI_MASTER_FREQ_8M, uint8_t bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE0) {}
};

class SPIClass
{
  private:
    spi_host_device_t host = VSPI_HOST;
    spi_device_handle_t spi = nullptr;
    spi_transaction_t transaction;
    bool host_init = false;
    int  device_cs = -1;
  public:
    SPIClass(spi_host_device_t bus = VSPI_HOST);
    bool begin();
    bool begin(uint8_t mosi, uint8_t miso, uint8_t sck, uint8_t cs);
    void end(void);
    void beginTransaction(SPISettings settings);
    void endTransaction(void);
    uint16_t transfer16(uint16_t data);
    uint8_t transfer(uint8_t data);
    void transfer(void *buf, size_t count);
    void usingInterrupt(uint8_t interruptNumber);
    void notUsingInterrupt(uint8_t interruptNumber);
};

extern SPIClass SPI;

#endif
