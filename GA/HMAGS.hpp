#ifndef algo_h
#define algo_h


#include <algorithm>
#include "individual.hpp"

const int NUM_OF_INDVS = 200;

struct HMAGS {
  
    /* The population */
    Individual pop[3 * NUM_OF_INDVS];

    /* Ranking for each indv */
    double rank[3 * NUM_OF_INDVS];

    /* initial function generate new population */
    void init();

    /* compute rank for pop */
    void compute_rank(int n);

    /* choose next indv with probability(prob) using binary search */
    int choose_by_rank(double prob);
  
    /* repopulation */
    void Repopulation();

    /* crossover function, return two new indvs */
    void distribute_crossover(Individual parent_1, 
                              Individual parent_2, 
                              int idx);
  
    /* weheel selection method, using by ranking */
    void Selection();
  
    /* evolution */
    void Evolution();

} ;

extern HMAGS hmags;

extern void initialize_HMAGS();

extern void free_HMAGS();

/*implement your heuristic in this function*/
extern void run_HMAGS();

// Other algorithms




#endif