######################################
# You can change the initialization paramters below
# Inspired on automatically generated file by Vivado HLS.
######################################

# Create a Vivado HLS project
open_project -reset CholeskyLinearSolver_prj
set_top CholeskyLS
add_files CholeskyLS.cpp
add_files -tb out.gold.dat
add_files -tb CholeskyLS_test.cpp


# Solution1 *************************
open_solution -reset "solution1"

#zybo part
set_part {xc7z010-clg400-1}
#Objetive clock
create_clock -period 10


## Uncomment the following lines with a single # if your code is already 
## verified

## Run C simulation
#sim_design

## Run Synthesis
#csynth_design

## Run RTL verification
#cosim_design

## Create the IP package
#export_design

exit
