.. _GettingStarted:

Getting Started
===============

Follow the steps below to install SimpleElastix, then see the :ref:`Introduction <Introduction>` for an overview of SimpleElastix. You can also go straight to the examples for a hands-on presentation.

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

.. note::

    Be careful not to run out of memory during the build. If you have 8GB or less, it is recommended not build on more than two threads, especially if you are wrapping multiple languages. 

.. _MacOSX:

SuperBuild On Mac OS X
----------------------

To build SimpleElastix, the Xcode Command Line Tools needs to be installed. First, check if it is already installed. 

- Open the OS X terminal and the the command

    ::
        $ make

    OS X will know if make is missing and prompt you to install Xcode Command Line Tools if this is the case. Do it and then follow the Linux installation instructions above.

- If you see an error message from the make program, the tools are installed and you can follow the Linux installation instructions above.
- Target-language dependencies have to be installed separately using e.g. `Macports <https://www.macports.org/>`_ or `Homebrew <http://http://brew.sh/>`_. Mac OS X comes with Python and Tcl already installed.

.. _Windows:

SuperBuild On Windows
---------------------

Building SimpleElastix on windows is conceptually similar the building on Unix. You will be using the CMake GUI to generate a Visual Studio solution and Visual Studio to compile the project, but you need to pay special attention to certain configuration settings before you start the build. These settings are explained below. Follow the steps closely and you should be good.

1. Generate build files.
    - Check whether your target languages are installed as 32-bit or 64-bit. For example, if your Python installation is 64-bit, you will need to build the 64-bit version of SimpleElastix to link with it. 
    - Download and install `CMake GUI <http://www.cmake.org/download/>`_.
    - :code:`git clone https://github.com/kaspermarstal/SimpleElastix` into a source folder of your choice.
    - Point the source directory to the :code:`SimpleElastix/SuperBuild` folder inside the source directory.
    - Point the build directory to a clean directory. Note that Visual Studio may complain during the build if the path is longer than 50 characters.
    - You may want to to speed up compilation by deselecting Examples, Testing and any wrapped languages you don't need as the full build can take a long time (1+ hour a standard quad-core machine). 

    .. figure:: _static/WindowsInstallationConfigureCMake.png
        :align: center
        :figwidth: 90%
        :width: 90% 

        Figure 3: Configure CMake.


2. Press configure, select your desired compiler and click Finish.
    - Choose a 64-bit version of the compiler and click next. CMake will find the selected compiler for you if you leave the "Use default native compiler" option checked.
    - If you need a compiler other than the default system option, select "Specifiy native compilers". If you don't know what this means or what you need, leave the "Use default native compiler" option checked.
    - If CMake complains that a compiler cannot be found, install the free `Visual Studio Community Edition <https://www.visualstudio.com/>`_ .
    - If CMake does not pick up your target language, you can set the paths manually. For example, you can now manually specify :code:`PYTHON_EXECUTABLE`, :code:`PYTHON_INCLUDE_DIR` and :code:`PYTHON_LIBRARY` if you wish to build the python package. See this section under Troubleshooting for details.

    .. figure:: _static/WindowsInstallationSelectCompiler.png
        :align: center
        :figwidth: 90%
        :width: 90% 

        Figure 4: WindowsInstallationSelectCompiler.

    - Press generate.

3. Open visual studio, select File -> Open Project/Solution -> Open and choose :code:`SuperBuildSimpleITK` solution.

    .. figure:: _static/WindowsInstallationOpenSolution.png
        :align: center
        :figwidth: 90%
        :width: 90% 

        Figure 5: Open the solution in Visual Studio.


4. Make sure "Release" build type is selected and build the :code:`ALL_BUILD` project. If the "Debug" build type is used instead of "Release" mode, you will experience a significant performance penalty and may not be able to build language packages that are distributed without development binaries, e.g. Python.

    .. figure:: _static/WindowsInstallationBuildSolution.png
        :align: center
        :figwidth: 90%
        :width: 90% 

        Figure 6: Right-click on :code:`ALL_BUILD` and click :code:`Build`.

Troubleshooting
---------------
- I have installed a target language but CMake cannot find it.
    - The language package may be configured incorrectly or the necessary folders may not have been added to your :code:`$PATH` environment variable during installation. Add the necessary folders to your :code:`$PATH`. Alternatively, you may also set the paths manually in CMake as a quck and dirt fix. For example, specify :code:`PYTHON_EXECUTABLE`, :code:`PYTHON_INCLUDE_DIR` and :code:`PYTHON_LIBRARY` in the cmake GUI if you wish to build the python package. If you are using the CMake GUI on Windows, tick "Advanced" to see these options. If you are using CMake from the command line, run :code:`$ ccmake .` in the build directory and press :code:`t` on your keyboard to see these options. You will have to repeat this procedure every time you setup a new build of SimpleElastix so we strongly recommended you fix your installation and configure your :code:`$PATH` environment variable correctly instead. If you still experience problems at this point, re-install the language package or consult Google or Stackoverflow.
- Visual Studio throws :code:`LNK1102 out of memory` error even though I selected the 64-bit compiler.
    - While Visual Studio targets 64-bit platforms when you select a 64-bit compiler, the Visual Studio toolchain itself will be 32-bit by default. This is a problem when SimpleElastix requires more than 4GB of memory during the linking stage. Switch to the 64-bit toolchain.
    - TIP: To force Visual Studio 2013/2012 to use x64 toolchain, set enviorment variable _IsNativeEnvironment=true in command prompt, and then call the VS2013 exe (i.e "c:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" c:\SimpleElastix\build\SimpleITK-build\SimpleITK.sln).
        OR in Visual Studio 2013:
        
        Edit your .vcxproj file and insert the following after the <Import...Microsoft.Cpp.Defaults line:
        <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
        <PropertyGroup>
            <PreferredToolArchitecture>x64</PreferredToolArchitecture>
        </PropertyGroup>
- Ruby build fails os Mac OS X.
    - The Ruby virtual machine cannot accomodate spaces in paths. If you see a path that contains spaces like :code:`/Applications/Apple Dev Tools/Xcode.app/Contents/Developer`, re-install Xcode Command Line Tools to a place with no spaces in the path.

If you are experiencing a problem that is not describes on this page, you are very welcome to open an issue on Github and we will try to help you. Likewise, if you have found a solution to a problem that is not described on this page, you are very welcome to open a pull request on Github and help us fix the problem for everyone.


Building Manually On Linux
--------------------------
This is not the recommended way of building SimpleElastix but it can be useful if you want to use a system version of ITK, SWIG or your own version of elastix (in this case check out the necessary changes to elastix source code at https://github.com/kaspermarstal/elastix). 

1. Setup the prerequisites
    - `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby python python-dev tcl tcl-dev tk tk-dev`.
2. Install the matching version of SWIG >= 3.0.5
3. Clone ITK from `github.com/InsightSoftwareConsortium/ITK <https://github.com/InsightSoftwareConsortium/ITK>`_.
4. Configure ITK using CMake
    - BUILD_SHARED_LIBS=OFF, ITK_USE_REVIEW=ON, ITK_WRAP_*=OFF
5. Build ITK. Make sure to note the build settings, e.g. Release x64.
6. Clone elastix from `github.com/kaspermarstal/elastix <https://github.com/kaspermarstal/elastix>`_.
7. Configure elastix using CMake
    - BUILD_TESTING=OFF, BUILD_EXECUTABLE=OFF, USE_KNNGraphAlphaMutualInformationMetric=OFF 
    - Set appropriate ELASTIX_IMAGE_2/3/4D_PIXELTYPES and any components that you might require
8. Build elastix
    - Set ITK_DIR to the location of the ITK build directory
9. Clone SimpleElastix from `github.com/kaspermarstal/SimpleElastix <https://github.com/kaspermarstal/SimpleElastix>`_.
10. Configure SimpleElastix using CMake
        - Set ITK_DIR to the location of the ITK build directory
        - Set ELASTIX_DIR to the location of the elastix build directory
11. Build SimpleITK. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.
