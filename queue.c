#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    if (q->head) {
        list_ele_t *tmp;
        while (q->head) {
            tmp = q->head;
            q->head = tmp->next;
            free(tmp->value);
            free(tmp);
        }
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    int Strlen = strlen(s);
    if (!q)
        return false;
    list_ele_t *newh;
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = (char *) malloc((Strlen + 1) * sizeof(char));
    if (!(newh->value)) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, Strlen + 1);
    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    if (q->size == 1)
        q->tail = newh;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    int Strlen = strlen(s);
    if (!q)
        return false;
    list_ele_t *newh;
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = (char *) malloc((Strlen + 1) * sizeof(char));
    if (!(newh->value)) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, Strlen + 1);
    newh->next = NULL;
    q->size += 1;
    if (q->size == 1)
        q->head = newh;
    else
        q->tail->next = newh;
    q->tail = newh;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */


bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || q->size == 0)
        return false;
    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    if (q->size == 1) {
        free(q->head->value);
        free(q->head);
        q->size -= 1;
        return true;
    }
    list_ele_t *tmp;
    tmp = q->head;

    q->head = q->head->next;
    q->size -= 1;
    free(tmp->value);
    free(tmp);
    if (q->size == 0)
        q->tail = NULL;
    return true;
}


/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || q->size == 0) {
        return;
    }
    /* Queue has only 1 element */
    if (q->size == 1) {
        return;
    }
    list_ele_t *pre, *cur, *pos;
    pre = pos = NULL;
    cur = q->head;
    while (cur) {
        pos = cur->next;
        cur->next = pre;
        pre = cur;
        cur = pos;
    }
    cur = q->head;
    q->head = q->tail;
    q->tail = cur;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
