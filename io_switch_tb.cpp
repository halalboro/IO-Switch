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

    // Routing Configuration
    top->ctrl_wr_en = 1;

    top->ctrl_addr = 0;
    top->ctrl_wr_data = 0; // Input 0 to Output 0
    tick(top, tfp);

    top->ctrl_addr = 1;
    top->ctrl_wr_data = 1; // Input 1 to Output 1
    tick(top, tfp);
    tick(top, tfp);        // This extra clock tick is to make sure that the configuration is complete (as it occurs at negative edge of clock)

    top->ctrl_addr = 2;
    top->ctrl_wr_data = 2; // Input 2 to Output 2
    tick(top, tfp);
    tick(top, tfp);        // This extra clock tick is to make sure that the configuration is complete (as it occurs at negative edge of clock)

    top->ctrl_addr = 3;
    top->ctrl_wr_data = 3; // Input 3 to Output 3
    tick(top, tfp);


    top->ctrl_wr_en = 0; // Disable control write after configuration complete

    //Input Data Stream
    top->in_data_0 = 0xAAAAAAAA;
    top->in_data_1 = 0xBBBBBBBB;
    top->in_data_2 = 0xCCCCCCCC;
    top->in_data_3 = 0xDDDDDDDD;


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
