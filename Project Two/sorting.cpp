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
    sort(bPrereqs begin(), bPrereqs.end());

    // Compare lexicographically sorted prerequisites
    if (aPrereqs != bPrereqs)
    {
        return aPrereqs < bPrereqs;
    }

    return false; // If prerequisites are the same, 'a' cannot be taken before 'b'
}

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
        if (aCourseNumber != bCourseNumber)
        {
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

int main(int argc, char *argv[])
{

    // Assuming we've already loaded the course data into the 'courseTable' object

    // Call the function to print the list of Computer Science courses in alphanumeric order
    PrintCourseList(courseTable);

    return 0;
}
