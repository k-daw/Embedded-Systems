#include <stdio.h>



#define TasksNumber 10
#define IDLE 0
#define READY 3 
#define DELAYED 5 


char TaskQueueHead = 1;
char TaskQueueTail = 1;
char DelayQueueHead = 0;
char DelayQueueTail = 0;


struct task{
    char delay;
    char status;
    char next;
    void (*tpntr)();  // we can add an optimzation here, by saving the initial pointer of the program, and saving only the offset of the program
} TASKS[TasksNumber+1];




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


void RunTask(){
		if(TaskQueueHead)
    {
			(*TASKS[TaskQueueHead].tpntr)();  // Execute the first task in the Queue
			TASKS[TaskQueueHead].status = IDLE;  // Make it an idle task
		}
}

char QueTask(void (*task_function_pointer)()){
    char index = AddNewTask(task_function_pointer);
    if(index)
    {
        TASKS[TaskQueueTail].next = index;
        TaskQueueTail = index;
				TASKS[index].next = 0;
        return 1;
    }
    return 0;
}

void QueDelay(void (*task_function_pointer)(), char delay_of_task){
    char delay = delay_of_task;
    char index = AddNewTask(task_function_pointer);
		
    if(index)
    {
			if(!DelayQueueHead){  // The Delay Queue is empty
				
				DelayQueueHead = index;
				DelayQueueTail = index;
				TASKS[index].status = DELAYED;
				TASKS[index].next = 0;
				TASKS[index].tpntr = task_function_pointer;
				TASKS[index].delay = delay_of_task;
			}
			else{
				char current_position = DelayQueueHead; 
				do
				{
						if (delay - TASKS[current_position].delay > 0){
							
								if (!TASKS[current_position].next){  //  we reached the end of the DelayQueue
									
									DelayQueueTail = index;
									TASKS[current_position].next = index;
									TASKS[index].status = DELAYED;
									TASKS[index].next = 0;
									TASKS[index].tpntr = task_function_pointer;
									TASKS[index].delay = delay - TASKS[current_position].delay;
									return;
								}
						}
						else
						{   
							TASKS[index].next = TASKS[current_position].next;
							TASKS[current_position].next = index;
							TASKS[current_position].delay = delay;
							break;
						}
					delay -= TASKS[current_position].delay;
					current_position = TASKS[current_position].next ;
					
						
				} while(delay_of_task >= delay);
			}
		}
}

void ReRunMe(char delay){
    if(delay == 0) QueTask(TASKS[TaskQueueHead].tpntr);  // No Delay so put it in the ReadyQueue
    else QueDelay(TASKS[TaskQueueHead].tpntr, delay);  // Add to Delay Queue // 
}

void DecrementDelay(){
		if (TASKS[DelayQueueHead].status == DELAYED){
			TASKS[DelayQueueHead].delay -= 1;  // Decrement the delay by one 
			if(!TASKS[DelayQueueHead].delay)  // Head of Delay is zero 
			{
				if(TaskQueueHead) TASKS[TaskQueueTail].next = DelayQueueHead;
				else TaskQueueHead = DelayQueueHead;
	
				TaskQueueTail = DelayQueueHead;
				DelayQueueHead = TASKS[DelayQueueHead].next;
				TASKS[TaskQueueTail].status = READY;
				  //  Let the next position in the delay queue as head
				TASKS[TaskQueueTail].next = 0;
				
			}
		}
}


void Dispatch(){
    RunTask();
    TaskQueueHead = TASKS[TaskQueueHead].next;  // Make the Next Task as the Queue Head
}
