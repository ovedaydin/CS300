//============================================================================
// Name        : Project-Two.cpp
// Author      : Oved AYDIN
// Version     : 1.0
// Copyright   : 2023 SNHU
// Description : Course Planning and Advising Assistance Program in C++
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <memory>

using namespace std;

const unsigned int DEFAULT_SIZE = 179;

class Course
{
public:
    string courseNumber;          // The course number, e.g., "CS101"
    string courseName;            // The name of the course
    vector<string> prerequisites; // A list of course prerequisites

    Course() {}
    Course(const string &number, const string &name, const vector<string> &prereqs)
        : courseNumber(number), courseName(name), prerequisites(prereqs) {}
};

class HashTable
{
private:
    struct Node
    {
        Course course;    // The course associated with this node
        unsigned int key; // Hash key
        Node *next;       // Pointer to the next node in the linked list

        Node()
        {
            key = UINT_MAX; // Initialize key to an invalid value
            next = nullptr;
        }

        Node(const Course &aCourse) : Node()
        {
            course = aCourse;
        }

        Node(const Course &aCourse, unsigned int aKey) : Node(aCourse)
        {
            key = aKey;
        }
    };

    vector<Node> nodes;                    // Vector to store linked lists of courses
    unsigned int tableSize = DEFAULT_SIZE; // Default table size

    unsigned int hash(const string &courseNumber); // Calculate the hash value
public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(const Course &course);                  // Insert a course into the hash table
    vector<pair<string, Course>> GetCourseList() const; // Get a list of all courses
    void Remove(const string &courseNumber);            // Remove a course by its course number
    Course Search(const string &courseNumber);          // Search for a course by its course number
};

// Default constructor
HashTable::HashTable()
{
    nodes.resize(tableSize); // Initialize the vector size to match the table size
}

// Constructor for specifying the size of the table
HashTable::HashTable(unsigned int size)
{
    this->tableSize = size; // Set the table size to the provided size
    nodes.resize(size);     // Resize the vector to match the specified size
}

// Destructor
HashTable::~HashTable()
{
    for (unsigned int i = 0; i < tableSize; i++)
    {
        Node *current = nodes[i].next;

        // Loop through the linked list and delete nodes
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
}

unsigned int HashTable::hash(const string &courseNumber)
{
    unsigned int index = 0;

    // Use a simple hash function to convert the course number to an index
    for (char ch : courseNumber)
    {
        index += static_cast<unsigned int>(ch);
    }

    return index % tableSize;
}

void HashTable::Insert(const Course &course)
{
    // Calculate the hash value for the course's unique identifier (e.g., courseNumber)
    unsigned int h = hash(course.courseNumber);

    // Retrieve the node in the hash table corresponding to the calculated hash value
    Node *currentNode = &nodes[h];

    // Check if there's already a node at that position
    if (currentNode->key == UINT_MAX)
    {
        // If not, create a new node and assign it to the key's position
        currentNode->course = course;
        currentNode->key = h;
        currentNode->next = nullptr;
    }
    else
    {
        // Loop If there's a node at that position
        while (currentNode->next != nullptr)
        {
            // Check if the existing node is unused (key set to UINT_MAX)
            if (currentNode->key == UINT_MAX)
            {
                currentNode->course = course;
                currentNode->key = h;
                return; // Course inserted, exit the function
            }
            // Move to the next node
            currentNode = currentNode->next;
        }

        // Create a new node and append it
        currentNode->next = new Node(course, h);
    }
}

/**
 * Get a list of courses stored in the hash table.
 *
 * @return A vector of pairs, where each pair contains the course number and the Course object.
 */
vector<pair<string, Course>> HashTable::GetCourseList() const
{
    vector<pair<string, Course>> courses;

    for (unsigned int i = 0; i < tableSize; i++)
    {
        const Node *currentNode = &nodes[i];

        // Check if the node at this position is used (contains a course)
        if (currentNode->key != UINT_MAX)
        {
            // Add the course to the vector with its course number as the key
            courses.push_back({currentNode->course.courseNumber, currentNode->course});

            // Move to the next node in the linked list
            currentNode = currentNode->next;

            // Iterate through the rest of the linked list if it exists
            while (currentNode != nullptr)
            {
                // Add the course to the vector with its course number as the key
                courses.push_back({currentNode->course.courseNumber, currentNode->course});

                // Move to the next node in the linked list
                currentNode = currentNode->next;
            }
        }
    }

    return courses; // Return the vector of courses
}

/**
 * Remove a course by its unique identifier (e.g., courseNumber)
 *
 * @param courseNumber The course number to search for
 */
void HashTable::Remove(const string &courseNumber)
{
    // Calculate the hash value for the courseNumber
    unsigned int h = hash(courseNumber);

    // Retrieve the node in the hash table corresponding to the calculated hash value
    Node *currentNode = &nodes[h];
    Node *prevNode = nullptr;

    // Traverse the linked list and find the node with the matching courseNumber
    while (currentNode != nullptr)
    {
        // Check if the current node has the matching courseNumber
        if (currentNode->course.courseNumber == courseNumber)
        {
            // If found, remove the node
            if (prevNode == nullptr)
            {
                // If the matched node is the first in the linked list
                // update the bucket entry
                nodes[h] = *currentNode->next;
            }
            else
            {
                // Otherwise, update the previous node's next pointer
                prevNode->next = currentNode->next;
                // Remove the node from memory
                delete currentNode;
            }
            return; // Course removed, exit the function
        }

        // Move to the next node in the linked list
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

/**
 * Search for the specified course by its unique identifier (e.g., courseNumber)
 *
 * @param courseNumber The course number to search for
 */
Course HashTable::Search(const string &courseNumber)
{
    // Calculate the hash value for the courseNumber
    unsigned int h = hash(courseNumber);

    // Retrieve the node in the hash table corresponding to the calculated hash value
    Node *currentNode = &nodes[h];

    // Traverse the linked list to find the course with the matching courseNumber
    while (currentNode != nullptr)
    {
        // Check if the current node has the matching courseNumber
        if (currentNode->course.courseNumber == courseNumber)
        {
            // If found, return the course
            return currentNode->course;
        }

        // Move to the next node in the linked list
        currentNode = currentNode->next;
    }

    Course course; // Create an empty Course object
    // If no matching course was found, return an empty Course
    return course;
}

/**
 * Custom comparison function for sorting courses based on their prerequisites.
 * Courses are sorted lexicographically by their prerequisites, and if the prerequisites
 * are the same, courses are sorted by their course numbers.
 *
 * @param a The first Course object to compare.
 * @param b The second Course object to compare.
 * @return True if 'a' should be sorted before 'b', otherwise false.
 */
bool compareCourses(const Course &a, const Course &b)
{
    // Sort prerequisites lexicographically
    vector<string> aPrereqs = a.prerequisites;
    vector<string> bPrereqs = b.prerequisites;
    sort(aPrereqs.begin(), aPrereqs.end());
    sort(bPrereqs.begin(), bPrereqs.end());

    // Compare lexicographically sorted prerequisites
    if (aPrereqs != bPrereqs)
    {
        return aPrereqs < bPrereqs;
    }

    return false; // If prerequisites are the same, 'a' cannot be taken before 'b'
}

/**
 * Print a list of courses in a sorted order, considering course prerequisites.
 *
 * @param table The HashTable containing the courses to be printed.
 */
void PrintCourseList(const unique_ptr<HashTable> &table)
{
    vector<pair<string, Course>> courses = table->GetCourseList();

    // Sort the courses based on custom comparison function
    sort(courses.begin(), courses.end(), [](const pair<string, Course> &a, const pair<string, Course> &b)
         {
        // Remove the last two characters from courseNumber and compare
        string aCourseNumber = a.second.courseNumber.substr(0, a.second.courseNumber.size() - 2);
        string bCourseNumber = b.second.courseNumber.substr(0, b.second.courseNumber.size() - 2);

        // Compare the modified courseNumber first
        if (aCourseNumber != bCourseNumber) {
            return aCourseNumber < bCourseNumber;
        }

        // Use the custom comparison function for courses with the same course number
        return compareCourses(a.second, b.second); });

    // Print the sorted course list
    cout << "Here is a sample schedule: \n"
         << endl;
    for (const auto &coursePair : courses)
    {
        const Course &course = coursePair.second;
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
}

/**
 * Print information about a course, including its course number, name, and prerequisites.
 *
 * @param course The Course object to be printed.
 */
void printCourseInfo(const Course &course)
{
    // Print the course number and name
    cout << course.courseNumber << ", " << course.courseName << endl;

    // Check if the course has prerequisites
    if (!course.prerequisites.empty())
    {
        // Print the prerequisites if they exist
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i)
        {
            cout << course.prerequisites[i];

            // Add a comma and space if there are more prerequisites to display
            if (i < course.prerequisites.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

/**
 * Split a string into tokens using a specified delimiter and store them in a vector.
 *
 * @param s         The string to be split.
 * @param delimiter The character used as a delimiter to split the string.
 * @return A vector containing the split tokens.
 */
vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    stringstream ss(s);
    string token;

    // Split the string using the specified delimiter and store tokens in the vector
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * Load course data from a data source into a container.
 *
 * @param dataSource The source of course data (e.g., a file, database, etc.).
 * @param hashTable  The hash table to store the courses.
 */
void loadCourses(string dataSource, HashTable *hashTable)
{
    cout << "Loading course data from " << dataSource << endl;

    ifstream file(dataSource);

    if (!file.is_open())
    {
        cerr << "Failed to open " << dataSource << endl;
        return;
    }

    string line;
    vector<string> header;

    while (getline(file, line))
    {
        vector<string> parts = split(line, ','); // Split the line into parts using a comma delimiter
        if (parts.size() >= 2)
        {
            Course course;
            course.courseNumber = parts[0];
            course.courseName = parts[1];

            if (parts.size() > 2)
            {
                for (size_t i = 2; i < parts.size(); i++)
                {
                    course.prerequisites.push_back(parts[i]);
                }
            }

            // Insert the course into the hash table
            hashTable->Insert(course);
        }
    }

    file.close();
    cout << "Data structure loaded." << endl;
}

int main(int argc, char *argv[])
{
    int tableSize = DEFAULT_SIZE; // Default table size

    if (argc > 1)
    {
        // Check if the user has provided a table size as a command-line argument
        tableSize = std::stoi(argv[1]);
    }

    string dataSource = "courses.dat"; // Default data source

    // Define a unique_ptr for HashTable with the specified size
    unique_ptr<HashTable> courseTable = make_unique<HashTable>(tableSize);

    int choice = 0;
    bool askedOnce = false; // To keep track of whether the question has been asked

    cout << "Welcome to the course planner." << endl;

    while (choice != 9)
    {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "\nWhat would you like to do? ";

        // Check if the input is a valid integer
        if (!(cin >> choice))
        {
            // Input is not a valid integer
            cout << "Invalid input. Please enter a valid integer option." << endl;
            cin.clear();                                         // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            // Load course data into the data structure from a data source
            if (!askedOnce)
            {
                // Ask the user if they want to load from the default source or input another one
                char loadChoice;
                cout << "Do you want to load data from the default source (courses.dat)? (Y/N): ";
                cin >> loadChoice;
                askedOnce = true;
                if (toupper(loadChoice) == 'Y')
                {
                    loadCourses(dataSource, courseTable.get());
                    break;
                }
            }
            cout << "Enter the path to the course data file: ";
            cin >> dataSource;
            if (!ifstream(dataSource))
            {
                cerr << "The specified file does not exist. Please check the file path." << endl;
                continue;
            }
            loadCourses(dataSource, courseTable.get());
            break;
        }
        case 2:
        {
            // Print the list of courses in alphanumeric order
            PrintCourseList(courseTable);
            break;
        }
        case 3:
        {
            // Print information for a specific course
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            for (char &c : courseNumber)
            {
                c = toupper(c);
            }
            Course course = courseTable->Search(courseNumber);
            if (course.courseNumber.empty())
            {
                cout << "Course not found." << endl;
                break;
            }
            printCourseInfo(course);
            break;
        }
        case 9:
        {
            // Exit the program
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        default:
        {
            cout << choice << " is not a valid option." << endl;
            break;
        }
        }
    }

    // No need to manually delete courseTable; it will be automatically released when it goes out of scope.
    return 0;
}
