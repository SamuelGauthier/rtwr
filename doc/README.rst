-------------
Documentation
-------------

.. sectnum::

.. contents:: Table of contents

This section contains all the relevant resources for real-time water rendering.

`Back to the project readme <../README.rst>`_

Summary
-------

The following survey gives and in-depth analysis of all the method as of 2011.
`A survey of ocean simulation and rendering techniques
<https://arxiv.org/abs/1109.6494>`_, Darles et al. 2011. It divides the works
into three sections which are represented here: `Ocean dynamics simulation in
deep water`_, `Ocean dynamics simulation in shallow water`_, `Realistic ocean
surface rendering and lighting`_.

The `Relevant`_ section contains the important papers and documents used for this
project.

Resources
---------

Ocean dynamics simulation in deep water
+++++++++++++++++++++++++++++++++++++++

+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| Year | Name                                                                                                               | Spatial | Spectral | Wave refraction | GPU | Level-Of-Detail |
+======+====================================================================================================================+=========+==========+=================+=====+=================+
| 1980 | `Schachter <https://doi.org/10.1016/0146-664X(80)90011-8>`_                                                        | X       |          |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 1981 | `Max <https://doi.org/10.1145/965161.806820>`_                                                                     | X       |          |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 1986 | `Fournier et al. <https://doi.org/10.1145/15886.15894>`_                                                           | X       |          |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 1987 | `Mastin et al. <https://doi.org/10.1109/MCG.1987.276961>`_                                                         |         | X        |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 1987 | `Ts’o et al. <https://doi.org/10.1145/35068.35070>`_                                                               | X       |          | X               |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 1999 | `Gonzato et al. 1999 <http://www.labri.fr/perso/gonzato/Articles/Gonzato_Wave_Wscg99.pdf>`_                        | X       |          |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2000 | `Gonzato et al. 2000 <http://www.labri.fr/perso/gonzato/Articles/GONZATO_Wave_JVCS2000.pdf>`_                      | X       |          | X               |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2000 | `Thon et al. a <https://doi.org/10.1109/CGI.2000.852321>`_                                                         | X       | X        |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2001 | `Premoze et al. <http://graphics.stanford.edu/courses/cs348b-competition/cs348b-01/ocean_scenes/ocean.pdf>`_       |         | X        |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2001 | `Tessendorf <http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf>`_                             |         | X        |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2001 | `Schneider et al. <https://pdfs.semanticscholar.org/7ecc/6fe654ddf62bfed6b70b64e676dd9ad9a321.pdf>`_               | X       |          |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2002 | `Gamito et al. <http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.105.1354&rep=rep1&type=pdf>`_             | X       |          | X               |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2002 | `Hinsinger et al. <https://hal.inria.fr/inria-00537490/document>`_                                                 | X       | X        |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2002 | `Isidoro et al. <http://developer.amd.com/wordpress/media/2012/10/ShaderX_OceanWater.pdf>`_                        | X       |          |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2002 | `Thon et al. b <https://pdfs.semanticscholar.org/930c/3df406ca42f695d57818780e2677e1e08c5a.pdf>`_                  | X       | X        |                 |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2003 | `Cieutat et al. <https://www.researchgate.net/publication/228576428_A_general_ocean_waves_model_for_ship_design>`_ |         | X        | X               |     |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2004 | `Finch <https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch01.html>`_                                          | X       |          |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2004 | `Johanson <http://fileadmin.cs.lth.se/graphics/theses/projects/projgrid/>`_                                        | X       |          |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2005 | `Kryachko <https://kineme.net/files/GPU_Gems2_ch18.pdf>`_                                                          | X       |          |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2005 | `Mitchell <https://pdfs.semanticscholar.org/0047/8af7044a7f1350d5ec75ffc7c15b40057051.pdf>`_                       |         | X        |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2006 | `Chiu et al. <https://doi.org/10.1109/ICME.2006.262655>`_                                                          |         | X        |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2006 | `Frechot <https://hal.archives-ouvertes.fr/hal-00307938/document>`_                                                |         | X        |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2006 | `Hu et al. <https://www.microsoft.com/en-us/research/wp-content/uploads/2016/12/rtwave.pdf>`_                      |         | X        |                 | X   | x               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2006 | `Lee et al. a <https://pdfs.semanticscholar.org/ce8a/0dd044be591bcf20c637bc03863f83cc22f4.pdf>`_                   | X       |          |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2006 | `Lee et al. b <https://doi.org/10.1007/11802372_63>`_                                                              | X       |          |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Robine et al. <https://hal.archives-ouvertes.fr/hal-00307929/>`_                                                  |         | X        |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Xin et al. <https://doi.org/10.1007/11941354_71>`_                                                                | X       | X        |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Chen et al. <https://doi.org/10.1007/978-3-540-73011-8_3>`_                                                       | X       |          |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Chou et al. <http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.138.2930&rep=rep1&type=pdf>`_               | X       |          | X               | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Lachman <http://thelachmans.net/Larry%20and%20Jenny/Documents/IMAGE%202007%20Paper%20-%20L.Lachman.pdf>`_         | X       | X        |                 | X   | X               |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Lee et al. <https://pdfs.semanticscholar.org/2856/83eb47f19407aa8030a03cbd88bf821267dd.pdf>`_                     | X       | X        |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+
| 2007 | `Salgado et al. <http://www.lbd.dcc.ufmg.br/bdbcomp/servlet/Trabalho?id=15912>`_                                   | X       |          |                 | X   |                 |
+------+--------------------------------------------------------------------------------------------------------------------+---------+----------+-----------------+-----+-----------------+

Ocean dynamics simulation in shallow water
++++++++++++++++++++++++++++++++++++++++++

Realistic ocean surface rendering and lighting
++++++++++++++++++++++++++++++++++++++++++++++

Relevant
++++++++

- `Large-Scale Interactive Water Simulation With Directional Waves
  <http://dl.acm.org/citation.cfm?id=3098916>`_, Wojtan and
  Jeschke, 2017 (`video  <https://youtu.be/hpuEdXn_M0Q?t=11m11s>`_)
- `Water Technology of Uncharted
  <http://www.gdcvault.com/play/1015309/Water-Technology-of>`_, Ochoa and
  Holder, 2012 (gdc presentation)
- `Sea Surface Visualization in World of Warships
  <http://dl.acm.org/citation.cfm?id=2927409>`_, Kryachko, 2016 (`presentation
  <http://wargaming.com/en/news/siggraph-2016/>`_)
- `Real-time Water Simulation with Wave Particles on the GPU
  <http://old.cescg.org/CESCG-2015/papers/Mikes-Real-time_Water_Simulation_with_Wave_Particles_on_the_GPU.pdf>`_,
  Mikes, 2015
- `Realistic Water Volumes in Real-Time
  <https://hal.inria.fr/inria-00510227/>`_, Galin, 2006
- `Water Flow in Portal 2
  <http://www.valvesoftware.com/publications/2010/siggraph2010_vlachos_waterflow.pdf>`_,
  Vlachos, 2010 (siggraph presentation)
- `Water Wave Packets
  <http://visualcomputing.ist.ac.at/publications/2017/WWP/>`_, Wojtan and
  Jeschke, 2017
- `Terrain and Ocean Rendering with Hardware Tessellation
  <https://doi.org/10.1201/b11325-3>`_, GPU Pro 2, Engel, 2011
- `Rendering Techniques in Call of Juarez: Bound in Blood
  <https://doi.org/10.1201/b10648-44>`_, GPU Pro, Engel, 2010
- `Volumetric Real-Time Water and Foam Rendering
  <https://doi.org/10.1201/b11642-10>`_, GPU Pro 3, Engel, 2012
- `Advected Textures <http://www-evasion.imag.fr/Publications/2003/Ney03/>`_,
  Neyret, 2003
- `Simulating Ocean Water
  <https://www-evasion.imag.fr/Membres/Fabrice.Neyret/NaturalScenes/fluids/water/waves/fluids-nuages/waves/Jonathan/articlesCG/simulating-ocean-water-01.pdf>`_,
  Tessendorf, 1999
- `Wave Particles
  <http://www.ewp.rpi.edu/hartford/~ernesto/S2013/ET/MaterialsforStudents/Ott/Wave%20Energy%20Sources-Ott/Thermodynamics%20of%20waves/wave%20particles.pdf>`_, Yuksel, 2007
- `Geometry clipmaps: Terrain rendering using nested regular grids
  <http://hhoppe.com/proj/geomclipmap/>`_, Hoppe, 2004
- `Terrain rendering using GPU-based geometry clipmaps
  <http://hhoppe.com/proj/gpugcm/>`_, Hopper, 2005
- `Using Vertex Texture Displacement for Realistic Water Rendering
  <https://developer.nvidia.com/gpugems/GPUGems2/gpugems2_chapter18.html>`_, GPU
  Gems 2, 2005
- `Real-time water rendering, Introducing the projected grid concept
  <http://fileadmin.cs.lth.se/graphics/theses/projects/projgrid/>`_, Johanson,
  2004
