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

For each of the entries in the table, the link points either directly to the
pdf file of the paper or to the online resource if none was found.

Ocean dynamics simulation in deep water
+++++++++++++++++++++++++++++++++++++++

==== =========================== ======= ======== =============== === ================
Author information                     Model            Implementation
-------------------------------- ---------------- ------------------------------------
Year     Name                    Spatial Spectral Wave refraction GPU Level-Of-Details
==== =========================== ======= ======== =============== === ================
1980 Schachter [Sch80_]
1981 Max [Max81_]
1986 Fournier et al. [FR86_]
1987 Mastin et al. [MWM87_]
1987 Ts’o et al. [TB87_]
1999 Gonzato et al. [GS99_]
2000 Gonzato et al. [GS00_]
2000 Thon et al. [TDG00_]
2001 Premoze et al. [PA00_]
2001 Tessendorf [Tes01_]
2001 Schneider et al. [SW01_]
2002 Gamito et al. [GM02_]
2002 Hinsinger et al. [HNC02_]
2002 Isidoro et al. [IVB02_]
2002 Thon et al. [TG02_]
2003 Cieutat et al. [CGG03_]
2004 Finch [Fin04_]
2004 Johanson [Joh04_]
2005 Kryachko [Kry05_]
2005 Mitchell [Mit05_]
2006 Chiu et al. [CC06_]
2006 Frechot [Fre06_]
2006 Hu et al. [HVT06_]
2006 Lee et al. [LGL06a_]
2006 Lee et al. [LGL06b_]
2006 Robine et al. [RF06_]
2006 Xin et al. [XFS06_]
2007 Chen et al. [CLW07_]
2007 Chou et al. [CF07_]
2007 Lachman [Lac07_]
2007 Lee et al. [LBR07_]
2007 Salgado et al. [SC07_]
==== =========================== ======= ======== =============== === ================

.. _Sch80: https://doi.org/10.1016/0146-664X(80)90011-8
.. _Max81: https://doi.org/10.1145/965161.806820
.. _FR86: https://doi.org/10.1145/15886.15894
.. _MWM87: https://doi.org/10.1109/MCG.1987.276961
.. _TB87: https://doi.org/10.1145/35068.35070
.. _GS99: http://www.labri.fr/perso/gonzato/Articles/Gonzato_Wave_Wscg99.pdf
.. _GS00: http://www.labri.fr/perso/gonzato/Articles/GONZATO_Wave_JVCS2000.pdf
.. _TDG00: https://doi.org/10.1109/CGI.2000.852321
.. _PA00: http://graphics.stanford.edu/courses/cs348b-competition/cs348b-01/ocean_scenes/ocean.pdf
.. _Tes01: http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf
.. _SW01: https://pdfs.semanticscholar.org/7ecc/6fe654ddf62bfed6b70b64e676dd9ad9a321.pdf
.. _GM02: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.105.1354&rep=rep1&type=pdf
.. _HNC02: https://hal.inria.fr/inria-00537490/document
.. _IVB02: http://developer.amd.com/wordpress/media/2012/10/ShaderX_OceanWater.pdf
.. _TG02: https://pdfs.semanticscholar.org/930c/3df406ca42f695d57818780e2677e1e08c5a.pdf
.. _CGG03: https://www.researchgate.net/publication/228576428_A_general_ocean_waves_model_for_ship_design
.. _Fin04: https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch01.html
.. _Joh04: http://fileadmin.cs.lth.se/graphics/theses/projects/projgrid/
.. _Kry05: https://kineme.net/files/GPU_Gems2_ch18.pdf
.. _Mit05: https://pdfs.semanticscholar.org/0047/8af7044a7f1350d5ec75ffc7c15b40057051.pdf
.. _CC06: https://doi.org/10.1109/ICME.2006.262655
.. _Fre06: https://hal.archives-ouvertes.fr/hal-00307938/document
.. _HVT06: https://www.microsoft.com/en-us/research/wp-content/uploads/2016/12/rtwave.pdf
.. _LGL06a: https://pdfs.semanticscholar.org/ce8a/0dd044be591bcf20c637bc03863f83cc22f4.pdf
.. _LGL06b: https://doi.org/10.1007/11802372_63
.. _RF06: https://hal.archives-ouvertes.fr/hal-00307929/
.. _XFS06: https://doi.org/10.1007/11941354_71
.. _CLW07: https://doi.org/10.1007/978-3-540-73011-8_3
.. _CF07: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.138.2930&rep=rep1&type=pdf
.. _Lac07: http://thelachmans.net/Larry%20and%20Jenny/Documents/IMAGE%202007%20Paper%20-%20L.Lachman.pdf
.. _LBR07: https://pdfs.semanticscholar.org/2856/83eb47f19407aa8030a03cbd88bf821267dd.pdf
.. _SC07: http://www.lbd.dcc.ufmg.br/bdbcomp/servlet/Trabalho?id=15912


Ocean dynamics simulation in shallow water
++++++++++++++++++++++++++++++++++++++++++

==== =========================== ======== ========== ======== ======= ================= ===
Author information                     Model            Resolution         Implementation
-------------------------------- ------------------- ---------------- ---------------------
Year     Name                    Eulerian Lagrangian 2D-based Full 3D Incompressibility LOD
==== =========================== ======== ========== ======== ======= ================= ===
1989 Miller et al. [MP89_]                    X                  X
1989 Terzopoulos et al. [TPF89_]              X                  X
1990 Kass et al. [KM90_]            X                    X
1991 Tonnesen [Ton91_]                        X                  X
1995 Stam et al. [SF95_]                      X                  X
1995 Chen et al. [CL95_]            X                    X
1995 O’Brien et al. [OH95_]         X         X          X
1996 Desbrun et al. [DC96_]                   X                  X
1996 Foster et al. [FM96_]          X                            X
1997 Foster et al. [FM97_]          X                            X
1999 Desbrun et al. [DC99_]                   X                  X                       X
1999 Stora et al. [SAC99_]                    X                  X
2001 Foster et al. [FF01_]          X                            X
2002 Enright et al. [EMF02_]        X                            X             X
2003 Premoze et al. [PTB03_]                  X                  X             X
2003 Muller et al. [MCG03_]                   X                  X
2003 Takahashi et al. [TFK03_]      X         X                  X             X
2004 Carlson et al. [CMT04_]        X                            X             X
2004 Greenwood et al. [GH04_]       X         X                  X
2004 Losasso et al. [LGF04_]        X                            X             X         X
2004 Mihalef et al. [MMS04_]        X                    X                     X
2005 Clavet et al. [CBP05_]                   X                  X
2005 Muller et al. [MSKG05_]                  X                  X
2005 Wang et al. [WMT05_]           X                            X             X
2006 Kim et al. [KCC06_]            X         X                  X                       X
2006 Losasso et al. [LSSF06_]       X                            X             X
2006 Thurey et al. [TRS06_]         X         X          X       X             X
2006 Wang et al. [WZC06_]                     X          X       X             X
2006 Zheng et al. [ZYP06_]          X         X                  X             X
2007 Adams et al. [APKG07_]                   X                  X                       X
2007 Becker et al. [BT07_]                    X                  X             X
2007 Thurey et al. [TMFSG07_]       X                    X       X
2007 Thurey et al. [TSS07_]         X         X          X                     X
2007 Yuksel et al. [YHK07_]         X         X          X       X
2008 Hong et al. [HHK08_]                     X                  X                       X
2008 Losasso et al. [LTKF08_]       X         X                  X             X
2009 Solenthaler et al. [SP09_]               X                  X             X
2009 Yan et al. [YWH09_]                      X                  X                       X
==== =========================== ======== ========== ======== ======= ================= ===

.. _MP89: https://doi.org/10.1016/0097-8493(89)90078-2
.. _TPF89: http://onlinelibrary.wiley.com/doi/10.1002/vis.4340020208/full
.. _KM90: http://www.heathershrewsbury.com/dreu2010/wp-content/uploads/2010/07/RapidStableFluidDynamicsForComputerGraphics.pdf
.. _Ton91: https://pdfs.semanticscholar.org/b315/fba6b708a67a77bce1c13e3cf77c57f45524.pdf
.. _SF95: http://www.naturewizard.at/papers/fire%20-%20p129-stam.pdf
.. _CL95: https://doi.org/10.1006/gmip.1995.1012
.. _OH95: https://smartech.gatech.edu/bitstream/handle/1853/3599/94-32.pdf
.. _DC96: https://hal.inria.fr/inria-00537534/document
.. _FM96: https://people.cs.clemson.edu/~dhouse/courses/817/papers/fostermetaxas97.pdf
.. _FM97: https://pdfs.semanticscholar.org/6b4b/69df23204c9400d8af18730246128ccbfd33.pdf
.. _DC99: https://hal.archives-ouvertes.fr/docs/00/07/28/29/PDF/RR-3829.pdf
.. _SAC99: https://hal.inria.fr/docs/00/51/00/66/PDF/gi99.pdf
.. _FF01: http://www.dtic.mil/get-tr-doc/pdf?AD=ADA479314
.. _EMF02: http://kucg.korea.ac.kr/seminar/2002/src/pa-02-43.pdf
.. _PTB03: https://pdfs.semanticscholar.org/8ae8/ad7bd4dd737b9c029b5d484ee79116b23088.pdf
.. _MCG03: https://www.researchgate.net/profile/Matthias_Mueller14/publication/231514052_Particle-Based_Fluid_Simulation_for_Interactive_Applications/links/5538d9f20cf2239f4e79c206.pdf
.. _TFK03: http://onlinelibrary.wiley.com/doi/10.1111/1467-8659.00686/full
.. _CMT04: http://silviojemma.com/public/papers/fluids/rigid%20fluid%20animating%20the%20interplay%20between%20rigid%20and%20fluids.pdf
.. _GH04: https://www.researchgate.net/profile/Donald_House/publication/234827643_Better_with_bubbles_Enhancing_the_visual_realism_of_simulated_fluid/links/00b7d53b573ad8a0c5000000.pdf
.. _LGF04: https://pdfs.semanticscholar.org/8362/6cf6017537a22df5a7f3952819a9595cc644.pdf
.. _MMS04: https://www.researchgate.net/profile/Dimitris_Metaxas/publication/234802413_Animation_and_Control_of_Breaking_Waves/links/0c960530e5df1217a2000000/Animation-and-Control-of-Breaking-Waves.pdf
.. _CBP05: https://www.researchgate.net/profile/Pierre_Poulin/publication/220789321_Particle-based_viscoelastic_fluid_simulation/links/0c96051824f22359e2000000.pdf
.. _MSKG05: https://graphics.ethz.ch/Downloads/Publications/Papers/2005/Mue05a/p_Mue05a.pdf
.. _WMT05: http://www.unc.edu/~mucha/Reprints/droplet.pdf
.. _KCC06: http://kucg.korea.ac.kr/Seminar/2007/src/PA-07-21.pdf
.. _LSSF06: https://www.researchgate.net/profile/Andrew_Selle/publication/220184456_Multiple_interacting_liquids/links/551f262f0cf2a2d9e140485a.pdf
.. _TRS06: http://www.thuerey.de/ntoken/download/nthuerey_060131_swscoupling.pdf
.. _WZC06: http://www-evasion.inrialpes.fr/Membres/Fabrice.Neyret/images/fluids-nuages/waves/Jonathan/articlesCG/Rendering%20Of%20Breaking%20Waves%20using%20MPS%20method.pdf
.. _ZYP06: https://hal.inria.fr/inria-00517956/document
.. _APKG07: https://infoscience.epfl.ch/record/149309/files/adams_2007_ASP.pdf
.. _BT07: http://dl.acm.org/citation.cfm?id=1272719
.. _TMFSG07: https://pdfs.semanticscholar.org/0f24/ba73b791b8a4479143c2dc071669474a6357.pdf
.. _TSS07: https://www-evasion.imag.fr/Membres/Fabrice.Neyret/NaturalScenes/fluids/water/waves/fluids-nuages/waves/Jonathan/articlesCG/real-time-simulations-of-bubbles-and-foam-within-a-shallow-water-framework-07.pdf
.. _YHK07: http://www.ewp.rpi.edu/hartford/~ernesto/S2013/ET/MaterialsforStudents/Ott/Wave%20Energy%20Sources-Ott/Thermodynamics%20of%20waves/wave%20particles.pdf
.. _HHK08: https://www.researchgate.net/profile/Donald_House/publication/220067042_Adaptive_Particles_for_Incompressible_Fluid_Simulation_Technical_Report_tamu-cs-tr_2007-7-2/links/0046351ae0c6ee6032000000/Adaptive-Particles-for-Incompressible-Fluid-Simulation-Technical-Report-tamu-cs-tr-2007-7-2.pdf
.. _LTKF08: http://ai2-s2-pdfs.s3.amazonaws.com/5bc0/7c8926986068e4f130f94cad41f2543a9fb9.pdf
.. _SP09: https://www.researchgate.net/profile/Barbara_Solenthaler/publication/228656950_Predictive-corrective_incompressible_SPH/links/0a85e5321a4ac4cda1000000.pdf
.. _YWH09: https://sites.google.com/site/xichenstephen/File-Download/Real-timefluidsimulationwithadaptiveSPH%28Official%29.pdf



Realistic ocean surface rendering and lighting
++++++++++++++++++++++++++++++++++++++++++++++

==== =========================== ========= ========= =========== ==============
Author information                  Foam and Spray    Light-water intercations 
-------------------------------- ------------------- --------------------------
Year     Name                    Empirical Particles First order Multiple order
==== =========================== ========= ========= =========== ==============
1986 Arvo [Arv86_]                                                     X
1986 Peachey [Pea86_]                          X
1993 Nishita et al. [NSTN93_]                             X
2000 Gonzato et al. [GS00_]                               X
2000 Premoze et al. [PA00_]         X                                  X
2001 Iwasaki et al. [IDN01_]                                           X
2001 Jensen [Jen01_]                                                   X
2001 Jensen et al. [JG01_]          X          X          X
2001 Schneider et al. [SW01_]                             X
2001 Tessendorf [Tes01_]                                  X
2003 Belyaev [Bel03_]                                     X
2003 Iwasaki et al. [IDN03_]                                           X
2003 Jeschke et al. [JBS03_]        X          X
2004 Cerezo et al. [CS04_]                                             X
2004 Holmberg et al. [HW04_]                   X
2006 Chiu et al. [CC06_]                       X
2006 Baboud et al. [BD06_]                                X
2006 Hu et al. [HVT06_]                                   X
2006 Wang et al. [WZC06_]                      X
2007 Darles et al. [DCG07_]         X                     X
2008 Gutierrez et al. [GSAM08_]                                        X
2010 Bruneton et al. [BNH10_]                             X
==== =========================== ========= ========= =========== ==============

.. _Arv86:             
.. _Pea86:          
.. _NSTN93:  
.. _IDN01:   
.. _Jen01:           
.. _JG01:     
.. _Bel03:          
.. _IDN03:   
.. _JBS03:   
.. _CS04:     
.. _HW04:   
.. _BD06:     
.. _DCG07:    
.. _GSAM08:
.. _BNH10:


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
