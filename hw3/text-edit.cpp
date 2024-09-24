#include "text-edit.h"

int main ()
// text editer within the command line
// should i use a vector and a trys and throws and excpetions?
{
    vector<string> *buffer = new vector<string>;

    int line = 1;
    int begin = 0;
    int end = 0;
    char command = '\0';
    string filename = "";
    string feed = "";
    char temp = '\0';
    bool change = false;
    bool staychanged = false;

    cout << "Welcome to Notepad--!" << endl << "Enter 'H' for help and 'Q' to quit." << endl << endl;

    cout << "Please enter a file to edit: ";
    cin >> filename;

    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout << "Exception: No such file exists" << endl << "Handled: Creating new file..." << endl;
        ofstream new_file;
        new_file.open(filename);
        new_file.close();
    }
    else
    {
        file.close();
        read_file(filename, buffer);
    }


    while(command != 'Q')
    // runs the editer until Q (quit input is given)
    {
        cout << filename << ": " << line << "> ";
        cin >> command;

        temp = getchar();

        if (!isspace(temp))
            command = '\0';

        switch (command)
        {
            case 'q':
                command = 'Q';
            case 'Q':
                if (staychanged)
                { 
                    cout << "Would you like to save the file? (Y/n) ";
                    cin >> temp;
                }

                if (temp != 'Y')
                    break;

            case 'w':
            case 'W':
                if (temp != '\n')
                    getline(cin, filename);

                write(filename, buffer);
                break;

            case 'j':
            case 'J':
                cin >> line;
                line = jump(line, buffer);
                break;

            case 'i':
            case 'I':
                if (temp != '\n')
                    getline(cin, feed);
                else
                    feed = "\n";

                change = insert_at(line, feed, buffer);
                if (!staychanged && change)
                    staychanged = change;
                break;

            case 'a':
            case 'A':
                if (temp != '\n')
                    getline(cin, feed);
                else
                    feed = "\n";

                change = insert_after(line, feed, buffer);
                if (!staychanged && change)
                    staychanged = change;
                break;

            case 'l':
            case 'L':
                if (temp == '\n')
                {
                    list_buffer(buffer);
                    break;
                }
                
                cin >> begin;
                temp = getchar();

                if (temp == '\n')
                {
                    list_buffer(buffer, begin, begin);
                }
                else
                {
                    cin >> end;  
                    list_buffer(buffer, begin, end);
                }
                break;

            case 'd':
            case 'D':
                if (temp == '\n')
                {
                    change = remove(buffer, line, line);
                    if (!staychanged && change)
                        staychanged = change;
                    break;
                }
                
                cin >> begin;
                temp = getchar();

                if (temp == '\n')
                {
                    change = remove(buffer, begin, begin);
                }
                else
                {
                    cin >> end;  
                    change = remove(buffer, begin, end);
                }
                if (!staychanged && change)
                    staychanged = change;
                break;

            case 'h':
            case 'H':
                help();
                break;

            default:
                cout << "Invalid Input" << endl;
                cout << "Enter H for Help" << endl << endl;

        }
    
    }

    delete buffer;


    return 0;
}