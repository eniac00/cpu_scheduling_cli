// what new processes came in the given interval find that and insert inside the queue
void NewProcess(process_t * process, int len, int start, int end, head_t_int * head, int cp) {
    for (int i=0; i<len; i++) {
        if (process[i].at >= start && process[i].at <= end) {
            if (!ExistINT(head, i) && i != cp) {
                EnQueueINT(head, i);
            }
        }
    }
}


