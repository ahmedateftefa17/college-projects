`timescale 1ns/1ns
module clk (output clock);
  reg clock = 0;
  always #10 clock = ~clock;
endmodule
