=========================
Real-time water rendering
=========================

.. image:: https://img.shields.io/badge/lang-C%2B%2B-blue.svg
        :target: https://github.com/SamuelGauthier/rtwr.git

.. image:: https://img.shields.io/badge/OpenGL-4.0-brightgreen.svg
        :target: https://github.com/SamuelGauthier/rtwr.git

.. image:: https://img.shields.io/badge/glsl-4.0-green.svg
        :target: https://github.com/SamuelGauthier/rtwr.git


.. image:: /doc/report/figures/application_5.png
   :align: center
   :width: 500pt

.. sectnum::

.. contents:: Table of contents

This project is a research into different methods to render in real-time
realisic large bodies of water. The chosen implementation is based on the
*Gerstner Waves* model. The report can be accessed further below in the
`Documentation`_ section.

**Important note: The code (shader and C++) is "research code" and is by no
means optimized.**

Dependencies and Requirements
-----------------------------

- Compiler supporting C++14

- Cmake >= 3.9

- Device supporting OpenGL 4.0

- GLEW

- GLFW

If `GLEW` and `GLFW` have been installed in a proper default location, cmake
automatically finds them on your system.

Compilation and Usage
---------------------

.. code:: bash

    $ git clone https://github.com/SamuelGauthier/rtwr.git
    $ cd rtwr
    $ mkdir build; cd build
    $ cmake -G "Unix Makefiles" ..; make
    $ ../bin/rtwr

- Zoom: scroll wheel

- Pan: right mouse button and drag

- Rotate: left mouse button and drag

Documentation
-------------

The report can be built using LaTeX in the folder ``doc/report`` ( `compiled pdf
version <doc/report/project2_report.pdf>`_, approx. 4000 words). `Slides of the
presentation <doc/presentation/project2.pdf>`_. A list of relevant papers can be
found `here <doc/README.rst>`_.

Screenshots
-----------


.. image:: /doc/report/figures/application_1.png
   :width: 45%
.. image:: /doc/report/figures/application_2.png
   :width: 45%

.. image:: /doc/report/figures/application_3.png
   :width: 45%
.. image:: /doc/report/figures/application_4.png
   :width: 45%

License
-------

See the `LICENSE <./LICENSE>`_ file for license rights and limitations
(Apache License 2.0).


Credits
-------

**Skybox:**

1. ``empty-sky`` from `custommapmakers.org
   <http://custommapmakers.org/skyboxes.php>`_
2. ``perea_beach, saint_lazarus_church, san_francisco, tenerife`` from `Humus
   <http://www.humus.name/index.php?page=Textures>`_ (licensed under `CC BY 3.0
   <https://creativecommons.org/licenses/by/3.0/>`_)

**Normal Map:** Visceral from `polycount <https://goo.gl/MnzXUd>`_
