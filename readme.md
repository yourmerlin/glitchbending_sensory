# Glitchbending pipeline via heart rate sensor

Using a heartrate sensor to control the output of a glitch-bending pipeline.

What is glitchbending/hex-editing?

Jpeg images and other file formats are made up in binary (01's)
You are able to arrange the binary code in the file format to create unique glitchs/distortion

key things to note:

- the first + last 100~ lines in the binary file is the most important part, because it makes up the file format. do not delete or rearrange because it will def break the file
- you can go into glitch bending doesnt always need to have a proper system
- but it is possible to create a consistent system based on where you are delete/rearranging the bytes in the file
- you can create thresholds to try to restrict the areas of glitch bending but still unique in every image due to your randomness threshold

## Baseline goal:

Create a program the user will take a selfie -> the heart rate sensor is connected to it. It will disingrate based on the live output of the heart rate sensor. Actual bytes will be destroyed or rearranged in the jpeg image.

## Target Goal:

Crete a program where the user uploads an OBJ file(a 3D scan of their body). It will disingrate base on live output of the heart rate sensor. With actual destructive changes in the OBJ file itself(deleting/bending) vertices, planes, and edges.

## Key Problems:

- Lack of documentation of this process
- Previously has been done via existing hex-editor
- No GUI or visual output of this distruction, kind of had to vibe based
- The OBJ file byte makeup is much more unique and difficult to work with compared to a jpeg.

## Previous work/research:

- Created the glitch jpeg pipeline using python
- Have connected heart rate sensor to p5js

## Next steps:

- Connect live sensor input to the pipeline
- Probably fine-tuning the ratio of BPM or heart rate spikes -> byte removal/rearrange

## Next Next steps:

- Research more into OBJ file type
- Figure out the glitch blending on an OBJ file
- Connect the heart rate sensor to the obj glitch bending pipeline

Important links/info:

Info about how OBJ files format works:

_each file is made up of_

- v = vertices
  - 3 dimensional coordinates of the 8 vertices of thast make up each plane
- vn = vertex normal
  - just means the directions it can go on a x/y/x coordinate system
- vt = vertex textures
  - these are points on a the x/y coordinate system to make up your texture
- f = faces
  - it made up of


people to contact:

- glitch arts collective 
- lark vcr 
