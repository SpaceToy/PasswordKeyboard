#include <iostream>
#include <string>
using namespace std;

#include<bits/unique_ptr.h>

#include<termios.h>
#include<unistd.h>

class virtualKeyboard {

protected:
    
    string key;

public:
    
    virtual void setUp()
    {
    }

    virtual void execute()
    {
    }

};


class virtualKeyboardLinux : public virtualKeyboard
{
private:
    char getch()
    {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);

    }

    void readInput()
    {
        key.clear();
        while(1)
        {
            // Get the character from internal implementation of getch()
            char ch = getch();

            // Dont append the character into the string if the characted is 'enter' key
            if(ch != '\n')
            {
                key.append(1, ch);
                // cout << key;
            }
            else
            {
                // Break out of  since now we need to print the string
                break;
            }
        }
    }

    void printOutput()
    {
        cout<<key<<endl;
    }

public:

    //virtual function to make sure derived class overrides it.
    void setUp()
    {
        // Register ctrl+q as interrupt call
        system("stty intr ^q");
    }
    void execute()
    {
        // Read the input from stdin
        readInput();
    
        // Print the output to stdout
        printOutput();          
    }
};
