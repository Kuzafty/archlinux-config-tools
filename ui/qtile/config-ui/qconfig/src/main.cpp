// keyswritter main program
#include <iostream>
#include <string>

using namespace std;

/**
* This function prints all usage information
* for all commands avalible in this program.
* To work it needs the number of command ID.
* By default it returns itself with 0 argument.
*/
void usage (int commandId) {

    switch(commandId){

        // Help message for help command
        case 0:
            cout << "\nUsage: help"<< endl;
            cout << "\n\tQconfig is a program to modify the config file of qtile" << endl;
            cout << "\tbefore using it, you should have good qtile configuration files" << endl;
            cout << "\totherwise, you can run 'qconfig load default' to set it" << endl;
            cout << "\tif you are running this program from kuzaftys qtile graphical configurator" << endl;
            cout << "\tall config files were written to standard for this program, it must work\n\n" << endl;
            cout << "\thelp command can be used to show information about commands, like:\n" << endl;
            cout << "\tqconfig help [COMMAND]\n" << endl;
            cout << "\tWhen is typed, the program ignores the rest of the arguments.\n" << endl; 

            break;
        // Info message
        case 1:
            cout << "\nUsage: info" << endl;
            cout << "\n\tqconfig was written by kuzafty as program of high efficiency to be used" << endl;
            cout << "\twith the config-for-qtile tools, if it can call like that. Otherwise, qconfig" << endl;
            cout << "\tcan be used as user interface to change all configs defined in confing.py of qtile." << endl;
            cout << "\tThis program don't work with default config.py, so you must set a recommended config" << endl;
            cout << "\tin autoinstall it set the config by default, but you can reset it replacing" << endl;
            cout << "\tin your config folder with all files included in config-for-qtile repository\n" << endl;

            break;
        // load command help usage
        case 2:
            cout << "\nUsage: load\n" << endl;
            cout << "\tqconfig load [FOLDER|DEFAULT|RESTORE]\n" << endl;
            cout << "\tWrite a file to use as config file for qtile (Only for keys)" << endl;
            cout << "\tthe new keys config file will renamed to keys.py and place in qtile config folder." << endl;
            cout << "\tWrite default to reset keys.py file to recommended. It will be downloaded from kuzafys.com" << endl;
            cout << "\tyou can add other options for default:\n" << endl;
            cout << "\tkeyswritter load default [GIT|OFFLINE|MIRROR]\n" << endl;
            cout << "\tGit download a repository with all config files by default and install it." << endl;
            cout << "\tOffline will check if the files are in the load machine. You can check directories" << endl;
            cout << "\tused for backup in the repository of this program." << endl;
            cout << "\tMirror is the default that will download only keys.py from kuzaftys.com\n" << endl;
            cout << "\tWrite restore to replace all files when your config is break." << endl;
            cout << "\trestore has the same options that default, but it will affect all config.\n" << endl;

            break;
        default:
            usage(0);
            break;

    }

}

// Main function
int main (int argc, char **argv){

    // Available commands
    const string options[] = {"help", "info"};

    // Available help options
    const string help[] = {"load"};

    // Available load options
    const string load[] = {"file", "default", "restore"};

    // Number of options
    const int options_size = 2;

    // Number of help options
    const int help_size = 1;

    // Random number for dafault pointer in switch for option selected by user
    int option = 99;
    
    // Second arg
    int second = 99;

    // If user don't send arguments
    if(argc == 1){
        // Print usage info (Program info only)
        usage(1);
        // Stop program
        return 0;
    }

    // Get the identifier of the command requested
    // Match argument with all command available list.
    for(int i = 0; i < options_size; i++){
        
        // Match
        if(argv[1] == options[i]){

            // Assing number of tries (This is the identifier number)
            option = i;
            break;

        }
    }

    // Check command of first argument
    switch (option){

        // help command
        case 0:
            // Check if user send a second argument
            if(argc == 3){
                // Check second command
                for(int i = 0; i < help_size; i++){
                    // Match
                    if(argv[2] == help[i]){
                        second = i+2;
                    }
                }
            }
            // Call usage with second arg
            usage(second);
            break;
        // info command
        case 1:
            usage(1);
            break;
        // load command
        case 2:
            // Check for second arg
            if(argc >= 3){
                // Check second command
                for(int i = 0; i < load_size; i++){

                }
            }
            break;
        default:
            usage(option);
    
    }

    // End of the way
    return 0;

}