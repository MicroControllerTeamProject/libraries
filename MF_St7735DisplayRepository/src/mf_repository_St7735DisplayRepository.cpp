// mf_repository_St7735DisplayRepository.cpp
#include "mf_repository_St7735DisplayRepository.h"

#include <Arduino.h>
#include <SPI.h>

mf_repository_St7735DisplayRepository::mf_repository_St7735DisplayRepository(uint8_t cs_pin, uint8_t dc_pin, uint8_t reset_pin, uint8_t led_pin, uint8_t column_start, uint8_t row_start)
    : cs_pin(cs_pin),
      dc_pin(dc_pin),
      reset_pin(reset_pin),
      led_pin(led_pin),
      column_start(column_start),
      row_start(row_start),
      current_width(native_width),
      current_height(native_height),
      ready(false)
{
}

mf_repository_St7735DisplayRepository::~mf_repository_St7735DisplayRepository()
{
}

bool mf_repository_St7735DisplayRepository::initialize()
{
    pinMode(cs_pin, OUTPUT);
    pinMode(dc_pin, OUTPUT);
    pinMode(reset_pin, OUTPUT);
    pinMode(led_pin, OUTPUT);

    release_chip();
    digitalWrite(dc_pin, HIGH);
    digitalWrite(led_pin, LOW);

    SPI.begin();

    hardware_reset();
    initialize_controller();
    set_rotation(0);

    ready = true;
    clear_screen(0x0000);
    set_backlight_enabled(true);
    return true;
}

void mf_repository_St7735DisplayRepository::set_rotation(uint8_t rotation_index)
{
    uint8_t normalized_rotation = rotation_index & 0x03;
    uint8_t madctl_value = madctl_rgb;

    if (normalized_rotation == 0)
    {
        madctl_value = madctl_mx | madctl_my | madctl_rgb;
        current_width = native_width;
        current_height = native_height;
    }
    else if (normalized_rotation == 1)
    {
        madctl_value = madctl_my | madctl_mv | madctl_rgb;
        current_width = native_height;
        current_height = native_width;
    }
    else if (normalized_rotation == 2)
    {
        madctl_value = madctl_rgb;
        current_width = native_width;
        current_height = native_height;
    }
    else
    {
        madctl_value = madctl_mx | madctl_mv | madctl_rgb;
        current_width = native_height;
        current_height = native_width;
    }

    write_command(command_madctl);
    write_data(madctl_value);
}

void mf_repository_St7735DisplayRepository::set_backlight_enabled(bool is_enabled)
{
    digitalWrite(led_pin, is_enabled ? HIGH : LOW);
}

void mf_repository_St7735DisplayRepository::clear_screen(uint16_t color_565)
{
    fill_rectangle(0, 0, current_width, current_height, color_565);
}

void mf_repository_St7735DisplayRepository::draw_pixel(uint8_t x, uint8_t y, uint16_t color_565)
{
    if (!ready)
    {
        return;
    }

    if (x >= current_width || y >= current_height)
    {
        return;
    }

    set_address_window(x, y, x, y);
    write_data16(color_565);
}

void mf_repository_St7735DisplayRepository::fill_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color_565)
{
    if (!ready)
    {
        return;
    }

    if (width == 0 || height == 0)
    {
        return;
    }

    if (x >= current_width || y >= current_height)
    {
        return;
    }

    uint8_t x1 = x + width - 1;
    uint8_t y1 = y + height - 1;

    if (x1 >= current_width)
    {
        x1 = current_width - 1;
    }

    if (y1 >= current_height)
    {
        y1 = current_height - 1;
    }

    uint16_t pixel_count = (uint16_t)(x1 - x + 1) * (uint16_t)(y1 - y + 1);

    set_address_window(x, y, x1, y1);

    select_chip();
    digitalWrite(dc_pin, HIGH);
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

    for (uint16_t pixel_index = 0; pixel_index < pixel_count; ++pixel_index)
    {
        SPI.transfer((uint8_t)(color_565 >> 8));
        SPI.transfer((uint8_t)(color_565 & 0xFF));
    }

    SPI.endTransaction();
    release_chip();
}

uint8_t mf_repository_St7735DisplayRepository::get_width() const
{
    return current_width;
}

uint8_t mf_repository_St7735DisplayRepository::get_height() const
{
    return current_height;
}

bool mf_repository_St7735DisplayRepository::is_ready() const
{
    return ready;
}

void mf_repository_St7735DisplayRepository::hardware_reset()
{
    digitalWrite(reset_pin, HIGH);
    delay(5);

    digitalWrite(reset_pin, LOW);
    delay(20);

    digitalWrite(reset_pin, HIGH);
    delay(150);
}

void mf_repository_St7735DisplayRepository::initialize_controller()
{
    write_command(command_swreset);
    delay(150);

    write_command(command_slpout);
    delay(150);

    write_command(command_frmctr1);
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);

    write_command(command_frmctr2);
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);

    write_command(command_frmctr3);
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);
    write_data(0x01);
    write_data(0x2C);
    write_data(0x2D);

    write_command(command_invctr);
    write_data(0x07);

    write_command(command_pwctr1);
    write_data(0xA2);
    write_data(0x02);
    write_data(0x84);

    write_command(command_pwctr2);
    write_data(0xC5);

    write_command(command_pwctr3);
    write_data(0x0A);
    write_data(0x00);

    write_command(command_pwctr4);
    write_data(0x8A);
    write_data(0x2A);

    write_command(command_pwctr5);
    write_data(0x8A);
    write_data(0xEE);

    write_command(command_vmctr1);
    write_data(0x0E);

    write_command(command_invoff);

    write_command(command_madctl);
    write_data(madctl_rgb);

    write_command(command_colmod);
    write_data(0x05);
    delay(10);

    write_command(command_gmctrp1);
    write_data(0x02);
    write_data(0x1C);
    write_data(0x07);
    write_data(0x12);
    write_data(0x37);
    write_data(0x32);
    write_data(0x29);
    write_data(0x2D);
    write_data(0x29);
    write_data(0x25);
    write_data(0x2B);
    write_data(0x39);
    write_data(0x00);
    write_data(0x01);
    write_data(0x03);
    write_data(0x10);

    write_command(command_gmctrn1);
    write_data(0x03);
    write_data(0x1D);
    write_data(0x07);
    write_data(0x06);
    write_data(0x2E);
    write_data(0x2C);
    write_data(0x29);
    write_data(0x2D);
    write_data(0x2E);
    write_data(0x2E);
    write_data(0x37);
    write_data(0x3F);
    write_data(0x00);
    write_data(0x00);
    write_data(0x02);
    write_data(0x10);

    write_command(command_noron);
    delay(10);

    write_command(command_dispon);
    delay(100);
}

void mf_repository_St7735DisplayRepository::select_chip()
{
    digitalWrite(cs_pin, LOW);
}

void mf_repository_St7735DisplayRepository::release_chip()
{
    digitalWrite(cs_pin, HIGH);
}

void mf_repository_St7735DisplayRepository::write_command(uint8_t command)
{
    select_chip();
    digitalWrite(dc_pin, LOW);
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(command);
    SPI.endTransaction();
    release_chip();
}

void mf_repository_St7735DisplayRepository::write_data(uint8_t data)
{
    select_chip();
    digitalWrite(dc_pin, HIGH);
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(data);
    SPI.endTransaction();
    release_chip();
}

void mf_repository_St7735DisplayRepository::write_data16(uint16_t data)
{
    select_chip();
    digitalWrite(dc_pin, HIGH);
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    SPI.transfer((uint8_t)(data >> 8));
    SPI.transfer((uint8_t)(data & 0xFF));
    SPI.endTransaction();
    release_chip();
}

void mf_repository_St7735DisplayRepository::set_address_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    uint8_t physical_x0 = x0 + column_start;
    uint8_t physical_x1 = x1 + column_start;
    uint8_t physical_y0 = y0 + row_start;
    uint8_t physical_y1 = y1 + row_start;

    write_command(command_caset);
    write_data(0x00);
    write_data(physical_x0);
    write_data(0x00);
    write_data(physical_x1);

    write_command(command_raset);
    write_data(0x00);
    write_data(physical_y0);
    write_data(0x00);
    write_data(physical_y1);

    write_command(command_ramwr);
}
