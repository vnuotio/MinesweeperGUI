//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Course
{
    string name;
    string location;
    int enrollments;
};

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.
//
// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}

// Lisää kurssin sille suunnattuun vektoriin. Mikäli löytyy
// vanha kurssi, jolla on sama nimi ja sijainti, poistetaan se,
// jolloin uuden kurssin tiedot tulevat voimaan.
void add_to_courses(vector<Course>& courses, Course new_course)
{
    size_t t = 0;
    for (auto i = courses.begin(); i < courses.end(); i++)
    {
        Course c = courses.at(t);
        if (c.name == new_course.name and c.location == new_course.location)
        {
            courses.erase(i);
            break;
        }
        t++;
    }
    courses.push_back(new_course);
}

bool read_file(map<string, vector<Course>>& course_map)
{
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream data_file(file_name);
    if (not data_file)
    {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

    string line;
    while (getline(data_file, line))
    {
        bool line_read_success = true;

        vector<string> line_data = split_ignoring_quoted_delim(line, ';');

        // Rivin datan tarkastelu
        if (line_data.size() != 4)
        {
            line_read_success = false;
        }

        for (string s : line_data)
        {
            if (s.empty() or all_of(s.begin(), s.end(), ::isspace))
            {
                line_read_success = false;
                break;
            }
        }

        if (not (line_data.at(3) == "full"
                 or all_of(line_data.at(3).begin(), line_data.at(3).end(), ::isdigit)))
        {
            line_read_success = false;
        }

        // Jokin meni pieleen. Kaikilla on kuitenkin sama virheviesti, joten käytetään
        // tätä testiä.
        if (not line_read_success)
        {
            cout << "Error: empty field" << endl;
            data_file.close();
            return false;
        }

        // Uuden kurssin luominen ja sen asettaminen säiliöön.
        string theme = line_data.at(0);
        string name = line_data.at(1);
        string location = line_data.at(2);
        int enrollments = (line_data.at(3) == "full")? 50 : stoi(line_data.at(3));

        Course new_course {name, location, enrollments};

        if (course_map.find(theme) == course_map.end())
        {
            course_map.insert({theme, vector<Course> ({new_course})});
        }
        else
        {
            add_to_courses(course_map.at(theme), new_course);
        }
    }

    data_file.close();
    return true;
}

int main()
{
    map<string, vector<Course>> course_map;

    if (not read_file(course_map))
    {
        return EXIT_FAILURE;
    }

    cout << "succ" << endl;
    return EXIT_SUCCESS;
}

