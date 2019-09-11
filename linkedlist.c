#include "linkedlist.h"
#include "shell.h"
#include <stdlib.h>

struct jobNode *head = NULL;

struct jobNode *createJobNode(int pid, char *name, int jobnum)
{
    struct jobNode *newJobNode = (struct jobNode *)malloc(sizeof(struct jobNode));
    newJobNode->pid = pid;
    strcpy(newJobNode->name, name);
    newJobNode->jobnum = jobnum;
    newJobNode->next = NULL;
    return newJobNode;
}

//adds job at end end of linked list
void addJobNode(struct jobNode *job)
{
    struct jobNode *insert = head;
    if (head == NULL)
    {
        head = job;
        return;
    }
    while (insert->next != NULL)
    {
        insert = insert->next;
    }
    insert->next = job;
    return;
}

//delete from linked list based on pid
void deleteJobNode(int pid)
{
    struct jobNode *prev = head;
    struct jobNode *curr = head;
    while (curr != NULL)
    {
        if (curr->pid == pid)
        {
            prev->next = curr->next;
            if(curr == head)
            {
                head = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}