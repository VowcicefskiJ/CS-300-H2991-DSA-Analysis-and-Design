#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <map> // Included for sorting

// Class representing a course
class Course {
public:
    std::string courseNumber; // Unique identifier for the course
    std::string name; // Name of the course
    std::vector<std::string> prerequisites; // List of prerequisites for the course

    // Default constructor
    Course() {}

    // Constructor with parameters
    Course(const std::string& courseNumber, const std::string& name, const std::vector<std::string>& prerequisites)
        : courseNumber(courseNumber), name(name), prerequisites(prerequisites) {}
};

// Function to load courses from a file
std::unordered_map<std::string, Course> loadCoursesFromFile(const std::string& fileName) {
    std::unordered_map<std::string, Course> courses; // Data structure to store courses
    std::ifstream file(fileName); // File stream for reading

    // Check if file can be opened
    if (!file) {
        std::cerr << "Error: Unable to open file: " << fileName << std::endl;
        return courses; // Return empty map if file cannot be opened
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::istringstream iss(line); // String stream for parsing line
        std::string token;
        std::vector<std::string> tokens; // Vector to store parsed tokens

        // Parse line by commas
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        // Check for sufficient data in line
        if (tokens.size() < 2) {
            std::cerr << "Error: Insufficient data in line: " << line << std::endl;
            continue; // Skip to next line if data is insufficient
        }

        // Extract course data
        std::string courseNumber = tokens[0];
        std::string name = tokens[1];
        std::vector<std::string> prerequisites(tokens.begin() + 2, tokens.end());

        // Add course to the map
        courses[courseNumber] = Course(courseNumber, name, prerequisites);
    }

    return courses; // Return the map of courses
}

// Function to print the list of courses
void printCourseList(const std::unordered_map<std::string, Course>& courses) {
    // Convert to map to sort courses
    std::map<std::string, Course> sortedCourses(courses.begin(), courses.end());

    std::cout << "\n--- Course List ---\n";
    // Iterate and print each course
    for (const auto& pair : sortedCourses) {
        std::cout << pair.first << ", " << pair.second.name << std::endl;
    }
    std::cout << "--- End of Course List ---\n\n";
}

// Function to print information about a specific course
void printCourseInformation(const std::unordered_map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber); // Find the course by its number

    // Check if course is found
    if (it != courses.end()) {
        const Course& course = it->second;
        std::cout << "\nCourse Number: " << course.courseNumber << std::endl;
        std::cout << "Name: " << course.name << std::endl;
        std::cout << "Prerequisites: ";
        for (const auto& prerequisite : course.prerequisites) {
            std::cout << prerequisite << " ";
        }
        std::cout << "\n\n";
    }
    else {
        std::cout << "\nCourse not found\n\n"; // Print error if course not found
    }
}

// Main function
int main() {
    std::unordered_map<std::string, Course> courses; // Map to store courses
    std::string choice, fileName, courseNumber;

    // Main loop for user interaction
    while (true) {
        std::cout << "\nWelcome to the course planner.\n";
        std::cout << "1. Load Data Structure.\n";
        std::cout << "2. Print Course List.\n";
        std::cout << "3. Print Course.\n";
        std::cout << "9. Exit\n";
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        // Handle user choices
        if (choice == "1") {
            std::cout << "\nEnter the filename to load: ";
            std::cin >> fileName;
            courses = loadCoursesFromFile(fileName);
            if (!courses.empty()) {
                std::cout << "\nCourse data loaded successfully.\n";
            }
        }
        else if (choice == "2") {
            if (courses.empty()) {
                std::cout << "\nNo course data available. Please load data first.\n";
            }
            else {
                printCourseList(courses);
            }
        }
        else if (choice == "3") {
            if (courses.empty()) {
                std::cout << "\nNo course data available. Please load data first.\n";
            }
            else {
                std::cout << "\nWhat course do you want to know about? ";
                std::cin >> courseNumber;
                printCourseInformation(courses, courseNumber);
            }
        }
        else if (choice == "9") {
            std::cout << "\nThank you for using the course planner!\n";
            break; // Exit the program
        }
        else {
            std::cout << "\nError, incorrect request\n\n"; // Handle invalid input
        }
    }

    return 0; // End of program
}
