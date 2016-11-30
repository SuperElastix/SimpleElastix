Known Issues
============

- Assigning a parameter in a parameter map list silently fails (e.g. `plist[1]['Transform'] = ['BSplineTransform']`). A workaround is to assign the value directly to the parameter map before adding the map to the list.