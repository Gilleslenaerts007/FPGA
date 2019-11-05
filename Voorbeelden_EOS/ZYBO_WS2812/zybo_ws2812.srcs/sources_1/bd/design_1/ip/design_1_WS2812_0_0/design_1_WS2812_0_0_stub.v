// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.1 (win64) Build 2552052 Fri May 24 14:49:42 MDT 2019
// Date        : Tue Nov  5 10:21:23 2019
// Host        : Gilles-Lenaerts running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               C:/FPGA/Voorbeelden_EOS/ZYBO_WS2812/zybo_ws2812.srcs/sources_1/bd/design_1/ip/design_1_WS2812_0_0/design_1_WS2812_0_0_stub.v
// Design      : design_1_WS2812_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "WS2812,Vivado 2019.1" *)
module design_1_WS2812_0_0(clk, d_out)
/* synthesis syn_black_box black_box_pad_pin="clk,d_out" */;
  input clk;
  output d_out;
endmodule
