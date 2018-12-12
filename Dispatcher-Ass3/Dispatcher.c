#include <stdio.h>

#define TasksNumber 10
#define IDLE 0
#define READY 3 
#define DELAYED 5 


char TaskQueueHead;
char TaskQueueTail;
char DelayQueueHead;
char DelayQueueTail;


struct task{
    char delay;
    char status;
    char next;
    void (*tpntr)();
};

struct task TASKS[TasksNumber+1];


char AddNewTask(void (*task_function_pointer)()){
    char index = 0;
    do
    { 
        index++;  // increment the counter
        if (TASKS[index].status == IDLE)  // Adding the New Task to the tail of the Queue //
        {
            TASKS[index].tpntr = task_function_pointer;
            TASKS[index].status = READY;
            return index;   
        }

    } while(index<=TasksNumber);

    return 0;
}

char QueTask(void (*task_function_pointer)()){
    char index = AddNewTask(task_function_pointer);
    if(index)
    {
        TASKS[TaskQueueTail].next = index;
        TaskQueueTail = index;
    }
}

void QueDelay(void (*task_function_pointer)(), char delay){
    
    char index = AddNewTask(task_function_pointer);

    if(index)
    {
        char current_position = DelayQueueHead;    
        do
        {
            if (delay - TASKS[current_position].delay > 0){
                current_position = TASKS[current_position].next;
                delay -= TASKS[current_position].delay;
            }
            else
            {   
                TASKS[index].next = TASKS[current_position].next;
                TASKS[current_position].next = index;
                TASKS[current_position].delay -= delay;
            }
        } while(delay > 0);
    }

}


void ReRunMe(char delay){
    if(delay == 0) QueTask(TASKS[TaskQueueHead].tpntr);  // No Delay so put it in the ReadyQueue
    else QueDelay(TASKS[TaskQueueHead].tpntr, delay);  // Add to Delay Queue // 
}

void DecrementDelay(){
    TASKS[DelayQueueHead].delay -= 1;  // Decrement the delay by one 
    if(!TASKS[DelayQueueHead].delay)  // Head of Delay is zero 
    {
        TASKS[TaskQueueTail].next = DelayQueueHead;
        TaskQueueTail = DelayQueueHead;
        TASKS[TaskQueueTail].status = READY;
        TASKS[TaskQueueTail].next = 0;
        DelayQueueHead = TASKS[DelayQueueHead].next;  //  Let the next position in the delay queue as head
    }
}

void RunTask()
{
    (*TASKS[TaskQueueHead].tpntr)();  // Execute the first task in the Queue
    TASKS[TaskQueueHead].status = IDLE;  // Make it an idle task
}

void Dispatch(){
    
    RunTask();
    TaskQueueHead = TASKS[TaskQueueHead].next;  // Make the Next Task as the Queue Head
}

void DisableIRQ();
void EnableIRQ();

int main(){
    char c =  (char) 66;

    printf("%d\n",c+3);
}