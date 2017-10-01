#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct LinkedRecord {
  int year;
  int stops;
  struct LinkedRecord *next;
};

struct LinkedRecord *list_find(struct LinkedRecord *head, int year) {
  if( head->year == -2 ){ //not sure how to emulate "is None"
    head->year = year;
    head->stops = 0;
    struct LinkedRecord *newRecord = malloc(sizeof(struct LinkedRecord));
    newRecord->year = -2;
    head->next = newRecord;
    // printf("\n");
    return head;
  }
  if ( head->year == year){
    // printf("\n");
    return head;
  }
  // printf("Searching for %d, CY: %d, CS: %d\n", year, head->year, head->stops);
  return list_find( head->next, year);
}

int parse_line(char *line){
  char year_text[5];
  strncpy(year_text, line+6, 4);
  year_text[5] = '\0';   //found this on SO: https://stackoverflow.com/questions/16807004/how-to-get-a-part-of-a-char-array-in-c
  int year = strtol(year_text, NULL, 10);
  if(year < 1920 || year > 2020){
    return -1; //-1 represents bad year string
  }
  return year;
}

int print_list(struct LinkedRecord *head) {
  if(head->year == -2){ //not sure how to emulate "is None"
    return 0;
  }
  printf("%d had %d stops\n", head->year, head->stops);
  print_list(head->next);
  return 0;
}

void free_LL(struct LinkedRecord *head){ //adapted from SO (https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list)
  struct LinkedRecord *temp;             //because not part of the assignment
  while (head->year != -2){
    temp = head;
    head = head->next;
    free(temp);
  }
  free(head);
}

int main(int argc, char **argv){
  if(argc < 2){
    printf("Usage: %s <traffic data>\nExiting...\n", argv[0]);
    return 0;
  }
  char *fname = argv[1];
  struct LinkedRecord *out_list = malloc(sizeof(struct LinkedRecord));
  out_list->year = -2;
  FILE *f = fopen(fname, "r");

  //lines below w 'line' var adapted from SO: https://stackoverflow.com/questions/9206091/going-through-a-text-file-line-by-line-in-c
  char line[512];
  fgets( line, sizeof(line), f );
  while( fgets(line, sizeof(line), f) ){
    int year = parse_line(line);
    struct LinkedRecord *node = list_find(out_list, year);
    node->stops++;
  }
  fclose(f);
  print_list(out_list);
  free_LL(out_list);
  return 0;
}
