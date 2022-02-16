#pragma once
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/crt/Types.h>

namespace Utils
{
    /**
     * A struct to hold the command line options that can be passed to the program from the terminal/console.
     */
    struct CommandLineOption
    {
        Aws::Crt::String CommandName;
        Aws::Crt::String ExampleInput;
        Aws::Crt::String HelpOutput;

        CommandLineOption(Aws::Crt::String p_Name, Aws::Crt::String p_ExampleInput, Aws::Crt::String p_Help="")
        {
            CommandName = p_Name;
            ExampleInput = p_ExampleInput;
            HelpOutput = p_Help;
        }
    };

    /**
     * A helper class that makes it easier to register, find, and parse commands passed to the program from the terminal/console.
     */
    class CommandLineUtils
    {
        public:
            /**
             * Changes the program name to the name given. The program name is shown when calling help and showing all the commands.
             * @param NewProgramName The program name to show when executing PrintHelp
             */
            void RegisterProgramName(Aws::Crt::String NewProgramName);

            /**
             * Adds a new command to the utility. Used to show command data when printing all commands.
             * @param NewCommand The command struct containing the new command/argument data
             */
            void RegisterCommand(CommandLineOption NewCommand);
            /**
             * Adds a new command to the utility. Used to show command data when printing all commands.
             * @param CommandName The name of the command
             * @param ExampleInput Example input for the command (example "<endpoint>")
             * @param HelpOutput The message to show with the command when printing all commands via help
             */
            void RegisterCommand(Aws::Crt::String CommandName, Aws::Crt::String ExampleInput, Aws::Crt::String HelpOutput="");

            /**
             * Removes the command if it has already been registered
             * @param CommandName 
             */
            void RemoveCommand(Aws::Crt::String CommandName);

            /**
             * Updates the help text of a registered command. If the given command does not exist, nothing happens
             * @param NewCommandHelp 
             */
            void UpdateCommandHelp(Aws::Crt::String CommandName, Aws::Crt::String NewCommandHelp);

            /**
             * Called to give the class a copy of the begin and end character pointers that contain the arguments from the terminal/console
             * @param begin The beginning of terminal/console input
             * @param end The end of terminal/console input
             */
            void SendArguments(char** begin, char** end);

            /**
             * Returns true if the command was inputted into the terminal/console
             * 
             * You must call SendArguments and pass terminal/console input first in order for the function to work.
             * 
             * @param CommandName The name of the command you are looking for
             * @return true If the command is found
             * @return false If the command is not found
             */
            bool HasCommand(Aws::Crt::String CommandName);

            /**
             * Gets the value of the command passed into the console/terminal. This function assumes the command exists
             * and was passed into the program through the console/terminal.
             * 
             * You must call SendArguments and pass console/terminal input first in order for the function to work.
             * 
             * @param CommandName The name of the command you want to get the value of
             * @return Aws::Crt::String The value passed into the program at the command name
             */
            Aws::Crt::String GetCommand(Aws::Crt::String CommandName);

            /**
             * Gets the value of the command passed into the console/terminal if it exists, otherwise it returns
             * whatever value is appsed into CommandDefault
             * 
             * You must call SendArguments and pass console/terminal input first in order for the function to work.
             *
             * @param CommandName The name of the command you want to get the value of
             * @param CommandDefault The value to assign if the command does not exist
             * @return Aws::Crt::String The value passed into the program at the command name
             */
            Aws::Crt::String GetCommandOrDefault(Aws::Crt::String CommandName, Aws::Crt::String CommandDefault);

            /**
             * Gets the value of the command passed into the console/terminal if it exists. If it does not exist,
             * the program will exit with an error message.
             * 
             * @param CommandName The name of the command you want to get the value of
             * @return Aws::Crt::String The value passed into the program at the command name
             */
            Aws::Crt::String GetCommandRequired(Aws::Crt::String CommandName, Aws::Crt::String OptionalAdditionalMessage="");

            /**
             * Prints to the console/terminal all of the commands and their descriptions.
             */
            void PrintHelp();

            /**
             * A helper function that adds endpoint, key, cert, and ca_file commands
             */
            void AddCommonMQTTCommands();

        private:
            Aws::Crt::String ProgramName = "Application";
            char** BeginPosition = nullptr;
            char** EndPosition = nullptr;
            Aws::Crt::Map<Aws::Crt::String, CommandLineOption> RegisteredCommands;    
    };
}