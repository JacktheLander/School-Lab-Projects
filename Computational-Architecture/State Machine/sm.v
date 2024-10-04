module l3_SM(input clk,
			 input execute,
			 input [2:0] operation,
			 output reg _Extern,
			 output reg Gout,
			 output reg Ain,
			 output reg Gin,
			 output reg RdX,
			 output reg RdY,
			 output reg WrX,
			 output reg add_sub,
			 output reg DPin,
			 output reg Iout,
		/* TODO 1: complete the module declaration */
			 output [3:0] cur_state);
			
	//defining all my states - 8 total
	parameter IDLE 		=  4'b0000;
	parameter LOAD 		=  4'b0001;
	parameter READ_Y 	=  4'b0010;
	parameter READ_X 	=  4'b0011;
	parameter ADD 		=  4'b0100;
	parameter SUB 		=  4'b0101;
	parameter MV 		=  4'b0110;
	parameter WRITE_X 	=  4'b0111;
	parameter DONE 		=  4'b1000;
	parameter SUBI      =  4'b1001;
	parameter ADDI      =  4'b1010;
	parameter DISP      =  4'b1011;
	/* TODO 2: define more state */
	
	reg [3:0] state = IDLE; // initial state being IDLE
	 
	assign cur_state = state;
	
	initial begin //instead of reset
      state <= IDLE;
	end
	
	always@(*)
	begin
	   case(state)
	       IDLE:
	           begin
	               _Extern = 1'b0;
	               Gout = 1'b0;
	               Iout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b0;
	               DPin = 1'b0;
	               RdX = 1'b0;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	           end
            LOAD:
	           begin
                   _Extern = 1'b1;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b0;
	               RdX = 1'b0;
	               RdY = 1'b0;
	               WrX = 1'b1;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end	   
	       READ_Y:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b1;
	               Gin = 1'b0;
	               RdX = 1'b0;
	               RdY = 1'b1;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end	   
	       READ_X:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b1;
	               Gin = 1'b0;
	               RdX = 1'b1;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end	  
	       ADD:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b1;
	               RdX = 1'b1;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end	
	       SUB:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b1;
	               RdX = 1'b0;
	               RdY = 1'b1;
	               WrX = 1'b0;
	               add_sub = 1'b1;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end
	       MV:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b1;
	               RdX = 1'b0;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end
	       WRITE_X:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b1;
	               Ain = 1'b0;
	               Gin = 1'b0;
	               RdX = 1'b0;
                   RdY = 1'b0;
	               WrX = 1'b1;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end	           
	       DONE:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b0;
	               RdX = 1'b0;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b0;
	           end
	       ADDI:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b1;
	               RdX = 1'b0;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b1;
	               DPin = 1'b0;
	           end
	       SUBI:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b1;
	               RdX = 1'b0;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b1;
	               Iout = 1'b1;
	               DPin = 1'b0;
	           end
	       DISP:
	           begin
			       _Extern = 1'b0;
	               Gout = 1'b0;
	               Ain = 1'b0;
	               Gin = 1'b0;
	               RdX = 1'b1;
	               RdY = 1'b0;
	               WrX = 1'b0;
	               add_sub = 1'b0;
	               Iout = 1'b0;
	               DPin = 1'b1;
	           end
	   endcase
	end

/*
opcode encodings
000 - load
001 - move
010 - subtract
011 - add
100 - disp
101 - reserved
110 - subi
111 - addi
*/
			 
	always@(posedge clk)
	begin
		
		case(state)
			/* TODO 4: complete the next state logic */
			IDLE: begin
					if(execute == 1 && operation == 0) state <= LOAD;
					if(execute == 1 && operation == 1) state <= READ_Y; 
					if(execute == 1 && operation == 3) state <= READ_Y;
					if(execute == 1 && operation == 2) state <= READ_X;
					if(execute == 1 && operation == 4) state <= DISP;
					if(execute == 1 && operation == 6) state <= READ_X;
					if(execute == 1 && operation == 7) state <= READ_X;
			  end
				  
			LOAD: begin
					state <= DONE; // always go to the DONE state at the next clock tick
				  end
				  
			READ_Y: begin
					if(execute == 1 && operation == 1) state <= MV; 
					if(execute == 1 && operation == 3) state <= ADD;

				end
					
			READ_X: begin
					if(execute == 1 && operation == 2) state <= SUB;
					if(execute == 1 && operation == 6) state <= SUBI;
					if(execute == 1 && operation == 7) state <= ADDI;
				end
					
			ADD: begin
					state <= WRITE_X;

			 end
				 
			SUB: begin
					state <= WRITE_X;


				 end
				 
			MV: begin
					state <= WRITE_X;

				end
				
			WRITE_X: begin
					state <= DONE;

				 end
				 
			DISP: begin
					state <= DONE;


				 end
				 
			SUBI: begin
					state <= WRITE_X;


				 end
				
			ADDI: begin
					state <= WRITE_X;


				 end
					 
			DONE: begin

					//back to idle if execute back to low
					if(execute == 0) state <= IDLE;
					
				  end
			        	  
			default: state <= IDLE;
			
		endcase
				
	end //end always
	
	
			 
			 
			 
endmodule


