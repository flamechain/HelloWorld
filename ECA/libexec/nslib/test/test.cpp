/*
This code is not meant to be used, nor is it written well.
This is purely a quick way to test the functionality of functions to find bugs before working on the main project.
*/

#include <nsstring>
#include <nsvector>
#include <stdio.h>

string testPrints() {
    string test1 = "Hello, world!";
    string test2 = (string)'H';
    string test3 = test1;

    printf("test1: %s\ntest2: %s\ntest3: %s\n", test1.c_str(), test2.c_str(), test3.c_str());

    return test3;
}

// tests nsstring & nsvector operators and functions
int main() {

    string testing = "Hello, world!";
    testing = testing;

    vector<int> testvec = {1, 2, 3};
    testvec.append(4);
    for (int i=0; i<(int)testvec.count(); i++)
        {
            printf("%i\n", testvec[i]);
        }

    string test2 = "Hello, world2?";

    printf("test2: %s\n", test2.c_str());
    // return 0;

    string test = testPrints();
    printf("test: %s\n", test.c_str());
    printf("calling operator= with self\n");
    test = test2;
    printf("done\n");
    printf("test1: %s\n", test.c_str());
    test += "..";
    printf("test2: %s\n", test.c_str());
    test = test2 + "??";
    test += ';';
    printf("test3: %s\n", test.c_str());

    if (test.startswith('H')) {
        printf("test starts with H\n");
    }
    if (test.startswith('e')) {
        printf("test starts with e\n");
    }
    if (test.startswith("Hello")) {
        printf("test starts with Hello\n");
    }
    if (test.startswith("World")) {
        printf("test starts with World\n");
    }
    if (test.endswith("???")) {
        printf("test ends with ???\n");
    }
    if (test.endswith('?')) {
        printf("test ends with ?\n");
    }
    if (test.endswith("asdf")) {
        printf("test ends with asdf\n");
    }
    if (test.endswith('a')) {
        printf("test ends with a\n");
    }

    test = test.substring(1, test.length()-1);
    printf("test 1:-1: %s\n", test.c_str());

    // return 0;
    if (test.contains("lo, ")) {
        printf("test contains 'lo, '\n");
    }
    if (test.contains("Hello")) {
        printf("test contains 'Hello'\n");
    }

    printf("\ntest: %s\nsplitted: ", test.c_str());

    vector<string> splitted = test.split(", ");

    string joined = string::join(", ", splitted);
    printf("joined1: %s\n", joined.c_str());

    joined = string(", ").join(splitted);
    printf("joined2: %s\n", joined.c_str());
    // consistent exit after this

    printf("appending\n");
    
    splitted.append("asdf");
    string join = string::join(", ", splitted);

    printf("joining\n");
    joined = string::join(", ", splitted);
    printf("after joining\n");
    printf("joined3: %s\n", joined.c_str());

    splitted.pop(1);
    joined = string::join(", ", splitted);
    printf("joined4: %s\n", joined.c_str());

    string stripped = joined.strip();
    printf("stripped1: %s\n", stripped.c_str());
    stripped = string("Hello, Hello, hello world!").strip("Hello, ");
    printf("stripped2: %s\n", stripped.c_str());

    return 0;
}
