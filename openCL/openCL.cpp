#include <vector>
#include "clheader.h"

#include <fstream>
#include <sstream>

std::string readFile(const std::string& fileName)
{
	std::ifstream fs(fileName);
	if (!fs.is_open())
		return nullptr;
	std::stringstream strstream;
	strstream << fs.rdbuf();
	return strstream.str();
}



//get platforms
std::vector<cl_platform_id> getPlatforms()
{
	cl_uint status;
   //get number of platforms
	cl_uint numPlatform;
	status = clGetPlatformIDs(1, nullptr, &numPlatform);
	
	std::vector<cl_platform_id> platforms;
	platforms.resize(numPlatform);
	status = clGetPlatformIDs(platforms.size(), platforms.data(), nullptr);
	return std::move(platforms);
}

//get devices
std::vector<cl_device_id> getDevices(cl_platform_id platform)
{
	cl_uint status; 
	//get number of devices
	cl_uint numDevices;
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);

	std::vector<cl_device_id> devices;
	if (CL_DEVICE_NOT_FOUND == status)
		return std::move(devices);

	devices.resize(numDevices);
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, numDevices, devices.data(), nullptr);
	return std::move(devices);
}

const char* kernalScript = R"(
	
    __kernel void vector_add_gpu (__global const float* src_a,  
                         __global const float* src_b,  
                         __global float* res,  
               const int num)  
    {  
       const int idx = get_global_id(0);  
       if (idx < num)  
          res[idx] = src_a[idx] + src_b[idx]; 
    }
)";

#include <iostream>

int main()
{
	std::cout<<kernalScript;

	cl_int errcode_ret=0;

	auto platforms = getPlatforms();

	for(auto platform : platforms)
	{
		auto devices = getDevices(platform);
		for(auto device : devices)
		{
			cl_context  context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &errcode_ret);
			if(context)
			{
				cl_program program = clCreateProgramWithSource(context, 1, &kernalScript, 0, &errcode_ret);	
				if(program)
				{
					std::cout << "create program" << std::endl;
				}
				else
				{
					std::cout << CLErrString(errcode_ret);
				}
				clReleaseContext(context);
			}
			else{
				std::cout<<CLErrString(errcode_ret);
			}				
		}

		
		
	}
	
  
    return 1;
}

