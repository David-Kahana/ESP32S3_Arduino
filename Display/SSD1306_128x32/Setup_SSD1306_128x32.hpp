#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_SSD1306     _panel_instance;
  lgfx::Bus_I2C        _bus_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      // I2C
      cfg.i2c_port    = 0;          // 0 or 1
      cfg.freq_write  = 400000;     
      cfg.freq_read   = 400000;     
      cfg.pin_sda     = 5;          // SDA
      cfg.pin_scl     = 4;          // SCL
      cfg.i2c_addr    = 0x3C;       // I2C

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();

      cfg.pin_cs           =    -1;  // CS (-1 = disable)
      cfg.pin_rst          =    -1;  // RST (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSY (-1 = disable)

      cfg.panel_width      =   128;
      cfg.panel_height     =    32;
      cfg.offset_x         =     0;
      cfg.offset_y         =     0;
      cfg.offset_rotation  =     0;  // 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;
      cfg.dummy_read_bits  =     1;
      cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};