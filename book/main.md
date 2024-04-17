\mainpage Overview

\section usage_sec Usage

You can use the following series of commands to locally run this project, which depends on SDL2 and `gettimeofday`.

```shell
git clone https://github.com/ethanuppal/graphics-dev.git
cd graphics-dev
make test
make
./main test1
```

\section mesh_file_sec Mesh File Format

Meshes are supplied via a textual format (which was chosen for ease of debugging).
In the future, a binary format will be developed.

The first line is of the form `"%%zu %%zu\n"`, corresponding to the number of vertices `n` and faces `m`.

The next `n` lines consist of entries of the form `%%fl %%lf %%lf\n`, which are the coordinates of a vertex in the standard basis.
Vertices are indexed starting from zero in the order in which they appear in this list.

The next `m` lines consist of entires of the form `%%zu %%zu %%%zu\n`, which are the indices of vertices in the faces of the mesh.
Meshes are indexed identically to vertices.
The order of vertices must be clockwise for proper normal vector orientation.
