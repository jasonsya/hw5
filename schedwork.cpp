#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCount,
    size_t day,
    size_t workerID
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t n = avail.size();
    size_t d = avail[0].size();

    sched.resize(n);

    vector<size_t> shiftCount(d, 0);
    
    return schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);


}

bool schedHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCount,
    size_t day,
    size_t workerID
) 
{
    size_t n = avail.size();
    size_t d = avail[0].size();

    if (day == n) {
        return true;
    }

    if (sched[day].size() == dailyNeed) {
        return schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day+1, 0);
    }

    if (workerID == d) {
        return false;
    }

    if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day, workerID+1)) {
        return true;
    }

    if (avail[day][workerID] && shiftCount[workerID] < maxShifts) {
        bool alreadyScheduled = false;
        for (size_t i = 0; i < sched[day].size(); ++i) {
            if (sched[day][i] == workerID) {
                alreadyScheduled = true;
                break;
            }
        }

        if (!alreadyScheduled) {
            sched[day].push_back(workerID);
            shiftCount[workerID]++;

            if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day, workerID+1)) {
                return true;
            }

            sched[day].pop_back();
            shiftCount[workerID]--;
        }
    }

    return false;

}
    
