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
  int i;
  if (temp[64] <= 'z' && temp[64] >= 'a') {
    perror("name is too long");
    exit(EXIT_FAILURE);
  }
  for (i = 0; /*temp[i] != ':'*/ isalpha(temp[i]) != 0 || temp[i] == ' '; i++) {
    state.name[i] = temp[i];
    if (isalpha(temp[i]) == 0 && temp[i] != ':' && temp[i] != ' ') {
      perror("invalid name");
      exit(EXIT_FAILURE);
    }
  }  //put the name of the state into name[]
  if (temp[i] != ':') {
    perror("you should use 1: ");
    exit(EXIT_FAILURE);
  }
  state.name[i] = '\0';
  char pop[64] = {0};  //read population in char format
  i++;
  for (int j = 0; /* temp[i] != ':'*/ temp[i] >= '0' && temp[i] <= '9'; j++, i++) {
    pop[j] = temp[i];
  }
  if (temp[i] != ':') {
    perror("you should use 2: to seperate");
    exit(EXIT_FAILURE);
  }

  state.population = atoi(pop);

  char elec[64] = {0};
  i++;
  if (!(temp[i] >= '0' && temp[i] <= '9')) {
    perror("you should have electoralvotes");
    exit(EXIT_FAILURE);
  }
  for (int j = 0; temp[i] != '\0'; j++, i++) {
    elec[j] = temp[i];
  }
  //  printf("State is ==>%s,  Population is ==> %lu\n ", state.name, state.population);
  state.electoralVotes = atoi(elec);
  return state;

  //STEP 1: write me
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  int total = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > (stateData[i].population / 2)) {
      //     printf("statename=%s", stateData[i].name);
      total += stateData[i].electoralVotes;
    }
  }
  //STEP 2: write me
  return total;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  double percent;

  for (size_t i = 0; i < nStates; i++) {
    if ((0.506 > (percent = ((double)voteCounts[i] / (double)stateData[i].population)) &&
         ((double)voteCounts[i] / (double)stateData[i].population) > 0.494)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             (double)voteCounts[i] / (double)stateData[i].population * 100);
    }
  }
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  double max = 0;
  int j = 0;
  double percent = 0;
  for (size_t i = 0; i < nStates; i++) {
    percent = ((double)voteCounts[i] / (double)stateData[i].population);
    if (max < percent) {
      max = percent;
      j = i;
      //      printf("Candidate A won %s with %.2f%% of the vote\n", stateData[j].name, percent * 100);
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[j].name, max * 100);

  //STEP 4: write me
}
