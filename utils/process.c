/* process struct where all of the informations of a process are stored in
 * pid[2] -> process name or ID
 * at -> arrival time
 * bt -> burst time
 * ct -> completion time
 * tat -> turnaround time
 * wt -> waiting time
 * prt -> priority of the process
 */

typedef struct process {
    char pid[2];
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int prt;
} process_t;
