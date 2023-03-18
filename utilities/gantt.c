/* We have tried to make three queues one for elapsed time or the each box size
 * one for the process names and another one for the range [ie each box start and finish time]
 
            *1
         ------------ ---------------------- ---------------- ------ ----------
        |    P1 *2   |          P4          |        P2      |  P3  |    P5    |
         ------------ ---------------------- ---------------- ------ ----------
        0            3                      12               18     19         22
        *3           *3

        *1 -> box size defined by elapsed time of that particular process stored in elapsedTime queue
        *2 -> process name stored in processNames queue
        *3 -> time ranges stored in intervals queue
 */


/* function that converts all the elapsed time of each box in the gantt chart out of 20
 * @param integer_queue_head
 * converts given queues all elements out of 20;
 */

void PreProcess(head_t_int * elapsedTime) {

    int sum = SumQueueINT(elapsedTime);
    int temp;
    
    node_t_int * e = NULL;
    TAILQ_FOREACH(e, elapsedTime, nodes_int) {
        temp = (((float)(e->c)/sum)*5)+1;
        e->c = temp;
    }
}

/* function that prints the gantt chart 
 * @param integer_queue_head [for the elapsed time or size of each box]
 * @param integer_queue_head [for the intervals of each box bascially the range]
 * @param string_queue_head [process names for each box]
 */

void MakeGanttChart(head_t_int * elapsedTime, head_t_int * intervals, head_t_str * processNames) {

    // convert all the elapsed time out of 20
    PreProcess(elapsedTime);

    node_t_int * et = NULL;
    node_t_int * ivals = NULL;
    node_t_str * pname = NULL;

    // we used to some of the queue built in functions
    // see https://man7.org/linux/man-pages/man3/tailq.3.html
    // or see man queue

//####################################################
// prints the first row of the gantt chart

    printf("\t");
    et = TAILQ_FIRST(elapsedTime);
    while (et!=NULL) {
        printf(" ");
        for (int j=0; j<(et->c)+2; j++) {
            printf("--");
        }
        et = TAILQ_NEXT(et, nodes_int);
    }
    printf("\n");

//####################################################
// prints second row of the gantt chart where process names lives

    printf("\t");
    et = TAILQ_FIRST(elapsedTime);
    pname = TAILQ_FIRST(processNames);
    while (et != NULL && pname != NULL) {
        printf("|");
        for (int j=0; j<(et->c)+2; j++) {
            if (((et->c)/2)+1 == j) {
                printf("%2s", pname->c);
                j++;
            }
            printf("  ");
        }

        et = TAILQ_NEXT(et, nodes_int);
        pname = TAILQ_NEXT(pname, nodes_str);
    }
    printf("|");
    printf("\n");

//####################################################
// prints the last row of the gantt chart
    printf("\t");
    et = TAILQ_FIRST(elapsedTime);
    while (et!=NULL) {
        printf(" ");
        for (int j=0; j<(et->c)+2; j++) {
            printf("--");
        }
        et = TAILQ_NEXT(et, nodes_int);
    }

    printf("\n");

//####################################################
// prints the time intervals or range of each process
    printf("\t");
    et = TAILQ_FIRST(elapsedTime);
    ivals = TAILQ_FIRST(intervals);
    while (et != NULL) {
        printf("%-3d", ivals->c);
        for (int j=0; j<(et->c)+1; j++) {
            printf("  ");
        }
        et = TAILQ_NEXT(et, nodes_int);
        ivals = TAILQ_NEXT(ivals, nodes_int);
    }
    printf("%-3d", ivals->c);
    printf("\n");
//####################################################

}
