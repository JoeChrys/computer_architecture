# Αρχιτεκτονική Προηγμένων Υπολογιστών

## Εργαστήριο 1

( insert names here :P )

---

| starter_se.py | config.ini | Χαρακτηριστικά Συστήματος |
| --- | --- | --- |
| cache_line_size = **64** | cache_line_size=**64**
| self.voltage_domain = VoltageDomain(voltage="**3.3V**") | [system.voltage_domain] voltage=3.3 |
| self.clk_domain = SrcClockDomain(clock="**1GHz**", voltage_domain=self.voltage_domain) | [system.clk_domain] clock=**1000** |
| parser.add_argument("**--cpu-freq**", type=str, default="**4GHz**") | [system.cpu_cluster.clk_domain] clock=**250** |
| parser.add_argument("**--num-cores**", type=int, default=**1**, help="Number of CPU cores") | [system.cpu_cluster.cpus] cpu_id=0
| parser.add_argument("**--mem-type**", default="**DDR3_1600_8x8**", choices=ObjectList.mem_list.get_names(), help = "type of memory to use") | beats_per_clock=2 |
| parser.add_argument("**--mem-channels**", type=int, default=**2**, help = "number of memory channels") | [system.mem_ctrls0.dram] [system.mem_ctrls1.dram] |
| parser.add_argument("**--mem-ranks**", type=int, default=**None**, help = "number of memory ranks per channel") | ranks_per_channel=2 |
| parser.add_argument("**--mem-size**", action="store", type=str, default="**2GB**", help="Specify the physical memory size") | mem_ranges=0:2147483648 |

mem_mode=timing άρα
> if self.cpu_cluster.memoryMode() == "timing":
        self.cpu_cluster.addL1()
        self.cpu_cluster.addL2(self.cpu_cluster.clk_domain)

_dache_ size=32768
block_size=64
_icache_ size=49152
_l2_ size=1048576
