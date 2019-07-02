module RegisterFile(rr1, rr2, wr, enable_write, write_data, clk, rd1, rd2);
  input clk;
  input wire enable_write;
  input wire unsigned [4:0] rr1;
  input wire unsigned [4:0] rr2;
  input wire unsigned [4:0] wr;
  input wire signed [31:0] write_data;
  output reg signed [31:0] rd1;
  output reg signed [31:0] rd2;
  reg signed [31:0] register_array [0:31];
  always @ (posedge clk) begin
    if(enable_write) register_array[wr] = write_data;
    rd1 = register_array[rr1];
    rd2 = register_array[rr2];
  end
endmodule
