# Computer Architecture

## Lab 1
22/11/2020\
Ilia Zarka 9289\
Iosif Chrysostomou 9130

All the numbers below correspond to our given ansewers for the questions found in the file `arch_assignment1_v3.pdf`

---

### 1. , 2a.

In the table below we present the parameters found in the script file `starter_se.py` (Question 1) and correlate them with the parameters found in the output file `config.ini` (Question 2a). In the final column are all the parameters accompanied by their value in their most commonly seen form (e.g. in GHz instead of ps).

| starter_se.py | config.ini | Parameter |
| --- | --- | --- |
| cache_line_size = **64** | [system] cache_line_size=**64** | Cache Block Size **64B**
| self.voltage_domain = VoltageDomain(voltage="**3.3V**") | [system.voltage_domain] voltage=**3.3** |  System Voltage **3.3V**
| self.clk_domain = SrcClockDomain(clock="**1GHz**", voltage_domain=self.voltage_domain) | [system.clk_domain] clock=**1000** | Top-Level Clock **1GHz**
| cpu_types = { "atomic", **"minor**"", "hpi" } | [system.cpu_cluster.cpus] type=**MinorCPU** | Simulated CPU Model **Minor** 
| parser.add_argument("**--cpu-freq**", type=str, default="**4GHz**") | [system.cpu_cluster.clk_domain] clock=**250** | CPU Frequency **4GHz**
| parser.add_argument("**--num-cores**", type=int, default=**1**, help="Number of CPU cores") | [system.cpu_cluster.cpus] cpu_id=0 | Number of Cores **1**
| parser.add_argument("**--mem-type**", default="**DDR3_1600_8x8**", choices=ObjectList.mem_list.get_names(), help = "type of memory to use") | [system.mem_ctrls.dram] beats_per_clock=**2** **(DDR)** [system.mem_ctrls.dram] **tCK=1250** **(800MHz)** | DRAM Type **1600MHz**
| parser.add_argument("**--mem-channels**", type=int, default=**2**, help = "number of memory channels") |  [system.mem_ctrls0.dram] [system.mem_ctrls1.dram] | Number of Memory Channels **2**
| parser.add_argument("**--mem-size**", action="store", type=str, default="**2GB**", help="Specify the physical memory size") | mem_ranges=**0:2147483648** | Total DRAM Size **2GB**
| - | [system.cpu_cluster.cpus.dcache] size=**32768** | L1 Cache Size **32KB**
| - | [system.cpu.icache] size=**32768** | Instruction Cache Size **32KB**
| - | [system.cpu_cluster.l2] size=**1048576** | L2 Cache Size **1MB**

---

### 2.b.

From the `stats.txt` file we can see that **5044** simulated CPU instructions were committed and **5853** simulated CPU operations were executed. These two numbers usually differ since an instruction can require more than one operation in order to get committed. 

### 2.c.

L2 cache was accessed **479** times overall (**332** for instructions and **147** for data, through the use of MSHR). This number can also be calculated by examining both Data Cache (`dcache`) and Instruction Cache (`icache`) MSHR misses which are **147** and **332** respectively.

---

### 3.
#### **SimpleCPU**
The **SimpleCPU** is a simple, purely functional in-order model, suitable for cases where a detailed model is not necessary. It is broken down into three classes, the first one of which is the **BaseSimpleCPU**. This class implements various basic functions, such as interrupt checking and andancing the PC. You can not run this on its own though. You need to use one of the classes that inherits from **BaseSimpleCPU**. Those classes are **AtomicSimpleCPU** and **TimingSimpleCPU**. **AtomicSimpleCPU** uses atomic memory access which is faster than timing memory access. **TimingSimpleCPU** uses the timing memory access which is the most detailed access type.
#### **MinorCPU**
**Minor** is a processor model with a fixed, 4 stage pipeline.  It is intended to be used to model processors with strict in-order execution behaviour and allows visualisation of an instruction’s position in the pipeline. The intention is to provide a framework for correlating the model with a particular, chosen processor with similar capabilities. The four stages of the pipeline work as follows.\
**Fetch1** fetches cache lines or partial cache lines from the I-cache and passing them on to Fetch2.\
**Fetch2** separates the data from **Fetch1** into individual instructions which are packed into a vector of instructions.\
**Decode Stage** decomposes those instructions into micro-ops (if necessary) and packs them into its output instruction vector.\
**Execute Stage** provides all the instruction execution and memory access mechanisms.
### 3.a.
The number of the simulated seconds was dramatically different between a **MinorCPU** model and a **TimingSimpleCPU** model. Our simple code run in 1.691 ms with on a **TimingSimpleCPU** and in 0.722 ms on a **MinorCPU** model.
### 3.b.
The biggest difference of the two models is the use of **pipelining** in the **MinorCPU** model. Given that the number of simulated instructions is almost the same in the two models, we have a 2.3 times increase in the cpi from the **MinorCPU** to the **TimingSimpleCPU**.
### 3.c.
Increasing the frequency from 2GHz to 4GHz on a **MinorCPU** model, we decrease the simulated seconds from 0.722 ms to 0.439 ms. This shown that the number of simulated seconds depends not only by the cpu frequency but on other delays as well. Notibly, the cpi was increased from 1.4 to 1.7 which is probably due to memory delays. In the **TimingSimpleCPU**, with the same frequency change, we see the simulated seconds drop from 1.691 to 0.924 ms. In both cpu models and both of the above cpu frequencies we tried running the simulation with the default DDR3_1600_8x8 and DDR4_2400_8x8. In every case, the difference was negligible. We saw 1 us decrease on the simulated seconds which corresponds in less than 0.5% improvement in performance in every case.

|                                                        | run time (ms) |  cpi |
|--------------------------------------------------------|:-------------:|:----:|
| **MinorCPU** with **DDR3_1600_8x8** @**0.5GHz**        |     2.403     | 1.17 |
| **MinorCPU** with **DDR3_1600_8x8** @**2GHz**          |     0.722     | 1.4  |
| **MinorCPU** with **DDR3_1600_8x8** @**4GHz**          |     0.439     |  1.7 |
| **MinorCPU** with **DDR3_1600_8x8** @**8GHz**          |      0.3      | 2.34 |
| **MinorCPU** with **DDR4_2400_8x8** @**0.5GHz**        |     2.476     |  1.2 |
| **MinorCPU** with **DDR4_2400_8x8** @**2GHz**          |     0.721     |  1.4 |
| **MinorCPU** with **DDR4_2400_8x8** @**4GHz**          |     0.438     |  1.7 |
| **MinorCPU** with **DDR4_2400_8x8** @**8GHz**          |      0.3      |  2.3 |
| **TimingSimpleCPU** with **DDR3_1600_8x8** @**0.5GHz** |     6.293     |   -  |
| **TimingSimpleCPU** with **DDR3_1600_8x8** @**2GHz**   |     1.691     |   -  |
| **TimingSimpleCPU** with **DDR3_1600_8x8** @**4GHz**   |     0.924     |   -  |
| **TimingSimpleCPU** with **DDR3_1600_8x8** @**8GHz**   |     0.549     |   -  |
| **TimingSimpleCPU** with **DDR4_2400_8x8** @**0.5GHz** |      6.55     |   -  |
| **TimingSimpleCPU** with **DDR4_2400_8x8** @**2GHz**   |     1.699     |   -  |
| **TimingSimpleCPU** with **DDR4_2400_8x8** @**4GHz**   |     0.952     |   -  |
| **TimingSimpleCPU** with **DDR4_2400_8x8** @**8GHz**   |     0.549     |   -  |

![][./images/bargraph.png]

### Sources
[Simple CPU](https://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU)\
[Minor CPU](https://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu)\
[Memory Systems](https://www.gem5.org/documentation/general_docs/memory_system/index.html#access-types)

### Comments
The exercise was simple enough for an introduction to ISA simulation however there are some difficulties that novice Linux users will encounter and quite possibly get stuck on. First things first, the given instructions for gem5 installation were simple and understandable enough, though they were not all applicable to newer systems and the latest itaration of the gem5 software, so the official instructions were followed. There has been some conceptual confusion on our part mostly since we have just started getting used to the terminology. Also we believe that the aforementioned documentation misses and some of the tasks are too demanding for a first contact with Linux.

Apart from that, this exercise packs a lot of skills to be earned since Markdown, Git and the use of CLI are essential tools for someone in the field of Computer Architecture.
