void NPP(process_t * process, int len) {

    qsort(process, len, sizeof(process[0]), SortAT);

    head_t_int elapsedTime;
    head_t_int intervals;
    head_t_int readyQ;
    head_t_str processNames;

    TAILQ_INIT(&elapsedTime);
    TAILQ_INIT(&intervals);
    TAILQ_INIT(&readyQ);
    TAILQ_INIT(&processNames);

    int bt[len];
    int prt[len];
    int start_time = 0;
    int elapsed_time = 0;
    int cp = 0;  // current process
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
        if (start_time < process[cp].at) {
            elapsed_time = process[cp].at - start_time;
            start_time += elapsed_time;

            EnQueueINT(&elapsedTime, elapsed_time);
            EnQueueSTR(&processNames, "-");
            EnQueueINT(&intervals, start_time);
            EnQueueINT(&readyQ, cp);
        } else {
            start_time += bt[cp];
            elapsed_time = bt[cp];
            NewProcess(process, len, start_time - bt[cp], start_time, &readyQ, cp); 
            SortQueueINT_Arr(prt, &readyQ);
            process[cp].ct = start_time;
            total_process_finished++;

            EnQueueINT(&elapsedTime, elapsed_time);
            EnQueueSTR(&processNames, process[cp].pid);
            EnQueueINT(&intervals, start_time);
        }
    }

    for(int i=0; i<len; i++) {
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;
    }

    printf(BOLD YEL "\n\n\tNPP [Non Preemptive Priority] \n\n\n" RESET);

    MakeGanttChart(&elapsedTime, &intervals, &processNames);
    // making the table
    TableMaker(process, len, 1);

    FreeQueueINT(&elapsedTime);
    FreeQueueINT(&intervals);
    FreeQueueINT(&readyQ);
    FreeQueueSTR(&processNames);

}
