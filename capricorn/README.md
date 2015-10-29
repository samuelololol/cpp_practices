PREPARE CPPCMS
==============

* get cppcms from sourceforge: 
[http://downloads.sourceforge.net/project/cppcms/cppcms/1.0.5/cppcms-1.0.5.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fcppcms%2Ffiles%2Fcppcms%2F1.0.5%2F&ts=1446140002&use_mirror=nchc](http://downloads.sourceforge.net/project/cppcms/cppcms/1.0.5/cppcms-1.0.5.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fcppcms%2Ffiles%2Fcppcms%2F1.0.5%2F&ts=1446140002&use_mirror=nchc)

* build cppcms
```
(capricorn)$ tar xjf cppcms-1.0.5.tar.bz2
(capricorn)$ cd cppcms-1.0.5/
(capricorn/cppcms-1.0.5)$ mkdir build
(capricorn/cppcms-1.0.5)$ cd build
(capricorn/cppcms-1.0.5/build)$ cmake -DDISABLE_SHARED=ON -DCMAKE_INSTALL_PREFIX=../../lib ..
(capricorn/cppcms-1.0.5/build)$ make
(capricorn/cppcms-1.0.5/build)$ make test
(capricorn/cppcms-1.0.5/build)$ make install
(capricorn/cppcms-1.0.5/build)$ cd ../..
```

* list lib
```
(capricorn)$ tree lib -L 2

lib
├── bin
│   ├── cppcms_config_find_param
│   ├── cppcms_make_key
│   ├── cppcms_run
│   ├── cppcms_scale
│   └── cppcms_tmpl_cc
├── include
│   ├── booster
│   └── cppcms
└── lib
    ├── libbooster.a
    └── libcppcms.a
```

