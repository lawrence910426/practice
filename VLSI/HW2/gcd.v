module GCD (
  input wire CLK,
  input wire RST_N,
  input wire [7:0] A,
  input wire [7:0] B,
  input wire START,
  output reg [7:0] Y,
  output reg DONE,
  output reg ERROR
);

wire found, err;
reg [7:0] reg_a, reg_b, next_a, next_b;
reg [7:0] big_one;
reg error_next;
reg [1:0] state, state_next;

parameter [1:0] IDLE = 2'b00;
parameter [1:0] CALC = 2'b01;
parameter [1:0] FINISH = 2'b10;

/* Finite State Machine Controller */
always @(posedge RST_N) begin
	if (RST_N) begin
		DONE <= 0;
		error_next <= 0;
		state_next <= IDLE;
		Y <= 0;
	end
end

always @(posedge START) begin
	if (START) begin
		state_next <= CALC;
	end
end

always @(posedge CLK) begin
	if (found || ERROR) begin
		state_next <= FINISH;
	end
end

always @* begin
	if (state == FINISH) begin
		if (found) begin
			Y <= big_one;
		end
		DONE <= 1;
		state_next <= IDLE;
	end
end

always @* begin
	if (state == IDLE && DONE == 1) begin
		DONE <= 0;
		error_next <= 0;
		Y <= 0;
	end
end

always @(posedge CLK) begin
	state <= state_next;
	ERROR <= error_next;
end
/* End of finite state machine controller */ 

assign err = (A == 0 || B == 0);

/* Feed inputs */
always @(posedge START) begin
	reg_a <= (A > B ? A : B);
	reg_b <= (A < B ? A : B);
	error_next <= (A == 0 || B == 0);
end

/* Combinational circuits for calculation */
always @* begin
	next_a <= reg_a - reg_b;
	next_b <= reg_b;
end

/* Swap the variables if a < b */
always @(posedge CLK) begin
	if (state == CALC) begin
		if (next_a < next_b) begin
			reg_a <= next_b;
			reg_b <= next_a;
			big_one <= next_b;
		end else begin
			reg_a <= next_a;
			reg_b <= next_b;
			big_one <= next_a;
		end
	end
end

assign found = (reg_b == 0 && state == CALC);

endmodule
