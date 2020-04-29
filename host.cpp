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
#include "xcl2.hpp"
#include <vector>

using std::vector;

static const int DATA_SIZE = 1024;
static const std::string error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %d Device result = %d\n";

// This example illustrates the very simple OpenCL example that performs
// an addition on two vectors
int main(int argc, char **argv) {
	float input_in[200][3], output[3];
     if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File>" << std::endl;
        return EXIT_FAILURE;
    }
	
	string bh_array[120],bi_arr[120],wii_array[90],wif_array[90],wig_array[90],wio_array[90];
    string who_array[900],whg_array[900],whi_array[900],whf_array[900]; 
    string bhi[30],bhf[30],bhg[30],bho[30];// creates array to hold names
    string bii[30],bif[30],big[30],bio[30];
    string wii[30][3],wif[30][3],wig[30][3],wio[30][3];
    string whi[30][30],whf[30][30],whg[30][30],who[30][30];
    
    float bhif[30],bhff[30],bhgf[30],bhof[30];// creates array to hold names
     
    float biif[30],biff[30],bigf[30],biof[30];
    
    float wiif[30][3],wiff[30][3],wigf[30][3],wiof[30][3];
    
    float whif[30][30],whff[30][30],whgf[30][30],whof[30][30];
    
    short loop=0; //short for loop for input
    string line,line1,line2,line3,line4,line5,line6,line7,line8,line9; //this will contain the data read from the file
    ifstream myfile ("bh.txt"); //opening the file.
    ifstream myfile1 ("bi.txt");
    ifstream myfile2 ("wii.txt");
    ifstream myfile3 ("wif.txt");
    ifstream myfile4 ("wig.txt");
    ifstream myfile5 ("wio.txt");
    ifstream myfile6("whi.txt");
    ifstream myfile7("whf.txt");
    ifstream myfile8("whg.txt");
    ifstream myfile9("who.txt");
    if (myfile.is_open()& myfile1.is_open()) //if the file is open
    {
        while (! myfile.eof() & !myfile1.eof() ) //while the end of file is NOT reached
        {
            getline (myfile,line); //get one line from the file
            bh_array[loop] = line;
            getline (myfile1,line1); //get one line from the file
            bi_arr[loop] = line1;
             //and output it
            loop++;
        }
        myfile.close(); //closing the file
        myfile1.close();
    }
    else cout << "Unable to open file"; //if the file is not open output
    
    
    for (int i = 0; i < 30; i++)
    {   
        bhi[i]=(bh_array[i]);
        bhf[i]=(bh_array[i+30]);
       
        bhg[i]=(bh_array[i+60]);
         
        bho[i]=(bh_array[i+90]);
        
        bii[i]=(bi_arr[i]);
         
        bif[i]=(bi_arr[i+30]);
         
        big[i]=(bi_arr[i+60]);
         
        bio[i]=(bi_arr[i+90]);
        
        
    }
    
    for (int i = 0; i < 30; i++)
    {   
        bhif[i]=stof(bhi[i]);
        bhff[i]=stof(bhf[i]);
       
        bhgf[i]=stof(bhg[i]);
         
        bhof[i]=stof(bho[i]);
        
        biif[i]=stof(bii[i]);
         
        biff[i]=stof(bif[i]);
         
        bigf[i]=stof(big[i]);
         
        biof[i]=stof(bio[i]);
        
        
    }
    loop=0;
    if (myfile2.is_open() & myfile3.is_open() & myfile4.is_open() & myfile5.is_open()) //if the file is open
    {
        while (! myfile2.eof() & !myfile3.eof() & !myfile4.eof() & !myfile5.eof() ) //while the end of file is NOT reached
        {  
            getline (myfile2,line2); //get one line from the file
            wii_array[loop] = line2;
            getline (myfile3,line3); //get one line from the file
            wif_array[loop] = line3;
            getline (myfile4,line4); //get one line from the file
            wig_array[loop] = line4;
            getline (myfile5,line5); //get one line from the file
            wio_array[loop] = line5;
             //and output it
             //cout<<wig_array[loop]<<endl;
            loop++;
        }
        myfile2.close(); //closing the file
        myfile3.close();
        myfile4.close();
        myfile5.close();
    }
    else cout << "Unable to open file"; //if the file is not open output
    
    
    for (int i = 0; i < 30; i++)
    {  
        for (int j=0;j<3;j++){
            
       wii[i][j]=(wii_array[i+(j*30)]);
       wif[i][j]=(wif_array[i+(j*30)]);
       wiif[i][j]=stof(wii[i][j]);
       wiff[i][j]=stof(wif[i][j]);
       wig[i][j]=(wig_array[i+(j*30)]);
       wio[i][j]=(wio_array[i+(j*30)]);
       wigf[i][j]=stof(wig[i][j]);
       wiof[i][j]=stof(wio[i][j]);
       
       //cout<< wiof[i][j]<<endl;
       //cout<<i<<endl;
        }
    }
    
    loop=0;
    if (myfile6.is_open() & myfile7.is_open() & myfile8.is_open())// & myfile9.is_open()) //if the file is open
    {
        while (! myfile6.eof()  & !myfile7.eof() & !myfile8.eof())// & !myfile9.eof() ) //while the end of file is NOT reached
        {  
            getline (myfile6,line6); //get one line from the file
            whi_array[loop] = line6;
            getline (myfile7,line7); //get one line from the file
            whf_array[loop] = line7;
            getline (myfile8,line8); //get one line from the file
            whg_array[loop] = line8;
            getline (myfile9,line9); //get one line from the file
            who_array[loop] = line9;
             //and output it
             //cout<<who_array[loop]<<endl;
            loop++;
        }
        myfile6.close(); //closing the file
        myfile7.close();
        myfile8.close();
        //myfile9.close();
    }
    else cout << "Unable to open file"; //if the file is not open output
    
    
    for (int i = 0; i < 30; i++)
    {  
        for (int j=0;j<30;j++){
            
       whi[i][j]=(whi_array[i+(j*30)]);
       whf[i][j]=(whf_array[i+(j*30)]);
       whif[i][j]=stof(whi[i][j]);
       whff[i][j]=stof(whf[i][j]);
       whg[i][j]=(whg_array[i+(j*30)]);
       who[i][j]=(who_array[i+(j*30)]);
       whgf[i][j]=stof(whg[i][j]);
       whof[i][j]=stof(who[i][j]);
       
      cout<< whof[i][j]<<endl;
       //cout<<i<<endl;
        }
    }
    
    
    cl_int err;
    cl::CommandQueue q;
    cl::Kernel LSTM;
    cl::Context context;

    // Creates a vector of DATA_SIZE elements with an initial value of 10 and 32
    
      
    // The get_xil_devices will return vector of Xilinx Devices
    auto devices = xcl::get_xil_devices();

    // read_binary_file() is a utility API which will load the binaryFile
    // and will return the pointer to file buffer.
    auto fileBuf = xcl::read_binary_file(binaryFile);
    cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};
    int valid_device = 0;
    for (unsigned int i = 0; i < devices.size(); i++) {
        auto device = devices[i];
        // Creating Context and Command Queue for selected Device
        OCL_CHECK(err, context = cl::Context({device}, NULL, NULL, NULL, &err));
        OCL_CHECK(err,
                  q = cl::CommandQueue(
                      context, {device}, CL_QUEUE_PROFILING_ENABLE, &err));

        std::cout << "Trying to program device[" << i
                  << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
        cl::Program program(context, {device}, bins, NULL, &err);
        if (err != CL_SUCCESS) {
            std::cout << "Failed to program device[" << i
                      << "] with xclbin file!\n";
        } else {
            std::cout << "Device[" << i << "]: program successful!\n";
            // This call will extract a kernel out of the program we loaded in the
            // previous line. A kernel is an OpenCL function that is executed on the
            // FPGA. This function is defined in the src/vetor_addition.cl file.
            OCL_CHECK(
                err, LSTM = cl::Kernel(program, "lstm", &err));
            valid_device++;
            break; // we break because we found a valid device
        }
    }
    if (valid_device == 0) {
        std::cout << "Failed to program any device found, exit!\n";
        exit(EXIT_FAILURE);
    }

    // These commands will allocate memory on the FPGA. The cl::Buffer objects can
    // be used to reference the memory locations on the device. The cl::Buffer
    // object cannot be referenced directly and must be passed to other OpenCL
    // functions.
	
    OCL_CHECK(err,
              cl::Buffer buffer_in(context,
                                  CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
                                  size_in_bytes,
                                  input_in,
                                  &err));
   
    OCL_CHECK(err,
              cl::Buffer buffer_op(context,
                                       CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
                                       size_in_bytes,
                                       output,
                                       &err));



// float bhif[30],bhff[30],bhgf[30],bhof[30];// creates array to hold names
     
   // float biif[30],biff[30],bigf[30],biof[30];
    
    //float wiif[30][3],wiff[30][3],wigf[30][3],wiof[30][3];
    
    //float whif[30][30],whff[30][30],whgf[30][30],whof[30][30];

    //set the kernel Arguments
    int narg = 0;
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++, buffer_in));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++, buffer_op));
    
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,biif ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,biff ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,bigf ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,biof ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,bhif ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,bhff ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,bhof ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,bhgf ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,wiif ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,wiff ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,wigf ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,wiof ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,whif ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,whff ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,whgf ));
    OCL_CHECK(err, err = krnl_img_thresh.setArg(narg++,whof ));

    // These commands will load the source_a and source_b vectors from the host
    // application and into the buffer_a and buffer_b cl::Buffer objects. The data
    // will be be transferred from system memory over PCIe to the FPGA on-board
    // DDR memory.
    OCL_CHECK(err,
              err = q.enqueueMigrateMemObjects({buffer_in},
                                               0 /* 0 means from host*/));

    //Launch the Kernel
    //This is equivalent to calling the enqueueNDRangeKernel function with a 
    //dimensionality of 1 and a global work size (NDRange) of 1.
    OCL_CHECK(err, err = q.enqueueTask(krnl_LSTM));

    // The result of the previous kernel execution will need to be retrieved in
    // order to view the results. This call will write the data from the
    // buffer_result cl_mem object to the source_results vector
    OCL_CHECK(err,
              err = q.enqueueMigrateMemObjects({buffer_op},
                                               CL_MIGRATE_MEM_OBJECT_HOST));
    q.finish();

    int match = 0;
    printf("Result = \n");
    for (int i = 0; i < isize; i++) {
		int host_result;
		if(img_in[i]>150)
          img_op[i]=255;
         else img_op[i]=0;
        
    }
    for (int i = 0; i < isize; i++) {
    if (img_os[i] != img_op[i]) {
            printf(error_message.c_str(), i, host_result, source_results[i]);
            match = 1;
            break;
        } 
 }
    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl;
    return (match ? EXIT_FAILURE : EXIT_SUCCESS);
}
