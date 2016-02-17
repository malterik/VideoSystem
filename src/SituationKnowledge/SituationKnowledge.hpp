#include <chrono>
enum FlightPhase {PARKING, TAKEOFF, CRUISE, LANDING };

class SituationKnowledge 
{
public:
    SituationKnowledge();

private:
    std::chrono::time_point<std::chrono::system_clock> system_clock_;
    int number_of_people_;
    FlightPhase current_flight_phase_;

    
public:
    std::chrono::time_point<std::chrono::system_clock> getSystemClock();
    void setSystemClock(std::chrono::time_point<std::chrono::system_clock> systemClock);

    int getNumberOfPeople();
    void setNumberOfPeople(int numberOfPeople);
};
