/*
 * Student solution for CMU 15-462 Project 2 (MeshEdit)
 *
 * Implemented by ____ on ____.
 *
 */

#include "student_code.h"
#include "mutablePriorityQueue.h"

namespace CMU462
{
   VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
   {
      // TODO This method should split the given edge and return an iterator to the newly inserted vertex.
      // TODO The halfedge of this vertex should point along the edge that was split, rather than the new edges.

			return VertexIter();
	 }

   VertexIter HalfedgeMesh::collapseEdge( EdgeIter e )
   {
      // TODO This method should collapse the given edge and return an iterator to the new vertex created by the collapse.

			return VertexIter();
   }

   EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
   {
      // TODO This method should flip the given edge and return an iterator to the flipped edge.
		
		 //collect elements
		 
		 //Halfedges
		 HalfedgeIter h0 = e0->halfedge();
		 HalfedgeIter h3 = h0->twin();
		 
		 //Faces
		 FaceIter f0 = h0->face();
		 FaceIter f1 = h3->face();

		 //Ignore requests to flip boundary edges
		 if(f0->isBoundary() || f1->isBoundary())
			 return e0;
		 
		 HalfedgeIter h1 = h0->next();
		 HalfedgeIter h2 = h1->next();
		 
	
		 HalfedgeIter h4 = h3->next();
		 HalfedgeIter h5 = h4->next();
		 
		 HalfedgeIter h6 = h1->twin();
		 HalfedgeIter h7 = h2->twin();
		 HalfedgeIter h8 = h4->twin();
		 HalfedgeIter h9 = h5->twin();
		 
		 //Vertices
		 VertexIter v0 = h0->vertex();
		 VertexIter v1 = h3->vertex();
		 VertexIter v2 = h2->vertex();
		 VertexIter v3 = h5->vertex();
		 
		 //Edges
		 //e0 is given
		 EdgeIter e1 = h1->edge();
		 EdgeIter e2 = h2->edge();
		 EdgeIter e3 = h4->edge();
		 EdgeIter e4 = h5->edge();
		 

		 //reassign elements
		 
		 //HalfEdges
		 h0->next() = h1; h0->twin() = h3; h0->vertex() = v3; h0->edge() = e0; h0->face() = f0;
		 
		 h1->next() = h2; h1->twin() = h7; h1->vertex() = v2; h1->edge() = e2; h1->face() = f0;
		 
		 h2->next() = h0; h2->twin() = h8; h2->vertex() = v0; h2->edge() = e3; h2->face() = f0;
		 
		 h3->next() = h4; h3->twin() = h0; h3->vertex() = v2; h3->edge() = e0; h3->face() = f1;
		 
		 h4->next() = h5; h4->twin() = h9; h4->vertex() = v3; h4->edge() = e4; h4->face() = f1;
		 
		 h5->next() = h3; h5->twin() = h6; h5->vertex() = v1; h5->edge() = e1; h5->face() = f1;
		 
			//exterior
		 h6->twin() = h5; h6->vertex() = v2; h6->edge() = e1;
		 
		 h7->twin() = h1; h7->vertex() = v0; h7->edge() = e2;
		 
		 h8->twin() = h2; h8->vertex() = v3; h8->edge() = e3;
		 
		 h9->twin() = h4; h9->vertex() = v1; h9->edge() = e4;
		 
		 //Vertices
		 v0->halfedge() = h2;
		 v1->halfedge() = h5;
		 v2->halfedge() = h3;
		 v3->halfedge() = h0;
		 
		 //Edges
		 e0->halfedge() = h0;
		 e1->halfedge() = h5;
		 e2->halfedge() = h1;
		 e3->halfedge() = h2;
		 e4->halfedge() = h4;
		 
		 //Faces
		 f0->halfedge() = h0;
		 f1->halfedge() = h3;
		 
		 return e0;
   }

   void MeshResampler::upsample( HalfedgeMesh& mesh )
   // This routine should increase the number of triangles in the mesh using Loop subdivision.
   {
      // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
      // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
      // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
      // the new subdivided (fine) mesh, which has more elements to traverse.  We will then assign vertex positions in
      // the new mesh based on the values we computed for the original mesh.


      // TODO Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,
      // TODO and store them in Vertex::newPosition. At this point, we also want to mark each vertex as being
      // TODO a vertex of the original mesh.


      // TODO Next, compute the updated vertex positions associated with edges, and store it in Edge::newPosition.


      // TODO Next, we're going to split every edge in the mesh, in any order.  For future
      // TODO reference, we're also going to store some information about which subdivided
      // TODO edges come from splitting an edge in the original mesh, and which edges are new,
      // TODO by setting the flat Edge::isNew.  Note that in this loop, we only want to iterate
      // TODO over edges of the original mesh---otherwise, we'll end up splitting edges that we
      // TODO just split (and the loop will never end!)


      // TODO Now flip any new edge that connects an old and new vertex.


      // TODO Finally, copy the new vertex positions into final Vertex::position.
   }

   // Given an edge, the constructor for EdgeRecord finds the
   // optimal point associated with the edge's current quadric,
   // and assigns this edge a cost based on how much quadric
   // error is observed at this optimal point.
   EdgeRecord::EdgeRecord( EdgeIter& _edge )
   : edge( _edge )
   {
      // TODO Compute the combined quadric from the edge endpoints.


      // TODO Build the 3x3 linear system whose solution minimizes
      // the quadric error associated with these two endpoints.


      // TODO Use this system to solve for the optimal position, and
      // TODO store it in EdgeRecord::optimalPoint.


      // TODO Also store the cost associated with collapsing this edge
      // TODO in EdgeRecord::Cost.

   }

   void MeshResampler::downsample( HalfedgeMesh& mesh )
   {
      // TODO Compute initial quadrics for each face by simply writing the plane
      // equation for the face in homogeneous coordinates.  These quadrics should
      // be stored in Face::quadric


      // TODO Compute an initial quadric for each vertex as the sum of the quadrics
      // associated with the incident faces, storing it in Vertex::quadric


      // TODO Build a priority queue of edges according to their quadric error cost,
      // TODO i.e., by building an EdgeRecord for each edge and sticking it in the queue.


      // TODO Until we reach the target edge budget, collapse the best edge.  Remember
      // TODO to remove from the queue any edge that touches the collapsing edge BEFORE
      // TODO it gets collapsed, and add back into the queue any edge touching the collapsed
      // TODO vertex AFTER it's been collapsed.  Also remember to assign a quadric to the
      // TODO collapsed vertex, and to pop the collapsed edge off the top of the queue.
   }

   void Vertex::computeCentroid( void )
   {
      // TODO Compute the average position of all neighbors of this vertex, and
      // TODO store it in Vertex::centroid.  This value will be used for resampling.
   }

   Vector3D Vertex::normal( void ) const
   // TODO Returns an approximate unit normal at this vertex, computed by
   // TODO taking the area-weighted average of the normals of neighboring
   // TODO triangles, then normalizing.
   {
      // TODO Compute and return the area-weighted unit normal.
			return Vector3D();
	 }

   void MeshResampler::resample( HalfedgeMesh& mesh )
   {
      // TODO Compute the mean edge length.


      // TODO Repeat the four main steps for 5 or 6 iterations


      // TODO Split edges much longer than the target length (being careful about how the loop is written!)


      // TODO Collapse edges much shorter than the target length.  Here we need to be EXTRA careful about
      // TODO advancing the loop, because many edges may have been destroyed by a collapse (which ones?)

      //
      // TODO Now flip each edge if it improves vertex degree


      // TODO Finally, apply some tangential smoothing to the vertex positions
   }
}
