module PCI_Arbiter(input clk, input frame, input [7:0] request, output reg [7:0] grant);
  always @(posedge clk) begin
    if(frame) begin
      grant <= request[0] ? 8'b00000001
             : request[1] ? 8'b00000010
             : request[2] ? 8'b00000100
             : request[3] ? 8'b00001000
             : request[4] ? 8'b00010000
             : request[5] ? 8'b00100000
             : request[6] ? 8'b01000000
             : request[7] ? 8'b10000000
             : 8'b00000000;
    end
  end
endmodule