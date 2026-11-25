# Goal

Use heart-rate sensor data (output) to control a glitch-bending pipeline to OBJ files

- Using a 3D scan of my body as the OBJ file I am working with
  I want to capture how stress & anxiety can effect our body overtime. Through using a heart-rate sensor to control a custom glitch-bending pipeline to a (OBJ file) 3D scan of myself

# Why?

We understand how stress and anxiety can effect our body overtime, but we don't always see that impact automatically.

I wanted to capture the permanent destruction of how stress can effect our body. Through this process of permanent deletion and manipulation of the data itself using your own body data to control it.

# What is Glitch/Data Bending?

A form of manipulation of a digital file through deleting or rearranging binary data, to create cool glitchy, weird and unpredictable affects.

This process isn't the same as a filter you add in photoshop, The changes are much more permanent and directly impact/change your file.

I have made my own automatic glitch-bending pipeline on jpeg images using python, but I wanted to see if its possible to glitch-bend on OBJ files
Unfortunately there is little-to no proper documentation of this process. It has been done before, but using outdated software programs or doing it by hand manually or through blender--there is no auto-mated way. There is no current open-source pipeline to automate the process(specifically for obj files)

Little to no proper documentation of this process
has been done in outdated software programs, doing it manually by hand or using blender. there is no "auto-mated" way

If glitch-bending pipelines exist already, why can't you use the same pipeline for OBJ files?
OBJ files are structured differently in the file, compared to jpegs or other 2Dimensional file formats.

# Exploration of computer graphics (fun!)

obj files store data that represents 3D geometry
it stores

- vertices = the position of each geometric vertex (x/y/z/[w])
- vertex texture = the UV position of each vertex texture (u/[v/w])
- vertex normal = the direction of where the vertices is pointing to based on a coordinate system(x/y/z)

- the faces = that make up each polygon based on the list of vertices, vertices texture and vertex normal

OBJ files are constructed of x/y/z coordinates to form a triangle, these triangles form a polygon mesh(3D model).
Obj files are special because it also contains data location of the UV map in the file itself.
UV mapping is just a way to add texture to a 3D model.

The OBJ file does not store the actual texture itself rather stores the instructions on where the texture should go on the 3D model.

A polygon mesh is a collection of vertices, edges and faces.

In the OBJ file, it stores location information to

In the file, it has x/y/z coordinates for each type of element.

# other

To be able to visualize my stress & anxiety in a poetic n potent way.
