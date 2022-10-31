//------------------------------------------------------------------------------
//
// kernel:  vadd  
//
// Purpose: Compute the elementwise sum c = a+b
// 
// input: a and b float vectors of length count
//
// output: c float vector of length count holding the sum a + b
//

__kernel void vadd_inplace(                             
   __global float* a,                      
   __global float* b,                      
   const unsigned int count)               
{                                          
   int i = get_global_id(0);               
   if(i < count)  {
       b[i] += a[i];                 
   }
}                                          
