#include <iostream>
#include "EVRP.hpp"
#include "stats.hpp"
#include "HMAGS.hpp"
#include <fstream>
using namespace std;

void start_run(int r)
{

    srand(19520166 + r); //random seed
    init_evals();
    init_current_best();
    cout << "Run: " << r << " with random seed " << 19520166 + r << endl;
}

/*gets an observation of the run for your heuristic*/
void end_run(int r)
{
    get_mean(r - 1, get_current_best()); //from stats.h
    cout << "End of run " << r << " with best solution quality " << get_current_best() << " total evaluations: " << get_evals() << endl;
    cout << " " << endl;
}

/*sets the termination conidition for your heuristic*/
bool termination_condition(void)
{

    bool flag;
    if (get_evals() >= TERMINATION)
        flag = true;
    else
        flag = false;

    return flag;
}
void save_solution(int run){
    ofstream outfile2;
    string file_name = "Data/file_" + to_string(run) +".txt";
    outfile2.open(file_name);
    outfile2 << best_sol->steps << "\n";
    for(int i = 0; i < best_sol->steps; i++) {
        outfile2 << node_list[best_sol->tour[i]].x  << " " << node_list[best_sol->tour[i]].y << " ";
    }
    outfile2.close();

    ofstream outfile;
    outfile.open("Data/location.txt");
    for(int i = 0; i < ACTUAL_PROBLEM_SIZE; i++) {
        if(i == 0) {
            outfile << "0 ";
        } else {
            if(i < problem_size) {
                outfile << "1 ";
            } else {
                outfile << "2 ";
            }
        }

        outfile << node_list[i].x  << " " << node_list[i].y << " ";
    }
    outfile.close();

}
/****************************************************************/
/*                Main Function                                 */
/****************************************************************/
int main(int argc, char *argv[])
{

    int run;
    /*Step 1*/
    problem_instance = argv[1];     //pass the .evrp filename as an argument
    read_problem(problem_instance); //Read EVRP from file from EVRP.h

    /*Step 2*/
    open_stats(); //open text files to store the best values from the 20 runs stats.h

    for (run = 3; run <= 3; run++)
    {
        /*Step 3*/
        start_run(run);

        //Initialize your heuristic here
        initialize_HMAGS();

        /*Step 4*/
        while (!termination_condition())
        {
            //Execute your heuristic
            run_HMAGS();  //heuristic.
        }
        save_solution(run);
        free_HMAGS();
        
        /*Step 5*/
        end_run(run); //store the best solution quality for each run
    }
    /*Step 6*/
    close_stats(); //close text files to calculate the mean result from the 20 runs stats.h

    //free memory

    return 0;
}
