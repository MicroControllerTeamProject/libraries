// mf_repository_St7735DisplayRepository.h
#ifndef MF_REPOSITORY_ST7735DISPLAYREPOSITORY_H
#define MF_REPOSITORY_ST7735DISPLAYREPOSITORY_H

#include <stdint.h>

class mf_repository_St7735DisplayRepository
{
public:
    mf_repository_St7735DisplayRepository(uint8_t cs_pin, uint8_t dc_pin, uint8_t reset_pin, uint8_t led_pin, uint8_t column_start = 2, uint8_t row_start = 1);
    virtual ~mf_repository_St7735DisplayRepository();

    virtual bool initialize();
    virtual void set_rotation(uint8_t rotation_index);
    virtual void set_backlight_enabled(bool is_enabled);

    virtual void clear_screen(uint16_t color_565);
    virtual void draw_pixel(uint8_t x, uint8_t y, uint16_t color_565);
    virtual void fill_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color_565);

    virtual uint8_t get_width() const;
    virtual uint8_t get_height() const;
    virtual bool is_ready() const;

private:
    static const uint8_t native_width = 128;
    static const uint8_t native_height = 128;

    static const uint8_t command_nop = 0x00;
    static const uint8_t command_swreset = 0x01;
    static const uint8_t command_slpout = 0x11;
    static const uint8_t command_noron = 0x13;
    static const uint8_t command_invoff = 0x20;
    static const uint8_t command_invon = 0x21;
    static const uint8_t command_dispon = 0x29;
    static const uint8_t command_caset = 0x2A;
    static const uint8_t command_raset = 0x2B;
    static const uint8_t command_ramwr = 0x2C;
    static const uint8_t command_madctl = 0x36;
    static const uint8_t command_colmod = 0x3A;

    static const uint8_t command_frmctr1 = 0xB1;
    static const uint8_t command_frmctr2 = 0xB2;
    static const uint8_t command_frmctr3 = 0xB3;
    static const uint8_t command_invctr = 0xB4;
    static const uint8_t command_pwctr1 = 0xC0;
    static const uint8_t command_pwctr2 = 0xC1;
    static const uint8_t command_pwctr3 = 0xC2;
    static const uint8_t command_pwctr4 = 0xC3;
    static const uint8_t command_pwctr5 = 0xC4;
    static const uint8_t command_vmctr1 = 0xC5;
    static const uint8_t command_gmctrp1 = 0xE0;
    static const uint8_t command_gmctrn1 = 0xE1;

    static const uint8_t madctl_mh = 0x04;
    static const uint8_t madctl_rgb = 0x00;
    static const uint8_t madctl_bgr = 0x08;
    static const uint8_t madctl_ml = 0x10;
    static const uint8_t madctl_mv = 0x20;
    static const uint8_t madctl_mx = 0x40;
    static const uint8_t madctl_my = 0x80;

    uint8_t cs_pin;
    uint8_t dc_pin;
    uint8_t reset_pin;
    uint8_t led_pin;
    uint8_t column_start;
    uint8_t row_start;

    uint8_t current_width;
    uint8_t current_height;
    bool ready;

    void hardware_reset();
    void initialize_controller();

    void select_chip();
    void release_chip();

    void write_command(uint8_t command);
    void write_data(uint8_t data);
    void write_data16(uint16_t data);

    void set_address_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
};

#endif
