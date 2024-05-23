// Testbench for io_switch.v
// Made by - Anubhav Panda


// Including the necessary libraries
#include "Vio_switch.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>

#define DATA_WIDTH 32

// Global variables for simulation time
vluint64_t main_time = 0;           // Current simulation time 
const vluint64_t sim_time = 100;    // Number of simulation steps


// Time stamp function used by Verilator
double sc_time_stamp() { 
    return main_time;
}


// Enables the clock and evaluates the DUT (Device Under Test)
void tick(Vio_switch* top, VerilatedVcdC* tfp) {
    top->clk = !top->clk;
    top->eval();
    main_time++;
    if (tfp) tfp->dump(main_time);
}


// Main function
int main(int argc, char **argv, char **env) {
    // Start Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the DUT 
    Vio_switch* top = new Vio_switch;

    // Enable tracing
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("io_switch.vcd");

    // Reset and apply all required signals
    top->clk = 0;
    top->rst = 1;
    top->in_valid_0 = 1;
    top->in_valid_1 = 1;
    top->in_valid_2 = 1;
    top->in_valid_3 = 1;
    top->out_ready_0 = 1;
    top->out_ready_1 = 1;
    top->out_ready_2 = 1;
    top->out_ready_3 = 1;
    tick(top, tfp);        // Generates a clock tick
    top->rst = 0;


    //Test Case 1 - Many Inputs to One Output

    //Input Data Stream
    top->in_data_0 = 0xAAAAAAAA;
    top->in_data_1 = 0xBBBBBBBB;
    top->in_data_2 = 0xCCCCCCCC;
    top->in_data_3 = 0xDDDDDDDD;

    // Routing Configuration
    top->ctrl_wr_en = 1;

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 1; // Input 0 to Output 0
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 2; // Input 1 to Output 0
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 4; // Input 2 to Output 0
    tick(top, tfp);
    tick(top, tfp); 

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 7; // Input 3 to Output 0
    tick(top, tfp);
    tick(top, tfp);


    top->ctrl_wr_en = 0; // Disable control write after configuration complete

    for (int i = 0; i < 5; ++i) {
    tick(top, tfp);
    }


    // Test Case 2 - One Input to One Output

    //Input Data Stream
    top->in_data_0 = 0x0000000A;
    top->in_data_1 = 0x0000000B;
    top->in_data_2 = 0x0000000C;
    top->in_data_3 = 0x0000000D;

    // Routing Configuration
    top->ctrl_wr_en = 1;

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 1; // Input 0 to Output 0
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 1;
    top->ctrl_wr_data = 2; // Input 1 to Output 1
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 2;
    top->ctrl_wr_data = 4; // Input 2 to Output 2
    tick(top, tfp);
    tick(top, tfp); 

    top->ctrl_addr = 3;
    top->ctrl_wr_data = 7; // Input 3 to Output 3
    tick(top, tfp);
    tick(top, tfp);


    top->ctrl_wr_en = 0; // Disable control write after configuration complete
    

    for (int i = 0; i < 5; ++i) {
    tick(top, tfp);
    }


    // Test Case 3 - One Input to Many Outputs

    //Input Data Stream
    top->in_data_0 = 0x10000000;
    top->in_data_1 = 0x11000000;
    top->in_data_2 = 0x11100000;
    top->in_data_3 = 0x11110000;

    // Routing Configuration
    top->ctrl_wr_en = 1;

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 1; // Input 0 to Output 0
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 1;
    top->ctrl_wr_data = 1; // Input 0 to Output 1
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 2;
    top->ctrl_wr_data = 1; // Input 0 to Output 2
    tick(top, tfp);
    tick(top, tfp); 

    top->ctrl_addr = 3;
    top->ctrl_wr_data = 1; // Input 0 to Output 3
    tick(top, tfp);
    tick(top, tfp);


    top->ctrl_wr_en = 0; // Disable control write after configuration complete
    

    for (int i = 0; i < 5; ++i) {
    tick(top, tfp);
    }


    // Test Case 4 - Wrong Routing Configuration

    //Input Data Stream
    top->in_data_0 = 0x10000001;
    top->in_data_1 = 0x11000011;
    top->in_data_2 = 0x11100111;
    top->in_data_3 = 0x11111111;

    // Routing Configuration
    top->ctrl_wr_en = 1;

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 3; // Wrong Value
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 1;
    top->ctrl_wr_data = 5; // Wrong Value
    tick(top, tfp);
    tick(top, tfp);

    top->ctrl_addr = 2;
    top->ctrl_wr_data = 3; // Wrong Value
    tick(top, tfp);
    tick(top, tfp); 

    top->ctrl_addr = 3;
    top->ctrl_wr_data = 5; // Wrong Value
    tick(top, tfp);
    tick(top, tfp);


    top->ctrl_wr_en = 0; // Disable control write after configuration complete



    // Simulate
    for (int i = 0; i < 40; ++i) {
        tick(top, tfp);

        // Printing out_data for debugging
        std::cout << "At time " << main_time << ":\n";
        std::cout << "out_data_0: " << std::hex << top->out_data_0 << ", out_valid_0: " << top->out_valid_0 << "\n";
        std::cout << "out_data_1: " << std::hex << top->out_data_1 << ", out_valid_1: " << top->out_valid_1 << "\n";
        std::cout << "out_data_2: " << std::hex << top->out_data_2 << ", out_valid_2: " << top->out_valid_2 << "\n";
        std::cout << "out_data_3: " << std::hex << top->out_data_3 << ", out_valid_3: " << top->out_valid_3 << "\n";
    }

    //Clean up and exit
    tfp->close();
    delete top;
    delete tfp;
    return 0;
}
