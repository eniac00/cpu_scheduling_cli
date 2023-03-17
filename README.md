# Cpu_Scheduling_CLI
---

A basic CLI simulator for cpu scheduling algorithms written in `c`. This simulator will print you a `Gantt Chart` along with process information.

## Compile
---
```bash
git clone https://github.com/eniac00/cpu_scheduling_cli
```
```bash
cd cpu_scheduling_cli
```
```bash
chmod +x compile.sh
./compile.sh
```

## Run
---
```
./cpu <algorithm> <text_file_containing_process>
```

## Process text file should contain
---
```code
For non-priority based scheduling

2       ------> total process
P1 0 5
P2 3 8
|  | |
|  | ┕--------> burst time
|  ┕----------> arrival time
┕-------------> process name or ID

----------------------------------------------------------------------
For priority based scheduling

2       ------> total process
P1 0 5 2
P2 3 8 1
|  | | |
|  | | ┕------> priority
|  | ┕--------> burst time
|  ┕----------> arrival time
┕-------------> process name or ID
```
