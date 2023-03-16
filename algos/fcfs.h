#ifndef __FCFS__
#define __FCFS__

void FCFS(process_t *process, int len) {

    // sorting all the process based on arrival time
    qsort(process, len, sizeof(process[0]), SortAT);

    // defining queue heads
    head_t_int elapsedTime;
    head_t_int intervals;
    head_t_str processNames;

    // intializing defined queues
    TAILQ_INIT(&elapsedTime);
    TAILQ_INIT(&intervals);
    TAILQ_INIT(&processNames);

    int start_time = 0;
    int elapsed_time = 0;

    // starting from time 0
    EnQueueINT(&intervals, start_time);

    for (int i=0; i<len; i++) {
        // checking if it is a ideal period for the cpu
        // ie no process started yet
        if (start_time < process[i].at) {
            elapsed_time = process[i].at - start_time;
            start_time += elapsed_time;

            EnQueueINT(&elapsedTime, elapsed_time);
            EnQueueSTR(&processNames, "-");
            EnQueueINT(&intervals, start_time);

            i--;

        } else {
            start_time += process[i].bt;
            process[i].ct = start_time;
            process[i].tat = process[i].ct - process[i].at;
            process[i].wt = process[i].tat - process[i].bt;

            EnQueueINT(&elapsedTime, process[i].bt);
            EnQueueSTR(&processNames, process[i].pid);
            EnQueueINT(&intervals, process[i].ct);
        }
    }

    printf("\n\n\tFCFS [First Come First Serve] \n\n\n");

    // making the gantt chart
    MakeGanttChart(&elapsedTime, &intervals, &processNames);
    // making the table
    TableMaker(process, len, 0);

    // freeing all of the defined queues
    FreeQueueINT(&elapsedTime);
    FreeQueueINT(&intervals);
    FreeQueueSTR(&processNames);

}

#endif
