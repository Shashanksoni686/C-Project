#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

const int MAX_SLOTS = 10;
const int RATE_PER_HOUR = 20; // Customize hourly rate ₹

struct Car {
    string plateNumber;
    time_t timeIn;
};

vector<Car> parkingLot;
int totalEarnings = 0;

void showMenu() {
    cout << "\n=== CAR PARKING MANAGEMENT SYSTEM (HOURLY RATE) ===\n";
    cout << "1. Park a Car\n";
    cout << "2. Remove a Car (Calculate Charges)\n";
    cout << "3. Show Parked Cars\n";
    cout << "4. Show Total Earnings\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

void parkCar() {
    if (parkingLot.size() >= MAX_SLOTS) {
        cout << "Parking is full! 🚫\n";
        return;
    }
    Car car;
    cout << "Enter Car Plate Number: ";
    cin >> car.plateNumber;
    car.timeIn = time(0); // current time
    parkingLot.push_back(car);
    cout << "Car parked at: " << ctime(&car.timeIn);
}

void removeCar() {
    string plate;
    cout << "Enter Plate Number to Remove: ";
    cin >> plate;
    
    time_t timeOut = time(0); // current time

    for (int i = 0; i < parkingLot.size(); i++) {
        if (parkingLot[i].plateNumber == plate) {
            double seconds = difftime(timeOut, parkingLot[i].timeIn);
            int hours = static_cast<int>(seconds / 3600);
            if (seconds > 0 && hours == 0) hours = 1; // round up if <1 hour

            int charge = hours * RATE_PER_HOUR;
            totalEarnings += charge;

            cout << "Car found! Parked from: " << ctime(&parkingLot[i].timeIn);
            cout << "Exit time: " << ctime(&timeOut);
            cout << "Duration: " << hours << " hour(s)\n";
            cout << "Parking Fee: ₹" << charge << "\n";

            parkingLot.erase(parkingLot.begin() + i);
            return;
        }
    }
    cout << "Car not found!\n";
}

void showParkedCars() {
    if (parkingLot.empty()) {
        cout << "No cars currently parked.\n";
        return;
    }
    cout << "\n--- Parked Cars ---\n";
    for (int i = 0; i < parkingLot.size(); i++) {
        cout << i + 1 << ". " << parkingLot[i].plateNumber
             << " | Time In: " << ctime(&parkingLot[i].timeIn);
    }
}

void showEarnings() {
    cout << "Total Earnings: ₹" << totalEarnings << "\n";
}

int main() {
    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: parkCar(); break;
            case 2: removeCar(); break;
            case 3: showParkedCars(); break;
            case 4: showEarnings(); break;
            case 5: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid option. Try again.\n";
        }
    }
}