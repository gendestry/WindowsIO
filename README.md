# WindowsIO library

A library that simulates input (keyboard, mouse) made in C++ using Windows.h and JNI.
List of functions in class file (WindowsIO.java).

## Supports:
 - simulating key press,
 - simluating mouse press,
 - simulating mouse movement (relative and absoulte)
 - getting pixel data at coordinates,
 - getting mouse position
 - getting and seting clipboard text

## Usage:
```java
    public class Example {
        public static void main(String[] args) {
            WindowsIO io = new WindowsIO();
            
            io.typeString("I support unicode characters!"); // types the string to the focused input
            io.moveMouseAbsolute(100, 100); // moves mouse to 100, 100 on the main monitor
        }   
    }
```

## Compiling and Running:
#### DLL:
You can either use the `.dll` provided in the repository or compile it on your own.

First you create the c++ files by running `javac -h . WindowsIO.java`.
Then to compile the `.dll` use whichever c++ compiler you have. Dont forget to link the JNI headers.
JNI Headers:
 - ...\jdk<version>\include
 - ...\jdk<version>\include\win32

#### Example project:
To compile use `javac Example.java` and then use `java Example`.