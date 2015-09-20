#include "parser.h"
void parser::parseBST(BinarySearchTree<SequenceMap> & current_tree, string filename){
    openFile(filename);
    string first_line, line, text;
    int count = 0;
    SequenceMap temp;
    char next;
    //Reads through the first 10 lines
     
    for(int i = 0; i < 9; i++)
        getline(inStream, first_line);
     
    //Reads through each line and inserts key and sequence into tree
    while(getline(inStream, line)) {
    //Reads the rest of the text and insert into tree
        getline(inStream, text, '/');
        temp.setNames(text);
        while(inStream.peek() != '/' && inStream.peek() != EOF){
            getline(inStream, text, '/');
            temp.setKey(text);
            current_tree.insert(temp);
        }
        inStream.ignore(1);
    }  
    closeFile();
}
void parser::parseAVL(AvlTree<SequenceMap> & current_tree, string filename){
	openFile(filename);
    string first_line, line, text;
    int count = 0;
    SequenceMap temp;
    char next;
    //Reads through the first 10 lines
     
    for(int i = 0; i < 9; i++)
        getline(inStream, first_line);
     
    //Reads through each line and inserts key and sequence into tree
    while(getline(inStream, line)) {
    //Reads the rest of the text and insert into tree
        getline(inStream, text, '/');
        temp.setNames(text);
        while(inStream.peek() != '/' && inStream.peek() != EOF){
            getline(inStream, text, '/');
            temp.setKey(text);
            current_tree.insert(temp);
        }
        inStream.ignore(1);
    }  
    closeFile();
}
void parser::parseLazy(AvlLazy<SequenceMap> & current_tree, string filename){
	openFile(filename);
    string first_line, line, text;
    int count = 0;
    SequenceMap temp;
    char next;
    //Reads through the first 10 lines
     
    for(int i = 0; i < 9; i++)
        getline(inStream, first_line);
     
    //Reads through each line and inserts key and sequence into tree
    while(getline(inStream, line)) {
    //Reads the rest of the text and insert into tree
        getline(inStream, text, '/');
        temp.setNames(text);
        while(inStream.peek() != '/' && inStream.peek() != EOF){
            getline(inStream, text, '/');
            temp.setKey(text);
            current_tree.insert(temp);
        }
        inStream.ignore(1);
    }  
    closeFile();
}
void parser::sequenceContainBST(BinarySearchTree<SequenceMap> & current_tree, string filename){
    string text;
    SequenceMap sequences;
    openFile(filename);
    if(inStream.fail()){
        cout << "Error, input file cannot be opened." << endl;
        exit(1);
    }
    //Goes through file, grabs each sequence and checks to see if it is contained in the tree.
    while(getline(inStream, text)){
        sequences.setKey(text);
        current_tree.contains(sequences);
    }
    closeFile();
}
void parser::sequenceContainAVL(AvlTree<SequenceMap> & current_tree, string filename){
    string text;
    SequenceMap sequences;
    openFile(filename);
    if(inStream.fail()){
        cout << "Error, input file cannot be opened." << endl;
        exit(1);
    }
    //Goes through file, grabs each sequence and checks to see if it is contained in the tree.
    while(getline(inStream, text)){
        sequences.setKey(text);
        current_tree.contains(sequences);
    }
    closeFile();
}
void parser::sequenceContainLazy(AvlLazy<SequenceMap> & current_tree, string filename){
    string text;
    SequenceMap sequences;
    openFile(filename);
    if(inStream.fail()){
        cout << "Error, input file cannot be opened." << endl;
        exit(1);
    }
    //Goes through file, grabs each sequence and checks to see if it is contained in the tree.
    while(getline(inStream, text)){
        sequences.setKey(text);
        current_tree.contains(sequences);
    }
    closeFile();
}
void parser::removeSequenceBST(BinarySearchTree<SequenceMap> & current_tree, string filename){
    string text;
    SequenceMap sequences;
    openFile(filename);
    if(inStream.fail()){
        cout << "Error, input file cannot be opened" << endl;
        exit(1);
    }
    //Goes through file, removes each sequence if it is contained in the tree.
    while(getline(inStream, text)){
        sequences.setKey(text);
        current_tree.remove(sequences);
    }
    closeFile();
}
void parser::removeSequenceAVL(AvlTree<SequenceMap> & current_tree, string filename){
    string text;
    SequenceMap sequences;
    openFile(filename);
    if(inStream.fail()){
        cout << "Error, input file cannot be opened" << endl;
        exit(1);
    }
    //Goes through file, removes each sequence if it is contained in the tree.
    while(getline(inStream, text)){
        sequences.setKey(text);
        current_tree.remove(sequences);
    }
    closeFile();
}
void parser::removeSequenceLazy(AvlLazy<SequenceMap> & current_tree, string filename){
    string text;
    SequenceMap sequences;
    openFile(filename);
    if(inStream.fail()){
        cout << "Error, input file cannot be opened" << endl;
        exit(1);
    }
    //Goes through file, removes each sequence if it is contained in the tree.
    while(getline(inStream, text)){
        sequences.setKey(text);
        current_tree.remove(sequences);
    }
    closeFile();
}
void parser::openFile(string filename){
	inStream.open(filename);
	if(inStream.fail()){
		cout << "Error, input file cannot be opened." << endl;;
		exit(1);
	}
}
void parser::closeFile(){
	inStream.close();
}

