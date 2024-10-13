#include <stdio.h>
#include <string.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};


void get_process_input(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }
}

void sort_by_arrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sort_by_burst(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time ||
                (processes[j].burst_time == processes[j + 1].burst_time && processes[j].arrival_time > processes[j + 1].arrival_time)) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void fcfs(struct Process processes[], int n) {
    sort_by_arrival(processes, n);
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].response_time = current_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].response_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }
}

void sjf(struct Process processes[], int n) {
    sort_by_burst(processes, n);
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].response_time = current_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].response_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }
}

void display_results(struct Process processes[], int n, char* algorithm) {
    printf("\n=== %s ===\n", algorithm);
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");
    printf("PID  AT  BT  WT  TAT  RT\n");
    for (int i = 0; i < n; i++) {
        printf("%d    %d   %d   %d   %d   %d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
    }
}

void calculate_averages(struct Process processes[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_response_time += processes[i].response_time;
    }
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Response Time: %.2f\n", total_response_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    get_process_input(processes, n);
    struct Process fcfs_processes[n];
    memcpy(fcfs_processes, processes, sizeof(fcfs_processes));
    fcfs(fcfs_processes, n);
    display_results(fcfs_processes, n, "First Come First Served (FCFS)");
    calculate_averages(fcfs_processes, n);
    struct Process sjf_processes[n];
    memcpy(sjf_processes, processes, sizeof(sjf_processes));
    sjf(sjf_processes, n);
    display_results(sjf_processes, n, "Shortest Job First (SJF)");
    calculate_averages(sjf_processes, n);
    return 0;
}
