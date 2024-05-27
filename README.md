<h1 align="center"><font color="red">Building a shell was never easy</font></h1>
This project goes beyond merely crafting a new shell from scratch; it endeavors to emulate the Bash source code and the GNU Bash POSIX manual while incorporating principles from compiler parsing.
 We don't need to create a new window/ tabs our vertical splits like our iTerm (this is what I imagined the assignment would be).
 Our assignment consists in creating a <./minishell executable that when opened, will show a prompt (>msh) and wait for user input.
 The user can then type any shell commands like echo, ls, env export, pwd and we will show the exact same information / error messages as bash.
 Fun fact: We can call other executables inside our minishell, including minishell itself. So we can type ./minishell to enter our minishell then ./minishell again.
 We will then have to exit twice to finish all our programs.
