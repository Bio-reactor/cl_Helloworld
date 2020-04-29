/**********
Copyright (c) 2019, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

// This function represents an OpenCL kernel. The kernel will be call from
// host application using the xcl_run_kernels call. The pointers in kernel
// parameters with the global keyword represents cl_mem objects on the FPGA
// DDR memory.
//
#define BUFFER_SIZE 200
#define DATA_SIZE 1024

//TRIPCOUNT indentifier
__constant uint c_len = DATA_SIZE/BUFFER_SIZE;
__constant uint c_size = BUFFE 	R_SIZE;

__kernel __attribute__((reqd_work_group_size(1, 1, 1)))
void LSTM(global float* op, global  float* in, const float bii,
			const float bif, const float big, const float bio,
	const float bhi, const float bhf, const float bho, const float bhg,
	const float wii, const float wif, const float wig, const float wio, 
	const float whi, const float whf, const float whg, const float who,)
{
	
    int arrayA[BUFFER_SIZE];
    float it[30],ft[30],gt[30],ot[30],ct[30],ht[30],mul1,mul2,mul3; 
	float htm1[30],ctm1[30];
   
    __attribute__((xcl_loop_tripcount(c_len, c_len)))
    for (int i = 0 ; i < 200 ; i +=1) {
         // it calculation
          for(int j=0; j< 30;j+=1){
            for(int k=0;k<3;k+=1){
		mul1[j][k]=wii[j][k]*in[i][k];
		}
        
        }

	for(int j=0; j< 30;j+=1)
	{
            for(int k=0;k<30;k+=1)
		{
		mul2[j][k]=whi[j][k]*htm1[k];
		}
        }
       for(int j=0; j< 30;j+=1)
	{
            it[i]=mul1[i]+mul2[i]+bii[i]+bhi[i];
        }
	
	for(int j=0; j< 30;j+=1)
	{
           it[i]= 1/(1+exp(-1*it[i]));
        }
	// ft calculation
          for(int j=0; j< 30;j+=1){
            for(int k=0;k<3;k+=1){
		mul1[j][k]=wif[j][k]*in[i][k];
		}
        
        }

	for(int j=0; j< 30;j+=1)
	{
            for(int k=0;k<30;k+=1)
		{
		mul2[j][k]=whf[j][k]*htm1[k];
		}
        }
       for(int j=0; j< 30;j+=1)
	{
            ft[i]=mul1[i]+mul2[i]+bif[i]+bhf[i];
        }
	
	for(int j=0; j< 30;j+=1)
	{
           ft[i]= 1/(1+exp(-1*ft[i]));
        }

	// gt calculation
          for(int j=0; j< 30;j+=1){
            for(int k=0;k<3;k+=1){
		mul1[j][k]=wig[j][k]*in[i][k];
		}
        
        }

	for(int j=0; j< 30;j+=1)
	{
            for(int k=0;k<30;k+=1)
		{
		mul2[j][k]=whg[j][k]*htm1[k];
		}
        }
       for(int j=0; j< 30;j+=1)
	{
            gt[i]=mul1[i]+mul2[i]+big[i]+bhg[i];
        }
	
	for(int j=0; j< 30;j+=1)
	{
           ft[i]= (exp(gt[i])-exp(-1*gt[i]))/(exp(gt[i])+exp(-1*it[i]));
        }
        
	// ot calculation
          for(int j=0; j< 30;j+=1){
            for(int k=0;k<3;k+=1){
		mul1[j][k]=wio[j][k]*in[i][k];
		}
        
        }

	for(int j=0; j< 30;j+=1)
	{
            for(int k=0;k<30;k+=1)
		{
		mul2[j][k]=who[j][k]*htm1[k];
		}
        }
       for(int j=0; j< 30;j+=1)
	{
            ot[i]=mul1[i]+mul2[i]+bio[i]+bho[i];
        }
	
	for(int j=0; j< 30;j+=1)
	{
           ot[i]= 1/(1+exp(-1*ot[i]));
        }
   // ct calculation
	 for(int i=0; i< 30;i+=1)
	{
           ct[i]= ft[i]*ctm1[i]+ it[i]*gt[i];
        }
 // ht calculation
	for(int i=0; i< 30;i+=1)
	{
           ht[i]= ot[i]*((exp(ct[i])-exp(-1*ct[i]))/(exp(ct[i])+exp(-1*ct[i])));
        }
     ctm1=ct;
	htm1=ht;
       

}
op=ct;
}
