// Embedded Systems, The American University in Cairo
// Assignment N2 --> RM scheduler simulator
// Mohamed Daw --> daw@aucegypt.edu

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>


using namespace std;


struct Task
{
    string TaskId;
    int WCET = 0;
    int Period = 0;
    int TimeNeeded = Period;
    bool operator <(const Task &other) const {return this->Period>other.Period;}
    bool operator >(const Task &other) const {return this->Period<other.Period;}
    bool operator ==(const Task &other) const {return this->Period==other.Period;}
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


void ExecuteTask(Task t){
    t.TimeNeeded--;
}


void UpdateScheduler(priority_queue<Task> ScheduleQueue, vector<Task> Tasks, int timer)
{
    std::vector<Task>::const_iterator it;
    priority_queue<Task> CopyScheduleQueue = ScheduleQueue;
    vector<Task> ScheduledTasks;
    
    while(!CopyScheduleQueue.empty())
    {
        Task temp_task = CopyScheduleQueue.top();
        CopyScheduleQueue.pop();
        ScheduledTasks.push_back(temp_task);
    }
    
    for(int i=0; i<Tasks.size(); i++)
        if(timer%Tasks[i].Period == 0)
        {
            it = find(ScheduledTasks.begin(), ScheduledTasks.end(), Tasks[i]);
            if (it == ScheduledTasks.end())
                ScheduleQueue.push(Tasks[i]);
            else
            {    cerr<<"A deadline was Missed \nAborting\n";
                exit(-9);
            }
            
        }
    
}
priority_queue<Task>  Initialize(vector<Task> Tasks)
{
    priority_queue<Task> ScheduleQueue(Tasks.begin(), Tasks.end());
    return ScheduleQueue;
}


void PrintScheduling(vector<string> Scheduling){
    for(int i=0; i<Scheduling.size(); i++)
        cout<<Scheduling[i];
}


vector<string> RMScheduler(vector<Task> Tasks)
{
    int HyperPeriod = CalculateHyperPeriod(Tasks);
    vector<string> Scheduling;
    string IDLE = "\tIdle";
    priority_queue<Task> ScheduleQueue;
    
    ScheduleQueue = Initialize(Tasks);
    
    
    
    for(int time=0; time<HyperPeriod; time++){
        
        if(!ScheduleQueue.empty()){
            Task HighestPriority = ScheduleQueue.top();
            ScheduleQueue.pop();
            
            ExecuteTask(HighestPriority);
            Scheduling.push_back('\t' + HighestPriority.TaskId);
            if(HighestPriority.TimeNeeded > 0)
                ScheduleQueue.push(HighestPriority);
            
            
            UpdateScheduler(ScheduleQueue, Tasks, time);
        }
        else
            Scheduling.push_back(IDLE);
        
    }
    PrintScheduling(Scheduling);
}

int main(){
    int NumberTasks,TaskPeriod, TaskWCET;
    vector<Task> Tasks;
    
    cout<<"Enter number of Tasks to excute\n";
    cin>> NumberTasks;
    
    for(int i=0; i<NumberTasks; i++)
    {
        Task Temp;
        cin>>Temp.TaskId>>Temp.Period>>Temp.WCET;
        Tasks.push_back(Temp);
    }
    
    
    return 0;
}
// Embedded Systems, The American University in Cairo
// Assignment N2 --> RM scheduler simulator
// Mohamed Daw --> daw@aucegypt.edu

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>


using namespace std;


struct Task
{
    string TaskId;
    int WCET = 0;
    int Period = 1;
    int TimeNeeded = 0;
    bool operator <(const Task &other) const {return this->Period>other.Period;}
    bool operator >(const Task &other) const {return this->Period<other.Period;}
    bool operator ==(const Task &other) const {return this->Period==other.Period;}
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


void ExecuteTask(Task& t){
    t.TimeNeeded--;
}


priority_queue<Task> UpdateScheduler(priority_queue<Task> ScheduleQueue, vector<Task> Tasks, int timer)
{
    std::vector<string>::const_iterator it;
    priority_queue<Task> CopyScheduleQueue = ScheduleQueue;
    vector<string> ScheduledTasks;
    
    while(!CopyScheduleQueue.empty())
    {
        Task temp_task = CopyScheduleQueue.top();
        CopyScheduleQueue.pop();
        ScheduledTasks.push_back(temp_task.TaskId);
    }
    
    for(int i=0; i<Tasks.size(); i++)
        if(timer%Tasks[i].Period == 0 && timer!=0)
        {
            it = find(ScheduledTasks.begin(), ScheduledTasks.end(), Tasks[i].TaskId);
            if (it == ScheduledTasks.end())
                ScheduleQueue.push(Tasks[i]);
            else
            {    cerr<<"A deadline was Missed \nAborting\n";
                exit(-9);
            }
            
        }
    return ScheduleQueue;
}
priority_queue<Task>  Initialize(vector<Task> Tasks)
{
    
    priority_queue<Task> ScheduleQueue(Tasks.begin(), Tasks.end());
    return ScheduleQueue;
}


void PrintScheduling(vector<string> Scheduling){
    for(int i=0; i<Scheduling.size(); i++)
        cout<<Scheduling[i];
    cout<<endl;
}


void RMScheduler(vector<Task> Tasks)
{
    int HyperPeriod = CalculateHyperPeriod(Tasks);
    vector<string> Scheduling;
    string IDLE = "\tIdle";
    priority_queue<Task> ScheduleQueue;
    
    ScheduleQueue = Initialize(Tasks);
    
    cout<< HyperPeriod;
    
    for(int time=0; time<HyperPeriod; time++){
        if(!ScheduleQueue.empty()){
            Task HighestPriority = ScheduleQueue.top();
            ScheduleQueue.pop();
            
            ExecuteTask(HighestPriority);
            
            
            if(HighestPriority.TimeNeeded > 0)
                ScheduleQueue.push(HighestPriority);
            Scheduling.push_back('\t' + HighestPriority.TaskId);
        }
        else
            Scheduling.push_back(IDLE);
        ScheduleQueue = UpdateScheduler(ScheduleQueue, Tasks, time);
        
    }
    PrintScheduling(Scheduling);
}

int main(){
    int NumberTasks;
    vector<Task> Tasks;
    
    cout<<"Enter number of Tasks to excute\n";
    cin>> NumberTasks;
    
    for(int i=0; i<NumberTasks; i++)
    {
        Task Temp;
        cin>>Temp.TaskId>>Temp.Period>>Temp.WCET;
        Temp.TimeNeeded = Temp.WCET;
        Tasks.push_back(Temp);
        
    }
    RMScheduler(Tasks);
    
    return 0;
}


