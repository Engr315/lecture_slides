module custom_hw_popcount (
	input 		ACLK,
	input 		ARESETN,
	input [31:0] 	S_TDATA,
	input		S_TVALID,
	output		S_TREADY,
	output [31:0] 	M_TDATA,
	output	 	M_TVALID,
	input	 	M_TREADY
);

integer i;
logic [31:0] tmp;

always_comb begin
    tmp = 32'h0;
    for (i = 0; i < 32; ++i) tmp += S_TDATA[i];
end

assign M_TDATA = tmp;
assign M_TVALID = S_TVALID;
assign S_TREADY = M_TREADY;

endmodule

