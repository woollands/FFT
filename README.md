# FFT

Have you ever felt like you wanted a quick look which frequencies dominate your time series?
Have you ever run a quick FFT and were frustrated by the obscure scaling of the results?

No more!

FFT version 3.0 is a wrapper for the famous FFTW (www.fftw.org/) written in C++, that allows input from multi-column time series files scaling the results so that a signal

S(t) = a * sin(nu * t * 2 pi)

would result in an amplitude peaking at "a" at the frequency "nu" no matter how many samples the file contains!

--------------------------------------------------------
written by Siegfried Eggl 2011 10 05

last modified by Siegfried Eggl 2018 04 11

--------------------------------------------------------
REQUIREMENTS:

library requirements: fftw3.h, fstream, iostream, math.h

file requirements:  fft.inn //input file, 
                    sig.dat //time series datafile example

--------------------------------------------------------
HOWTO?

1) Download the code
2) unzip the package fft-3.zip
3) run the configure script: ./configure
4) make
5) make install

ALTERNATIVELY...
*) in case you do not have the "make" utility installed compile with e.g.: g++ fft.cpp -o fft3.exe -lfftw -lm

6) modify the input file: fft.inn to include your time series file name and adjust other parameters
7) run fft
8) the output file: fft.csv (comma separated value format) contains the (resolved) frequencies, periods and the signal amplitudes. Optionally real and imaginary FFT results can be desplayed (modify fft.inn)

--------------------------------------------------------
THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.




