#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
state_t parseLine(const char * line) {
  if (line == NULL) {
    perror("invalid information!!!");
    EXIT_FAILURE;
  }

  const char * temp = line;
  state_t state;
  int i = 0;
  state.name[0] = temp[0];
  for (i = 1; temp[i] != ':'; i++) {
    state.name[i] = temp[i];
  }  //put the name of the state into name[]
  /*  if (temp[i] != ':') {
    perror("you should use 1: to seperate");
    EXIT_FAILURE;
    }*/

  state.name[i] = '\0';
  char pop[64];  //read population in char format
  i++;
  for (int j = 0; temp[i] != ':'; j++, i++) {
    pop[j] = temp[i];
  }
  /* if (temp[i] != ':') {
    perror("you should use 2: to seperate");
    EXIT_FAILURE;
    }*/

  state.population = atoi(pop);

  char elec[64];
  i++;
  for (int j = 0; temp[i] != '\0'; j++, i++) {
    elec[j] = temp[i];
  }
  state.electoralVotes = atoi(elec);
  return state;

  //STEP 1: write me
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  double percent;
  uint64_t total = 0;
  for (size_t i = 0; i < nStates; i++) {
    if ((percent = (double)voteCounts[i] / (double)stateData[i].population) > 0.5) {
      total = total + stateData[i].electoralVotes;
    }
  }
  //STEP 2: write me
  return total;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
