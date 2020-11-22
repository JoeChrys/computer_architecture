# Computer Architecture

## Lab 1

Ilia Zarka 9289\
Iosif Chrysostomou 9130

---

| starter_se.py | config.ini | Parameter |
| --- | --- | --- |
| cache_line_size = **64** | [system] cache_line_size=**64** | Cache Block Size **64B**
| self.voltage_domain = VoltageDomain(voltage="**3.3V**") | [system.voltage_domain] voltage=3.3 |  System Voltage **3.3V**
| self.clk_domain = SrcClockDomain(clock="**1GHz**", voltage_domain=self.voltage_domain) | [system.clk_domain] clock=**1000** | Top-Level Clock **1GHz**
| cpu_types = { "atomic", **"minor**"", "hpi" } | [system.cpu_cluster.cpus] type=**MinorCPU** | Simulated CPU Model **Minor** 
| parser.add_argument("**--cpu-freq**", type=str, default="**4GHz**") | [system.cpu_cluster.clk_domain] clock=**250** | CPU Frequency **4GHz**
| parser.add_argument("**--num-cores**", type=int, default=**1**, help="Number of CPU cores") | [system.cpu_cluster.cpus] cpu_id=0 | Number of Cores **1**
| parser.add_argument("**--mem-type**", default="**DDR3_1600_8x8**", choices=ObjectList.mem_list.get_names(), help = "type of memory to use") | [system.mem_ctrls.dram] beats_per_clock=2 (DDR) [system.mem_ctrls.dram] tCK=1250 (800MHz)| DRAM Type **1600MHz**
| parser.add_argument("**--mem-channels**", type=int, default=**2**, help = "number of memory channels") |  [system.mem_ctrls0.dram] [system.mem_ctrls1.dram] | Number of Memory Channels **2**
| parser.add_argument("**--mem-size**", action="store", type=str, default="**2GB**", help="Specify the physical memory size") | mem_ranges=0:2147483648 | Total DRAM Size **2GB**
| - | [system.cpu_cluster.cpus.dcache] size=**32768** | L1 Cache Size **32KB**
| - | [system.cpu.icache] size=**32768** | Instruction Cache Size **32KB**
| - | [system.cpu_cluster.l2] size=**1048576** | L2 Cache Size **1MB**

mem_mode=timing άρα
> if self.cpu_cluster.memoryMode() == "timing":
        self.cpu_cluster.addL1()
        self.cpu_cluster.addL2(self.cpu_cluster.clk_domain)

_dache_ size=32768
block_size=64
_icache_ size=49152
_l2_ size=1048576

#### **SimpleCPU**
The **SimpleCPU** is a simple, purely functional in-order model, suitable for cases where a detailed model is not necessary. It is broken down into three classes, the first one of wich is the **BaseSimpleCPU**. This class implements various basic functions, such as interrupt checking and andancing the PC. You can not run this on its own though. You need to use one of the classes that inherits from **BaseSimpleCPU**. Those classes are **AtomicSimpleCPU** and **TimingSimpleCPU**. **AtomicSimpleCPU** uses atomic memory access witch is faster than timing memory access. **TimingSimpleCPU** uses the timing memory access wich is the most detailed access type.
#### **MinorCPU**
**Minor** is a processor model with a fixed, 4 stage pipeline.  It is intended to be used to model processors with strict in-order execution behaviour and allows visualisation of an instruction’s position in the pipeline. The intention is to provide a framework for correlating the model with a particular, chosen processor with similar capabilities. The four stages of the pipeline work as follows.\
**Fetch1** fetches cache lines or partial cache lines from the I-cache and passing them on to Fetch2.\
**Fetch2** separates the data from **Fetch1** into individual instructions which are packed into a vector of instructions.\
**Decode Stage** decomposes those instructions into micro-ops (if necessary) and packs them into its output instruction vector.\
**Execute Stage** provides all the instruction execution and memory access mechanisms.
