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

#include <new.h>

struct stat st = {0};

    // [name]
    //  ├── .proman
    //  │    └── info.txt
    //  ├── src
    //  │    ├── include
    //  │    │    └── [main header]
    //  │    └── [main file]
    //  ├── Makefile
    //  └── README.md

int new(char *name, char *pwd) {

	// First of all, check if the user has a project with the same name, cuz its gonna get confusing, like this comment when it gets really long, i know i should stop right now but i just cant, its like when you want to stop something really bad but you cant, like, im trying to think of an example but i cant so sorry. anyway this comment is really long so i think i have to stop cuz this is not gud. *deap breath* *cough* *cough*

	// open config file, i know, i know, I already have another var but I'm too lazy to bring it over here and change stuff so can some nice contributer do this? I mean, if you're reading this comment can't *you* do it? *please*?
	FILE *check_name_in_config;

	char *home = getenv("HOME");
 	char *config_file = "/proman/proman.cfg";
 	char *temp = (char *) malloc(strlen(home) + strlen(config_file) + 1);
 	strcpy(temp, home);
 	strcat(temp, config_file);
 	printf("+ Checking if '%s' is in config file\n", name);
 	check_name_in_config = fopen(temp, "r");

 	free(check_name_in_config);

   // Get some info:

	// Check if it's a C project or C++
	int type = -1;
	do {
		printf("➡ Enter the project type: (1- C, 2- C++): ");
		char input;
		scanf("%c", &input);
		if (input == '1') type = 1;
		else if (input == '2') type = 0;
	} while(type == -1);

	// Check if there is a git repo somewhere :/
	char git = ' ';
	char init_git = ' ';
	char *url = malloc(sizeof(char) * 100);
	while(git != 'y' && git != 'n') {
		printf("➡ Do you already have a git repository for this project? (y or n):  ");
		scanf("%c", &git);
	}
	if (git == 'y') {
		printf("➡ Enter the URL to your git repository: ");
		scanf("%s", &*(url));
	} else {
		while(init_git != 'y' && init_git != 'n') {
			printf("➡ Do you want to initialize this project as a git repository? (y or n): ");
			scanf("%c", &init_git);			
		}
	}

	char config_git = 'n';
	if (init_git == 'y' || git == 'y') config_git = 'y';

	FILE *readme, *info, *main, *mainh, *makefile, *config;
	
	// Directory paths
	char *src = "/src";
	char *include = "/src/include";
	char *current = "./";
	char *proman = "/.proman";
	char *dir = (char *) malloc(3 + strlen(src)+ strlen(include) ); 

	// File paths
	char *info_path = "/.proman/info.txt";
	char *main_header_path = "/src/include/main.h";
	char *main_path = " ";
	if (type == 1) main_path = "/src/main.c";
	else main_path = "/src/main.cpp";
	
	char *make_path = "/Makefile";
	char *readme_path = "/README.md";
	char *file_path = (char *) malloc(3 + strlen(main_header_path)+ strlen(main_path) ); 

   	char *project_path = (char *) malloc(strlen(pwd) + strlen(name) + 3);
	strcpy(project_path, pwd);
	strcat(project_path, "/");
	strcat(project_path, name);

	if (git == 'y') init_git = 'y';
	if (stat(name, &st) == -1) {
    	mkdir(name, 0700);

    	/////////////////
    	// Directories //
    	/////////////////

    	// src directory
    	strcpy(dir, current);
    	strcat(dir, name);
    	strcat(dir, src);
    	printf("+ Creating directory %s\n", dir);
    	mkdir(dir, 0700);

    	// include directory
    	strcpy(dir, current);
    	strcat(dir, name);
    	strcat(dir, include);
    	printf("+ Creating directory %s\n", dir);
    	mkdir(dir, 0700);

    	// proman directory
    	strcpy(dir, current);
    	strcat(dir, name);
    	strcat(dir, proman);
    	printf("+ Creating directory %s\n", dir);
    	mkdir(dir, 0700);

    	///////////
    	// Files //
    	///////////

    	// README.md
    	strcpy(file_path, current);
    	strcat(file_path, name);
    	strcat(file_path, readme_path);
    	printf("+ Creating file %s\n", file_path);
    	readme = fopen(file_path, "w");
    	fprintf(readme, "# %s\nA super awesome project that does super awesome stuff\n", name);
    	fclose(readme);

    	// info.txt
    	strcpy(file_path, current);
    	strcat(file_path, name);
    	strcat(file_path, info_path);
    	printf("+ Creating file %s\n", file_path);
    	info = fopen(file_path, "w");
    	fprintf(info, "[name: %s]\n[type: %d]\n[git: %c]\n[path: %s]\n----\n", name, type, config_git, project_path);
    	fclose(info);

    	// main.c / main.cpp
    	strcpy(file_path, current);
    	strcat(file_path, name);
    	strcat(file_path, main_path);
    	printf("+ Creating file %s\n", file_path);
    	main = fopen(file_path, "w");
    	if (type == 1) fprintf(main, "#include <stdio.h>\n\nint main(void) {\n  printf(\"Hello world!\\n\");\n}\n");
    	else fprintf(main, "#include <iostream>\n\nint main(void) {\n  std::cout << \"Hello world!\\n\";\n}\n");
    	fclose(main);

    	// main.h
    	strcpy(file_path, current);
    	strcat(file_path, name);
    	strcat(file_path, main_header_path);
    	printf("+ Creating file %s\n", file_path);
    	mainh = fopen(file_path, "w");
    	fprintf(mainh, "#ifndef __HEADER_H__\n#define __HEADER_H__\n\n // Put some awesome stuff here \n\n #endif\n");
    	fclose(mainh);

    	// Makefile
    	strcpy(file_path, current);
    	strcat(file_path, name);
    	strcat(file_path, make_path);
    	printf("+ Creating file %s\n", file_path);
    	makefile = fopen(file_path, "w");
    	if (type == 1) { 
    		fprintf(makefile, "LD = gcc\nCC = gcc\n\nCFLAGS := \\\n		-Isrc/include \\\n	-Wall \\\n	-Wextra \\\n	-std=gnu99 \\\n\nCFILES := $(shell find src/ -name '*.c')\nOFILES := $(CFILES:.c=.o)\n\nTARGET = %s\n\nall: clean compile\n\ncompile: ld\n	@ echo \"Done!\"\n\nld: $(OFILES)\n	@ echo \"[LD] $^\"\n	@ $(LD) $^ -o $(TARGET)\n\n%%.o: %%.c\n		@ echo \"[CC] $<\"\n	@ $(CC) $(CFLAGS) -c $< -o $@\n\nclean:\n	@ echo \"[CLEAN]\"\n	@ rm -rf $(OFILES) $(TARGET)\n", name);
    	} else {
    		fprintf(makefile, "LD = g++\nCC = g++\n\nCFLAGS := \\\n		-Isrc/include \\\n	-Wall \\\n	-Wextra \\\n\nCFILES := $(shell find src/ -name '*.cpp')\nOFILES := $(CFILES:.cpp=.o)\n\nTARGET = %s\n\nall: clean compile\n\ncompile: ld\n	@ echo \"Done!\"\n\nld: $(OFILES)\n	@ echo \"[LD] $^\"\n	@ $(LD) $^ -o $(TARGET)\n\n%%.o: %%.cpp\n		@ echo \"[CC] $<\"\n	@ $(CC) $(CFLAGS) -c $< -o $@\n\nclean:\n	@ echo \"[CLEAN]\"\n	@ rm -rf $(OFILES) $(TARGET)\n", name);
    	}
    	fclose(makefile);

    	// Config
    	char *home = getenv("HOME");
    	char *config_file = "/proman/proman.cfg";
    	char *temp = (char *) malloc(strlen(home) + strlen(config_file) + 1);
    	strcpy(temp, home);
    	strcat(temp, config_file);
    	printf("+ Adding '%s' to config file\n", name);
    	config = fopen(temp, "a");

    	if (config == NULL) printf("Error: could not open config file\n");
    	else {
    		fprintf(config, "[name: %s]\n[type: %d]\n[git: %c]\n[path: %s]\n----\n", name, type, config_git, project_path);


    		fclose(config);
    	}

    	///////////////
    	// Git stuff //
    	///////////////

    	if (init_git == 'y') {
    		char *command = "git init ";
    		char *git_command = malloc(strlen(command) + strlen(name) + 1);
    		strcpy(git_command, command);
    		strcat(git_command, name);
    		system(git_command);

    		free(git_command);
    	}

    	if (git == 'y') {
    		char *command = "git remote add origin ";
			char *git_command = malloc((strlen(command) + strlen(url) + 1) * sizeof(char)); 		
    		strcpy(git_command, command);
    		strcat(git_command, url);

    		chdir(name);
    		system(git_command);
    		printf("+ Connecting to git remote\n");
    	}
    	free(dir);
    	free(file_path);
    	free(temp);
	} else {
		printf("Error: Directory '%s' already exists\n", name);
		return 0;
	}
	
	return 0;
}
