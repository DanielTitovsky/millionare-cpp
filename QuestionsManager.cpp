#include "QuestionsManager.h"

#include <iostream>
#include <fstream>

using namespace std;

Value QuestionsManager::ReadFile() 
{
    Value root;
    Reader reader;

    ifstream readFile(QuestionsFilePath, ifstream::binary);
    bool parsingSuccessful = reader.parse(readFile, root, false);
    if (!parsingSuccessful)
    {
        cout << reader.getFormattedErrorMessages() << "\n";
    }

    return root;
}

Value QuestionsManager::GetQuestions()
{
    Value fileData = ReadFile();
    return fileData;
}
