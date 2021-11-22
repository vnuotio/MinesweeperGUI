//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

/*
COMP.CS.110 Ohjelmointi 2: Projekti Kurssikeskus
Tekijät:
Roope Mantere(50049244), roope.mantere@tuni.fi
Vertti Nuotio(H300132), vertti.nuotio@tuni.fi

Ohjelma pitää kirjaa kansalaisopiston kurssitarjonnasta ja
kurssien suoritus paikoista. Ohjelmassa on mahdollista perua kursseja,
etsimään kursseja teeman sekä sijainnin perusteella, katsomaan suosituimmat
kurssit sekä etsimään saatavilla olevat kurssit.
*/

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
        result.erase(result.end()--);
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

bool read_file(map<string, vector<Course>>& course_map, set<string>& course_names)
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
        // Väärä määrä kenttiä
        if (line_data.size() != 4)
        {
            goto ERROR;
        }

        // Tyhjä tai pelkistä välilyönneistä koostuva kenttä
        for (string s : line_data)
        {
            if (s.empty() or all_of(s.begin(), s.end(), ::isspace))
            {
                goto ERROR;
            }
        }

        // Osallistujamäärä väärin
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

        course_names.insert(name);

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
bool sort_by_name(const Course& a, const Course& b)
{
    return a.name <= b.name;
}

// Vertaa kahta kurssia niiden sijainnin aakkosjärjestyksen perusteella.
// Käytetään sort-funktion parametrina.
bool sort_by_location(const Course& a, const Course& b)
{
    return a.location <= b.location;
}

// Vertaa kahta kurssia, ensin niiden sijainnin ja tämän jälkeen niiden
// nimen aakkosjärjestyksien perusteella. Käytetään sort-funktion parametrina.
bool sort_by_location_and_name(const Course& a, const Course& b)
{
    if (sort_by_location(a, b)) return true;
    if (sort_by_location(b, a)) return false;

    if (sort_by_name(a, b)) return true;
    if (sort_by_name(b, a)) return false;

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

// Ohjelman varsinainen suoritus.
// Parametrit: kurssien map, kurssien nimien set.
void read_input(map<string, vector<Course>>& course_map, set<string>& course_names)
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
            // Virhe parametrien määrässä.
            if (input_split.size() != 3)
            {
                cout << "Error: error in command " << cmd << endl;
                continue;
            }
            const string location = input_split.at(1);
            const string theme = input_split.at(2);

            // Teemaa eli mapin avainta ei ole olemassa.
            if (course_map.find(theme) == course_map.end())
            {
                cout << "Error: unknown theme" << endl;
                continue;
            }

            // Etsii kaikki kurssit tältä paikkakunnalta.
            vector<Course> courses_vec = find_by_location(course_map.at(theme), location);

            // Yhtäkään ei löytynyt!
            if (courses_vec.size() == 0)
            {
                cout << "Error: unknown location" << endl;
                continue;
            }

            // Järjestää kurssit nimen mukaiseen aakkosjärjestykseen.
            sort(courses_vec.begin(), courses_vec.end(), sort_by_name);

            for (const Course& c : courses_vec)
            {
                // Tämä tarvitsee tehdä vain, koska Course-structiin piti tallentaa osallistujamäärä
                // lukuarvona, eikä sitä voinut tehdä stringinä!
                string enrollment = (c.enrollments == 50)? "full" : to_string(c.enrollments) + " enrollments";

                cout << c.name << " --- " << enrollment << endl;
            }
        }
        // Kaikki kurssit, jotka eivät ole täynnä.
        else if (cmd == "available")
        {
            for (auto& pair : course_map)
            {
                // Järjestää kurssit ensin paikkakunnan, sen jälkeen nimen mukaan
                // aakkosjärjestykseen.
                sort(pair.second.begin(), pair.second.end(), sort_by_location_and_name);

                for (const Course& c : pair.second)
                {
                    if (c.enrollments < 50)
                    {
                        cout << pair.first << " : " << c.location << " : " << c.name << endl;
                    }
                }
            }
        }
        // Kaikki tietyn teeman kurssit
        else if (cmd == "courses_in_theme")
        {
            // Virhe parametrien määrässä.
            if (input_split.size() != 2)
            {
                cout << "Error: error in command " << cmd << endl;
                continue;
            }
            const string theme = input_split.at(1);

            // Teemaa eli mapin avainta ei ole olemassa.
            if (course_map.find(theme) == course_map.end())
            {
                cout << "Error: unknown theme" << endl;
                continue;
            }

            // Järjestää kurssit paikkakunnan mukaan aakkosjärjestykseen.
            sort(course_map.at(theme).begin(), course_map.at(theme).end(), sort_by_location);

            for (const Course& c : course_map.at(theme))
            {
                cout << c.location << " : " << c.name << endl;
            }
        }
        // Kaikki kurssit tietyllä paikkakunnalla.
        else if (cmd == "courses_in_location")
        {
            // Virhe parametrien määrässä.
            if (input_split.size() != 2)
            {
                cout << "Error: error in command " << cmd << endl;
                continue;
            }
            const string location = input_split.at(1);
            vector<Course> location_courses;

            // Käy läpi jokaisen teeman, ja etsii sen vektorista ne kurssit, joiden sijainta on
            // tähän annettu paikkakunta. Lisää nämä kurssit location_courses-vektoriin.
            for (const auto& pair : course_map)
            {
                const vector<Course> temp_courses = find_by_location(pair.second, location);
                location_courses.insert(location_courses.end(), temp_courses.begin(), temp_courses.end());
            }

            if (location_courses.size() == 0)
            {
                cout << "Error: unknown location" << endl;
                continue;
            }

            // Järjestää kurssit aakkosjärjestykseseen nimen perusteella.
            sort(location_courses.begin(), location_courses.end(), sort_by_name);
            for (const Course& c : location_courses)
            {
                cout << c.name << endl;
            }
        }
        // Suosituin teema
        else if (cmd == "favorite_theme")
        {
            int highest_enrollments = 0;
            set<string> favorite_courses;

            for (const auto& pair : course_map)
            {
                int enrollments = theme_enrollments(pair.second);
                if (enrollments > highest_enrollments)
                {
                    highest_enrollments = enrollments;
                    favorite_courses.clear();
                    favorite_courses.insert(pair.first);
                }
                else if (enrollments == highest_enrollments)
                {
                    favorite_courses.insert(pair.first);
                }
            }

            if (highest_enrollments == 0)
            {
                cout << "No enrollments" << endl;
                continue;
            }

            cout << highest_enrollments << " enrollments in themes" << endl;
            for (const string& s : favorite_courses)
            {
                cout << "--- " << s << endl;
            }
        }
        // Peruu annetun kurssin kaikilta paikkakunnilta
        else if (cmd == "cancel")
        {

            // Virhe parametrien määrässä.
            if (input_split.size() != 2)
            {
                cout << "Error: error in command " << cmd << endl;
                continue;
            }
            const string course = input_split.at(1);

            if (course_names.find(course) == course_names.end())
            {
                cout << "Error: unknown course" << endl;
                continue;
            }

            // Etsii jokaisen teeman jokaisen kurssivektorin sisältä ne kurssit,
            // joiden nimi on sama kuin poistettava kurssityyppi, ja poistaa ne.
            for (auto& pair : course_map)
            {
                for (Course& c : pair.second)
                {
                    pair.second.erase(remove_if(pair.second.begin(), pair.second.end(),
                                                [&](const Course& c){return c.name == course;}),
                                      pair.second.end());
                }
            }

            course_names.erase(course_names.find(course));
            cout << course << " cancelled in all locations" << endl;
        }
        else
        {
            cout << "Error: Unknown command: " << cmd << endl;
        }
    }
}

int main()
{
    // map - teema, kurssit vektorissa
    map<string, vector<Course>> course_map;
    // kaikkien kurssien nimet
    set<string> course_names;

    if (not read_file(course_map, course_names))
    {
        return EXIT_FAILURE;
    }

    read_input(course_map, course_names);

    return EXIT_SUCCESS;
}

