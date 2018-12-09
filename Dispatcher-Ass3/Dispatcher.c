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


char QueTask(void (*task_function_pointer)()){
    char index = 0;
    do
    { 
        index++;  // increment the counter
        if (TASKS[index].status == IDLE)  // Adding the New Task to the tail of the Queue //
        {
            TASKS[index].tpntr = task_function_pointer;
            TASKS[index].status = READY;
            TASKS[index].index = 0;
            TASKS[TaskQueueTail].next = index;
            TaskQueueTail = index;
        }

    } while(index<=TasksNumber);

    return index==TasksNumber? 0:1;  // Return 0 if insertions is not successful 
}

void QueDelay(void (*task_function_pointer)(), char delay){
    
    char current_position = DelayQueueHead;
    delay -= TASKS[current_position].delay;
    while(delay > 0){
        if (delay - TASKS[current_position].delay > 0 ){
            current_position = TASKS[current_position].next;
            delay -= TASKS[current_position].next;
        }
        else
        {   
            NewTask.next = TASKS[current_position].next;
            TASKS[current_position].next = NewTask;
        }

    }

    }
}

void ReRunMe(char delay = 0){
    
    NewTask = TASKS[TaskQueueHead];  // Create New Task
    
    if(delay == 0) QueTask();  // No Delay so put it in the ReadyQueue
    else QueDelay(delay);  // Add to Delay Queue // 
}

void DecrementDelay(){
    
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