# 2D Graphics Editor (C)

A simple console-based 2D graphics editor written in C.

## Features

* Add objects:

  * Line
  * Rectangle
  * Triangle
  * Circle
* Delete existing objects
* Modify object properties
* List all objects
* Display the canvas

## Compilation

```bash
gcc graphics_editor.c -o editor -lm
```

## Run

```bash
./editor
```

## Menu

1. Add object
2. Delete object
3. Modify object
4. List objects
5. Display canvas
6. Exit

## Notes

* Canvas size: 40 rows × 80 columns
* Maximum objects: 10
* Objects are rendered using `*` characters
* Empty canvas cells are represented by `_`