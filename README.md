
Research Project for Viavi Solutions:
Radar System using Chirp Pulse Compression

Drew Wiggs

Indiana University-Purdue University Indianapolis
July 2023
     
     Mihran Tuceryan




					     Abstract
Of the many products that Viavi Solutions offers, radar systems are one of the largest facets of the company. Of the many uses for radar systems offered at Viavi Solutions, most of them are used for various applications for militaries, specifically for military aircraft. 
  Introduction
One specific problem that certain radar systems face is that they use common signal processing methods that aren’t accurate enough, especially for military operations. With this, these methods waste a lot of energy and time to complete simple signaling tasks. One way that this can be fixed is by using a much more accurate method of filtering and compressing signals, which will give us more energy to complete tasks. Chirp compression is a method used in signal processing that optimizes detection and ranging capabilities of radar systems which fixes these issues. When linearly modulated frequency signals(chirps) are transmitted through echoes, target data that consists of movement of objects and people are extracted. 
For this project, I implemented the functions for chirp compressions for a radar system in a C compiler such that when the program is run, it will extract interesting data that determines the scope and variability of movement. What sets Chirp compression aside from other signal processing methods is that signals are compressed through filters, which then increases the signal energy in a small amount of time. When a chirp compression algorithm is implemented correctly in the C compiler, the Digit-to-Analog converter(DAC) creates a chirp signal by taking the rate of change of the frequency of a signal with respect to time. When the Chirp signal travels from the DAC and encounters a moving object, it gets reflected back. When the Chirp signal comes back to the DAC, it is compared to the Chirp signal initially transmitted. The returned chirp signal is then compressed through a signal filter. This filtering strongly improves the accuracy of signals due to its ability to take out any unnessecary values.  
This project consisted of setting up and configuring the AD9082 Digit-Analog-Converter, the software that manages the AD9082, the API and DLL for the AD9082, along with creating and testing the Chirp radar program. Other equipment that was used includes a spectrum analyzer to test signal output, a microSD card inserted into the ADS9 portion of the DAC, and a log periodic antenna that is used to point at moving and still metal objects when the program is run. For reference, the desired signal that we are looking for looks like this:


As shown in the left picture, the desired wave will form given that a signal is filtered and compressed properly once it returns from the moving object




Approaches with technical and operational details
 AD9082 Setup
To begin, 3 separate outlets were plugged into the AD9082 for it to do three things. First, the ADS9-V2EBZ was plugged into a nearby power outlet for it to receive power when turned on. Second, a PC was connected to the ADS9-V2EBZ using a USB cable for the PC to have access to the interface. Lastly, the Evaluation Board was connected to the network using an ethernet cable. Additionally, it was made sure that an SMA cable was connected to the ADC0 port, and a 20 ft cable was connected to the DAC0 port of the AD9082-FMCA-EBZ as shown here:


 Both cables were connected from the AD9082 to a 3GHz amplifier. The amplifier was then connected to a log periodic antenna. For this setup,  the appropriate IP address and IP gateway (192.168.0.1) were inputted in the network settings. Once this was accomplished, The ACE software offered from the analog devices website was downloaded. Once the ACE software and ACE’s extension DPGDownloaderLite was installed, The ACE configuration process began. The entire AD9082 along with the AD9082-FMCA-EBZ attached to it is shown here:

ACE and DPGLite configuration
Ace is a software application that allows users to configure and control evaluation boards such as the AD9082. With regards to this specific implementation of the ACE software, a limited number of attributes were configured. These attributes include but were not limited to changing the TX and RX JESD link0 modes to 12 and 13 respectively, setting TX and RX data rates to 1500 megabits per second, setting the Tx Coarse DUC0 NCO Frequency to 2 GHz, setting the Rx coarse DDC Decimation ratio to 4x, setting the RX coarse NCO mode to Variable IF mode, and setting the RX fine DDC decimation ratio to 1x. The Rx coarse DDC0 NCO frequency was also set from 0 Hz to 2Ghz. Fine DDC0 was enabled. Input was turned on for coarse DDC0  decibels Gain Enable which would then change to coarse DDC0 6db Gain Enable. Lastly, Enable Fine DDC1 should be set to false. After a successful configuration of the ACE software, DPGDownloaderlite(used for downloading sample data) was opened, and a chosen .txt sample data file was uploaded. Once a solid connection was established, sample data was downloaded into a file and then the Fourier Transform was captured in ACE. Once the data was captured, it was put into two .txt files(I and Q) that represent transmit pulses.  
    AD9082 API access from Linux shell
The next step in the implementation process was to make sure the connection was truly stable across all other platforms excluding DPGlite and ACE. Once the API was received, the API file structure was accessed through the Linux shell (teraterm or MobaXterm was what I used to access a linux shell) after identifying the User’s local machine. After inputting the correct username and password, the connection was established with the MicroZed board. The remote host that was used was 192.168.0.10. To access the API, the app_ads9 folder was identified. 

To get there, this linux command was used:
cd /root/api/AD9082/src/ad9082_xtra/app_ads9
To capture the .txt data, this command was utilized:
./debug/ad9082_xtra rx --cap test 65536
The sample data was collected into 2 .txt files. In the context of the radar system implementation that is of interest, these 2 .txt files represent I data and Q data respectively, given that this is an implimentation of a radar system that uses chirp compression.
  FTP server and client Connection
 In preparation for using the C compiler, a well-established connection was ensured between the FTP server and FTP Client. An FTP server and client can be created using the FTP application FileZilla. It was made sure that the right server IP address, in this case 192.168.0.10, along with the appropriate port number (21) and a secure password and username (PW: analog, User: root) was used when creating an FTP server.          
Radar System implementation using C compiler
CVI national instruments is a C compiler with an extensive set of useful libraries that will meet users’ needs for any kind of project. After the I and Q sample data was created, it was transmitted through the C program that I created. Before the program was executed, the log periodic antenna had to be pointed at a moving object to get an accurate reading and scope on the graph. When the program was run, sample data was captured into the I and Q test files.  The I and Q files were then retrieved from the FTP server and the contents of these files were read. The sample points were correlated to the calculated distance. The sample data were then correlated to filter coefficients. After the sample data was run through the Fourier transform, it was then run through the time domain. The pulse counter then found the magnitude of the signals and the sample data points were then plotted. The sample data points that these files consisted of were plotted on a graph on the User interface using PlotXY () functions As shown below:

The top graph shows distance with respect to time and the bottom graph shows sample data points with respect to distance. 

Results and Lessons learned
In the last few weeks of working on the project, we brought the AD9082 outside and began collecting the data that the AD9082 gathered when connected to the C-compiler. We first tested the program on a few small pieces of moving metal, and then moved on to larger objects that included moving vehicles. We initially didn’t see any signal changes, but as soon as we started to configure the .txt files, we started seeing signal variations that represented the metallic objects that we hoped it would recieve. We then recorded our findings onto spreadsheets to be analyzed by a new team of electrical engineers. As desired in the graph, we recognized two peaks that represented the chirp compression when the DAC received and transmitted signal data of moving objects. The photo shown below shows what the average waveform looked like from 15 different test cases.


Conclusions and Future Work
This project was a 2-month long endeavor with a lot of trial and error. Within the first week of working on the project, me and my supervisor immediately started running into some major issues. After weeks of consulting with my supervisor and other engineers, we managed to dismantle them and turn them into smaller, manageable issues that were solved once at a time. A crucial challenge encountered was when I was first setting up the DAC. The IP address did not recognize the microSD, and therefore, the UID value was not displayed. To fix this, it was made sure that even after the ethernet cable was hooked up from the AD9081 to the PC, network settings were configured such that the network IP address was appropriately named and was assigned to the ethernet cable. 

The longest duration of my time working on this project was spent debugging the chirp compression code and designing the algorithm for the chirp compression system. I had no prior knowledge or experience working with circuit boards and the measurements that they produce. In the future, I expect to be working on more projects with similar complexities and scopes given that I now have a seasoned knowledge of circuit boards and how to configure them.









References:

Analysis: Control: Evaluation (ACE) software. Analysis | Control | Evaluation (ACE) Software | Design Center | Analog Devices. (n.d.). https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-development-platforms/ace-software.html 

           Chirp compression. Wikiwand. (n.d.). https://www.wikiwand.com/en/Chirp_compression 

Creating custom use cases with Analog Devices’ apis. Creating Custom Use Cases with Analog Devices’ APIs | Analog Devices. (n.d.). https://www.analog.com/en/education/education-library/videos/6310061743112.html 