#include "linkedlist.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

struct jobNode *head = NULL;

struct jobNode *createJobNode(int pid, char *name)
{
    struct jobNode *newJobNode = (struct jobNode *)malloc(sizeof(struct jobNode));
    newJobNode->pid = pid;
    strcpy(newJobNode->name, name);
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
        //set jobnum to 1
        job->jobnum = 1;
        return;
    }
    while (insert->next != NULL)
    {
        insert = insert->next;
    }
    insert->next = job;
    //adjust job number based on preceding job
    job->jobnum = insert->jobnum + 1;
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
            if (curr == head)
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

//returns the head of the linked list
struct jobNode *getHead()
{
    return head;
}