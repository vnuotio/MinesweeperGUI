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
        vector<string> line_data = split_ignoring_quoted_delim(line, ';');

        // Rivin datan tarkastelu
        if (line_data.size() != 4)
        {
            goto ERROR;
        }

        for (string s : line_data)
        {
            if (s.empty() or all_of(s.begin(), s.end(), ::isspace))
            {
                goto ERROR;
            }
        }

        if (not (line_data.at(3) == "full"
                 or all_of(line_data.at(3).begin(), line_data.at(3).end(), ::isdigit)))
        {
            goto ERROR;
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

    ERROR:
        cout << "Error: empty field" << endl;
        data_file.close();
        return false;
}

// Vertaa kahta kurssia niiden kurssinimen aakkosjärjestyksen perusteella.
// Käytetään sort-funktion parametrina.
bool compare_by_name(const Course& a, const Course& b)
{
    return a.name < b.name;
}

// Vertaa kahta kurssia niiden sijainnin aakkosjärjestyksen perusteella.
// Käytetään sort-funktion parametrina.
bool compare_by_location(const Course& a, const Course& b)
{
    return a.location < b.location;
}

// Vertaa kahta kurssia, ensin niiden sijainnin ja tämän jälkeen niiden
// nimen aakkosjärjestyksien perusteella. Käytetään sort-funktion parametrina.
bool compare_by_location_and_name(const Course& a, const Course& b)
{
    if (compare_by_location(a, b)) return true;
    if (compare_by_location(b, a)) return false;

    if (compare_by_name(a, b)) return true;
    if (compare_by_name(b, a)) return false;

    return false;
}

// Palauttaa kaikki kurssit annetulta paikkakunnalta vektorina. Mikäli paikkakuntaa ei ole,
// palauttaa tyhjän vektorin.
vector<Course> find_by_location(const vector<Course>& courses, const string& location)
{
    vector<Course> result;
    for (const Course& c : courses)
    {
        if (c.location == location)
        {
            result.push_back(c);
        }
    }
    return result;
}

// Laskee tietyn teeman(jonka kurssit esitetty vektorina) ilmoittautumisen
// yhteismäärän.
int theme_enrollments(const vector<Course>& courses)
{
    int result = 0;
    for (const Course& c : courses)
    {
        result += c.enrollments;
    }
    return result;
}

void read_input(map<string, vector<Course>>& course_map)
{
    string input = "";
    bool exit = false;
    while (not exit)
    {
        cout << "> ";
        getline(cin, input);

        vector<string> input_split = split_ignoring_quoted_delim(input, ' ');

        string cmd = input_split.front();

        if (cmd == "quit")
        {
            return;
        }
        // Kaikki teemat aakkosjärjestyksessä.
        else if (cmd == "themes")
        {
            for (const auto &pair : course_map)
            {
                cout << pair.first << endl;
            }
        }
        // Kaikki kurssit paikkakunnalla.
        else if (cmd == "courses")
        {
            // TODO
        }
        // Kaikki kurssit, jotka eivät ole täynnä.
        else if (cmd == "available")
        {
            // TODO
        }
        // Kaikki tietyn teeman kurssit
        else if (cmd == "courses_in_theme")
        {
            // TODO
        }
        // Kaikki kurssit tietyllä paikkakunnalla.
        else if (cmd == "courses_in_location")
        {
            // TODO
        }
        // Suosituin teema
        else if (cmd == "favorite_theme")
        {
            // TODO
        }
        // Peruu annetun kurssin kaikilta paikkakunnilta
        else if (cmd == "cancel")
        {
            // TODO
        }
        else
        {
            cout << "Error: Unknown command: " << cmd << endl;
        }
    }
}

int main()
{
    map<string, vector<Course>> course_map;

    if (not read_file(course_map))
    {
        return EXIT_FAILURE;
    }

    read_input(course_map);
    return EXIT_SUCCESS;
}

