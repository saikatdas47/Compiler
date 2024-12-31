#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string inputFile = "input.c";
    string outputFile = "output.txt";

    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open())
    {
        return 1;
    }

    string line;
    for (; getline(inFile, line);)
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == 'p' && line.substr(i, 6) == "printf")
            {
                i += 6; // printfe er f e achi..
                while (i < line.length() && line[i] != '(')
                    i++; // Find (
                         //    i++;

                string output = "";
                bool insideString = false;
                while (i < line.length() && line[i] != ')')
                {
                    if (line[i] == '"')
                    {
                        insideString = !insideString;
                    }
                    else if (insideString)
                    {
                        if (line[i] != '\\')
                        {
                            output += line[i];
                        }
                        if (line[i] == '\\')  ////    /n
                        {

                            output = output + '\n';
                            i++;
                            
                        }
                    }
                    i++;
                }
                outFile << output << endl;
                insideString = !insideString;
            }
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}
