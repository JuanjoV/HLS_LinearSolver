############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2013 Xilinx Inc. All rights reserved.
############################################################

# Create a Vivado HLS project
open_project -reset CholeskyLinearSolver_prj
set_top CholeskyLS
add_files CholeskyLS.cpp

# Solution1 *************************
open_solution -reset "solution1"
#set_part  {xcvu9p-flgb2104-1-e}
#zybo part
set_part {xc7z010-clg400-1}
create_clock -period 10

# Run C simulation
#csim_design
# Run Synthesis
#csynth_design
# Run RTL verification
#cosim_design
# Create the IP package
#export_design

exit
