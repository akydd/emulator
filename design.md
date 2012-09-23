# Emulator design

## The Assembler

Assembly language is parsed using the following states and transitions:

* newline
	* "\n": newline
	* whitespace and char position <= 9: lws
	* other: label
* leading whitespace (lws)
	* alphanumeric and char position < 8: label
	* whitespace and char position < 8: lws
	* whitespace and char position = 8: ws1
	* "\n": newline
	* other: instruction
* label
	* alphanumeric: label
	* whitespace and char position < 8: lws
	* whitespace and char position = 8: ws1
* whitespace1 (ws1)
	* alphanumeric: instruction
* instruction
	* alphanumeric: instruction
	* whitespace: ws2
* whitespace2 (ws2)
	* whitespace: ws2
	* "\n": newline
	* other: op1
* op1
	* comma: comma
	* alphanumeric: op1
	* whitespace: ws3
	* "\n": newline
* comma
	* alphanumeric: op2
* op2
	* alphanumeric: op2
	* whitespace: ws3
	* "\n": newline
* whitespace3 (ws3)
	* whitespace: ws3
	* "#": comment
	* "\n": newline
* comment
	* "\n": newline
	* other: comment

