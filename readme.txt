I felt that attaching the usage and about files for the different languages would
clutter the submission so i left them out.  They will work with spanish though if
you follow the same format as english.

For Install:
            run the setup.sh script to add the path for "setport".
Makefile:
            The make file has multiple uses.  Ex. "make execute_test" will compile
            both .cpp files and then execute test_setport and run the tests.
            BEWARE that this command will not run the setup script for the /bin
            path. You must install that first(see above).
            The tests for the program are included now in a file and not hard
            coded.
Program Use: "setport -h" "setport --help" or "setport" will explain the usage of
            the program.
            
Enjoy!