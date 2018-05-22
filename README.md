# OGL Info
OGL Info is a C++17 Visual Studio 2017 Solution to interrogate a Windows platform / graphics
driver for its support of OpenGL capabilities.

The VS Solution comprises 3 projects:
## oglinfo
This is a DLL project and is the main project component that does all the work in
interrogating the system for its OpenGL capabilities.

Note: only the public interface is documented.

## test
This is a console test harness application for the **oglinfo** dll.
It shows how to use the **oglinfo** dll with pre-defined constants representing
OpenGL context and pixel attributes.

Note: this project is not documented.

## mfcTest
This is an MFC application test harness but which is also a useful
tool in allowing a user to see basic OpenGL driver information, request pixel format
numbers that fulfill the users required OpenGL context and pixel attibutes, and finally
to allow the user to query a given pixel format for tha values of a selection of pixel attributes.
It shows how to use the **oglinf** dll by building up lists of OpenGL context and pixel attributes
and feeding them into **oglinfo**.

Note: this project is not documented.

Examples of screenshots for this tool are located in the _screenshots_ directory.
One such example:
![Alt text](/oglinfo/screenshots/opengldriverpage.png?raw=true "Driver Info")

#### Purpose
The main reason for writing this project has been to learn OpenGL context creation for Windows
with the focus on OpenGL 3 and above. This has involved reading the documentation at
https://www.khronos.org/registry/OpenGL and other resources.<br/>
Another reason: to provide a software component that can be used by client code to easily check
the resident system's OpenGL facilities without interfering with any other OpenGL context that
the client code may have currently active. This is achieved by the **oglinfo** dll creating a thread
for each _interrogation_ and creating an OpenGL context in that thread; these
threads are not directly / easily accessible by client code.

Along the way I had to learn / re-learn a bit of MFC. May be I should have used Qt5.


##### Notes
Version of Visual Studio 2017 Professional: 15.7.1<br/>
[The latest Visual C++ redistributables.](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)

