# FFT

Have you ever felt like you wanted a quick look which frequencies dominate your time series?
Have you ever run a quick FFT and were frustrated by the obscure scaling of the results?

No more!

FFT version 3.0 is a wrapper for the famous FFTW (www.fftw.org/) written in C++, that allows input from multi-column time series files scaling the results so that the FFT of a signal

S(t) = a * sin(nu * t * 2 * pi)

would result in an amplitude "a" peaking at the frequency "nu" irrespective of the number of samples the time series contains.

--------------------------------------------------------
REQUIREMENTS:

library requirements: fftw3.h, fstream, iostream, math.h

file requirements:  fft.inn //input file, 
                    sig.dat //time series datafile example

--------------------------------------------------------
HOWTO?

1) Download the code
2) unzip the package fft-3.zip
3) run the configure script: 
```console
./configure
```
4) compile with 
```console 
make ```
5) install with 
```console 
make install 
```

ALTERNATIVELY...
*) in case you do not have the "make" utility installed compile with e.g.: 
```console
g++ fft.cpp -o fft3.exe -lfftw -lm
```

6) modify the input file: fft.inn to include your time series file name and adjust other parameters
7) run fft
8) the output file: fft.csv (comma separated value format) contains the (resolved) frequencies, periods and the signal amplitudes. Optionally real and imaginary FFT results can be desplayed (modify fft.inn)

--------------------------------------------------------
COMPILATION VERIFICATION

1) after installing fft change into the "test" folder where you will find an input file called "fft.inn" as well as a time series file "sig.dat"
2) run fft in that folder
3) the resulting "fft.csv" should show three distinct peaks at the frequencies 2, 4 and 10 with amplitudes 3, 5 and 1.5, and phases of 0, pi/2 and pi/4, respectively.


--------------------------------------------------------
WRITTEN BY: Siegfried Eggl 2011 10 05

--------------------------------------------------------
THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

