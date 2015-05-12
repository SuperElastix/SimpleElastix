.. _GettingStarted:

Getting Started
===============

If you are completely new to SimpleElastix, or even medical image registration, you might not know where to start, or what questions to ask. This document walk you through the basics.

Image Registration
------------------

Medical image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. This is a prerequisite for a wide range of medical image analysis tasks and a key algorithmic component for statistical analysis and machine learning in medical image processing. For example, registration can be used to obtain biological correspondence between images of the brains of mulitiple patients. Image intensities of brain regions can then be compared in an anatomically normalized reference frame. Computer scientists and medical doctors use this information to build computational models of disease processes.

Registration is not limited to brain images of course. Many body parts are rutinely registered and the outputs are used in many different applications ranging from segmentation of anatomical structures to computer-aided diagnosis, monitoring of disease progression, surgical intervention and treatment planning. 

Image registration is such a fundamental algorithmic building block that the field continues to enourmous amounts of research. The surge in development and availability of scanners, computing power and potential to save time, money and lives makes it an increasingly relevant field of study. In the future, patient-specific computational models may deliver the next paradigm shift in modern medical diagnosis and treatment planning.

While this is all very inspiring, it is not always easy for us mortals to get our hands on decent implementations of state-of-the-art methods. They all say we should stand on the shoulders of giants, but how do we get up there? One possibility is to use SimpleElastix.

SimpleElastix
-------------

There are as many registration methods as there are people working in the field. Some methods have proved themselves to be more useful than others and have stood the test of time. Elastix is a collection of some of these algorithms and a significant amount of research has focused on making them robust, fast and easy to use through a simple command line interface. SimpleElastix takes this idea a step further and makes elastix available in a wide variety of scripting languages. Follow the steps below to install elastix and read the rest of the documentation for an overview of methods implement in SimpleElastix and useful, real-world examples. 

.. _Linux:

SuperBuild On Linux
-------------------

SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. To build SimpleElastix in unix-like environments, clone the repository and invoke the SuperBuild.

::

    git clone https://github.com/kaspermarstal/SimpleElastix
    mkdir build
    cd build
    cmake ../SimpleElastix/SuperBuild
    make -j4

The SuperBuild will download and install dependencies (elastix, ITK and SWIG) and compile SimpleElastix. You will find language packages in the :code:`${BUILD_DIRECTORY}/SimpleITK-build/Wrapping` directory. For example, to install the python module onto your system, compile the project, navigate to

::

    ${BUILD_DIRECTORY}/SimpleITK-build/Wrapping/PythonPackage

and run the following command:

::

    sudo python setup.py install

Target language dependencies need to be pre-installed. The :code:`apt-get` packages are  

::

    python python-dev monodevelop r-base r-base-dev ruby tcl tcl-dev tk tk-dev

Note that this project takes around an hour to build on a quad-core machine. SimpleElastix has been tried and tested on Ubuntu 14.10 using GCC 4.9.2 and Clang 3.4.0, Mac OSX Yosemite using Apple Clang 600.0.56 and Windows 8.1 using Microsft Visual Studio 2010 C++ compiler.

.. note::

    Be careful not to run out of memory during the build. If you have 8GB or less, it is recommended not build on more than two threads, especially if you are wrapping multiple languages. 

.. _MacOSX:

SuperBuild On Mac OS X
----------------------

To download, compile and install SimpleElastix follow the Linux instructions above. Target-language dependencies have to be installed separately using e.g. `Macports <https://www.macports.org/>`_ or `Homebrew <http://http://brew.sh/>`_. Mac OS X comes with Python and Tcl already installed. 

.. _Windows:

SuperBuild On Windows
---------------------

Building SimpleElastix on windows is similar the building on Unix except you will be using the CMake GUI to generate a Visual Studio solution and Visual Studio to compile the project.

1. Generate build files.
    - Download and install `CMake GUI <http://www.cmake.org/download/>`_.
    - :code:`git clone https://github.com/kaspermarstal/SimpleElastix` into a source folder of your choice.
    - Point the source directory to the :code:`SimpleElastix/SuperBuild` folder inside the source directory.
    - Point the build directory to a clean directory. Note that Visual Studio may complain during the build if the path is longer than 50 characters.
    - You may want to to speed up compilation by deselecting Examples, Testing and any wrapped languages you don't need. It takes 1+ hour to build the full project on a quad-core machine. 

    .. figure:: _static/WindowsInstallationConfigureCMake.png
        :align: center
        :figwidth: 90%
        :width: 90% 

        Figure 3: Configure CMake.


2. Press configure, select your desired compiler and click Finish. CMake will choose a compiler for you if you just select the default option.

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


4. Make sure "Release" build type is selected and build the :code:`ALL_BUILD` project. If the "Debug" build type is used instead of "Release" mode, you will experience a significant performance penalty and may not be able to build language packages that are distributed without development binaries by default.

    .. figure:: _static/WindowsInstallationBuildSolution.png
        :align: center
        :figwidth: 90%
        :width: 90% 

        Figure 6: Right-click on :code:`ALL_BUILD` and click :code:`Build`.


Building Manually On Linux
--------------------------
This is not the recommended way of building SimpleElastix but it can be useful if you want to use a system version of ITK, SWIG or your own version of elastix (in this case check out the necessary changes to elastix source code at https://github.com/kaspermarstal/elastix). 

1. Setup the prerequisites
    - `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby python python-dev tcl tcl-dev tk tk-dev`.
2. Install the matching version of SWIG >= 2.0.12
3. Clone ITK from `github.com/InsightSoftwareConsortium/ITK <https://github.com/InsightSoftwareConsortium/ITK>`_.
4. Configure ITK using CMake
    - BUILD_EXAMPLES=OFF, BUILD_TESTING=OFF, BUILD_SHARED_LIBS=OFF, ITK_USE_REVIEW=ON, ITK_WRAP_*=OFF
5. Build ITK. Make sure to note the build settings, e.g. Release x64.
6. Clone elastix from `github.com/kaspermarstal/elastix <https://github.com/kaspermarstal/SimpleElastix>`_.
7. Configure elastix using CMake
    - BUILD_TESTING=OFF, BUILD_EXECUTABLE=OFF, BUILD_SHARED_LIBRARIES=ON, USE_KNNGraphAlphaMutualInformationMetric=OFF 
    - Set appropriate ELASTIX_IMAGE_2/3/4D_PIXELTYPES and any components that you might require
8. Build elastix
    - Set ITK_DIR to the location of the ITK build directory
9. Clone SimpleITK from `github.com/SimpleITK/SimpleITK <https://github.com/SimpleITK/SimpleITK>`_.
10. Configure SimpleITK using CMake
        - Set ITK_DIR to the location of the ITK build directory
        - Set ELASTIX_DIR to the location of the elastix build directory
11. Build SimpleITK. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.