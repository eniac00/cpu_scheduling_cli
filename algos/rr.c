static void RR(process_t * process, int len, int tq) {

    // sorting the process array according to the arrival time
    qsort(process, len, sizeof(process[0]), SortAT);

    // defining queue heads
    head_t_int elapsedTime;
    head_t_int intervals;
    head_t_int readyQ;
    head_t_str processNames;

    // initializing queues
    TAILQ_INIT(&elapsedTime);
    TAILQ_INIT(&intervals);
    TAILQ_INIT(&readyQ);
    TAILQ_INIT(&processNames);

    int bt[len];                    // burst time array for temporary use
    int start_time = 0;
    int elapsed_time = 0;
    int cp = 0;                     // current process
    int total_process_finished = 0;

    // copying all the processes burst time to bt[]
    for (int i=0; i<len; i++) {
        bt[i] = process[i].bt;
    }

    EnQueueINT(&intervals, start_time);
    EnQueueINT(&readyQ, cp);

    while (!TAILQ_EMPTY(&readyQ) && total_process_finished<len) {

        if (start_time < process[cp].at) {

            elapsed_time = process[cp].at - start_time;
            start_time += elapsed_time;

            // context switch
            EnQueueINT(&elapsedTime, elapsed_time);
            EnQueueSTR(&processNames, "-");
            EnQueueINT(&intervals, start_time);

        } else {

            cp = Dequeue(&readyQ);

            if (bt[cp] > tq) {

                elapsed_time = tq;
                start_time += elapsed_time;
                bt[cp] -= tq;

                NewProcess(process, len, start_time-elapsed_time, start_time, &readyQ, cp);

                // context switch
                EnQueueINT(&elapsedTime, elapsed_time);
                EnQueueSTR(&processNames, process[cp].pid);
                EnQueueINT(&intervals, start_time);

                if (bt[cp] == 0) {

                    process[cp].ct = start_time;
                    total_process_finished++;

                } else {

                    EnQueueINT(&readyQ, cp);

                }

            } else {

                elapsed_time = bt[cp];
                start_time += elapsed_time;
                bt[cp] = 0;

                NewProcess(process, len, start_time-elapsed_time, start_time, &readyQ, cp);

                // context switch
                EnQueueINT(&elapsedTime, elapsed_time);
                EnQueueSTR(&processNames, process[cp].pid);
                EnQueueINT(&intervals, start_time);

                process[cp].ct = start_time;
                total_process_finished++;

            }
        }
    }

    // calculating waiting times and turnaround times of all process using completion time
    for(int i=0; i<len; i++) {
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;
    }

    printf(BOLD YEL "\n\n\tRR [Round Robin] \n" RESET);
    printf(BOLD GRN "\tTime Quantum: %d \n\n\n", tq);
    printf(RESET);

    // making gantt chart
    MakeGanttChart(&elapsedTime, &intervals, &processNames);
    // making the table
    TableMaker(process, len, 0);

    // freeing memory allocations of all the queues
    FreeQueueINT(&elapsedTime);
    FreeQueueINT(&intervals);
    FreeQueueINT(&readyQ);
    FreeQueueSTR(&processNames);

}
