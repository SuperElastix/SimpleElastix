.. _GettingStarted:

Getting Started
===============

This page explains how to install SimpleElastix. The process typically involves compiling the C++ project and linking against a target language from which you would like to use SimpleElastix. SimpleElastix can be linked against Python, Java, R, Ruby, Octave, Lua, Tcl and C#. 

.. _Linux:

SuperBuild On Linux
-------------------

SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. To build SimpleElastix in unix-like environments, clone the repository and invoke the SuperBuild. 

::

    $ git clone https://github.com/kaspermarstal/SimpleElastix
    $ mkdir build
    $ cd build
    $ cmake ../SimpleElastix/SuperBuild
    $ make -j4

The SuperBuild will download and install dependencies (elastix, ITK and SWIG) and compile SimpleElastix. When you have built the project, you will find language packages in the :code:`${BUILD_DIRECTORY}/SimpleITK-build/Wrapping` directory. For example, to install the python module onto your system, navigate to

::

    ${BUILD_DIRECTORY}/SimpleITK-build/Wrapping/PythonPackage

and run the following command:

::

    $ sudo python setup.py install

This will install the SimpleITK python module with SimpleElastix unto your system, which can then be imported into your scripts like any other python module. 

Target language dependencies need to be pre-installed. The :code:`apt-get` packages are  

::

    python python-dev monodevelop r-base r-base-dev ruby ruby-dev tcl tcl-dev tk tk-dev

Note that this project takes around an hour to build on a quad-core machine. SimpleElastix has been tried and tested on Ubuntu 14.10 using GCC 4.9.2 and Clang 3.4.0, Mac OSX Yosemite using Apple Clang 600.0.56 and Windows 8.1 using Microsft Visual Studio 2010 C++ compiler.

.. warning::

    Be careful not to run out of memory during the build. If you have 8GB or less, it is recommended not build on more than two threads, especially if you are wrapping multiple languages. 

.. _MacOSX:

SuperBuild On Mac OS X
----------------------

The Mac OS X installation procedure is identical to that of Linux. You will use CMake to generate build files and Clang to compile the project. First, however, check if a working compiler is installed:

- Open the OS X terminal and run :code:`make`. OS X will know if the Xcode Command Line Tools is missing and prompt you to install them if this is the case.
- If you see an error message from the make program, the tools are installed and you can follow the Linux installation instructions above.

Target-language dependencies also need to be installed seperately. This can be done with `Macports <https://www.macports.org/>`_ or `Homebrew <http://http://brew.sh/>`_. Mac OS X comes with Python and Tcl already installed.

.. _Windows:

SuperBuild On Windows
---------------------

SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. The SuperBuild will download and install dependencies (elastix, ITK and SWIG) and compile SimpleElastix. You will use CMake to generate build files and the Visual Studio compiler to compile the project. You need to pay special attention to certain configuration settings before you start the build, but everything is explained below. Follow the steps closely and you should be good.

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
    - Check whether your target languages are installed as 32-bit or 64-bit. For example, if your Python installation is 64-bit, you will need to build the 64-bit version of SimpleElastix to link with it. If possible at all, we recommend 64-bit since compilation may run out of memory on 32-bit platforms.
    - Choose a compiler and click next. CMake will find the selected compiler for you if you leave the "Use default native compiler" option checked.

    .. tip::

        - If you need a compiler other than the default system option, select "Specify native compilers". If you don't know what this means or what you need, leave the "Use default native compiler" option checked.
        - If CMake complains that a compiler cannot be found, install the free `Visual Studio Community Edition <https://www.visualstudio.com/>`_ .
        - If CMake does not pick up your target language, you can set the paths manually. For example, to manually configure CMake Python paths, tick "Advanced" and specify :code:`PYTHON_EXECUTABLE`, :code:`PYTHON_INCLUDE_DIR` and :code:`PYTHON_LIBRARY`. See Troubleshooting section for details.

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


4. Make sure "Release" build type is selected and build the :code:`ALL_BUILD` project. If the "Debug" build type is used instead of "Release" mode, you will experience a significant performance penalty and may not be able to build language packages that are distributed without development binaries, e.g. Python.

    .. figure:: _static/WindowsInstallationBuildSolution.png
        :align: center
        :width: 100% 

        Figure 6: Right-click on :code:`ALL_BUILD` and click :code:`Build`.


Manually Building On Linux
--------------------------
The following approach allows you to use a system version of ITK or your own version of elastix. In the latter case, start out with the elastix source code at https://github.com/kaspermarstal/elastix which includes some changes that make elastix play nicely with SimpleITK. 

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
    - Make sure your own compontents are properly registered by the elastix build system if you are writing your own components.
    - Compile elastix. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.
5. Build SimpleElastix. 
    - Clone SimpleElastix from `github.com/kaspermarstal/SimpleElastix <https://github.com/kaspermarstal/SimpleElastix>`_.
    - Configure CMake. Point ITK_DIR to the location of the ITK build directory and ELASTIX_DIR to the location of the elastix build directory.
    - Build SimpleElastix. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.

Troubleshooting
---------------

I have installed a target language but CMake cannot find it.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The language package may be configured incorrectly or the necessary folders may not have been added to your :code:`$PATH` environment variable during installation. Two solutions are available.

    - Add the necessary folders to your :code:`$PATH` environment variable. 
        - Linux and Mac OS X: Add :code:`export PATH=${PATH}:/path/to/folder` to your :code:`$HOME/.bash_profile` (or :code:`$HOME/.profile` depending on your system) and restart the terminal.
        - Windows: Go to Control Panel -> System -> Advanced tab -> Environment Variables and add the target language installation directory to the :code:`PATH` variable.
    - Set the paths manually in CMake (quick and dirty fix). For example, specify :code:`PYTHON_EXECUTABLE`, :code:`PYTHON_INCLUDE_DIR` and :code:`PYTHON_LIBRARY` if you wish to build the python package. 
        - Linux and Mac OS X: Run :code:`$ ccmake .` in the build directory and press :code:`t` on your keyboard to see these options.
        - Windows: Tick "Advanced" in the CMake GUI to see these options.
        - You will have to repeat this procedure every time you setup a new build of SimpleElastix so it is worth considering configuring your :code:`PATH` variable instead (we recommend you configure your :code:`$PATH` environment variable correctly in any case). If you still experience problems at this point, re-install the language package or consult Google or Stackoverflow.

Visual Studio throws :code:`LNK1102 out of memory` error even though I selected the 64-bit compiler.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
While Visual Studio targets 64-bit platforms when you select a 64-bit compiler, the Visual Studio toolchain itself will be 32-bit by default. This is a problem when SimpleElastix requires more than 4GB of memory during the linking stage. 

    - Switch to the 64-bit toolchain. There are two ways of doing this.
        - Set the environment variable :code:`_IsNativeEnvironment=true` in command prompt, then call the VS2013 executable from command line. For example:
        ::

            c:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" c:\SimpleElastix\build\SimpleITK-build\SimpleITK.sln)
        - In Visual Studio, edit your .vcxproj file and insert the following after the :code:`<Import...Microsoft.Cpp.Defaults>` line:
        ::

            <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
            <PropertyGroup>
                <PreferredToolArchitecture>x64</PreferredToolArchitecture>
            </PropertyGroup>

Ruby build fails os Mac OS X.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The Ruby virtual machine cannot accomodate spaces in paths. If you see a path that contains spaces like :code:`/Applications/Apple Dev Tools/Xcode.app/Contents/Developer`, re-install Xcode Command Line Tools to a place with no spaces in the path.

If you are experiencing a problem that is not describes on this page, you are very welcome to open an issue on Github and we will do our best to help you out. Likewise, if you have found a solution to a problem that is not described on this page, you are welcome to open a pull request on Github and help fix the problem for everyone.

SimpleElastix takes a long time to build!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The full build take 2+ hours to build on a standard machine. You can speed up compilation by deselecting Examples, Testing and any wrapped languages you don't need.

