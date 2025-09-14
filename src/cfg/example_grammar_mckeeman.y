
E	: T '$'
	;

T	: F
	| T '*' F
	;
	
F	: i
	;
	
F	: '(' T ')'
	;
