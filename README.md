To run the program in the cluster the user needs to upload the pbs file and the program file in it; control if the pbs can execute, if it can’t he has to use the chmod +x (file_name) function; once the interactive section is open he can simply launch it with ./(file_name) function. 
To change the number of threads he will need to open the file and change it manually at lines 178 and 206, and then reload the file in the cluster.
To run the program on Visual Studio Code compiler or any other compiler the user will have to comment lines 32 and 33, these lines take the input from the PBS file, and take off the comments on lines 30 and 31, these lines allow the user to put the input itself without using the pbs file. 
