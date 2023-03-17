// what new processes came in the given interval find that and insert inside the queue
void NewProcess(process_t * process, int len, int start, int end, head_t_int * head) {
    for (int i=0; i<len; i++) {
        if (process[i].at > start && process[i].at <= end) {
            EnQueueINT(head, i);
        }
    }
}

// takeout the first value and return and remove from the queue
int Dequeue(head_t_int * readyQ) {
    node_t_int * e = NULL;
    int index = -1;
    e = TAILQ_FIRST(readyQ);
    index = e->c;
    TAILQ_REMOVE(readyQ, e, nodes_int);
    free(e);
    return index;
}


void RR(process_t * process, int len, int tq) {

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
    int start_time = 0;
    int elapsed_time = 0;
    int cp = 0;  // current process
    int total_process_finished = 0;

    for (int i=0; i<len; i++) {
        bt[i] = process[i].bt;
    }

    EnQueueINT(&intervals, start_time);
    EnQueueINT(&readyQ, cp);

    while (TAILQ_EMPTY(&readyQ)==0 && total_process_finished<len) {
        if (start_time < process[cp].at) {
            elapsed_time = process[cp].at - start_time;
            start_time += elapsed_time;

            EnQueueINT(&elapsedTime, elapsed_time);
            EnQueueSTR(&processNames, "-");
            EnQueueINT(&intervals, start_time);
        } else {

            int cp = Dequeue(&readyQ);

            if (bt[cp] > tq) {
                elapsed_time = tq;
                start_time += elapsed_time;
                bt[cp] -= tq;

                NewProcess(process, len, start_time-elapsed_time, start_time, &readyQ);


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

                NewProcess(process, len, start_time-elapsed_time, start_time, &readyQ);

                EnQueueINT(&elapsedTime, elapsed_time);
                EnQueueSTR(&processNames, process[cp].pid);
                EnQueueINT(&intervals, start_time);

                process[cp].ct = start_time;
                total_process_finished++;
            }
        }
    }

    for(int i=0; i<len; i++) {
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;
    }


    MakeGanttChart(&elapsedTime, &intervals, &processNames);
    // making the table
    TableMaker(process, len, 0);

    FreeQueueINT(&elapsedTime);
    FreeQueueINT(&intervals);
    FreeQueueINT(&readyQ);
    FreeQueueSTR(&processNames);

}