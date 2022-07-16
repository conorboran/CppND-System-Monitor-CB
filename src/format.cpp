#include <string>
#include <vector>

#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds_in)
{
    int hours = int(seconds_in / 3600);
    int minutes = int((seconds_in % 3600) / 60);
    int seconds = int((seconds_in % 3600) % 60);

    std::vector<int> time_ints {hours, minutes, seconds};
    std::vector<string> time_strings {std::to_string(hours), std::to_string(minutes), std::to_string(seconds)};

    for(int i = 0; i < time_ints.size(); i++)
    {
        if(time_ints[i] < 10)
        {
            time_strings[i] = "0" + time_strings[i];
        }
    }

    string elapsed_time = time_strings[0] + ":" + time_strings[1] + ":" + time_strings[2];

    return elapsed_time;
}
