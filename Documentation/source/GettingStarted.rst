Getting Started
===============

You can download and install SimpleElastix in a few easy steps outlined below. If you thirst for more, consult the `Elastix Manual <http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf>`_ for an elaborate discussion of all components supported by the Elastix API.

SuperBuild On Linux
-------------------
SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. To build SimpleElastix in unix-like environments, clone the repository and invoke the SuperBuild.

::

    git clone https://github.com/kaspermarstal/SimpleElastix
    mkdir build
    cd build
    cmake ../SimpleElastix/SuperBuild
    make -j4

The SuperBuild will download and install dependencies (elastix, ITK and SWIG) and compile SimpleElastix. You will find language packages in the :code:`${BUILD_DIRECTORY}/SimpleITK-build/Wrapping` directory. For example, to install the python module onto your system, navigate to

::

    ${BUILD_DIRECTORY}/SimpleITK-build/Wrapping/PythonPackage

and run the following command:

::

    sudo python setup.py install

Target language dependencies need to be pre-installed. These :code:`apt-get` packages are  

::

    python python-dev monodevelop r-base r-base-dev ruby tcl tcl-dev tk tk-dev

Note that this project takes around an hour to build on a quad-core machine. SimpleElastix has been tried and tested on Ubuntu 14.10 using GCC 4.9.2 and Clang 3.4.0, Mac OSX Yosemite using Apple Clang 600.0.56 and Windows 8.1 using Microsft Visual Studio 2010 C++ compiler.

.. note::

    Be careful not to run out of memory during the build. If you have 8GB or less, it is recommended not build on more than two threads, especially if you are wrapping more than one language. 

SuperBuild On Windows
---------------------

The process is similar to building on Unix except you will be using the CMake GUI to generate a Visual Studio solution and compile the project with Visual Studio.

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


4. Make sure "Release" build type is selected and build the :code:`ALL_BUILD` project. If the "Debug" build type is used instead of "Release" mode, but stick with the debug build type, you will experience a significant performance penalty and may not be able to build language packages that are distributed without development binaries by default (e.g. Python).

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
6. Clone elastix from `github.com/kaspermarstal/elastix <https://github.com/kaspermarstal/SimpleElastix>`_ (or use your own repo).
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