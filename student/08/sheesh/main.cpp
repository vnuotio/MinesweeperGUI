//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------
/*
COMP.CS.110 Ohjelmointi 2: Projekti Kurssikeskus
Tekijät:
Roope Mantere(50049244), roope.mantere@tuni.fi
Vertti Nuotio(H), vertti.nuotio@tuni.fi
*/

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>

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
    std::vector<std::string> result = { "" };
    bool inside_quotation = false;
    for (char current_char : str)
    {
        if (current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if (current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if (result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;

}

bool course_in_set(const set<Course>& course_set, const Course& course)
{
    for (Course c : course_set)
    {
        if (c.enrollments == course.enrollments and c.location == course.location and c.name == course.name)
        {
            return true;
        }
    }
    return false;
}

/// <summary>
/// Lukee käyttäjän syötteestä tiedoston nimen ja yrittää avata sen.
/// Tutkii, ovatko jokaisen rivin kentät kunnossa.
/// Muokkaa
/// <param name='course_map'>
/// Viite tietorakenteeseen, johon informaatio kursseista säilötään.
/// </param>
/// </summary>
/// <returns>
/// true, mikäli tiedosto pystytään lukemaan ja kentät ovat kunnossa -
/// false, mikäli jokin menee pieleen
/// </returns>
bool read_file(map<string, set<Course>>& course_map)
{
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream input_file(file_name);
    if (not input_file)
    {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

    string line;
    while (getline(input_file, line))
    {
        vector<string> split_line = split_ignoring_quoted_delim(line, ';');

        // Kenttiä on virheellinen määrä
        if (split_line.size() != 4)
        {
            cout << "Input file: " << file_name << endl;
            cout << "Error: empty field" << endl;
            return false;
        }

        for (string s : split_line)
        {
            // Tyhjien / pelkkää välilyöntiä olevien kenttien tutkiminen
            if (s.size() == 0 or all_of(s.begin(), s.end(), ::isspace))
            {
                cout << "Input file: " << file_name << endl;
                cout << "Error: empty field" << endl;
                return false;
            }
        }

        // Viimeisen kentän eli osallistujamäärän tarkastelu
        string num_field = split_line.at(3);
        if (num_field != "full" and not all_of(num_field.begin(), num_field.end(), ::isdigit))
        {
            cout << "Input file: " << file_name << endl;
            cout << "Error: empty field" << endl;
            return false;
        }

        string course_theme = split_line.at(0);
        string course_name = split_line.at(1);
        string course_location = split_line.at(2);
        int course_enrollments = (num_field == "full") ? 50 : stoi(num_field);

        Course new_course {course_name, course_location, course_enrollments};

        if (course_map.find(course_theme) == course_map.end())
        {
            course_map.insert({ course_theme, set<Course> ({new_course})});
        }
        else
        {
            set<Course> course_set = course_map.at(course_theme);
            auto set_iter = course_set.find(new_course);

            if (set_iter != course_set.end())
            {
                course_set.erase(set_iter);
            }

            course_set.insert(new_course);
        }

    }
    cout << "Succ!" << endl;
    return true;
}

int main()
{
    map<string, set<Course>> course_map;

    if (not read_file(course_map))
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

