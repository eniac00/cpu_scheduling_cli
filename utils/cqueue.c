/* These are custom queue functions for queue data structure */
/* Here we have defined two variation of queue integer and string */
/* full documentation of this code can be found in the below links */
/* https://blog.taborkelly.net/programming/c/2016/01/09/sys-queue-example.html */
/* https://github.com/TaborKelly/queue-example */

#include <sys/queue.h>
#include <string.h>


typedef struct node_int {
    int c;
    TAILQ_ENTRY(node_int) nodes_int;
} node_t_int;

typedef struct node_str {
    char c[2];
    TAILQ_ENTRY(node_str) nodes_str;
} node_t_str;


typedef TAILQ_HEAD(head_i, node_int) head_t_int;
typedef TAILQ_HEAD(head_s, node_str) head_t_str;


      /**************************/
     /**** For the Integers ****/
    /**************************/

static int EnQueueINT(head_t_int * head, const int num) {
    node_t_int * e = malloc(sizeof(node_t_int));
    if (e == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    e->c = num;
    TAILQ_INSERT_TAIL(head, e, nodes_int);
    e = NULL;
    return 0;
}

static void FreeQueueINT(head_t_int * head) {
    node_t_int * e = NULL;
    while (!TAILQ_EMPTY(head)) {
        e = TAILQ_FIRST(head);
        TAILQ_REMOVE(head, e, nodes_int);
        free(e);
        e = NULL;
    }
}

/*sort the queue using an supporting array
 * queue will be sorted based on the value in array
 * @param an array that will be the basis of the sorting usually burt_time array or priority array
 * @param head reference of the ready queue
 */
static void SortQueueINT_Arr(int *arr, head_t_int * head) {
    node_t_int * e = NULL;
    node_t_int * f = NULL;
    int temp;

    e = TAILQ_FIRST(head);

    while (e!=NULL) {
        f = TAILQ_NEXT(e, nodes_int);
        while (f!=NULL) {
            if (arr[e->c] > arr[f->c]) {
                temp = e->c;
                e->c = f->c;
                f->c = temp;
            }
            if (arr[e->c] == arr[f->c] && e->c > f->c) {
                temp = e->c;
                e->c = f->c;
                f->c = temp;
            }
            f = TAILQ_NEXT(f, nodes_int);
        }
        e = TAILQ_NEXT(e, nodes_int);
    }
}


/* static void PrintQueueINT(head_t_int * head) { */
/*     node_t_int * e = NULL; */
/*     if (TAILQ_EMPTY(head)) { */
/*         printf("Empty\n"); */
/*     } */
/*     TAILQ_FOREACH(e, head, nodes_int) { */
/*         printf("%d\n", e->c); */
/*     } */
/* } */

static int ExistINT(head_t_int * head, const int num) {
    node_t_int * e = NULL;
    TAILQ_FOREACH(e, head, nodes_int) {
        if (e->c == num) {
            return 1;
        }
    }
    return 0;
}

// takeout the first value and return and remove from the queue
static int Dequeue(head_t_int * head) {
    node_t_int * e = NULL;
    int num = -1;
    e = TAILQ_FIRST(head);
    num = e->c;
    TAILQ_REMOVE(head, e, nodes_int);
    free(e);
    return num;
}


/* static int CountQueueINT(head_t_int * head) { */
/*     int count = 0; */
/*     node_t_int * e = NULL; */
/*     TAILQ_FOREACH(e, head, nodes_int) { */
/*         count++; */
/*     } */

/*     return count; */
/* } */

static int SumQueueINT(head_t_int * head) {
    int sum = 0;
    node_t_int * e = NULL;
    TAILQ_FOREACH(e, head, nodes_int) {
        sum += e->c;
    }

    return sum;
}


      /**************************/
     /**** For the Strings *****/
    /**************************/

static int EnQueueSTR(head_t_str * head, const char * str) {
    if (strlen(str) > 2) {
        fprintf(stderr, "String size too long\n");
        return 1;
    }

    node_t_str * e = malloc(sizeof(node_t_str));
    if (e == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    strcpy(e->c, str);
    TAILQ_INSERT_TAIL(head, e, nodes_str);
    e = NULL;
    return 0;
}

/* static void PrintQueueSTR(head_t_str * head) { */
/*     node_t_str * e = NULL; */
/*     TAILQ_FOREACH(e, head, nodes_str) { */
/*         printf("%s\n", e->c); */
/*     } */
/* } */

static void FreeQueueSTR(head_t_str * head) {
    node_t_str * e = NULL;
    while (!TAILQ_EMPTY(head)) {
        e = TAILQ_FIRST(head);
        TAILQ_REMOVE(head, e, nodes_str);
        free(e);
        e = NULL;
    }
}
