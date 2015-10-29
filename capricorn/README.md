PREPARE CPPCMS
==============

* get cppcms from sourceforge: 
[http://downloads.sourceforge.net/project/cppcms/cppcms/1.0.5/cppcms-1.0.5.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fcppcms%2Ffiles%2Fcppcms%2F1.0.5%2F&ts=1446140002&use_mirror=nchc](http://downloads.sourceforge.net/project/cppcms/cppcms/1.0.5/cppcms-1.0.5.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fcppcms%2Ffiles%2Fcppcms%2F1.0.5%2F&ts=1446140002&use_mirror=nchc)

* build cppcms
```
tar xjf cppcms-1.0.5.tar.bz2
cd cppcms-1.0.5/
mkdir build
cd build
cmake -DDISABLE_SHARED=ON -DCMAKE_INSTALL_PREFIX=../../lib ..
make
make test
make install
cd ../..
```

 
