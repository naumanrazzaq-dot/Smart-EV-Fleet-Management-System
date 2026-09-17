#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string plateNumber;
    double batteryLevel;

public:
    static int activeVehiclesOnRoad;

    Vehicle(string plateNumber, double batteryLevel) {
        this->plateNumber = plateNumber;
        this->batteryLevel = batteryLevel;
        activeVehiclesOnRoad++;
    }

    virtual ~Vehicle() {
        cout << "[OFFLINE] Vehicle " << plateNumber << " returned to base." << endl;
        activeVehiclesOnRoad--;
    }

    virtual double calculateRemainingRange() = 0;
    virtual void showStatus() = 0;
};

int Vehicle::activeVehiclesOnRoad = 0;

class DeliveryVan : public Vehicle {
private:
    double cargoWeightKg;

public:
    DeliveryVan(string plateNumber, double batteryLevel, double cargoWeightKg)
        : Vehicle(plateNumber, batteryLevel), cargoWeightKg(cargoWeightKg) {}

    double calculateRemainingRange() override {
        double range = (batteryLevel * 3.0) - (cargoWeightKg * 0.1);
        return (range < 0.0) ? 0.0 : range;
    }

    void showStatus() override {
        cout << "\n--- [DELIVERY VAN STATUS] ---" << endl;
        cout << "Plate Number    : " << plateNumber << endl;
        cout << "Battery Level   : " << batteryLevel << "%" << endl;
        cout << "Cargo Weight    : " << cargoWeightKg << " kg" << endl;
        cout << "Estimated Range : " << calculateRemainingRange() << " km" << endl;
    }
};

class PassengerCab : public Vehicle {
private:
    int passengerCount;

public:
    PassengerCab(string plateNumber, double batteryLevel, int passengerCount)
        : Vehicle(plateNumber, batteryLevel), passengerCount(passengerCount) {}

    double calculateRemainingRange() override {
        double range = (batteryLevel * 4.0) - (passengerCount * 5.0);
        return (range < 0.0) ? 0.0 : range;
    }

    void showStatus() override {
        cout << "\n--- [PASSENGER CAB STATUS] ---" << endl;
        cout << "Plate Number    : " << plateNumber << endl;
        cout << "Battery Level   : " << batteryLevel << "%" << endl;
        cout << "Passenger Count : " << passengerCount << endl;
        cout << "Estimated Range : " << calculateRemainingRange() << " km" << endl;
    }
};

int main() {
    Vehicle* fleet[2];

    fleet[0] = new DeliveryVan("VAN-404", 90.0, 120.0);
    fleet[1] = new PassengerCab("CAB-786", 75.0, 3);

    for (int i = 0; i < 2; i++) {
        fleet[i]->showStatus();
    }

    cout << "\n=============================================" << endl;
    cout << "Active Vehicles on Road: " << Vehicle::activeVehiclesOnRoad << endl;
    cout << "=============================================\n" << endl;

    for (int i = 0; i < 2; i++) {
        delete fleet[i];
        fleet[i] = nullptr;
    }

    cout << "\n=============================================" << endl;
    cout << "Active Vehicles after Return: " << Vehicle::activeVehiclesOnRoad << endl;
    cout << "=============================================" << endl;

    return 0;
}