/**
 TRIE AUTOCOMPLETE

 *_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_
*_*_*_*_*_*_TO COMPILE, ENTER:                   _*_*_*_*__*_*
_*_*_*_*_*_*  >   gcc -c trie.c                 *_*_*_*_*_*_*_*
*_*_*_*_*_*_  >   gcc -c complete.c             _*_*_*_*_*_*_*_*
_*_*_*_*_*_*  >   gcc -o test complete.o trie.o *_*_*_*_*_*_*_*
*_*_*_*_*_*_*                                    _*_*_*_*_*_*
 *_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*



**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#define WORD_SIZE 25 //Max length of a word in the dictionary; assumed to be 25
  int main(){
  trie_t trie;  //Instantiate new Trie ADT
  initialize(&trie);  //Initialize the Trie
  FILE *file = fopen("american-english-no-accents","r");  //Open the dictionary for reading only
  if (!file)  return 0;  //The file opened successfully
  char word[WORD_SIZE];  //Initiate a buffer "word"
  while (fscanf(file, "%s", word)!=EOF){  //Read words into variable "word"
    insert(&trie, word);  //insert words into trie
  }

  //Prepare Loop for user input
  char searchForWord[WORD_SIZE];
  printf("ENTER A WORD TO SEARCH FOR: (CTRL-D to end)\n");

  while (scanf("%s",searchForWord) != EOF){  //Checks CTRL-D
    int i;
    int isValid = 1;
    for (i = 0; i < strlen(searchForWord); i++){
    //loop through word and check validity
      char c = searchForWord[i];
      if (!isalpha(c)) {  //if found any characters non-alpha
        isValid = 0;  //invalid
       }
    }
    if (!isValid) printf("Invalid input! Letters only!\n");
    if (isValid) traverse(&trie,searchForWord);  //word is valid:traverse
    printf("ENTER A WORD TO SEARCH FOR: (CTRL-D to end)\n");
  }
  fclose(file); //close the file
  return 0;
}
