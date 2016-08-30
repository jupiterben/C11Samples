#include <CL/CL.h>

int main()
{
   cl_uint status;

   cl_platform_id platform;
   status = clGetPlatformIDs( 1, &platform, NULL );


    return 1;
}