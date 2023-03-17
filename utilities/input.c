/* Takes input and makes process entries
 * Returns a process_t pointer basically  creates an process array and returns it
 * @param file name where to read
 * @param length[process array] memory address; will be populated after reading from file
 * @param pFlag = 1 if it is a priority based scheduling otherwise 0
 */

process_t *takeInput(char *fileName, int *len, int pFlag) {

    FILE *fp = fopen(fileName, "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s\n", fileName);
        return NULL;
    }

    if (fscanf(fp, "%d", len) != 1) {
        fprintf(stderr, "Invalid Length\n");
        fclose(fp);
        return NULL;
    }

    if (len == 0) {
        fclose(fp);
        return  NULL;
    }


    process_t *process = (process_t *) malloc(sizeof(process_t) * (*len));

    if (process == NULL) {
        fprintf(stderr, "Malloc Failed\n");
        fclose(fp);
        return NULL;
    }

    char pid[200];
    int at;
    int bt;
    int prt;

    if (pFlag) {
        for (int i=0; i<(*len); i++) {
            if (fscanf(fp, "%s %d %d %d", pid, &at, &bt, &prt) != 4) {
                fprintf(stderr, "Missing or Too much Values in %s\n", fileName);
                free(process);
                fclose(fp);
                return NULL;
            }

            if (strlen(pid) > 2) {
                fprintf(stderr, "PID name too long\n");
                free(process);
                fclose(fp);
                return NULL;
            }
            
            strcpy(process[i].pid, pid);
            process[i].at = at;
            process[i].bt = bt;
            process[i].prt = prt;
        }

    } else {
        for (int i=0; i<(*len); i++) {
            if (fscanf(fp, "%s %d %d", pid, &at, &bt) < 3) {
                fprintf(stderr, "Missing or Too much Values in %s\n", fileName);
                free(process);
                fclose(fp);
                return NULL;
            }

            if (strlen(pid) > 2) {
                fprintf(stderr, "PID name too long\n");
                free(process);
                fclose(fp);
                return NULL;
            }

            strcpy(process[i].pid, pid);
            process[i].at = at;
            process[i].bt = bt;
        }
    }

    fclose(fp);

    return process;
}

/* Takes time quantum input used only in Round Robin scheduling
 * Returns time quantum [integer number]
 */

int TQinput() {
    int tq=0;
    do {
        printf("Please specify a Time Quantum: ");
        scanf("%d", &tq);
    } while (tq <= 0);

    return tq;
}

