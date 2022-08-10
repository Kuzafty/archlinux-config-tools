// keyswritter main program
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <filesystem>

using namespace std;

namespace fs = filesystem;

/**
*
* Default path using
*
*/
#define QTILE_CONFIG_BACKUP     "/usr/share/arch-config-tools/backup/qtile"
#define QTILE_CONFIG_DEFAULT    "/usr/share/arch-config-tools/default/qtile"

/**
*
* Defs to understand better the code when usage is used
*
*/
#define USAGE_SELF 99
#define USAGE_HELP 0
#define USAGE_INFO 1
#define USAGE_LOAD 2
#define USAGE_SAVE 3


/**
* This function prints all usage information
* for all commands avalible in this program.
* To work it needs the number of command ID.
* By default it returns itself with 0 argument.
*/
void usage (int commandId) {

    switch(commandId){

        // Help message for help command
        case USAGE_HELP:
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
        case USAGE_INFO:
            cout << "\nUsage: info" << endl;
            cout << "\n\tqconfig was written by kuzafty as program of high efficiency to be used" << endl;
            cout << "\twith the archlinux-config-tools, if it can call like that. Otherwise, qconfig" << endl;
            cout << "\tcan be used as user interface to change all configs defined in confing.py of qtile." << endl;
            cout << "\tThis program don't work with default config.py, so you must set a recommended config" << endl;
            cout << "\tin autoinstall it set the config by default, but you can reset it replacing" << endl;
            cout << "\tin your config folder with all files included in archlinux-config-tools repository\n" << endl;

            break;
        // load command help usage
        case USAGE_LOAD:
            cout << "\nUsage: load\n" << endl;
            cout << "\tqconfig load [FOLDER|DEFAULT|RESTORE]\n" << endl;
            cout << "\tWrite a folder path to use as config for qtile." << endl;
            cout << "\tWrite default to reset config folder to recommended. It will be downloaded from kuzafys.com" << endl;
            cout << "\tyou can add other options for default:\n" << endl;
            cout << "\tqconfig load default [GIT|OFFLINE|MIRROR]\n" << endl;
            cout << "\tGit download a repository with all config files by default and install it." << endl;
            cout << "\tOffline will check if the files are in the local machine. You can check directories" << endl;
            cout << "\tused for backup in the repository of this program." << endl;
            cout << "\tMirror is the default that will download the config folder from kuzaftys.com\n" << endl;
            cout << "\tWrite restore to replace all files when your config is break." << endl;
            cout << "\trestore has the same options that default.\n" << endl;

            break;
        case USAGE_SAVE:
            cout << "\nUsage: save\n" << endl;
            cout << "\tqconfig save [PATH]\n" << endl;
            cout << "\tGive a path (Directory) as argument for save all configs, this folder can be used with load command." << endl;
            cout << "\tCheck: qconfig help save, for more information.\n" << endl;

            break;
        default:
            usage(USAGE_HELP);
            break;

    }

}

// Main function
int main (int argc, char **argv){

    const char home[] = "/home/"; 
    char *user = getlogin();
    const char path[] = "/.config/qtile";

    char QTILE_CONFIG[100];

    strcpy(QTILE_CONFIG, home);
    strcat(QTILE_CONFIG, user);
    strcat(QTILE_CONFIG, path);

    const auto copyOptions = fs::copy_options::recursive;

    // Available commands
    const string options[] = {"help", "info", "load", "save"};              // If you add a command remember update options_size

    // Available help options
    const string help[] = {"load", "save"};

    // Available load options
    const string load[] = {"folder", "default", "restore"};

    // Save command has not extra options

    // Number of options
    const int options_size = 4;

    // Number of help options
    const int help_size = 2;

    // Number of load options
    const int load_size = 3;

    // save command array don't exist

    // Default argument
    int option = USAGE_SELF;

    // Default second argument
    int second = USAGE_SELF;
    // If user don't send arguments
    if(argc == 1){
        // Print help
        usage(USAGE_HELP);
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
        case USAGE_HELP:
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
        case USAGE_INFO:
            usage(USAGE_INFO);
            break;
        // load command
        case USAGE_LOAD:
            // Check for second arg
            if(argc >= 3){
                // Check second command
                for(int i = 0; i < load_size; i++){

                }
            }else{
                // This command needs a second argument
                cout << "\rLoad command syntax is wrong." << endl;
                // Print load help
                usage(USAGE_LOAD);
            }
            break;
        case USAGE_SAVE:

            // Check for path to save
            if(argc >= 2){
                
                // stat struct
                struct stat sb;
                // Check path to save
                if(stat(argv[2], &sb) == -1){    
                    perror("\nqconfig checking path");
                    exit(EXIT_FAILURE);
                }

                // Posible results
                switch(sb.st_mode & S_IFMT){
                    // Is directory
                    case S_IFDIR:
                        // Check qtile config files
                        if(stat(QTILE_CONFIG, &sb) == -1){
                            perror("\nqconfig checking qtile config files");
                            exit(EXIT_FAILURE);
                        }
                        // If found, save files
                        fs::copy(QTILE_CONFIG, argv[2], copyOptions);

                        break;
                    // Other types
                    default:
                        cout << "\nSend a directory, not other object." << endl;
                        usage(USAGE_SAVE);
                        break;
                }
                
            }else{
                // This command needs a second argument
                cout << "\rSave command syntax is wrong." << endl;
                // Print save help
                usage(USAGE_SAVE);
            }

            break;
        default:
            usage(option);
    
    }

    // End of the way
    return 0;

}