Documentation
=============

This is the source code for project documentation found online at [simpleelastix.readthedocs.org](http://simpleelastix.readthedocs.org/). The documentation can be built locally by installing sphinx 

```bash
$ sudo apt-get pip install python-sphinx
```

and run the following make command in `Documentation/`:

```bash
$ make html
```

The docs will be generated and the output files will be placed in the `build/html/` directory which can be browsed (locally) with your favorite browser.
