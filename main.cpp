#include <iostream>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

class BusStopSimulation {
private:
    double avg_passenger_arrival_time;
    double avg_bus_arrival_time;
    bool is_terminal;
    int max_people_at_stop;
    int passengers_at_stop;

public:
    BusStopSimulation(double avg_passenger_arrival_time, double avg_bus_arrival_time, bool is_terminal, int max_people_at_stop)
        : avg_passenger_arrival_time(avg_passenger_arrival_time),
        avg_bus_arrival_time(avg_bus_arrival_time),
        is_terminal(is_terminal),
        max_people_at_stop(max_people_at_stop),
        passengers_at_stop(0) {}

    double generate_passenger_arrival_time() {
        random_device rd;
        mt19937 gen(rd());
        exponential_distribution<> passenger_distribution(1.0 / avg_passenger_arrival_time);
        return passenger_distribution(gen);
    }

    double generate_bus_arrival_time() {
       random_device rd;
       mt19937 gen(rd());
       exponential_distribution<> bus_distribution(1.0 / avg_bus_arrival_time);
        return bus_distribution(gen);
    }

    void simulate(double simulation_time) {
        double time_elapsed = 0;

        while (time_elapsed < simulation_time) {
            double passenger_arrival_time = generate_passenger_arrival_time();
            double bus_arrival_time = generate_bus_arrival_time();

            if (passenger_arrival_time < bus_arrival_time) {
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(passenger_arrival_time * 1000)));
                passengers_at_stop++;
                cout << "Passenger arrived at the stop. People at stop: " << passengers_at_stop << endl;
            }
            else {
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(bus_arrival_time * 1000)));
                if (passengers_at_stop > 0) {
                    int passengers_boarded = std::min(passengers_at_stop, max_people_at_stop);
                    passengers_at_stop -= passengers_boarded;
                    cout << "Bus arrived at the stop. Passengers boarded: " << passengers_boarded << ". People at stop: " << passengers_at_stop << endl;
                }
                else {
                    cout << "Bus arrived at the stop. No passengers to board. People at stop: 0" << endl;
                }
            }

            time_elapsed += min(passenger_arrival_time, bus_arrival_time);
        }
    }
};

int main() {
    BusStopSimulation simulation(10.0, 15.0, false, 5); 
    simulation.simulate(60.0); 

    return 0;
}

