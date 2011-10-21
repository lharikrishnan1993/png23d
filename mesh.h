/*
 * Copyright 2011 Vincent Sanders <vince@kyllikki.org>
 *
 * Licenced under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 *
 * This file is part of png23d. 
 * 
 * mesh routines header.
 */

#ifndef PNG23D_MESH_H
#define PNG23D_MESH_H 1

#define FACETPNT_CNT 16

/* 3d point */
typedef struct pnt {
    float x;
    float y;
    float z;
} pnt;


/* an indexed point */
typedef uint32_t idxpnt;

/** facet
 *
 * A facet is a triangle with its normal 
 */
struct facet {
    pnt n; /**< surface normal */
    pnt v[3]; /**< triangle vertices */
    idxpnt i[3]; /** triangle indexed vertices */
};

/** An indexed vertex within the mesh.
 */
struct vertex {
    struct pnt *p; /**< the location of this vertex */
    unsigned int fcount; /**< the number of facets that use this vertex */
    struct facet *facets[FACETPNT_CNT]; /**< facets that use this vertex */
};

/** A 3d triangle mesh 
 */
struct mesh {
    /* facets */
    struct facet *f; /**< array of facets */
    uint32_t fcount; /**< number of valid facets in the array */
    uint32_t falloc; /**< numer of facets currently allocated */

    /* indexed points */
    struct vertex *p; /**< array of verticies */
    uint32_t pcount; /**< number of valid verticies in the array */
    uint32_t palloc; /**< numer of verticies currently allocated */
    
    uint32_t cubes; /**< number of cubes with at lease one face */
};


/** Convert raster image into triangle mesh
 *
 * consider each pixel in the raster image:
 *   - generate a bitfield indicating on which sides of the pixel faces need to
 *     be covered to generate a convex manifold.
 *   - add triangle facets to list for each face present
 *
 * @todo This could probably be better converted to a marching cubes solution
 *       instead of this simple 2d extrusion of modified marching squares
 *       http://en.wikipedia.org/wiki/Marching_cubes
 */
struct mesh *generate_mesh(bitmap *bm, options *options);

/** free mesh and all resources it holds */
void free_mesh(struct mesh *mesh);

/** update the mesh geometry index representation */
bool index_mesh(struct mesh *mesh);

/** remove uneccessary verticies */
bool simplify_mesh(struct mesh *mesh);

#endif