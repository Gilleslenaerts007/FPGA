set_property IOSTANDARD LVCMOS33 [get_ports sonar_echo_0]
set_property IOSTANDARD LVCMOS33 [get_ports sonar_trig_0]
set_property PACKAGE_PIN L15 [get_ports sonar_echo_0]
set_property PACKAGE_PIN M15 [get_ports sonar_trig_0]

create_clock -period 15.385 -name design_1_i/vhdlnoclk_0/U0/i_clk -waveform {0.000 7.693} [get_pins design_1_i/vhdlnoclk_0/U0/STARTUPE2_inst/CFGMCLK]
set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets clk]
