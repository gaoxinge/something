#define PROFILING // Define to see the time the k rnel takes
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#define __CL_ENABLE_EXCEPTIONS // needed for exceptions
#include <CL/cl.hpp>

#include <fstream>

#include <iostream>

#include <string>

using namespace std;
 
void displayPlatformInfo(cl::vector< cl::Platform > platformList,
			 int deviceType)
{
  // print out some device specific information
  cout << "Platform number is: " << platformList.size() << endl;
    
  string platformVendor;
  platformList[0].getInfo((cl_platform_info)CL_PLATFORM_VENDOR, 
			  &platformVendor);
 
  cout << "device Type " 
       << ((deviceType==CL_DEVICE_TYPE_GPU)?"GPU":"CPU") << endl;
  cout << "Platform is by: " << platformVendor << "\n";
}
 
class OclTest {
private:
  int nIter, vLen,vSize;
  cl::Kernel kernel;
  int  *h_vecA, *h_vecB, *h_vecC;
  cl::Buffer d_vecA, d_vecB, d_vecC;
  
public:
  OclTest( cl::Context& context, cl::vector<cl::Device>& devices,
	   const char* kernelFile, int n_iter, int vecLen) {
    nIter = n_iter;
    vLen = vecLen;
    vSize = vLen * sizeof(int);
    
    // build the program from the source in the file
    ifstream file(kernelFile);
    string prog(istreambuf_iterator<char>(file),
		(istreambuf_iterator<char>()));
    cl::Program::Sources source( 1, make_pair(prog.c_str(),
					      prog.length()+1));
    cl::Program program(context, source);
    file.close();
 
    try {
      program.build(devices);
    } catch(cl::Error& err) {
      // Get the build log
      cerr << "Build failed! " << err.what() 
	   << '(' << err.err() << ')' << endl;
      cerr << "retrieving  log ... " << endl;
      cerr 
	<< program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0])
	<< endl;
      exit(-1);
    }
    kernel = cl::Kernel(program, "vec_iii_1d");
    
    // set up the kernel inputs
    h_vecA = new int[vLen];
    h_vecB = new int[vLen];
    h_vecC = new int[vLen];
    
    d_vecA = cl::Buffer(context, CL_MEM_READ_ONLY, vSize);
    d_vecB = cl::Buffer(context, CL_MEM_READ_WRITE, vSize);
    d_vecC = cl::Buffer(context, CL_MEM_READ_WRITE, vSize);
    
    kernel.setArg(0, d_vecA);
    kernel.setArg(1, d_vecB);
    kernel.setArg(2, d_vecC);
  }
  
  inline void initData(cl::CommandQueue& queue, cl::Event& event, 
		       int seed) 
  {
    srand(seed);
    for(int i=0; i < vLen; i++) h_vecA[i] = rand();
    for(int i=0; i < vLen; i++) h_vecB[i] = abs(rand()) % nIter;
    queue.enqueueWriteBuffer(d_vecA, CL_TRUE, 0, vSize, h_vecA);
    queue.enqueueWriteBuffer(d_vecB, CL_TRUE, 0, vSize, h_vecB);
  }
 
  inline cl::Kernel& getKernel() { return(kernel); }
 
  inline int goldenTest(cl::CommandQueue& queue, cl::Event& event) 
  {
    event.wait();
#ifdef PROFILING
    cl_ulong start=
      event.getProfilingInfo<CL_PROFILING_COMMAND_START>();
    cl_ulong end=
      event.getProfilingInfo<CL_PROFILING_COMMAND_END>();
    double time = 1.e-9 * (end-start);
    cout << "Time for kernel to execute " << time << endl;
#endif
 
    // bring data back to the host via a blocking read
    queue.enqueueReadBuffer(d_vecC, CL_TRUE, 0, vSize, h_vecC);
    for(int i=0; i < vLen; i++) 
      if(h_vecC[i] != h_vecA[i] + h_vecB[i]) 
	return(1);
    return(0);
  }
};
 
int main(int argc, char* argv[])
{
  int seed=4;
 
  if( argc < 4) {
    cerr 
      << "Use: {cpu|gpu} kernelFile n_iter vectorSize (k)" 
      << endl;
    exit(EXIT_FAILURE);
  }
 
  // handle command-line arguments
  const string platformName(argv[1]);
  int deviceType = platformName.compare("cpu")?
    CL_DEVICE_TYPE_GPU:CL_DEVICE_TYPE_CPU;
 
  const char* kernelFile = argv[2];
  unsigned int n_iter = atoi(argv[3]);
  unsigned int vecLen = 1000 * atoi(argv[4]);
 
  try {
    cl::vector< cl::Platform > platformList;
    cl::Platform::get(&platformList);
    
    displayPlatformInfo(platformList, deviceType);
    
    cl_context_properties cprops[3] = 
    {CL_CONTEXT_PLATFORM, 
     (cl_context_properties)(platformList[0])(), 0};
 
    cl::Context context(deviceType, cprops);
    
    cl::vector<cl::Device> devices = 
      context.getInfo<CL_CONTEXT_DEVICES>();
    
#ifdef PROFILING
    cl::CommandQueue queue(context, devices[0], 
			   CL_QUEUE_PROFILING_ENABLE);
#else
    cl::CommandQueue queue(context, devices[0], 0);
#endif
 
    OclTest test(context, devices, kernelFile, n_iter, vecLen);
 
    cl::Event event;
    test.initData(queue, event, seed);
 
    queue.enqueueNDRangeKernel(test.getKernel(), 
			       cl::NullRange, cl::NDRange(vecLen),
			       cl::NDRange(1, 1), NULL, &event);
 
    if(test.goldenTest(queue, event) == 0) {
      cout << "test passed" << endl;
    } else {
      cout << "TEST FAILED!" << endl;
    }
    
  } catch (cl::Error error) {
    cerr << "caught exception: " << error.what() 
	 << '(' << error.err() << ')' << endl;
  }
  return EXIT_SUCCESS;
}
