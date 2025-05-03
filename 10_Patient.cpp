#include <queue>
#include <string>
#include <iostream>

// Define a Patient struct to hold patient information and priority
struct Patient {
  std::string name;
  int priority; // 1 (highest) - 3 (lowest)

  Patient(const std::string& name, int priority) : name(name), priority(priority) {}
};

int main() {
  // Create a priority queue using a min-heap and custom comparison function (lambda function)
  auto comparePatients = [](const Patient& p1, const Patient& p2) {
    return p1.priority > p2.priority; // Higher priority goes first (lower number)
  };

  std::priority_queue<Patient, std::vector<Patient>, decltype(comparePatients)> patientQueue(comparePatients);

  // Number of patients to add
  int numPatients;
  std::cout << "Enter the number of patients: ";
  std::cin >> numPatients;
  std::cin.ignore(); // Clear input buffer

  // Add patients
  for (int i = 0; i < numPatients; ++i) {
    std::string name;
    int priority;
    
    std::cout << "Enter name of patient " << i+1 << ": ";
    std::getline(std::cin, name);
    
    std::cout << "Enter priority of patient " << i+1 << " (1 for Serious, 2 for Non-serious, 3 for General Checkup): ";
    std::cin >> priority;
    std::cin.ignore(); // Clear input buffer

    patientQueue.emplace(name, priority);
  }

  // Simulate treating patients
  std::cout << "\nTreating patients:\n";
  while (!patientQueue.empty()) {
    Patient nextPatient = patientQueue.top();
    patientQueue.pop();

    // Treat the patient (simulated by printing information)
    std::string priorityStr;
    if (nextPatient.priority == 1)
        priorityStr = "Serious";
    else if (nextPatient.priority == 2)
        priorityStr = "Non-serious";
    else
        priorityStr = "General Checkup";

    std::cout << "Name: " << nextPatient.name << ", Priority: " << priorityStr << std::endl;
  }

  return 0;
}