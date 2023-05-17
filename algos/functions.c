/* what new processes came in the given interval find that and insert inside the ready queue
 * @param refernce of process_t array
 * @param length of the process_t array
 * @param start time of the time range
 * @param end time of the time range
 * @param ready queue heads reference
 * @param cp means current process id or index in the process_t array
 * @return if found new processes then return the first found process id else just return -1;
 */
int NewProcess(process_t * process, int len, int start, int end, head_t_int * head, int cp) {
    int flag = -1;
    for (int i=0; i<len; i++) {
        if (process[i].at >= start && process[i].at <= end) {
            if (!ExistINT(head, i) && i != cp) {
                EnQueueINT(head, i);
                if (flag == -1) {
                    flag = i;
                }
            }
        }
    }

    return flag;
}


