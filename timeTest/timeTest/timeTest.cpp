// timeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t ms;
} TIME_T;    

void ms2time(uint32_t ms, TIME_T * time) {
        time->ms = ms % 1000;
        time->seconds = (ms / 1000) % 60;
        time->minutes = (ms / 60000) % 60;
        time->hours = ms / 3600000;
    }
    void time2ms(TIME_T time, uint32_t * ms) {
        *ms = time.ms + time.seconds * 1000 + time.minutes * 60000 + time.hours * 3600000;
    }
    

int main()
{
    TIME_T t;
    t.hours = 15;
    t.minutes = 2;
    t.seconds = 44;
    t.ms = 392;

    uint32_t ms;
    time2ms(t, &ms);
    printf("ms: %u\r\n", ms);
    ms2time(ms, &t);
    printf("t: %u:%u:%u::%u", t.hours, t.minutes, t.seconds, t.ms);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
