/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The program fft.cpp is a wrapper for fftw3 to perform Fast Fourier Transforms (FFTs) on time series files with several columns
// 
// fft uses an input file (fft.inn) to read in the name of the file and column of the data therein that should be analyzed.
//
// The output is written to a comma separated value file named fft.csv
//---------------------------------------------------------------------------------------------------------------
// written by: Siegfried Eggl 2011 10 05
//
// current version: 3.0
//
// last modified: 2018 04 19
//---------------------------------------------------------------------------------------------------------------
//
// library requirements: fftw3.h, fstream, iostream, math.h
//---------------------------------------------------------------------------------------------------------------
//
// input file: fft.inn 
// contains:
//
// fft.dat          .../file containing time series (50 characters max)
// 0                 .../data file header line skip
// 1                 .../total number of columns in the data file
// 1                 .../id of selected column (starts at 1) 
// 10               .../total sampling timespan of the time series data [time units] - used for frequency calculations
// y                 .../additional output of real and imaginary parts of the fft result (y/n)
//
// please note that the above comments (.../) should be ERASED in the actual input file.
//
//---------------------------------------------------------------------------------------------------------------
// in absence of a makefile compile with:
// g++ fft.cpp -o fft.exe -lfftw -lm
//---------------------------------------------------------------------------------------------------------------
// license: GNU GPL v3.0 or later
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <fftw3.h>
#include <math.h>
#include <fstream>
using namespace std;

const int outprec=7;               // output precision, set =0 for default single precision output

//---------------------------------------------------------------------------------------------------
int main ()
//reads parameters from input file: fft3.inn
//reads time series data from data file defined in fft3.inn into array 
//performs fft using fftw3
//creates output file: fft3.out    
{
  int N,M;                                      //number of samples in input file N, M=N/2-1
  int cols,selcol,lineskip;               //integers for input file data selection 
  int i,j;                                         //local counters
  int outfw ;                                // output field width
      
  double *inp,*dum;                     //pointers to input and dummy arrays
  double  pow,ttot,nu;                  //FFT signal power^2, total sampling time, frequency
  string dums;                              //dummy string
    
  char inname[50],re_im;    //input filename, selector for output of real and imaginary parts of the FFT (y/n)
  fftw_complex  *outp;       //pointer to FFTW output array 
  fftw_plan p;                     //FFTW plan array
  
  
//file to read input parameters  
  ifstream inn;
  inn.open ("fft.inn");
  
//file name of input file  
  inn>>inname;
  inn>>lineskip;
  inn>>cols;
  inn>>selcol;
  inn>>ttot;
  inn>>re_im;
   
  inn.close();
  dum = new double [cols];
  std::cout<<inname<<" ...input file"<<endl;
  
//file for data input  
  ifstream in;
  in.open (inname);
  
//file for data output
   ofstream out;
   out.open ("fft.csv");
   out  << std::setprecision(outprec)<<scientific;
   outfw=4+outprec;
    
   if(re_im=='y'){
   out<<"frequency [1/timeunit], period [timeunits], Re(X_k)/(N/2), Im(X_k)/(N/2), power spectrum amplitude/(N/2), where N is the number of samples in the file, and X_k the FFT datapoint \n";}
   else{
   out<<"frequency [1/timeunit], period [timeunits], power spectrum amplitude/(N/2) \n";}
  
//Read number of file entries
  N=-1;
  while(in.eof()== false)
  {  
    getline(in,dums);
    N++;
  }
 
  N=N-lineskip;
  std::cout<<endl<<N<<" ...number of samples in " << inname << endl;
  in.close();
        
  //Allocate fftw variables 
  M=int(N/2)+1;
  inp = (double*) fftw_malloc(sizeof(double) * N);                            //fftw input array    
  outp = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * M);     //fftw output array
  p = fftw_plan_dft_r2c_1d(N, inp, outp,0);                                     //fftw plan
         	
 
  //INPUT: read dummy header lines from time series file   
   in.open(inname);
   j=0;
  while(j<lineskip)
  {
    getline(in,dums);
    j++;
  }
    
  //read input data from time series file   
    i=0;   
  while(i < N)
  {
    for (j=1;j<=cols;j++)
    {
       in>>dum[j];
    }
    inp[i]=dum[selcol];
 //    std::cout<<inp[i]<<"\n";
     i++;
  }
  
  //Execute FFT
  fftw_execute(p); 
     
     //Output
	  for(int i=0;i<M;i++)
      {
	    pow=0.;
        //Frequency correction for total sampling time  
        nu=double(i)/ttot;   
	    out  << setw(outfw)<<nu<<" , "  << setw(outfw)<<1.L/nu<<" , ";
          
	    for(int j=0;j<2;j++)
        {
	      if(re_im=='y') {out<< setw(outfw)<<outp[i][j]/double(M-1) <<" , ";}
	      pow=pow+outp[i][j]*outp[i][j];
	    }
	    //amplitude correction (divide by number of entries-1 and multiply by 2 (mirror loss))
	    out<< setw(outfw)<<sqrt(pow)/double(M-1)<<endl;
	 }
	 
    //deallocate plan, input and output arrays
     fftw_destroy_plan(p);
     fftw_free(inp); fftw_free(outp);
	   
	 in.close();
	 out.close();
     return(0);
}



