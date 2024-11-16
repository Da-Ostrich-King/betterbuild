# Build instructions
run make to build this, to build your own project, keep reading

# Configuration

The configuration file must be named ```BuildFile``` or be specified at runtime
The configuration file has a simple syntax of ```keyword arg1 arg2 # comment```

Use the ```set``` keyword to set settings, ie c compiler, target archetecture, etc. it is basically search and replace on the file, the below mentioned are "special" set values that are used in directly by the build system

- CC # compiler

The CC must be a compiler that supports standard CC arguments like "-o name" like gcc or clang

Use the arg keyward to specify compilation arguments
    arg -g -d debug -lSomeLib -LsomeDir -IsomeDir # etc

Sample configuration:

    config default
        set CC g++
        prepare cp -r resources/ build/default/resources # runs arbitrary command
        bin name
            arg -Iinclude -d _debug -g --std=c++20 # setting includedir and defining debug, adding debug symbols, cxx version

# NOTES 
Cannot be run as root unless the special "install" config is selected or configuration contains the substring "install" like "installHeaders".

Will not ever support windows unless someone else does it, there is no "fork()" or "exec()" or other unix syscalls.
May support Macos but I don't have a Mac for testing.




# TODO
- [x] Make compile function parralel b/c i forgor
- [x] Do final compilation in compile function
- [x] File tokenization
- [ ] Implement build function with parsing and all that bullshit
