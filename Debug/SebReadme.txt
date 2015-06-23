All these prototypes were based on on tutorial of NeHe_gamedev_net (OpenGL Lesson 05:  Solid Objects), by Jeff Molofee ( NeHe )

Proto 006: 
-Loads 2 3D files (each one containing the same objects, but modified) of format .pov
-Places the first file at position -1 in the fourth dimension.
-Places the second file at position +1 in the fourth dimension.
-Generates the 4D object composed of 4d-Triangles using the 2 files
-Permits the operator to move in the 4 dimension
  User-Interface is:


                Y++            
          .->    ^    <-.      
         /       |       \     
        |  +-----------+  |    
           | A | S | D |       
           |-----------|       
    X-- <- | Z | X | C | -> X++
           +-----------+       
                 |             
                 v             
                Y--            


                Z++            
          .->    ^    <-.      
         /       |       \     
        |  +-----------+  |    
           | F | G | H |       
           |-----------|       
    X-- <- | V | B | N | -> X++
           +-----------+       
                 |             
                 v             
                Z--            


             4 th Dim  ++      
          .->    ^    <-.      
         /       |       \     
        |  +-----------+  |    
           | 1 | 2 | 3 |       
           |-----------|       
    X-- <- | Q | W | E | -> X++
           +-----------+       
                 |             
                 v             
             4 th Dim --       


- And there a countinous oscillation in the 4 th Dimension.

- Note: there are still strange problem with rotation, the object becomes flat!

