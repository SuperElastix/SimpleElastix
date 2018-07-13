Documentation
=============

This is the source code for the project documentation at [simpleelastix.readthedocs.org](http://simpleelastix.readthedocs.org/). If you want to contribute, you can build the documentation locally by installing sphinx: 

```bash
$ sudo apt-get install python-sphinx
```

and run the following make command in `Documentation/`:

```bash
$ make html
```

If you are building docs in a Python environment, you can install packages through pip and run `sphinx-build` directly:

```bash
$ pip install sphinx
$ pip install sphinx_rtd_theme
$ sphinx-build -b html Sphinx build
```

The docs will be generated and the output files will be placed in the `build/html/` directory which can be browsed (locally) with your favorite browser. The documentation can be automatically regenerated whenever a file changes (useful for development) using `sphinx-autobuild`:

```bash
make livehtml
```

To enable this behaviour, install `sphinx-autobuild` with `pip install sphinx-autobuild`.
