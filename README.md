Numerical Geometry Project
==========================

AUTHORS : Van Geersdaele Arthur - Vekemans Astrid
DATE :  21/12/21


IMPORTANT: This version is implemented for WINDOWS OS.
The Sleep() function used in main.c has to be replaced the the LINUX equivalent (written in comment below the WINDOWS command) before running. 

All command lines to be modified (2) are tagged with "// (FOR WINDOWS)" and "// (FOR LINUX)", a simple ctrl-f can make it very quick.



  _____   _   _                                                        _                   
 |  ___| (_) | |   ___   ___      ___   __   __   ___   _ __  __   __ (_)   ___  __      __
 | |_    | | | |  / _ \ / __|    / _ \  \ \ / /  / _ \ | '__| \ \ / / | |  / _ \ \ \ /\ / /
 |  _|   | | | | |  __/ \__ \   | (_) |  \ V /  |  __/ | |     \ V /  | | |  __/  \ V  V / 
 |_|     |_| |_|  \___| |___/    \___/    \_/    \___| |_|      \_/   |_|  \___|   \_/\_/  
                                                                                           
- geometry.c/.h : contains the structure of Points/Segments/Segment-linked-list as needed for the algorithm + associated functions

- point_list.c/.h : contains the Points (geometry.h) linked list structure + associated functions

- point_tree.c/.h : contains the binary tree structure capable to handle the Point structure defined in geometry.h + associated functions

- segment_tree.c/.h : contains the binary tree structure capable to hande the Segment structure defined in geometry.h + associated functions

- inputs.c/.h (external) : used to create a random array of coordinates

- sweepline.c/.h : hold all the algorithmic implementation (as described in the reference book, using all the structures predefined) + associated functions

- main.c : contains all the instructions for displaying images or animations, and calls to the algorithm from sweepline.c



  _   _                        _                                          
 | | | |   ___   __      __   | |_    ___      _   _   ___    ___     _   
 | |_| |  / _ \  \ \ /\ / /   | __|  / _ \    | | | | / __|  / _ \   (_)  
 |  _  | | (_) |  \ V  V /    | |_  | (_) |   | |_| | \__ \ |  __/    _   
 |_| |_|  \___/    \_/\_/      \__|  \___/     \__,_| |___/  \___|   (_) (every parameter is correctly commented in main.c)


Before executing the main program (in main.c), have a look to the different parameters : 

- PRESETS : Just choose between the different proposed presets or customize each parameters described below

- (bool) image : # use image to display huge amount of points (from 100 to 10000)
	* Run the Sweepline Algorithm for segment intersections 
	* Print the performances in the console (nbr of segments given, nbr of intersections found and execution time)
	* display the final 2D configuration (segments and their intersection points)
	! image will always override animation 

- (bool) animation :
	* Run the Sweepline Algorithm for segment intersections 
	* display the progressive 2D configuration (segments and their intersection points) point by point
	* Highlight the segments that are considered by the algorithm at instant t

  [IF image AND animation ARE NOT SET TO TRUE, THE PROGRAM RUN ITS FASTEST VERSION AND SIMPLY PRINT THE RESULTS IN THE CONSOLE]

- (bool) on_click : 
	* disable the automatic animation, you decide when to go to the next point by left-clicking

- (float) dt : 
	* define the minimal waiting time before window update during automatic animation in milliseconds

- (bool) fullscreen : 
	* decide if the image or animation is fullscreen or not (automatic animation will always be fullscreened)

- (GLsizei) nPoints :
	* number of points needed to define the segments you want to be analysed

- (GLfloat[nPoints][2]) segment_coord : 
	* array of points coordinates that define segments 2 by 2.


                 _                      
   ___    ___   | |   ___    _ __   ___ 
  / __|  / _ \  | |  / _ \  | '__| / __|
 | (__  | (_) | | | | (_) | | |    \__ \
  \___|  \___/  |_|  \___/  |_|    |___/  (useful to now during animation)
                                                

- YELLOW : considered point on the sweepline and intersections already found 
- BLUE   : sweepline representation

- GREY & CONTOURED : Segments that are considered by the algorithm at time t.

- RED   : Left Most Segment and Left Neighbour of the considered point 
- GREEN : Right Most Segment and Right Neighbour of the considered point 
  (colors overlap with transparency in case of identicity, resulting in a light brown)

- VIOLET: 
