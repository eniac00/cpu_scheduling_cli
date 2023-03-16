#ifndef __TABLEMAKER__
#define __TABLEMAKER__

/* Finds average waiting time of the given processes 
 * @param reference of process_t array
 * @param length of the process_t array
 */
float AverageWT(process_t * process, int len) {
    
    int total_wt = 0;

    for (int i=0; i<len; i++) {
        total_wt += process[i].wt;
    }

    return ((float) total_wt/len);
}

/* Finds average turnaround time of the given processes 
 * @param reference of process_t array
 * @param length of the process_t array
 */
float AverageTAT(process_t * process, int len) {
    int total_tat = 0;

    for (int i=0; i<len; i++) {
        total_tat += process[i].tat;
    }

    return ((float) total_tat/len);
}

/* prints the process table
 * @param reference of process_t array
 * @param length of the process_t array
 * @param pFlag = 1 if it is a priority based scheduling otherwise 0
 */
void TableMaker(process_t * process, int len, int pFlag) {


    if (pFlag) {
        printf("ppp\n");
    } else {
        printf("\n");
        printf("\t+-----+-------------+------------+-----------------+-----------------+--------------+\n");
        printf("\t| PID | Arival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
        printf("\t+-----+-------------+------------+-----------------+-----------------+--------------+\n");

        for (int i=0; i<len; i++) {
            printf("\t| %3s |     %3d     |     %3d    |       %3d       |       %3d       |     %3d      |\n", process[i].pid, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt);
            printf("\t+-----+-------------+------------+-----------------+-----------------+--------------+\n");
        }
    }

	printf("\n");

    printf("\n\tAverage Waiting Time     : %-2.3f\n", AverageWT(process, len));
	printf("\tAverage Turnaround Time  : %-2.3f\n", AverageTAT(process, len));
    
    printf("\n");
    printf("\n");

}

#endif
