module register_file (write_data, write_addr, load_enable, read_addr0, read_addr1, read_data0, read_data1, CLK);

input  [7:0] write_data;
input  [2:0] write_addr;
input  load_enable;
input  [2:0] read_addr0;
input  [2:0] read_addr1;
input  CLK;

wire [7:0] read_data_bus1;
wire [7:0] read_data_bus2;
wire [7:0] read_data_bus3;
wire [7:0] read_data_bus4;
wire [7:0] read_data_bus5;
wire [7:0] read_data_bus6;
wire [7:0] read_data_bus7;
wire [7:0] read_data_bus8;
reg [7:0] load_enable_bus;

output reg[7:0] read_data0;
output reg [7:0] read_data1;

reg8 r1(load_enable_bus[0], CLK, write_data, read_data_bus1);
reg8 r2(load_enable_bus[1], CLK, write_data, read_data_bus2);
reg8 r3(load_enable_bus[2], CLK, write_data, read_data_bus3);
reg8 r4(load_enable_bus[3], CLK, write_data, read_data_bus4);
reg8 r5(load_enable_bus[4], CLK, write_data, read_data_bus5);
reg8 r6(load_enable_bus[5], CLK, write_data, read_data_bus6);
reg8 r7(load_enable_bus[6], CLK, write_data, read_data_bus7);
reg8 r8(load_enable_bus[7], CLK, write_data, read_data_bus8);

always @(posedge CLK) begin
	if(load_enable) begin 			
		case(write_addr)
			3'b000: load_enable_bus = 8'b00000001;
			3'b001: load_enable_bus = 8'b00000010;
			3'b010: load_enable_bus = 8'b00000100;
			3'b011: load_enable_bus = 8'b00001000;
			3'b100:	load_enable_bus = 8'b00010000;
			3'b101: load_enable_bus = 8'b00100000;
			3'b110:	load_enable_bus = 8'b01000000;
			3'b111: load_enable_bus = 8'b10000000;
		endcase
	end else begin
		load_enable_bus = 8'b00000000;
	end
	
	if(load_enable && read_addr0 == write_addr) begin
		read_data0 = write_data;
	end else begin
		case(read_addr0)
			3'b000: read_data0 = read_data_bus1;
			3'b001: read_data0 = read_data_bus2;
			3'b010: read_data0 = read_data_bus3;
			3'b011: read_data0 = read_data_bus4;
			3'b100: read_data0 = read_data_bus5;
			3'b101: read_data0 = read_data_bus6;
			3'b110: read_data0 = read_data_bus7;
			3'b111: read_data0 = read_data_bus8;
		endcase		
	end

	if (load_enable && read_addr1 == write_addr) begin
		read_data1 = write_data;
	end else begin
		case(read_addr1)
			3'b000: read_data1 = read_data_bus1;
			3'b001: read_data1 = read_data_bus2;
			3'b010: read_data1 = read_data_bus3;
			3'b011: read_data1 = read_data_bus4;
			3'b100: read_data1 = read_data_bus5;
			3'b101: read_data1 = read_data_bus6;
			3'b110: read_data1 = read_data_bus7;
			3'b111: read_data1 = read_data_bus8;
		endcase
	end
end



endmodule
