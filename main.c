#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"
#include "algos/algos.h"


int main (int argc, char *argv []) {

    if (argc < 2) {
        fprintf(stderr, "Run command: %s <algorithm> <text_file>\n", argv[0]);
        fprintf(stderr, "FCFS [First Come First Served]\nSJF [Shortest Job First]\nSRTF [Shortest Remaining Time First]\nNPP [Non Preemptive Priority]\nPP [Preemptive Priority Scheduling]\nRR [Round Robin]\n");
        return 1;
    }

    if (argc < 3) {
        fprintf(stderr, "Provide a text file\n");
        return 1;
    }


    int len = 0;
    process_t *process;

    if ((strcmp(argv[1], "PP") == 0) || (strcmp(argv[1], "NPP") == 0)) {
        process = takeInput(argv[2], &len, 1);
    } else {
        process = takeInput(argv[2], &len, 0);
    }

    if (process == NULL) {
        return 1;
    }

    if (strcmp(argv[1], "FCFS") == 0) {
        FCFS(process, len);
    } else if (strcmp(argv[1], "SJF") == 0) {
        SJF(process, len);
    } else if (strcmp(argv[1], "RR") == 0) {
        int tq = TQinput();
        RR(process, len, tq);
    } else if (strcmp(argv[1], "NPP") == 0) {
        NPP(process, len);
    } else if (strcmp(argv[1], "PP") == 0) {
        PP(process, len);
    } else if (strcmp(argv[1], "SRTF") == 0) {
        SRTF(process, len);
    } else {
        fprintf(stderr, "Error\n");
    }

    free(process);

    return 0;

}
