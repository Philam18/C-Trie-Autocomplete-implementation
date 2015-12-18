#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
////////////////////////////////////makeNode///////////////////////////////////////
// Creates a new node,
// sets all of the elements in the subArray "children" to NULL.
trie_node_t *makeNode(void){
  trie_node_t *node = NULL;
  node = (trie_node_t *)malloc(sizeof(trie_node_t));  //DynMemAlloc for the Trie ADT.
  if( node ){  //If memory was allocated successfully...
    int i;
    node->isWord = false;
    for(i = 0; i < ALPHABET_SIZE; i++){  //Set all of the children to NULL.
      node->children[i] = NULL;
    }
  }
  return node;
}
/////////////////////////////////////intialize//////////////////////////////////////
// Initiates a new ADT, with root being a new node and count being 0.
// Root is a buffer node;
// Count represents the level (height) of the tree.
void initialize(trie_t *pTrie)
{
  pTrie->root = makeNode();
  pTrie->count = 0;
}
///////////////////////////////////insert////////////////////////////////////////
// Inserts each letter of a word into a trie
// If the letter isnt contained in the trie, it creates a new node.
void insert(trie_t *pTrie, char key[]){
  int level;
  int length = strlen(key);
  int index;
  char x;
  trie_node_t *temp;  //New node temp to hold the ADT.
  pTrie->count++;  //Increase the count of the trie since a word is being added.
  temp = pTrie->root;  //Set the temporary node to the pTrie root, in order to not modify the pTrie.
  for( level = 0; level < length; level++ ){  //For every letter in the key...
    index = alphabetIndex(key[level]);  //Convert that letter to a number (index).
    x = key[level];  //Save the letter for later.
    if( !temp->children[index] ){  //If the character is a new letter...
        temp->children[index] = makeNode();  //Make a new node at index.
        temp->children[index]->letter = x;  //Set the node's letter to x.
    }
    temp = temp->children[index]; //Traverse to the next letter/index.
  }
  temp->isWord = true;  //Mark last node as word.
  /** The reason why marking the last node remains outside of the loop at the end, is
  *   because after inserting all the letters/nodes into their indexes, the last letter
  *   will always be garanteed to be a new leaf. even if you insert the same word twice.
  *   The last letter will always be a leaf node.
  **/
}
////////////////////////////////////traverse///////////////////////////////////////
// traverses a tree given a key
// the function will traverse to the end letter of the key, where it will
// then send a node to the autocomplete function and print out all the
// subtries of that node.
int traverse(trie_t *pTrie, char key[]){
  int level;
  int length = strlen(key);
  int index;
  trie_node_t *temp;
  temp = pTrie->root;  //once again, create a temporary node to hold the ADT Trie
  printf("TRAVERSING TRIE FOR %s\n",key);
  for( level = 0; level < length; level++ ){  //From 0 to the end of the key...
    index = alphabetIndex(key[level]);  //Take the letter at i and turn it into an index.
    if( !temp->children[index] ){  //If the child's index is NULL, then obviously the word is not found
      printf("WORD NOT FOUND!\n");
      return 0;  //Thus we may exit the function.
    }
    temp = temp->children[index];  //Keep moving deeper to the found node.
  }
  /**At this point, the "temp" node should be right at the end of the "key".
  *  If we imagine "key" as a prefix (for example "ab"), then every ending of
  *  the prefix "ab" should be a subtree of the node "temp"(abalone, aback, abacus...).
  *  Thus, it is safe to assume we can print the entire subtree of "temp" because we
  *  KNOW it suffixes the key ("ab"). Thus we send "temp" into autocomplete, as well as "key".
  */
  printf("---WORD FOUND: AUTCOMPLETE---\n");
  autocomplete(temp,key);
  printf("---END AUTOCOMPLETE---\n");
  return (0 != temp && temp->isWord);  //returns, if "temp" is not NULL and "temp" was a word
}
////////////////////////////////////autocomplete///////////////////////////////////////
// Takes a node, and prints out all the subtries of that node.
// Essentially, it works as an autocomplete function, given a string "word",
// it can print out all the words that have "word" as a prefix.
void autocomplete(trie_node_t *subTrie, char word[]){
  if (subTrie != NULL){ //Base case: the subTrie is NULL
    int i;
    //If subtrie is a word, print the word
    if (subTrie->isWord == true){
      printf("%s\n",word);
    }
    for (i = 0; i < ALPHABET_SIZE; i++){ //For every single index in the children[] array...
      //If the children[] array has any nodes that represents letters...
      if (subTrie->children[i] != NULL){  //If those nodes are not NULL...
        char *append;  //Create a new string.
        append = (char *)malloc(strlen(word)+1);  //DynMemAlloc for that char[] array pointer.
        strcpy(append,word);  //Take the current built string of letters, and set it equal to the ptr.
        append[strlen(word)] = subTrie->children[i]->letter;  //Append the letter at children[i] to the ptr.
        autocomplete(subTrie->children[i], append);  //Recursive Case: recurse the child at i, and the new ptr.
      }
    }
  }
}
////////////////////////////////////alphabetIndex///////////////////////////////////////
// Takes a char and returns an index of where it should go in an array.
// Accepts A-Z, a-z, ' (apostrophe), and terminal characters.
int alphabetIndex(char c){
  int value;
  if (c >= 65 && c <= 90){  //If the character is capital A-Z
    value = c - 65;
    return value;
  }
  else if (c >= 97 && c <= 122){  //If the character is lowercase a-z
    value = c - 97;
    return value + 26;
  }
  else if (c == 39){  //If the character is an apostrophe '
    return 52;
  }
  else{
    return 0;
  }
}
/////////////////////////////////////indexAlphabet//////////////////////////////////////
// takes an integer (index) and converts it into a character
// can accept values from 1-53, returning A-Z, a-z, or '
char indexAlphabet(int i){
  if (i >= 0 && i <= 25){  //If the character is capital A-Z
    char c = i + 65;
    return c;
  }
  if (i >= 26 && i <= 51){  //If the character is lowercase a-z
    char c = i + 71;
    return c;
  }
  if (i == 52){  //If the character is an apostrophe '
    char c = 39;
    return c;
  }
  return 0;
}


