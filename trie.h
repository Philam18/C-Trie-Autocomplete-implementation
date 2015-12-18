#define ALPHABET_SIZE (54) //54 alphabets: 26 for A-Z, 26 for a-z, 1 for apostrophe, 1 for /0 and other
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////
// Boolean struct implementation
typedef int bool;
#define true 1
#define false 0
//////////////////////////////////////////////////////////////////////////////
// Trie node implementation
typedef struct trie_node trie_node_t;
struct trie_node
{
        char letter;  //The letter the node represents.
        bool isWord;  //If this node represents a word.
        trie_node_t *children[ALPHABET_SIZE];  //All the children of this node.
};
//////////////////////////////////////////////////////////////////////////////
// Trie ADT implementation
typedef struct trie trie_t;
struct trie
{
        trie_node_t *root;  //The head of the ADT, which is just a dummy node.
        int count;  //Represents how many words are in the node. (UNUSED, but nice to have)
};
//////////////////////////////////////////////////////////////////////////////
// Name: makeNode
// Use:
//      Instantiates a node and it's members.
//      The members include "letter" and "isWord".
//      (refer to >struct trie_node)
// Param:
//      -
// Return:
//      node - A node of type trie_node_t.
trie_node_t *makeNode(void);
//////////////////////////////////////////////////////////////////////////////
// Name: intialize
// Use:
//      Initializes a Trie ADT.
// Param:
//      pTrie - a Trie ADT initialized
// Return:
//      -
void initialize(trie_t *pTrie);
//////////////////////////////////////////////////////////////////////////////
// Name: insert
// Use:
//      Inserts a key(word) into the Trie.
// Param:
//      pTrie - The main Trie ADT
//      key - A word
// Return:
//      -
void insert(trie_t *pTrie, char key[]);
//////////////////////////////////////////////////////////////////////////////
// Name: traverse
// Use:
//      Given a key (assuming it is located IN the trie), the traverser will
//      locate the LAST letter of the key. At this point it will print out
//      all the subtries of this last letter.
// Param:
//      pTrie - The main Trie ADT
//      key - The word to be traversed
// Return:
//      -
int traverse(trie_t *pTrie, char key[]);
//////////////////////////////////////////////////////////////////////////////
// Name: autocomplete
// Use:
//      Prints out all the subnodes/subtries of a node.
// Param:
//      subTrie - The subTrie to be printed.
//      word - The built word that will be printed
// Return:
//      -
void autocomplete(trie_node_t *subTrie, char word[]);
//////////////////////////////////////////////////////////////////////////////
// Name: alphabetIndex
// Use:
//      Converts a char C to an index. This is useful for locating which index
//      to insert a node in WITHIN a node's children[] array.
//      (Think of it like an array of pointers, pointing to other arrays of pointers)
// Param:
//      c - The character to be converted
// Return:
//      value - The index the node will be inserted
int alphabetIndex(char c);
//////////////////////////////////////////////////////////////////////////////
// Name: indexAlphabet
// Use:
//      When a node is found within an array, the INDEX of the node in the array
//      represents what letter this node is. Thus this method converts an index
//      to letter/alphabet.
// Param:
//      i - The index
// Return:
//      c - The converted index to alphabet
char indexAlphabet(int i);
