# JASS++ Transpiler

The goal of this project is to create a more C-like syntax for the JASS language.

### The problems with JASS
JASS is a keyword language which sometimes makes it very cumbersome to produce code. It is certainly descriptive, but perhaps too descriptive at times.
For instance, a simple struct in JASS:
```
// JASS
struct Point
	private integer x
	private integer y

	static method create takes integer x, integer y returns thistype
		local thistype this = thistype.allocate()
		set this.x = x
		set this.y = y
		return this
	endmethod
endstruct
```
Could be made simpler with a more C-like syntax:
```
// JASS++
class Point {
	int x;
	int y;

public:
	Point(int x, int y) {
		this.x = x;
		this.y = y;
	}
}
```
Statements in JASS are separated with new line. There are a few instances when this might not be preferable.
<i>Method chaining</i> could potentially lead to very long lines.
```
// JASS
local ComplexObject complexObject = ComplexObject.create().debug("Let's build team1Object.").team1Object().append(applicationContext1).debug("Let's build team2Object.").team2Object().append(applicationContext2).debug("All done.").build()
```
However using the proposed C-like syntax where statements are separated with `;`, we could make this code more readable.
```
// JASS++
ComplexObject complexObject = ComplexObject.create()
																				.debug("Let's build team1Object.")
																				.team1Object()
																				.append(applicationContext1)
																				.debug("Let's build team2Object.")
																				.team2Object()
																				.append(applicationContext2)
																				.debug("All done.")
																				.build();
```
There is a way to do this using multi line comments in JASS but it doesn´t look very nice.
```
// JASS
local ComplexObject complexObject = ComplexObject.create()\*
																					  */.debug("Let's build team1Object.")\*
																					  */.team1Object()\*
																					  */.append(applicationContext1)\*
																					  */.debug("Let's build team2Object.")\*
																					  */.team2Object()\*
																					  */.append(applicationContext2)\*
																					  */.debug("All done.")\*
																					  */.build()
```
Furthermore, due to the new line separator in JASS, we can not make our code more compact if we wanted to:
```
// JASS
struct Vector
	private integer x
	private integer y
	private integer z

	method getX takes nothing returns integer
		return x
	endmethod
	method setX takes integer x returns nothing
		set this.x = x
	endmethod

	method getY takes nothing returns integer
		return y
	endmethod
	method setY takes integer y returns nothing
		set this.y = y
	endmethod

	method getZ takes nothing returns integer
		return z
	endmethod
	method setZ takes integer z returns nothing
		set this.z = z
	endmethod
endstruct
```
While in JASS++:
```
// JASS++
class Vector {
	int x;
	int y;
	int z;

public:
	int getX() { return x; }
	void setX(int x) { this.x = x; }

	int getY() { return y; }
	void setY(int y) { this.y = y; }

	int getZ() { return z; }
	void setX(int z) { this.z = z; }
}
```

## Compiler Options

| Name | Default | Type | Description |
| :------------ | :------------ | :------------ |:------------ |
| sourceFolderPath | src | string | The folder containing the `.jpp` source files to compile. |
| outFolderPath | out | string | Target folder of the resulting `.j` file. |
| mainSourceFilename | main | string | The Main file is the entry point for locating all imports. Semantically sensible to use as script entry point as well but it´s not required. |


Each compiler option is <b>optional</b> and can be specified either in the `settings.json` file or as a command line argument at execution.

If a compiler option is specified both in the `settings.json` file and as a command line argument, the command line argument takes priority.

If a compiler option is absent from both the `settings.json` file and the command line, its default value will be used as shown in the table above.

## Using imports

Imports are defined using the keyword `#import` followed by the semi-absolute path to the `.jpp` code file without `.jpp` file extension like such:
```
#import "wrappers/String"
```

Each path is relative to the given source folder compiler option ("sourceFolderPath").

Imports are merely a preprocessor text-macro and they are not equivalent to the vJass imports `//! import`. Subsequently the Transpiler allows circular imports as the code will be compiled to a single `.j` file.

Note: Files are not scopes. You can not define exports as everything from a file is included when imported.
