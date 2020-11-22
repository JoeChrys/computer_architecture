# Computer Architecture

## Lab 1

Ilia Zarka 9289
Iosif Chrysostomou 9130

---

| starter_se.py | config.ini | Parameter |
| --- | --- | --- |
| cache_line_size = **64** | cache_line_size=**64** | Cache Block Size
| self.voltage_domain = VoltageDomain(voltage="**3.3V**") | [system.voltage_domain] voltage=3.3 |  System Voltage
| self.clk_domain = SrcClockDomain(clock="**1GHz**", voltage_domain=self.voltage_domain) | [system.clk_domain] clock=**1000** | System Clock _(not the clock of the actual simulated components)_
| parser.add_argument("**--cpu-freq**", type=str, default="**4GHz**") | [system.cpu_cluster.clk_domain] clock=**250** | CPU Frequency
| parser.add_argument("**--num-cores**", type=int, default=**1**, help="Number of CPU cores") | [system.cpu_cluster.cpus] cpu_id=0 | Number of Cores
| parser.add_argument("**--mem-type**", default="**DDR3_1600_8x8**", choices=ObjectList.mem_list.get_names(), help = "type of memory to use") | beats_per_clock=2 (DDR)| DRAM Type
| parser.add_argument("**--mem-channels**", type=int, default=**2**, help = "number of memory channels") |  [system.mem_ctrls0.dram] [system.mem_ctrls1.dram] | Number of Memory Channels
| parser.add_argument("**--mem-ranks**", type=int, default=**None**, help = "number of memory ranks per channel") | ranks_per_channel=2 | Memory Ranks in each Channel
| parser.add_argument("**--mem-size**", action="store", type=str, default="**2GB**", help="Specify the physical memory size") | mem_ranges=0:2147483648 | Total DRAM Size

mem_mode=timing άρα
> if self.cpu_cluster.memoryMode() == "timing":
        self.cpu_cluster.addL1()
        self.cpu_cluster.addL2(self.cpu_cluster.clk_domain)

_dache_ size=32768
block_size=64
_icache_ size=49152
_l2_ size=1048576

#### **SimpleCPU**
The **SimpleCPU** is a simple, purely functional in-order model, suitable for cases where a detailed model is not necessary. It is broken down into three classes, the first one of wich is the **BaseSimpleCPU**. This class implements various basic functions, such as interrupt checking and andancing the PC. You can not run this on its own though. You need to use one of the classes that inherits from **BaseSimpleCPU**. Those classes are **AtomicSimpleCPU** and **TimingSimpleCPU**. **AtomicSimpleCPU** uses atomic memory access wich is faster than timing memory access. **TimingSimpleCPU** uses the timing memory access wich is the most detailed access type.
#### **MinorCPU**
**Minor** is a processor model with a fixed, 4 stage pipeline.  It is intended to be used to model processors with strict in-order execution behaviour and allows visualisation of an instruction’s position in the pipeline. The intention is to provide a framework for correlating the model with a particular, chosen processor with similar capabilities. The four stages of the pipeline work as follows.
**Fetch1** fetches cache lines or partial cache lines from the I-cache and passing them on to Fetch2.
**Fetch2** separates the data from **Fetch1** into individual instructions which are packed into a vector of instructions.
**Decode Stage** decomposes those instructions into micro-ops (if necessary) and packs them into its output instruction vector.
**Execute Stage** provides all the instruction execution and memory access mechanisms.
