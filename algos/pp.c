static void PP(process_t * process, int len) {

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

    int bt[len];                // burst time array for temporary use
    int prt[len];
    int start_time = 0;
    int elapsed_time = 0;
    int cp = 0;                 // current process
    int new_cp = -1;
    int total_process_finished = 0;

    // copying all the processes burst time to bt[]
    for (int i=0; i<len; i++) {
        bt[i] = process[i].bt;
        prt[i] = process[i].prt;
    }

    EnQueueINT(&intervals, start_time);
    EnQueueINT(&readyQ, cp);
    NewProcess(process, len, start_time, start_time, &readyQ, cp);
    SortQueueINT_Arr(prt, &readyQ);
    

    while (!TAILQ_EMPTY(&readyQ) && total_process_finished<len) {

        cp = Dequeue(&readyQ);
        EnQueueINT(&readyQ, cp);
        SortQueueINT_Arr(prt, &readyQ);

        if (start_time < process[cp].at) {

            elapsed_time = process[cp].at - start_time;
            start_time += elapsed_time;

            // context switch
            EnQueueINT(&elapsedTime, elapsed_time);
            EnQueueSTR(&processNames, "-");
            EnQueueINT(&intervals, start_time);
            EnQueueINT(&readyQ, cp);
            SortQueueINT_Arr(prt, &readyQ);

        } else {

            start_time++;
            elapsed_time++;
            bt[cp]--;


            NewProcess(process, len, start_time-1, start_time, &readyQ, cp);
            SortQueueINT_Arr(prt, &readyQ);

            if (bt[cp] == 0) {

                total_process_finished++;
                process[cp].ct = start_time;
                // context switch
                EnQueueINT(&elapsedTime, elapsed_time);
                EnQueueSTR(&processNames, process[cp].pid);
                EnQueueINT(&intervals, start_time);
                Dequeue(&readyQ); 
                elapsed_time = 0;

            } else {

                new_cp = Dequeue(&readyQ);
                EnQueueINT(&readyQ, new_cp);
                SortQueueINT_Arr(prt, &readyQ);

                if (new_cp != -1 && new_cp != cp) {

                    // context switch
                    EnQueueINT(&elapsedTime, elapsed_time);
                    EnQueueSTR(&processNames, process[cp].pid);
                    EnQueueINT(&intervals, start_time);
                    SortQueueINT_Arr(prt, &readyQ);
                    elapsed_time = 0;

                }
            }
        }
    }

    // calculating waiting times and turnaround times of all process using the completion time
    for(int i=0; i<len; i++) {
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;
    }

    printf(BOLD YEL "\n\n\tPP [Preemptive Priority] \n\n\n" RESET);

    // making gantt chart
    MakeGanttChart(&elapsedTime, &intervals, &processNames);
    // making the table
    TableMaker(process, len, 1);

    // freeing memory allocations of all the queues 
    FreeQueueINT(&elapsedTime);
    FreeQueueINT(&intervals);
    FreeQueueINT(&readyQ);
    FreeQueueSTR(&processNames);

}
