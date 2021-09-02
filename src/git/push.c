/* 
 * MIT License
 * 
 * Copyright (c) 2021 Adam Salhi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <git/push.h>

int push(char *message, char *pwd) {
    // TODO: check if name is in config file.
    printf("+ Pushing changes in directory %s\n", pwd);
    char *add_command = "git add .";
    char *commit = "git commit -m ";
    char *commit_command = (char *) malloc((strlen(commit) + strlen(message)) * sizeof(char));
    strcpy(commit_command, commit);
    strcat(commit_command, message);
    char *push_command = "git push -u origin master";

    system(add_command);
    system(commit_command);
    system(push_command);

    printf("+ Done!\n");
    free(commit_command);

    return 0;
}
