<h1>Configuration</h1>
<p>Configuration format is this <br>
```
kword arg1...
``` <br>
Necessary config values <br>
```
config default
set CC g++
set CCVer c++20
``` <br>
If there is no default config, a configuration must be specified at runtime
</p>
<p>use the <code>set</code> keyword to set settings, ie c compiler, c/c++ version, target archetecture, etc.</p>

<h1>TODO</h1>
build function <a href="https://c-for-dummies.com/blog/?p=5195">ref</a> // done
make compile function parralel b/c i forgor // done
implement build function
do final compilation in compile function
