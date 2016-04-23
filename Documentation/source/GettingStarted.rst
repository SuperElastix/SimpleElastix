.. _GettingStarted:

Getting Started
===============

This page explains how to install SimpleElastix. The process involves compiling the C++ project and linking against a target language from which you would like to use SimpleElastix. SimpleElastix can be linked against Python, Java, R, Ruby, Octave, Lua, Tcl and C#. 

.. _Linux:

SuperBuild On Linux
-------------------

SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. The SuperBuild is a script that automatically downloads and installs dependencies (in this case elastix, ITK and SWIG) before compiling the main project. The following steps assume that CMake, git and a compiler toolchain is installed. To build SimpleElastix, clone the repository and invoke the SuperBuild. 

::

    $ git clone https://github.com/kaspermarstal/SimpleElastix
    $ mkdir build
    $ cd build
    $ cmake ../SimpleElastix/SuperBuild
    $ make -j4

When the project has been built, we can find language packages in the :code:`${BUILD_DIRECTORY}/SimpleITK-build/Wrapping` directory. For example, to install the python module onto your system, navigate to

::

    ${BUILD_DIRECTORY}/SimpleITK-build/Wrapping/PythonPackage

and run the following command:

::

    $ sudo python setup.py install

This will install the SimpleITK python module with SimpleElastix unto your system, which can then be imported into your scripts like any other python module. 

Target language dependencies need to be pre-installed. The relevant :code:`apt-get` packages are  

::

    python python-dev monodevelop r-base r-base-dev ruby ruby-dev tcl tcl-dev tk tk-dev

Note that this project takes around an hour to build on a quad-core machine. SimpleElastix has been tried and tested on Ubuntu 14.10 using GCC 4.9.2 and Clang 3.4.0, Mac OSX Yosemite using Apple Clang 600.0.56 and Windows 8.1 using Microsft Visual Studio 2010 C++ compiler.

.. warning::

    Be careful not to run out of memory during the build. A rule of thumb is that we need 4GB of memory per core. For example, if we compile SimpleElastix with 4 cores (e.g. :code:`make -j4`) we need a machine with at least 16GB of RAM.

.. _MacOSX:

SuperBuild On Mac OS X
----------------------

The Mac OS X installation procedure is identical to that of Linux, so simply follow the Linux installation steps above to install SimpleElastix. Mac OS X comes with Python and Tcl preinstalled. Other target-language dependencies need to be installed seperately. This can be done with `Macports <https://www.macports.org/>`_ or `Homebrew <http://http://brew.sh/>`_.

It is assumed that a CMake, git and a compiler toolchain has already been installed. We can check for a working compiler by opening the OS X terminal and run :code:`make`. OS X will know if the Xcode Command Line Tools is missing and prompt you to install them if this is the case. If the make program throws an error message, the tools have already been installed.

.. _Windows:

SuperBuild On Windows
---------------------

SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. The SuperBuild is a script that automatically downloads and installs dependencies (in this case elastix, ITK and SWIG) before compiling the main project.

In this guide we will use CMake to generate build files and the Visual Studio compiler to compile the project. 

1. Setup directories.
    - Download and install `CMake GUI <http://www.cmake.org/download/>`_.
    - :code:`git clone https://github.com/kaspermarstal/SimpleElastix` into a source folder of your choice.
    - Point the CMake source directory to the :code:`SimpleElastix/SuperBuild` folder inside the source directory.
    - Point the CMake build directory to a clean directory. Note that Visual Studio may complain during the build if the path is longer than 50 characters. Make a build directory with a short name at the root of your harddrive to avoid any issues.

    .. figure:: _static/WindowsInstallationConfigureCMake.png
        :align: center
        :width: 100%

        Figure 3: Configure CMake.


2. Select compiler.
    - Press configure to bring up the compiler selection window.
    - Check whether our target languages are installed as 32-bit or 64-bit. For example, if our Python installation is 64-bit, we will need to build the 64-bit version of SimpleElastix to link it. If at all possible, we choose the 64-bit version since the build may run out of memory on 32-bit platforms.
    - Choose a compiler and click next. CMake will find the selected compiler for us if we leave the "Use default native compiler" option checked.

    .. tip::

        - If we need a compiler other than the default system option, we select "Specify native compilers". If we don't know what this means or what we need, we leave the "Use default native compiler" option checked.
        - If CMake complains that a compiler cannot be found, we install the free `Visual Studio Community Edition <https://www.visualstudio.com/>`_ .
        - If CMake does not pick up our target language, we can set the paths manually. For example, to manually configure CMake Python paths, tick "Advanced" and specify :code:`PYTHON_EXECUTABLE`, :code:`PYTHON_INCLUDE_DIR` and :code:`PYTHON_LIBRARY`. See Troubleshooting section for details.

    .. figure:: _static/WindowsInstallationSelectCompiler.png
        :align: center
        :width: 100% 

        Figure 4: Select compiler.


    - Press generate.

3. Open Visual Studio, select File -> Open Project/Solution -> Open and choose :code:`SuperBuildSimpleITK` solution.

    .. figure:: _static/WindowsInstallationOpenSolution.png
        :align: center
        :width: 100% 

        Figure 5: Open the solution in Visual Studio.


4. Make sure "Release" build type is selected and build the :code:`ALL_BUILD` project. If the "Debug" build type is used instead of "Release" mode, we will experience a significant performance penalty and may not be able to build language packages that are distributed without development binaries, e.g. Python.

    .. figure:: _static/WindowsInstallationBuildSolution.png
        :align: center
        :width: 100% 

        Figure 6: Right-click on :code:`ALL_BUILD` and click :code:`Build`.


Manually Building On Linux
--------------------------
The following approach allows us to use a system version of ITK or our own version of elastix. 

1. Setup the prerequisites
    - `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby python python-dev tcl tcl-dev tk tk-dev`.
2. Install the matching version of SWIG >= 3.0.5
3. Install ITK. Configure CMake using the same approach as above.
    - Clone ITK from `github.com/InsightSoftwareConsortium/ITK <https://github.com/InsightSoftwareConsortium/ITK>`_.
    - Configure CMake. Set the following CMake variables: BUILD_SHARED_LIBS=OFF, ITK_USE_REVIEW=ON, ITK_WRAP_*=OFF.
    - Compile ITK. Make sure to note the build settings, e.g. Release x64.
4. Build elastix. 
    - Clone elastix from `github.com/kaspermarstal/elastix <https://github.com/kaspermarstal/elastix>`_.
    - Set ITK_DIR to the location of the ITK build directory
    - Configure CMake. Set the following CMake variables: BUILD_EXECUTABLE=OFF, USE_KNNGraphAlphaMutualInformationMetric=OFF 
    - Set appropriate ELASTIX_IMAGE_2/3/4D_PIXELTYPES and any components that you might require.
    - If you are developing your own elastix components, make sure they are properly registered by the elastix build system.
    - Compile elastix. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.
5. Build SimpleElastix. 
    - Clone SimpleElastix from `github.com/kaspermarstal/SimpleElastix <https://github.com/kaspermarstal/SimpleElastix>`_.
    - Configure CMake. Point ITK_DIR to the location of the ITK build directory and ELASTIX_DIR to the location of the elastix build directory.
    - Build SimpleElastix. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.

Troubleshooting
---------------

I have installed a target language but CMake cannot find it
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The language package may be configured incorrectly or the necessary folders may not have been added to your :code:`$PATH` environment variable during installation. Two solutions are available.

    - Solution 1: Add the necessary folders to your :code:`$PATH` environment variable. 
        - Linux and Mac OS X: Add :code:`export PATH=${PATH}:/path/to/folder` to your :code:`$HOME/.bash_profile` (or :code:`$HOME/.profile` depending on your system) and restart the terminal.
        - Windows: Go to Control Panel -> System -> Advanced tab -> Environment Variables and add the target language installation directory to the :code:`PATH` variable.
    - Solution 2: Set the paths manually in CMake (quick and dirty fix). For example, specify :code:`PYTHON_EXECUTABLE`, :code:`PYTHON_INCLUDE_DIR` and :code:`PYTHON_LIBRARY` if you wish to build the python package. 
        - Linux and Mac OS X: Run :code:`$ ccmake .` in the build directory and press :code:`t` on your keyboard to see these options.
        - Windows: Tick "Advanced" in the CMake GUI to see these options.
        - You will have to repeat this procedure every time you setup a new build of SimpleElastix so it is worth considering configuring your :code:`PATH` variable instead (we recommend you configure your :code:`$PATH` environment variable correctly in any case). If you still experience problems at this point, re-install the language package or consult Google or Stackoverflow.

Visual Studio throws :code:`LNK1102 out of memory` error even though I selected the 64-bit compiler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
While Visual Studio targets 64-bit platforms when we select a 64-bit compiler, the Visual Studio toolchain itself will be 32-bit by default. We may therefore experience an out-of-memory error even though you compile a 64-bit vesion of elastix, especially during the linking stage. There are (at least) two ways we can try switch to a 64-bit toolchain (we say "try" because these methods work, someimes they don't).

    - Solution 1: Set the environment variable :code:`_IsNativeEnvironment=true` in command prompt, then call the Visual Studio  executable from command line. For example, in the case of VS2013:
    ::

        start "c:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" c:\SimpleElastix\build\SimpleITK-build\SimpleITK.sln
    - Solution 2: In Visual Studio, edit your .vcxproj file and insert the following after the :code:`<Import...Microsoft.Cpp.Defaults>` line:
    ::

        <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
        <PropertyGroup>
            <PreferredToolArchitecture>x64</PreferredToolArchitecture>
        </PropertyGroup>

The SuperBuild throws :code:`Server SSL certificate verification failed: certificate has expired` during checkout of elastix
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~
This is because the SSL certificate for the elastix SVN repository needs to be updated. Until this is fixed, we need to manually add the elastix certificate to our list of trusted certificates.

    - Solution 1: We run :code:`svn info https://svn.bigr.nl/elastix/trunkpublic/` in out terminal. It will then prompt us to "(R)eject, accept (t)emporarily or accept (p)ermanently?" the certificate. Hit 'p' and then enter. It may then ask us for our SVN username, which is :code:`elastixguest`, and password, which is also :code:`elastixguest`. Then we restart the build. You may have to change permissions recusively in ~/.subversion/auth. This is done by doing "chmod -R 777 ~/.subversion/auth". If all else fails, our last port of call will be to delete ~/.subversion/auth/svn.ssl.server and then carry out the steps in Solution 1. The commands noted here are linux-specific.

PCRE (Perl Compatible Regular Expression) build fails on Mac OS X
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
On recent versions of Mac OS X you may experience the following error when using the SuperBuild:

::

    Performing build step for 'PCRE'
    make[3]: *** No targets specified and no makefile found. Stop.
    make[2]: *** [PCRE-prefix/src/PCRE-stamp/PCRE-build] Error 2
    make[1]: *** [CMakeFiles/PCRE.dir/all] Error 2
    make: *** [all] Error 2

This happens during the SWIG build. We can work around this issue by forcing CMake to use clang. Add the following flags to the CMake configure command and run it in a *clean* directory:

::

    cmake -DCMAKE_CXX_COMPILER:STRING=/usr/bin/clang++ -DCMAKE_C_COMPILER:STRING=/usr/bin/clang path/to/SimpleElastix/SuperBuild

Ruby build fails on Mac OS X
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The Ruby virtual machine cannot accomodate spaces in paths. If you see a path that contains spaces like :code:`/Applications/Apple Dev Tools/Xcode.app/Contents/Developer`, re-install Xcode Command Line Tools to a place with no spaces in the path.

I get compilation errors like :code:`elastixlib.h' and 'transformixlib.h' file not found`  
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This error may stem from a space in the path of the build directory. For example, if we are building SimplElastix in :code:`/Users/kasper/folder name/build` we should rename it to :code:`/Users/kasper/folder_name/build` or similar.

SimpleElastix takes a long time to build!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The full build take 2+ hours to build on a standard machine. We can speed up compilation by deselecting Examples, Testing and any wrapped languages we don't need. Other than that there is not much we can do. SimpleITK has to compile all filters (including elastix) for all pixel types in order to support runtime selection of the correct template parameters. So yeah, it takes a long time.

I am unable to assign a parameter to a parameter map in a parameter map list
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is a known issue which is possibly related to the SWIG-generated code. If you have a solution please make a pull request!

Contribute
----------
If you are experiencing a problem that is not describes on this page, you are very welcome to open an issue on Github and we will do our best to help you out. Likewise, if you have found a solution to a problem that is not described on this page, we hope you will open a pull request on Github and help fix the problem for everyone.

