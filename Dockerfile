# Verilator Image as base
FROM verilator/verilator

# Installing dependencies
RUN apt-get update && \
    apt-get install -y git perl python3 make libgoogle-glog-dev \
                       libboost-dev libboost-program-options-dev \
                       libboost-thread-dev libboost-system-dev \
                       libboost-filesystem-dev libfl-dev ccache

# Working directory
WORKDIR /Documents

# Copy project files
COPY io_switch.v io_switch_tb.cpp ./

# Compile the design
RUN verilator --cc io_switch.v --exe io_switch_tb.cpp --trace

# Change the working directory
WORKDIR /Documents/obj_dir

# Build the makefile
RUN make -f Vio_switch.mk

# Run the simulation and create waveform
ENTRYPOINT ["bash", "-c", "./Vio_switch && mv io_switch.vcd /workspace/"]

# Save the generated waveform
VOLUME ["/workspace"]