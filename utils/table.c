/* Finds average waiting time of the given processes 
 * @param reference of process_t array
 * @param length of the process_t array
 */
static float AverageWT(process_t * process, int len) {
    
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
static float AverageTAT(process_t * process, int len) {
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
static void TableMaker(process_t * process, int len, int pFlag) {

    /* for (int i=0; i<len; i++) { */
    /*     printf("%s\t%d\t%d\t%d\n", process[i].pid, process[i].at, process[i].bt, process[i].ct); */
    /* } */


    if (pFlag) {
        printf("\n");
        printf(BOLD BLU "\t+-----+----------+--------------+------------+-----------------+-----------------+--------------+\n");
        printf("\t| PID | Priority | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
        printf("\t+-----+----------+--------------+------------+-----------------+-----------------+--------------+\n" RESET);

        for (int i=0; i<len; i++) {
            printf(BOLD WHT"\t| %3s |   %3d    |     %3d      |     %3d    |       %3d       |       %3d       |     %3d      |\n", process[i].pid, process[i].prt, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt);
            printf("\t+-----+----------+--------------+------------+-----------------+-----------------+--------------+\n" RESET);
        }
    } else {
        printf("\n");
        printf(BOLD BLU "\t+-----+--------------+------------+-----------------+-----------------+--------------+\n");
        printf("\t| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
        printf("\t+-----+--------------+------------+-----------------+-----------------+--------------+\n" RESET);

        for (int i=0; i<len; i++) {
            printf(BOLD WHT"\t| %3s |      %3d     |     %3d    |       %3d       |       %3d       |     %3d      |\n", process[i].pid, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt);
            printf("\t+-----+--------------+------------+-----------------+-----------------+--------------+\n" RESET);
        }
    }

	printf("\n");

    printf(BOLD MAG "\n\tAverage Waiting Time     : " RESET);
    printf("%-2.3f\n", AverageWT(process, len));
	printf(BOLD MAG "\tAverage Turnaround Time  : " RESET);
    printf("%-2.3f\n", AverageTAT(process, len));
    
    printf("\n");
    printf("\n");

}
