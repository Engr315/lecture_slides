module popcnt(
	input 		ACLK,
	input 		ARESETN,
	input [31:0] 	S_TDATA,
	input		S_TVALID,
	output		S_TREADY,
	output [31:0] 	M_TDATA,
	output	 	M_TVALID,
	input	 	M_TREADY
);

custom_hw_popcount hw0(
	.ACLK(ACLK),
	.ARESETN(ARESETN),
	.S_TDATA(S_TDATA),
	.S_TVALID(S_TVALID),
	.S_TREADY(S_TREADY),
	.M_TDATA(M_TDATA),
	.M_TVALID(M_TVALID),
	.M_TREADY(M_TREADY)
);


endmodule

