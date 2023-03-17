/* comparison function for qsort() 
 * SortAT -> sort by arrival time
 * see `man qsort`
 * it takes two void type paramater cast them to process_t
 * and compares using process arrival time
 */

int SortAT(const void *a, const void *b) {

    process_t *ptrA = (process_t *) a;
    process_t *ptrB = (process_t *) b;

    return ptrA->at - ptrB->at;
}

