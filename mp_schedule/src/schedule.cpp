/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
#include <climits>
using namespace std;
/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    V2D r_value;
    ifstream input_file(filename);
    string x;
    while(getline(input_file,x)){
        vector<string> line;
        int hey = split_string(x,',',line);
        for(string &x_:line){
            x_ = trim(x_);
        }
        r_value.push_back(line);
    }
    return r_value;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    V2D some_vector;
    //.size() refers to height of array (number of rows)
    //.[].size() refers to the number of elements in a row (number of columns in that row)
    //cv[x][y] x refers to the row number and y refers to the column number
    for(unsigned long i = 0; i < cv.size(); i++){
        bool exists = false;
        string course_name = cv[i][0];
        vector<string> line;
        vector<string> potential_names;
        line.push_back(course_name);
        for(unsigned long x = 0; x < student.size(); x++){
            for(unsigned long y = 0; y < student[x].size(); y++){
                if (course_name == student[x][y])
                    {
                        string student_name = student[x][0];
                        bool exists_ = false;
                        for(unsigned long j = 0; j < cv[i].size(); j++){
                            if (cv[i][j] == student_name) {exists_ = true;}
                        }
                        if (exists_ == true){
                            exists = true;
                            potential_names.push_back(student_name);
                        }
                    }
            }
        }
        for(unsigned long m = 0; m < cv[i].size(); m++){
            for(unsigned long n = 0; n < potential_names.size(); n++){
                if (cv[i][m] == potential_names[n]){
                    line.push_back(cv[i][m]);
                }
            }
        }
        if (exists == true){
            some_vector.push_back(line);
        }
    }
    return some_vector;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
vector<vector<string>> graph = make_graph(courses);
int number_of_time_slots = timeslots.size();
int min_colors = INT_MAX;
V2D best_work;
vector<string> hey;
hey.push_back("-1");
best_work.push_back(hey);
for (unsigned long start_node = 1; start_node <= courses.size(); start_node++){
    V2D work = greedy_algorithm(graph, timeslots, courses, start_node);
    int num_colors = work.size();
    if (num_colors < min_colors && work[0][0] != "-1"){
        min_colors = num_colors;
        best_work = work;
        break;
    }
}
return best_work;
}



vector<vector<string>> make_graph(V2D courses){
    int n = courses.size()+1;
    vector<vector<string>> graph;
    graph.resize(n);
    for (int i = 0; i < n; i++){
        graph[i].resize(n);
    }
    graph[0][0] = "origin";
    for (int i = 1; i < n; i++){
        graph[i][0] = courses[i-1][0];
        graph[0][i] = courses[i-1][0];
    }
    for (int i = 1; i < n; i++){
        for (int j = 1; j < n; j++){
            graph[i][j] = "0";
        }
    }
    for (int i = 0; i < n - 1; i++){
        for (unsigned long j = 1; j < courses[i].size(); j++){
            for (int x = 0; x < n - 1; x++){
                for (unsigned long y = 1; y < courses[x].size(); y++){
                    if (courses[x][y] == courses[i][j]){
                        graph[x+1][i+1] = "1";
                        graph[i+1][x+1] = "1";
                    }
                }
            }
        }
    }
    for (int i = 1; i < n; i++){
        graph[i][i] = "0";
    }
    return graph;
    
}

V2D greedy_algorithm(vector<vector<string>> graph, vector<string> timeslots, V2D courses, unsigned long start_node){
int nocs = 1;
int nots = timeslots.size();
V2D work;
vector<int> color;
color.resize(courses.size());
color[start_node-1] = 0;
vector<bool> used;
used.resize(courses.size());
for (unsigned long i = 0; i < color.size(); i++){
    if (i != start_node-1){
    color[i] = -1;
    }
}
for (unsigned long i = 1; i < courses.size(); i++){
    unsigned long node = (start_node-1 + i) % courses.size();
    for (unsigned long j = 0; j < courses.size(); j++){
        if (graph[node+1][j+1] == "1"){
            if (color[j] != -1){
                used[color[j]] = true;
            }
        }
    }

    unsigned long uc;
    for (uc = 0; uc < courses.size(); uc++){
        if(!used[uc]){
            break;
        }
    }
    color[node] = uc;
    for (unsigned long j = 0; j < courses.size(); j++){
        if (graph[node+1][j+1] == "1"){
            if(color[j] != -1){
                used[color[j]] = false;
            }
        }
    }
}
for(unsigned long i = 0; i < color.size(); i++){
    if (color[i] > nocs){
        nocs = color[i];
    }
}

if (nocs + 1 > nots){
    V2D work_;
    vector<string> hey;
    hey.push_back("-1");
    work_.push_back(hey);
    return work_;
}

for(unsigned long i = 0; i < timeslots.size(); i++){
    vector<string> push;
    push.push_back(timeslots[i]);
    for (unsigned long j = 0; j < color.size(); j++){
        int num = i;
        if (color[j] == num){
            push.push_back(courses[j][0]);
        }
    }
    work.push_back(push);
}
return work;
}