#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

const int MAX_RESOURCES = 10;
const int MAX_THREADS = 5;

vector<int> available(MAX_RESOURCES);
vector<vector<int>> maximum(MAX_THREADS, vector<int>(MAX_RESOURCES));
vector<vector<int>> allocation(MAX_THREADS, vector<int>(MAX_RESOURCES));
vector<vector<int>> need(MAX_THREADS, vector<int>(MAX_RESOURCES));

mutex mtx;

bool isSafeState(vector<int>& request, int thread_id) {
    vector<int> work(available);
    vector<bool> finish(MAX_THREADS, false);

    // Check if the request is within the need of the thread
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[thread_id][i])
            return false;
    }

    // Check if the request can be granted
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > work[i])
            return false;
    }

    // Try to allocate the request and check if the new state is safe
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] -= request[i];
        allocation[thread_id][i] += request[i];
        need[thread_id][i] -= request[i];
        finish[thread_id] = true;
    }

    bool found;
    do {
        found = false;
        for (int i = 0; i < MAX_THREADS; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < MAX_RESOURCES; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while (found);

    // Release the request if the new state is safe
    if (finish[thread_id]) {
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] = work[i];
        }
    }
    else {
        for (int i = 0; i < MAX_RESOURCES; i++) {
            allocation[thread_id][i] -= request[i];
            need[thread_id][i] += request[i];
        }
    }

    return finish[thread_id];
}

void processRequest(int thread_id, vector<int>& request) {
    mtx.lock();
    if (isSafeState(request, thread_id)) {
        cout << "Thread " << thread_id << " request granted." << endl;
    }
    else {
        cout << "Thread " << thread_id << " request denied." << endl;
    }
    mtx.unlock();
}

int main() {
    ifstream input("request.txt");
    if (!input.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 0;
    }

    // Read available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        input >> available[i];
    }

    // Read maximum resources
    for (int i = 0; i < MAX_THREADS; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            input >> maximum[i][j];

