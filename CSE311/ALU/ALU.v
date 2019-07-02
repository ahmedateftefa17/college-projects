module ALU (rd1, rd2, op, shift_amt, result);
  input wire unsigned [3:0] op;
  input wire signed [31:0] rd1;
  input wire signed [31:0] rd2;
  input wire unsigned [4:0] shift_amt;
  output wire signed [31:0] result;
  assign result = op == 0 ? rd1 + rd2 
                : op == 1 ? rd1 - rd2 
                : op == 2 ? rd1 & rd2 
                : op == 3 ? rd1 | rd2 
                : op == 4 ? rd1 << shift_amt 
                : op == 5 ? rd1 >> shift_amt
                : op == 6 ? rd1 >>> shift_amt
                : op == 7 ? rd1 > rd2
                : op == 8 ? rd1 < rd2
                : 0;
endmodule
