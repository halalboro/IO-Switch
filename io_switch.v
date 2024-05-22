// 4x4 Streaming I/O Switch built on a simplified version of AXI protocol
// Made by - Anubhav Panda 

//Instantiate the module by defining all inputs and outputs
module io_switch #(
    parameter DATA_WIDTH = 32
) (
    input clk,
    input rst,

    // Control Interface
    input [1:0] ctrl_addr,
    input ctrl_wr_en,
    input [1:0] ctrl_wr_data,

    // Input Streaming Interfaces
    input [DATA_WIDTH-1:0] in_data_0,
    input reg in_valid_0,
    output in_ready_0,

    input [DATA_WIDTH-1:0] in_data_1,
    input reg in_valid_1,
    output in_ready_1,

    input [DATA_WIDTH-1:0] in_data_2,
    input reg in_valid_2,
    output in_ready_2,

    input [DATA_WIDTH-1:0] in_data_3,
    input reg in_valid_3,
    output in_ready_3,

    // Output Streaming Interfaces
    output reg [DATA_WIDTH-1:0] out_data_0,
    output out_valid_0,
    input out_ready_0,

    output reg [DATA_WIDTH-1:0] out_data_1,
    output out_valid_1,
    input out_ready_1,

    output reg [DATA_WIDTH-1:0] out_data_2,
    output out_valid_2,
    input out_ready_2,

    output reg [DATA_WIDTH-1:0] out_data_3,
    output out_valid_3,
    input out_ready_3
);

    // Registers to store the routing logic
    reg [1:0] routing_reg_0, routing_reg_1, routing_reg_2, routing_reg_3;

    // Main Logic 
    always @(posedge clk) begin
        if (rst) begin
            // Reset all registers
            routing_reg_0 <= 2'b00;
            routing_reg_1 <= 2'b00;
            routing_reg_2 <= 2'b00;
            routing_reg_3 <= 2'b00;

        end else if (ctrl_wr_en) begin
            // Write to the routing registers from the routing table
            case (ctrl_addr)
                2'd0: routing_reg_0 <= ctrl_wr_data;
                2'd1: routing_reg_1 <= ctrl_wr_data;
                2'd2: routing_reg_2 <= ctrl_wr_data;
                2'd3: routing_reg_3 <= ctrl_wr_data;
            endcase
        end    
    end

    // Output assignments instantiated in the form of a state machine
    always @(negedge clk) begin
        case (routing_reg_0)
            2'b00: begin
                out_data_0 <= in_data_0;
                out_valid_0 <= in_valid_0;
                in_ready_0 <= out_ready_0;
            end
            2'b01: begin
                out_data_0 <= in_data_1;
                out_valid_0 <= in_valid_1;
                in_ready_1 <= out_ready_0;
            end
            2'b10: begin
                out_data_0 <= in_data_2;
                out_valid_0 <= in_valid_2;
                in_ready_2 <= out_ready_0;
            end
            2'b11: begin
                out_data_0 <= in_data_3;
                out_valid_0 <= in_valid_3; 
                in_ready_3 <= out_ready_0;
            end
        endcase

        case (routing_reg_1)
            2'b00: begin
                out_data_1 <= in_data_0;
                out_valid_1 <= in_valid_0;
                in_ready_0 <= out_ready_1;
            end
            2'b01: begin
                out_data_1 <= in_data_1;
                out_valid_1 <= in_valid_1;
                in_ready_1 <= out_ready_1;
            end
            2'b10: begin
                out_data_1 <= in_data_2;
                out_valid_1 <= in_valid_2;
                in_ready_2 <= out_ready_1;
            end
            2'b11: begin
                out_data_1 <= in_data_3;
                out_valid_1 <= in_valid_3;
                in_ready_3 <= out_ready_1;
            end
        endcase

        case (routing_reg_2)
            2'b00: begin
                out_data_2 <= in_data_0;
                out_valid_2 <= in_valid_0;
                in_ready_0 <= out_ready_2; 
            end
            2'b01: begin
                out_data_2 <= in_data_1;
                out_valid_2 <= in_valid_1;
                in_ready_1 <= out_ready_2;
            end
            2'b10: begin
                out_data_2 <= in_data_2;
                out_valid_2 <= in_valid_2;
                in_ready_2 <= out_ready_2;
            end
            2'b11: begin
                out_data_2 <= in_data_3;
                out_valid_2 <= in_valid_3;
                in_ready_3 <= out_ready_2;
            end
        endcase

        case (routing_reg_3)
            2'b00: begin
                out_data_3 <= in_data_0;
                out_valid_3 <= in_valid_0;
                in_ready_0 <= out_ready_3;
            end
            2'b01: begin
                out_data_3 <= in_data_1;
                out_valid_3 <= in_valid_1;
                in_ready_1 <= out_ready_3;
            end
            2'b10: begin
                out_data_3 <= in_data_2;
                out_valid_3 <= in_valid_2;
                in_ready_2 <= out_ready_3;
            end
            2'b11: begin
                out_data_3 <= in_data_3;
                out_valid_3 <= in_valid_3;
                in_ready_3 <= out_ready_3;
            end
        endcase
    end

endmodule