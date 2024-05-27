<h1 align="center">Building a shell was never easy</h1>

![Bash](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4b/Bash_Logo_Colored.svg/2048px-Bash_Logo_Colored.svg.png)

## Objectif
This project goes beyond merely crafting a new shell from scratch; it endeavors to emulate the Bash source code and the GNU Bash POSIX manual while incorporating principles from compiler parsing.
We don't need to create a new window/ tabs or vertical splits like our iTerm (this is what I imagined the assignment would be).
Our assignment consists in creating a `./minishell` executable that when opened, will show a prompt (`>minishell`) and wait for user input.
The user can then type any shell commands like `echo`, `ls`, `env`, `export`, `pwd` and we will show the exact same information / error messages as bash.
Fun fact: We can call other executables inside our minishell, including minishell itself. So we can type `./minishell` to enter our minishell then `./minishell` again.
We will then have to exit twice to finish all our programs.

## TEAM
This project was done in pairs. It taught us how to write cleaner code so that it can be easily used by our coding partner. We also learned how to work with git and how to communicate and find solutions in teamwork.

I'd like to thank Houda for the hard work she put in and for her commitment to write clean and understandable code. Keep sharing your knowledge like you brilliantly did with this sweet README. It was great working with you, sweety!

**Our work was generally split in the following way:**
### [Houda](https://github.com/hobenaba)
- Extracting and Tokenizing the user input
- Parsing
- Signal handling
### [Nouhaila](https://github.com/nouhaerr)
- Builtin Functions
- Executables
- Pipes and Redirections
