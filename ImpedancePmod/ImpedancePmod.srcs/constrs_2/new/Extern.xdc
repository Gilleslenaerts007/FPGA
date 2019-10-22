set_property IOSTANDARD LVCMOS33 [get_ports IIC_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_0_sda_io]
set_property PACKAGE_PIN L15 [get_ports IIC_0_scl_io]
set_property PACKAGE_PIN M15 [get_ports IIC_0_sda_io]

set_property PULLUP true [get_ports IIC_0_scl_io]
set_property PULLUP true [get_ports IIC_0_sda_io]


set_property PACKAGE_PIN P13 [get_ports {spi_rtl_ss_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {spi_rtl_ss_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_io0_io]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_io1_io]
set_property PACKAGE_PIN P14 [get_ports spi_rtl_io0_io]
set_property PACKAGE_PIN N11 [get_ports spi_rtl_io1_io]

set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_sck_io]
set_property PACKAGE_PIN N12 [get_ports spi_rtl_sck_io]
