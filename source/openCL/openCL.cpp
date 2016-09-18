#include <vector>
#include "clheader.h"

#include <fstream>
#include <sstream>
std::string readFile(const std::string fileName)
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
	status = clGetPlatformIDs(numPlatform, platforms.data(), nullptr);
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


int main()
{

	auto platforms = getPlatforms();
	auto devices = getDevices(platforms.front());
	cl_context  context = clCreateContext(nullptr, 1, devices.data(), nullptr, nullptr, nullptr);
	
	std::string source = readFile("E:\\360Cloud\\Projects\\cppSamples\\source\\openCL\\kernal.cl");
	const char* s = source.c_str();
	cl_program program = clCreateProgramWithSource(context, 1, &s, 0, 0);
	

	
	
	clReleaseContext(context);
  


    return 1;
}

