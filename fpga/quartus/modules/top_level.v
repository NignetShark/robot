// Top level wrapper

module top_level(
	clock,
	reset,
	channelA,
	channelB,
	led
);


input wire	clock;
input wire	reset;
input wire	channelA;
input wire	channelB;
output wire	[5:0] led;

wire	not_reset;
wire 	[31:0] position;

RotaryEncoder	rotaryEncoder(
	.clock(clock),
	.reset(not_reset),
	.io_channelA(channelA),
	.io_channelB(channelB),
	.io_position(position));

assign led = position[5:0];
assign not_reset = ~reset;


endmodule
