extract a full line (bunch of words where in the end we have \n)
analyze the line itself( that would be the work of a parser)
read command line -> puts it into a data structure called (command table)
				  -> store the commands that will be executed.
REDIRECTIONS : 
> take the output of a command and put it into a chosen file(overwrite)
>>  the same as > but does finish on what's already on that file (no overwriting)
< -> it takes the input of the file used as the input for the command.

parser/executor/shell subsystems -> environment variables, wildcards, subshells.
what does lex and yacc tools stand for.

lexer -> takes the input characters and puts the charactes together into words called tokens
parser -> processes the tokens according to a certain grammar and build the command line that will be looked upon wildcard and envars
<< ->> that would be the heredoc
->> when we use redirections, we use word updated or read of THAT file.




////////////////////////////////////

STEPS OF WORK :
->> lexer (sub struct){
	char *value => token.
	enum e_type type => type (word/ wspace/redirection/pipe/env)
}
->>> check syntax errors.
->>> parsing (MAIN struct) -> here im gonna have nodes depending on how much command i do have => three -> 3 nodes -> 3 child processes
each node gonna have {
	node of words;
	node of outfile -> two types;
	node of infile
	node of heredoc
}

//the expanssion of the environment variables ->>
'1(doesnt matter the number) -> "impair => expand /// '1 ->"pair -> not expand
"1(doesnt matter the number) -> 'impair -> not expand /// "1 -> ' pair  -> expand


// to take care of :
-> echo hello > out |
-> | echo hi
-> handle redirections must not be empty after it.
-> abort : echo "$USER"dkdjkhdjd'djkddd"d"dD'$USER

REMARKS: 

// the cause of memory leak would be :
//->> failure to free memory where i have used malloc and its cousins
//-> unreachable memory : a pointer to an allocated memory is lost or i have overwritten on it 


syntax errors to check:
->> when pipe and redirections have nothing after them


->> FOR THE EXPANSION IN HEREDOC :
	-> NONE -> expansion of the input.
	-> "" oder '' -> no expansion.

->> for signals in my heredoc :
 .ctrl + d = go out of heredoc no less no more.