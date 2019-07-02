module cpu(clk);
  input clk;
  parameter nop = 32'd0, lw = 6'd35, sw = 6'd43, RInstruction = 6'd0, beq = 6'd4, bne = 6'd5, j = 6'd2;
  reg [31:0] PC = 32'd0, RegisterFile [0:31], IMemory [0:1023], DMemory [0:1023],
             IFID_Instruction = nop, IFID_PC,
             IDEX_Instruction = nop, IDEX_PC, IDEX_Rs, IDEX_Rt, IDEX_Constant,
             EXMEM_Instruction = nop, EXMEM_PC, EXMEM_ALUout, EXMEM_Rt,
             MEMWB_Instruction = nop, MEMWB_Value, MEMWB_ALUout;
  always @ * begin
    if(MEMWB_Instruction[31:26] == RInstruction & MEMWB_Instruction[15:11] != 0
       & MEMWB_Instruction[15:11] == IDEX_Instruction[25:21]) IDEX_Rs <= MEMWB_ALUout;
    else if(EXMEM_Instruction[31:26] == RInstruction & EXMEM_Instruction[15:11] != 0
            & EXMEM_Instruction[15:11] == IDEX_Instruction[25:21]) IDEX_Rs <= EXMEM_ALUout;
    if(MEMWB_Instruction[31:26] == RInstruction & MEMWB_Instruction[15:11] != 0
       & MEMWB_Instruction[15:11] == IDEX_Instruction[20:16]) IDEX_Rt <= MEMWB_ALUout;
    else if(EXMEM_Instruction[31:26] == RInstruction & EXMEM_Instruction[15:11] != 0
             & EXMEM_Instruction[15:11] == IDEX_Instruction[20:16]) IDEX_Rt <= EXMEM_ALUout;
    if(MEMWB_Instruction[31:26] == lw) begin
      if(MEMWB_Instruction[20:16] == IDEX_Instruction[25:21]) IDEX_Rs <= MEMWB_Value;
      else if(MEMWB_Instruction[20:16] == IDEX_Instruction[20:16]) IDEX_Rt <= MEMWB_Value;
    end
  end
  always @ * if( (IDEX_Instruction[31:26] == lw)
    & (IDEX_Instruction[20:16] == IFID_Instruction[25:21] | IDEX_Instruction[20:16] == IFID_Instruction[20:16])) begin
    IFID_Instruction <= nop;
    PC <= PC - 4;
  end
  always @ * if((IDEX_Instruction[31:26] == beq & IDEX_Rs == IDEX_Rt) | (IDEX_Instruction[31:26] == bne & IDEX_Rs != IDEX_Rt)) begin
    IFID_Instruction <= nop;
    PC = PC - 4 + (IDEX_Constant << 2);
  end
  always @ * if(IDEX_Instruction[31:26] == j) begin
    IFID_Instruction <= nop;
    PC <= { { 4 { IFID_Instruction[25] } }, IDEX_Instruction[25:0] << 2};
  end
  always @(posedge clk) begin
    IFID_PC <= PC;
    IFID_Instruction <= IMemory[PC>>2];
    PC <= PC + 4;
    IDEX_PC <= IFID_PC;
    IDEX_Instruction <= IFID_Instruction;
    IDEX_Rs <= RegisterFile[IFID_Instruction[25:21]];
    IDEX_Rt <= RegisterFile[IFID_Instruction[20:16]];
    IDEX_Constant <= { { 16 { IFID_Instruction[15] } }, IFID_Instruction[15:0]};
    EXMEM_PC <= IDEX_PC;
    EXMEM_Instruction <= IDEX_Instruction;
    EXMEM_Rt <= IDEX_Rt;
    if(IDEX_Instruction[31:26] == lw | IDEX_Instruction[31:26] == sw)
      EXMEM_ALUout <= IDEX_Rs + (IDEX_Constant>>2);
    else if(IDEX_Instruction[31:26] == RInstruction) begin
      case(IDEX_Instruction[5:0])
        6'd00: EXMEM_ALUout <= IDEX_Rt << IDEX_Instruction[10:6];
        6'd02: EXMEM_ALUout <= IDEX_Rt >> IDEX_Instruction[10:6];
        6'd32: EXMEM_ALUout <= IDEX_Rs + IDEX_Rt;
        6'd34: EXMEM_ALUout <= IDEX_Rs - IDEX_Rt;
        6'd36: EXMEM_ALUout <= IDEX_Rs & IDEX_Rt;
        6'd37: EXMEM_ALUout <= IDEX_Rs | IDEX_Rt;
        6'd39: EXMEM_ALUout <= ~(IDEX_Rs | IDEX_Rt);
      endcase
    end else if(IDEX_Instruction[31:26] == 6'd08) EXMEM_ALUout <= IDEX_Rs + IDEX_Constant;
        else if(IDEX_Instruction[31:26] == 6'd12) EXMEM_ALUout <= IDEX_Rs & IDEX_Constant;
        else if(IDEX_Instruction[31:26] == 6'd13) EXMEM_ALUout <= IDEX_Rs | IDEX_Constant;
    MEMWB_Instruction <= EXMEM_Instruction;
    MEMWB_ALUout <= EXMEM_ALUout;
    if(EXMEM_Instruction[31:26] == lw)
      MEMWB_Value <= DMemory[EXMEM_ALUout];
    else if(EXMEM_Instruction[31:26] == sw)
      DMemory[EXMEM_ALUout] <= EXMEM_Rt;
  end
  always @(negedge clk) if(MEMWB_Instruction[31:26] == lw & MEMWB_Instruction[20:16] != 0)
    RegisterFile[MEMWB_Instruction[20:16]] <= MEMWB_Value;
  else if(MEMWB_Instruction[31:26] == RInstruction & MEMWB_Instruction[15:11] != 0)
    RegisterFile[MEMWB_Instruction[15:11]] <= MEMWB_ALUout;
  else if(MEMWB_Instruction[31:26] == 6'd8
          | MEMWB_Instruction[31:26] == 6'd12
          | MEMWB_Instruction[31:26] == 6'd13)
    RegisterFile[MEMWB_Instruction[20:16]] <= MEMWB_ALUout;
endmodule