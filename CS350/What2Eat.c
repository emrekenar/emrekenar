#include <stdio.h>
#include <stdbool.h>

// Author:      Emre Kenar    github.com/emrekenar
// Program:     What to Eat
// Description: A text-based program that helps N people decide what to eat
// Note:        For simplicity, only main function is used
// MODULE_LICENSE("GPL");

int main() {
  int num_ppl = 0;
  char foods[5][9] = {"Kebab", "Burger", "Pasta", "Lahmacun", "Salad"};
  bool chosen[5];
  int scores[5];
  for (int i = 0; i < 5; ++i)
    scores[i] = 0;

  printf("How many people are eating? ");
  scanf("%d", &num_ppl);

  // calculate the scores of the first round
  for (int i = 0; i < num_ppl; ++i) {
     for (int j = 0; j < 5; ++j) {
       printf("%s [%d] ", foods[j], j + 1);
       chosen[j] = false;
     }
     printf("\n");

     for (int j = 0; j < 5; ++j) {
       int choice = -1;
       while (choice < 0 || choice >= 5 || chosen[choice]) {
         printf("What is %d. person's %d. choice? ", i + 1, j + 1);
         scanf("%d", &choice);
         --choice;
       }
       scores[choice] += 5 - j;
       chosen[choice] = true;
     }
  }

  // determine if there is a second round
  int threshold = num_ppl * 5 / 2;
  bool passed[5];
  int num_psd = 0;
  for (int i = 0; i < 5; ++i) {
    if (scores[i] > threshold) {
      passed[i] = true;
      printf("%s goes to the second round with %d points\n",
             foods[i], scores[i]);
      ++num_psd;
    } else {
      passed[i] = false;
    }
    scores[i] = 0;
  }
  if (!num_psd) {
    printf("You are eating at home/dorm today!\n");
    return 0;
  }

  // calculate the scores of the second round
  for (int i = 0; i < num_ppl; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (!passed[j]) continue;
      printf("%s [%d] ", foods[j], j+1);
      chosen[j] = false;
    }
    printf("\n");

    for (int j = 0; j < num_psd; ++j) {
      int choice = -1;
      while (choice < 0 || choice >= 5 ||
             !passed[choice] || chosen[choice]) {
        printf("What is %d. person's %d. choice? ", i + 1, j + 1);
        scanf("%d", &choice);
        --choice;
      }
      scores[choice] += num_psd - j;
      chosen[choice] = true;
    }
  }

  // print the results
  for (int i = 0; i < 5; ++i) {
    if (!passed[i]) continue;
    int max_index = 0;
    for (int j = 0; j < 5; ++j) {
      if (!passed[j]) continue;
      if (scores[j] > scores[max_index]) max_index = j;
    }
    passed[max_index] = false;
    printf("%s: %d points\n", foods[i], scores[i]);
  }

  return 0;
}





