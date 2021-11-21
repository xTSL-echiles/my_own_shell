# my_own_shell


Not interpret unclosed quotes or unspecified special characters like \ or;.

Show a prompt when waiting for a new command.

Have a working History.

Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)
_______________________
Implement the builtins:

◦ echo with option -n

◦ cd with only a relative or absolute path

◦ pwd with no options

◦ export with no options

◦ unset with no options

◦ env with no options or arguments

◦ exit with no options
_______________________


• ’ inhibit all interpretation of a sequence of characters.

• " inhibit all interpretation of a sequence of characters except for $.
_______________________

Redirections:

◦ < redirect input.

◦ >  redirect output.

◦ “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t update history!

◦ “>>” redirect output with append mode.
_______________________

Pipes.

• Pipes | The output of each command in the pipeline is connected via a pipe to the
input of the next command.

• Environment variables ($ followed by characters)expand to their values.

• $? expand to the exit status of the most recently executed foreground
pipeline.

• ctrl-C ctrl-D ctrl-\ should work like in bash.

• When interactive:

◦ ctrl-C print a new prompt on a newline.

◦ ctrl-D exit the shell.

◦ ctrl-\ do nothing.
