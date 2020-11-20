/*******************************************************************************
Vendor: Xilinx 
Associated Filename: window_fn_test.cpp
Purpose: Vivado HLS tutorial example 
Revision History: March 13, 2012 - initial release
                                                
*******************************************************************************
Copyright (C) 2013 XILINX, Inc. 

This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer assumes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "CholeskyLS.h"

#define ABS_ERR_THRESH 0.01


int main(void)
{
   cout << "Running Test..." << endl;
   fixedP testA[A_LEN][A_LEN];
   fixedP testb[A_LEN];
   fixedP hw_result[A_LEN];
   fixedP x;
   string line;
   float sw_result[A_LEN];
   unsigned err_cnt = 0;
   ifstream inFile;
   float number;
   inFile.open("D:\\Users\\juanj\\U\\IPD432\\Ejercicios\\LinearSolver\\out.gold.dat");

   if(!inFile.is_open())
   {
	   cerr << "Unable to open file out.gold.dat";
	   exit(1);
   }

   for (int r = 0; r < N_SYS; r++)
   {
	   for (int i = 0; i < A_LEN; i++)
	   {
		   getline(inFile, line);
		   stringstream stream(line);

		   for (int j = 0; j < A_LEN; j++)
		   {
			   stream >> number;
			   testA[i][j] = number;

		   }
		   stream >> number;
		   testb[i] = number;
	   }

	   for (int k = 0; k < A_LEN; k++)
	   {
		   getline(inFile,line);
		   stringstream stream(line);
		   stream >> number;
		   sw_result[k] = number;

	   }

	   //Run the DUT
	   CholeskyLS(testA, testb, hw_result);

	   cout << "Checking results against a tolerance of " << ABS_ERR_THRESH <<endl;
	   cout << fixed << setprecision(5);
	   for (int i = 0; i < A_LEN;i++)
	   {
		   float abs_err = float(hw_result[i]) - sw_result[i];
		   cout << "i = " << i << "\thw_result = " << hw_result[i];
		   cout << "\t sw_result = " << sw_result[i] << endl;
		   if (fabs(abs_err) > ABS_ERR_THRESH)
		   {
			   cout << "Error threshold exceeded: i = " << i;
			   cout << "  Expected: " << sw_result[i];
			   cout << "  Got: " << hw_result[i];
			   cout << "  Delta: " << abs_err << endl;
			   err_cnt++;
		   }


	   }
	   cout << endl;
   }
   inFile.close();
   if (err_cnt) {
	   cout << "!!! TEST FAILED - " << err_cnt;
	   cout << " results out of tolerance." << endl;
   } else
	   cout << "Test Passed" << endl;

   // Only return 0 on success
   return err_cnt;
}
