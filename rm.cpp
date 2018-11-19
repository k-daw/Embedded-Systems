// Embedded Systems, The American University in Cairo
// Assignment N2 --> RM scheduler simulator
// Mohamed Daw --> daw@aucegypt.edu

#include<iostream>
#include<vector>
#include<queue>

using namespace std;


struct Task
{
    int WCET = 0;
    int Period = 0;
};

  
int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 
  
// Returns LCM of array elements 
int findlcm(vector<int> arr) 
{ 
    // Initialize result 
    int ans = arr[0]; 
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < arr.size(); i++) 
        ans = (((arr[i] * ans)) / 
                (gcd(arr[i], ans))); 
  
    return ans; 
} 

int CalculateHyperPeriod(vector<Task> Tasks){
    vector<int> TaskPeriod;
    for(int i=0; i<Tasks.size(); i++)
        TaskPeriod.push_back(Tasks[i].Period);
    
    return findlcm(TaskPeriod);
}

void ExecuteTask(Task &t);

void UpdateScheduler(priority_queue<Task> ScheduleQueue);

void RMScheduler(vector<Task> Tasks)
{   
    int HyperPeriod = CalculateHyperPeriod(Tasks);
}
void main(){
    int NumberTasks,TaskPeriod, TaskWCET;
    vector<Task> Tasks;
    
    cout<<"Enter number of Tasks to excute\n";
    cin>> NumberTasks;

    for(int i=0; i<NumberTasks; i++)
    {   
        Task Temp;
        cin>>Temp.Period>>Temp.WCET;
        Tasks.push_back(Temp);
    }






}