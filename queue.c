#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#include "strnatcmp.h"


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
        q->head = NULL;
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


int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}


void q_reverse(queue_t *q)
{
    if (!q || q->size == 0) {
        return;
    }
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
// list_ele_t *merge(list_ele_t *left, list_ele_t *right)
// {
//     if (!left) {
//         return right;
//     }

//     if (!right) {
//         return left;
//     }

//     list_ele_t *start = NULL;

//     for (list_ele_t *merge_ele = NULL; left || right;) {
//         if (right == NULL ||
//             (left && strnatcmp(left->value, right->value) < 0)) {
//             if (!merge_ele)
//                 start = merge_ele = left;
//             else {
//                 merge_ele->next = left;
//                 merge_ele = merge_ele->next;
//             }
//             left = left->next;
//         } else {
//             if (!merge_ele)
//                 start = merge_ele = right;
//             else {
//                 merge_ele->next = right;
//                 merge_ele = merge_ele->next;
//             }
//             right = right->next;
//         }
//     }
//     return start;
// }

static list_ele_t *merge(list_ele_t *left, list_ele_t *right)
{
    list_ele_t *head = NULL;

    for (list_ele_t **iter = &head; true; iter = &((*iter)->next)) {
        if (!left) {
            (*iter) = right;
            break;
        }
        if (!right) {
            (*iter) = left;
            break;
        }
        if (strcmp(left->value, right->value) < 0) {
            (*iter) = left;
            left = left->next;
        } else {
            (*iter) = right;
            right = right->next;
        }
    }
    return head;
}

// list_ele_t *merge_sort(list_ele_t *head)
// {
//     if (!head || !head->next) {
//         return head;
//     }

//     list_ele_t *fast = head->next;
//     list_ele_t *slow = head;

//     while (fast && fast->next) {
//         fast = fast->next->next;
//         slow = slow->next;
//     }

//     list_ele_t *left = head;
//     list_ele_t *right = slow->next;
//     slow->next = NULL;

//     left = merge_sort(left);
//     right = merge_sort(right);

//     return merge(left, right);
// }
static list_ele_t *merge_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;

    list_ele_t *slow = head, *fast;
    for (fast = head->next; fast && fast->next; fast = fast->next->next)
        slow = slow->next;

    list_ele_t *mid = slow->next;
    slow->next = NULL;
    return merge(merge_sort(head), merge_sort(mid));
}


void q_sort(queue_t *q)
{
    if (!q || !q->head) {
        return;
    }
    if (q->head == q->tail) {
        return;
    }
    q->head = merge_sort(q->head);
    list_ele_t *iter;
    iter = q->head;
    while (iter && iter->next)
        iter = iter->next;
    q->tail = iter;
}