/*
 * Student solution for CMU 15-462 Project 2 (MeshEdit)
 *
 * Implemented by Yang Zhou.
 * Last Modified: Mar 11.
 *
 */

#include "student_code.h"
#include "mutablePriorityQueue.h"

#include <unordered_set>
#include <algorithm>

namespace std
{
	template<> struct hash<EdgeIter>
	{
		std::size_t operator()(const EdgeIter& e) const
		{
			return std::hash<CMU462::Edge*>()(&*e);
		}
	};
}

namespace CMU462
{
   VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
   {
      // TODO This method should split the given edge and return an iterator to the newly inserted vertex.
      // TODO The halfedge of this vertex should point along the edge that was split, rather than the new edges.
		 
		 //1. collect elements
		 //Halfedges
		 HalfedgeIter h0 = e0->halfedge();
		 HalfedgeIter h3 = h0->twin();
		 
		 //Faces
		 FaceIter f0 = h0->face();
		 FaceIter f1 = h3->face();
		 
		 //Ignore requests to split boundary edges
		 if(f0->isBoundary() && f1->isBoundary())
			 return verticesEnd();
		 else if(f0->isBoundary())
		 {
			 //1. collent elements (continue)
			 HalfedgeIter h1 = h0->next();
			 
			 HalfedgeIter h4 = h3->next();
			 HalfedgeIter h5 = h4->next();

			 //Vertices
			 VertexIter v0 = h0->vertex();
			 VertexIter v1 = h3->vertex();
			 VertexIter v3 = h5->vertex();
			 
			 //Edges
			 //e0 is given
			 
			 //2. allocate new elements
			 HalfedgeIter h11 = newHalfedge();
			 HalfedgeIter h13 = newHalfedge();
			 HalfedgeIter h14 = newHalfedge();
			 HalfedgeIter h15 = newHalfedge();
			 
			 FaceIter f3 = newFace();
			 
			 EdgeIter e6 = newEdge();
			 EdgeIter e7 = newEdge();
			 
			 VertexIter v4 = newVertex();
			 v4->position = 0.5f * (v0->position + v1->position);
			 
			 //3. reassign elements
			 
				//Halfedges
			 h0->next() = h11;
			 h11->setNeighbors(h1, h14, v4, e7, f0);
			 h3->vertex() = v4;
			 h4->next() = h13;
			 h13->setNeighbors(h3, h15, v3, e6, f1);
			 h14->setNeighbors(h15, h11, v1, e7, f3);
			 h15->setNeighbors(h5, h13, v4, e6, f3);
			 h5->next() = h14; h5->face() = f3;
			 
			 //Vertices
			 v0->halfedge() = h0;
			 v1->halfedge() = h14;
			 v3->halfedge() = h13;
			 v4->halfedge() = h3;
			 
			 //Edges
			 e6->halfedge() = h13;
			 e7->halfedge() = h14;
			 
			 //Faces
			 f1->halfedge() = h3;
			 f3->halfedge() = h14;
			 return v4;
			 
		 }
		 else if(f1->isBoundary())
		 {
			 //1. collent elements (continue)
			 HalfedgeIter h1 = h0->next();
			 HalfedgeIter h2 = h1->next();
			 
			 
			 //HalfedgeIter h4 = h3->next();
			 HalfedgeIter h5 = h3;
			 do
				 h5 = h5->next();
			 while(h5->next() != h3);
			 
			 //Vertices
			 VertexIter v0 = h0->vertex();
			 VertexIter v1 = h3->vertex();
			 VertexIter v2 = h2->vertex();
			 
			 //Edges
			 //e0 is given

			 //2. allocate new elements
			 HalfedgeIter h10 = newHalfedge();
			 HalfedgeIter h11 = newHalfedge();
			 HalfedgeIter h12 = newHalfedge();
			 HalfedgeIter h14 = newHalfedge();
			 
			 FaceIter f2 = newFace();
			 
			 EdgeIter e5 = newEdge();
			 EdgeIter e7 = newEdge();
			 
			 VertexIter v4 = newVertex();
			 v4->position = 0.5f * (v0->position + v1->position);
			 
			 //3. reassign elements
			 
			 //Halfedges
			 h0->next() = h10;
			 h10->setNeighbors(h2, h12, v4, e5, f0);
			 h11->setNeighbors(h1, h14, v4, e7, f2);
			 h1->next() = h12; h1->face() = f2;
			 h12->setNeighbors(h11, h10, v2, e5, f2);
			 h3->vertex() = v4;
			 h5->next() = h14;
			 
			 h14->setNeighbors(h3, h11, v1, e7, f1);
			 
			 //Vertices
			 v0->halfedge() = h0;
			 v1->halfedge() = h14;
			 v2->halfedge() = h12;
			 v4->halfedge() = h3;
			 
			 //Edges
			 e7->halfedge() = h11;
			 e5->halfedge() = h10;
			 
			 //Faces
			 f0->halfedge() = h0;
			 f1->halfedge() = h3;
			 f2->halfedge() = h1;
			 
			 return v4;
			 
		 }
		 else
		 {
			 //1. collent elements (continue)
			 HalfedgeIter h1 = h0->next();
			 HalfedgeIter h2 = h1->next();
			 
			 
			 HalfedgeIter h4 = h3->next();
			 HalfedgeIter h5 = h4->next();
			 
//			 HalfedgeIter h6 = h1->twin();
//			 HalfedgeIter h7 = h2->twin();
//			 HalfedgeIter h8 = h4->twin();
//			 HalfedgeIter h9 = h5->twin();
			 
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
			 
			 //2. allocate new elements
			 HalfedgeIter h10 = newHalfedge();
			 HalfedgeIter h11 = newHalfedge();
			 HalfedgeIter h12 = newHalfedge();
			 HalfedgeIter h13 = newHalfedge();
			 HalfedgeIter h14 = newHalfedge();
			 HalfedgeIter h15 = newHalfedge();
			 
			 FaceIter f2 = newFace();
			 FaceIter f3 = newFace();
			 
			 EdgeIter e5 = newEdge();
			 EdgeIter e6 = newEdge();
			 EdgeIter e7 = newEdge();
		 
			 VertexIter v4 = newVertex();
			 v4->position = 0.5f * (v0->position + v1->position);

			 //3. reassign elements
		 
			 //Halfedges
			 h0->next() = h10; h0->twin() = h3; h0->vertex() = v0; h0->edge() = e0; h0->face() = f0;
			 
			 h1->next() = h12; /*h1->twin() = h6;*/ h1->vertex() = v1; h1->edge() = e1; h1->face() = f2;
			 
			 h2->next() = h0; /*h2->twin() = h7;*/ h2->vertex() = v2; h2->edge() = e2; h2->face() = f0;
		 
			 h3->next() = h4; h3->twin() = h0; h3->vertex() = v4; h3->edge() = e0; h3->face() = f1;
		 
			 h4->next() = h13; /*h4->twin() = h8;*/ h4->vertex() = v0; h4->edge() = e3; h4->face() = f1;
		 
			 h5->next() = h14; /*h5->twin() = h9;*/ h5->vertex() = v3; h5->edge() = e4; h5->face() = f3;
		 
//			 h6->twin() = h1; h6->vertex() = v2; h6->edge() = e1;
		 
//			 h7->twin() = h2; h7->vertex() = v0; h7->edge() = e2;
		 
//			 h8->twin() = h4; h8->vertex() = v3; h8->edge() = e3;
		 
//			 h9->twin() = h5; h9->vertex() = v1; h9->edge() = e4;
		 
			 h10->next() = h2; h10->twin() = h12; h10->vertex() = v4; h10->edge() = e5; h10->face() = f0;
		 
			 h11->next() = h1; h11->twin() = h14; h11->vertex() = v4; h11->edge() = e7; h11->face() = f2;
		 
			 h12->next() = h11; h12->twin() = h10; h12->vertex() = v2; h12->edge() = e5; h12->face() = f2;
		 
			 h13->next() = h3; h13->twin() = h15; h13->vertex() = v3; h13->edge() = e6; h13->face() = f1;
			 
			 h14->next() = h15; h14->twin() = h11; h14->vertex() = v1; h14->edge() = e7; h14->face() = f3;
		 
			 h15->next() = h5; h15->twin() = h13; h15->vertex() = v4; h15->edge() = e6; h15->face() = f3;
		 
			 //Vertices
			 v0->halfedge() = h0;
			 v1->halfedge() = h1;
			 v2->halfedge() = h2;
			 v3->halfedge() = h5;
			 v4->halfedge() = h3;
			 
			 //Edges
			 e0->halfedge() = h0;
			 e1->halfedge() = h1;
			 e2->halfedge() = h2;
			 e3->halfedge() = h4;
			 e4->halfedge() = h5;
			 e5->halfedge() = h10;
			 e6->halfedge() = h13;
			 e7->halfedge() = h11;
			 
			 //Faces
			 f0->halfedge() = h0;
			 f1->halfedge() = h3;
			 f2->halfedge() = h1;
			 f3->halfedge() = h5;
		 
			 return v4;
		 }
	 }
	
	
	 bool willCollapseBeValid(EdgeIter e)
	 {
		 EdgeIter e4 = e;
		 
		 //Halfedges
		 HalfedgeIter h1 = e4->halfedge();
		 HalfedgeIter h5 = h1->twin();
		 
		 //Faces
		 FaceIter f0 = h1->face();
		 FaceIter f1 = h5->face();
		 
		 if(f0->isBoundary() || f1->isBoundary())
			 return false;
		 
		 //Halfedges, cont'
		 HalfedgeIter h2 = h1->next();
		 HalfedgeIter h0 = h2->next();
		 HalfedgeIter h3 = h5->next();
		 HalfedgeIter h4 = h3->next();
		 
		 //Vertices
		 VertexIter v0 = h0->vertex();
		 VertexIter v1 = h3->vertex();
		 VertexIter v2 = h4->vertex();
		 VertexIter v3 = h2->vertex();
		 
		 if(v0->isBoundary() && v0->degree() <= 1)
			 return false;
		 if(v1->isBoundary() && v1->degree() <= 1)
			 return false;
		 if(v2->isBoundary() && v2->degree() <= 1)
			 return false;
		 if(v3->isBoundary() && v3->degree() <= 1)
			 return false;
		 
		 //Early Exit #3: degenerated case: v0/v1/v2/v3 are duplicated
		 if(v0 == v1 || v0 == v2 || v0 == v3 || v1 == v2 || v1 == v3 || v2 == v3)
			 return false;
		 
		 //Early Exit #4: v1, v3 cannot be both boundary vertex
		 if(v1->isBoundary() && v3->isBoundary())
			 return false;
		 
		 return true;
	 }
	
   VertexIter HalfedgeMesh::collapseEdge( EdgeIter e )
   {
      // TODO This method should collapse the given edge and return an iterator to the new vertex created by the collapse.
		 
		 //1. collect elements
		 EdgeIter e4 = e;

		 //Halfedges
		 HalfedgeIter h1 = e4->halfedge();
		 HalfedgeIter h5 = h1->twin();
		 
		 //Faces
		 FaceIter f0 = h1->face();
		 FaceIter f1 = h5->face();
		 
		 //Early Exit #1: Ignore requests to collapse boundary edges
		 if(f0->isBoundary() || f1->isBoundary())
			 return verticesEnd();
		 
		 //Halfedges, cont'
		 HalfedgeIter h2 = h1->next();
		 HalfedgeIter h0 = h2->next();
		 HalfedgeIter h3 = h5->next();
		 HalfedgeIter h4 = h3->next();
		 
		 HalfedgeIter h7 = h0->twin();
		 HalfedgeIter h12 = h3->twin();
		 
		 HalfedgeIter h20 = h2->twin();
		 HalfedgeIter h15 = h4->twin();
		 
		 //Edges
		 EdgeIter e0 = h0->edge();
		 EdgeIter e1 = h3->edge();
		 EdgeIter e2 = h4->edge();
		 EdgeIter e3 = h2->edge();
			//EdgeIter e4
		 
		 //Faces
		 
		 //Vertices
		 VertexIter v0 = h0->vertex();
		 VertexIter v1 = h3->vertex();
		 VertexIter v2 = h4->vertex();
		 VertexIter v3 = h2->vertex();
		 
		 //Early Exit #2: The number of the joint neighbor vertices of the two merging vertices
		 //must be EXACTLY TWO
		 std::vector<VertexIter> v1_neighbors;
		 std::vector<VertexIter> v3_neighbors;
		 HalfedgeIter h = h3;
		 do
		 {
			 h = h->twin();
			 if(h->vertex() != v1)
				 v1_neighbors.push_back(h->vertex());
			 h = h->next();
		 }
		 while(h != h3);
		 h = h2;
		 do
		 {
			 h = h->twin();
			 if(h->vertex() != v3)
				 v3_neighbors.push_back(h->vertex());
			 h = h->next();
		 }
		 while(h != h2);
		 std::sort(v1_neighbors.begin(), v1_neighbors.end());
		 std::sort(v3_neighbors.begin(), v3_neighbors.end());
		 std::vector<VertexIter> joint_neighbors;
		 std::set_intersection(v1_neighbors.begin(), v1_neighbors.end(),
													 v3_neighbors.begin(), v3_neighbors.end(),
													 std::back_inserter(joint_neighbors));
		 if(joint_neighbors.size() != 2)
			 return verticesEnd();
		 
		 //Early Exit #3: mesh must have more than 4 vertices if neither v1 nor v3 is boundary vertex,
		 //and more than 3 vertices if either v1 or v3 is boundary vertex
		 if(!v1->isBoundary() && !v3->isBoundary() && nVertices() <= 4)
			 return verticesEnd();
		 if((v1->isBoundary() || v3->isBoundary()) && nVertices() <= 3)
			 return verticesEnd();
		 
		 //Early Exit #4: v1, v3 cannot be both boundary vertex
		 if(v1->isBoundary() && v3->isBoundary())
			 return verticesEnd();
		 
		 //Early Exit #5: boundary vertex needs at least one triangle
		 //By convention, Vertex::degree() returns the face degree
		 if(v0->isBoundary() && v0->degree() <= 1)
			 return verticesEnd();
		 if(v1->isBoundary() && v1->degree() <= 1)
			 return verticesEnd();
		 if(v2->isBoundary() && v2->degree() <= 1)
			 return verticesEnd();
		 if(v3->isBoundary() && v3->degree() <= 1)
			 return verticesEnd();
		
		 //Early Exit #6: degenerated case: v0/v1/v2/v3 are duplicated
		 if(v0 == v1 || v0 == v2 || v0 == v3 || v1 == v2 || v1 == v3 || v2 == v3)
			 return verticesEnd();
		 

		 
		 VertexIter output = verticesEnd();
		 if(v3->isBoundary())
		 {
			 std::vector<HalfedgeIter> v1_out;
			 HalfedgeIter h = v1->halfedge();
			 do
			 {
				 v1_out.push_back(h);
				 h = h->next()->next()->twin();
			 }
			 while(h != v1->halfedge());
			 
			 //2. reassign elements
			 
			 //Halfedges
			 h7->twin() = h20; h7->edge() = e3;
			 h20->twin() = h7;
			 h12->twin() = h15; h12->edge() = e2;
			 h15->twin() = h12;
			 
			 for(auto h = v1_out.begin(); h!= v1_out.end(); ++h)
				 (*h)->vertex() = v3;
			 
			 //Vertices
			 v0->halfedge() = h20;
			 v3->halfedge() = h15;
			 v3->position = 0.5f * (v1->position + v3->position);
			 v2->halfedge() = h12;
			 
			 //Edges
			 e3->halfedge() = h20;
			 e2->halfedge() = h15;
			 
			 //Faces
			 
			 //3. delete elements
			 //Halfedges
			 deleteHalfedge(h0);
			 deleteHalfedge(h1);
			 deleteHalfedge(h2);
			 deleteHalfedge(h3);
			 deleteHalfedge(h4);
			 deleteHalfedge(h5);
			 
			 //Vertices
			 deleteVertex(v1);
			 
			 //Edges
			 deleteEdge(e0);
			 deleteEdge(e1);
			 deleteEdge(e4);
			 
			 //Faces
			 deleteFace(f0);
			 deleteFace(f1);
			 
			 output = v3;
		 }
		 else
		 {
			 std::vector<HalfedgeIter> v3_out;
			 HalfedgeIter h = v3->halfedge();
			 do
			 {
				 v3_out.push_back(h);
				 h = h->next()->next()->twin();
			 }
			 while(h != v3->halfedge());
			 
			 //2. reassign elements
			 
			 //Halfedges
			 h7->twin() = h20;
			 h20->twin() = h7; h20->edge() = e0;
			 h12->twin() = h15;
			 h15->twin() = h12; h15->edge() = e1;
			 
			 for(auto h = v3_out.begin(); h!= v3_out.end(); ++h)
				 (*h)->vertex() = v1;
			 
			 //Vertices
			 v0->halfedge() = h20;
			 v1->halfedge() = h15;
			 v1->position = 0.5f * (v1->position + v3->position);
			 v2->halfedge() = h12;
			 
			 //Edges
			 e0->halfedge() = h20;
			 e1->halfedge() = h15;
			 
			 //Faces
			 
			 //3. delete elements
			 //Halfedges
			 deleteHalfedge(h0);
			 deleteHalfedge(h1);
			 deleteHalfedge(h2);
			 deleteHalfedge(h3);
			 deleteHalfedge(h4);
			 deleteHalfedge(h5);
			 
			 //Vertices
			 deleteVertex(v3);
			 
			 //Edges
			 deleteEdge(e2);
			 deleteEdge(e3);
			 deleteEdge(e4);
			 
			 //Faces
			 deleteFace(f0);
			 deleteFace(f1);
			 
			 output = v1;
		 }
		 
		 return output;
   }
	
	 bool willFlipEdgeImprove(EdgeIter e0)
	 {
		 
		 //1. collect elements
		 
		 //Halfedges
		 HalfedgeIter h0 = e0->halfedge();
		 HalfedgeIter h3 = h0->twin();
		 
		 //Faces
		 FaceIter f0 = h0->face();
		 FaceIter f1 = h3->face();
		 
		 //Early Exit #1: Ignore requests to flip boundary edges
		 if(f0->isBoundary() || f1->isBoundary())
			 return false;
		 
		 HalfedgeIter h1 = h0->next();
		 HalfedgeIter h2 = h1->next();
		 
		 
		 HalfedgeIter h4 = h3->next();
		 HalfedgeIter h5 = h4->next();
		 
		 //Vertices
		 VertexIter v0 = h0->vertex();
		 VertexIter v1 = h3->vertex();
		 VertexIter v2 = h2->vertex();
		 VertexIter v3 = h5->vertex();
		 
		 //Early Exit #2: Does the flipped edge already exist?
		 HalfedgeIter h = v2->halfedge();
		 do
		 {
			 h = h->twin();
			 if(h->vertex() == v3)
				 return false;
			 h = h->next();
		 }
		 while(h != v2->halfedge());
		 
		 int oldDev =
		 std::abs((int)v0->degree() - 6) +
		 std::abs((int)v1->degree() - 6) +
		 std::abs((int)v2->degree() - 6) +
		 std::abs((int)v3->degree() - 6);
		 
		 int newDev =
		 std::abs((int)v0->degree() - 7) +
		 std::abs((int)v1->degree() - 7) +
		 std::abs((int)v2->degree() - 5) +
		 std::abs((int)v3->degree() - 5);
		 
		 if( newDev < oldDev)
			 return true;
		 else return false;
	 }
	
   EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
   {
      // TODO This method should flip the given edge and return an iterator to the flipped edge.
		
		 //1. collect elements
		 
		 //Halfedges
		 HalfedgeIter h0 = e0->halfedge();
		 HalfedgeIter h3 = h0->twin();
		 
		 //Faces
		 FaceIter f0 = h0->face();
		 FaceIter f1 = h3->face();
		 
		 //Early Exit #1: Ignore requests to flip boundary edges
		 if(f0->isBoundary() || f1->isBoundary())
			 return edgesEnd();
		 
		 HalfedgeIter h1 = h0->next();
		 HalfedgeIter h2 = h1->next();
		 
	
		 HalfedgeIter h4 = h3->next();
		 HalfedgeIter h5 = h4->next();
		 
		 //Vertices
		 VertexIter v0 = h0->vertex();
		 VertexIter v1 = h3->vertex();
		 VertexIter v2 = h2->vertex();
		 VertexIter v3 = h5->vertex();
		 
		 //Early Exit #2: Does the flipped edge already exist?
		 HalfedgeIter h = v2->halfedge();
		 do
		 {
			 h = h->twin();
			 if(h->vertex() == v3)
				 return edgesEnd();
			 h = h->next();
		 }
		 while(h != v2->halfedge());
		 
		 //Edges
		 //e0 is given

		 //2. reassign elements
		 
		 //HalfEdges
		 h0->next() = h5; h0->vertex() = v2;
		 h5->next() = h1; h5->face() = f0;
		 h1->next() = h0;
		 h3->next() = h2; h3->vertex() = v3;
		 h2->next() = h4; h2->face() = f1;
		 h4->next() = h3;
		
		 //Vertices
		 v0->halfedge() = h4;
		 v1->halfedge() = h1;
		 v2->halfedge() = h0;
		 v3->halfedge() = h3;
		 
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
			for(VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); ++v )
			{
				v->isNew = false;
				if(!v->isBoundary())
				{
					//By convention, Vertex::degree() returns the face degree,
					//not the edge degree. The edge degree can be computed by finding the face
					//degree, and adding 1 if the vertex is a boundary vertex.
					int degree = v->degree();
					
					double u = degree == 3 ? 0.1875 : (3.0 / (8.0 * degree)); //0.1875 = 3/16
					v->newPosition = v->position * (1.0 - u * degree);
					HalfedgeIter h = v->halfedge();
					do
					{
						h = h->twin();
						v->newPosition += (h->vertex()->position * u);
						h = h->next();
					}
					while(h != v->halfedge());
					}
				else
				{
					HalfedgeIter h0_b = v->halfedge();
					while(!h0_b->isBoundary())
						h0_b = h0_b->twin()->next();
					VertexIter v0_b = h0_b->twin()->vertex();
					
					HalfedgeIter h1_b = v->halfedge();
					do
					{
						h1_b = h1_b->twin();
						if(h1_b->isBoundary())
							break;
						h1_b = h1_b->next();
					}
					while(h1_b != v->halfedge());
					VertexIter v1_b = h1_b->vertex();
					v->newPosition = 0.75 * v->position + 0.125 * (v0_b->position + v1_b->position);
				}
			}

      // TODO Next, compute the updated vertex positions associated with edges, and store it in Edge::newPosition.
			for(EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); ++e)
			{
				e->isNew = false;
				FaceIter f0 = e->halfedge()->face();
				FaceIter f1 = e->halfedge()->twin()->face();
				if(f0->isBoundary() || f1->isBoundary())
				{
					VertexIter v0_b = e->halfedge()->vertex();
					VertexIter v1_b = e->halfedge()->twin()->vertex();
					e->newPosition = 0.5 * (v0_b->position + v1_b->position);
				}
				else
				{
					Vector3D v0,v1; //this diagonal
					v0 = e->halfedge()->vertex()->position;
					v1 = e->halfedge()->twin()->vertex()->position;
					e->newPosition = 0.375 * (v0 + v1);
					Vector3D v2,v3; //opposite diagonal
					v2 = e->halfedge()->next()->next()->vertex()->position;
					v3 = e->halfedge()->twin()->next()->next()->vertex()->position;
					e->newPosition += 0.125 * (v2 + v3);
				}
			}

      // TODO Next, we're going to split every edge in the mesh, in any order.  For future
      // TODO reference, we're also going to store some information about which subdivided
      // TODO edges come from splitting an edge in the original mesh, and which edges are new,
      // TODO by setting the flat Edge::isNew.  Note that in this loop, we only want to iterate
      // TODO over edges of the original mesh---otherwise, we'll end up splitting edges that we
      // TODO just split (and the loop will never end!)
			EdgeIter e = mesh.edgesBegin();
			while(e != mesh.edgesEnd())
			{
				EdgeIter next = e;
				++next;
				if(!e->isNew &&
					 !e->halfedge()->vertex()->isNew &&
					 !e->halfedge()->twin()->vertex()->isNew)
				{
					VertexIter e_v0 = e->halfedge()->vertex();
					VertexIter e_v1 = e->halfedge()->twin()->vertex();
					VertexIter v_new = mesh.splitEdge(e);
					v_new->isNew = true;
					v_new->position = e->newPosition;
					
					HalfedgeIter h = v_new->halfedge();
					do
					{
						h = h->twin();
						VertexIter v = h->vertex();
						h->edge()->isNew = (v != e_v0 && v != e_v1);
						h = h->next();
					}
					while(h != v_new->halfedge());
				}
				
				e = next;
			}

      // TODO Now flip any new edge that connects an old and new vertex.
			for(EdgeIter e = mesh.edgesBegin(); e!= mesh.edgesEnd(); ++e)
			{
				VertexIter v0 = e->halfedge()->vertex();
				VertexIter v1 = e->halfedge()->twin()->vertex();
				bool v_old_new = (v0->isNew && !v1->isNew) || (!v0->isNew && v1->isNew);
				if(v_old_new && e->isNew)
					mesh.flipEdge(e);
			}

      // TODO Finally, copy the new vertex positions into final Vertex::position.
		 for(VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); ++v)
		 {
			 if(!v->isNew)
				 v->position = v->newPosition;
		 }
   }

   // Given an edge, the constructor for EdgeRecord finds the
   // optimal point associated with the edge's current quadric,
   // and assigns this edge a cost based on how much quadric
   // error is observed at this optimal point.
   EdgeRecord::EdgeRecord( EdgeIter& _edge )
   : edge( _edge )
   {
      // TODO Compute the combined quadric from the edge endpoints.
			Matrix4x4 q = _edge->halfedge()->vertex()->quadric +
										_edge->halfedge()->twin()->vertex()->quadric;
		 
      // TODO Build the 3x3 linear system whose solution minimizes
      // the quadric error associated with these two endpoints.
			Matrix3x3 quadratic;
			quadratic(0,0) =  q(0,0); quadratic(0,1) =  q(0,1); quadratic(0,2) =  q(0,2);
			quadratic(1,0) =  q(1,0); quadratic(1,1) =  q(1,1); quadratic(1,2) =  q(1,2);
			quadratic(2,0) =  q(2,0); quadratic(2,1) =  q(2,1); quadratic(2,2) =  q(2,2);
			Vector3D linear(q(3,0), q(3,1), q(3,2));
		 
      // TODO Use this system to solve for the optimal position, and
      // TODO store it in EdgeRecord::optimalPoint.
			optimalPoint = - quadratic.inv() * linear;
		 
      // TODO Also store the cost associated with collapsing this edge
      // TODO in EdgeRecord::Cost.
			Vector4D optH(optimalPoint);
			optH.w = 1.0;
			score = dot(optH, q * optH);
   }

   void MeshResampler::downsample( HalfedgeMesh& mesh )
   {
      // TODO Compute initial quadrics for each face by simply writing the plane
      // equation for the face in homogeneous coordinates.  These quadrics should
      // be stored in Face::quadric
			for(auto face = mesh.facesBegin(); face != mesh.facesEnd(); ++face)
			{
				Vector3D n = face->normal();
				Vector4D v(n);
				v.w = - dot(n, face->halfedge()->vertex()->position);
				//a: v->x; b: v->y; c: v->z; d: v->w
				face->quadric = outer(v, v);
			}

      // TODO Compute an initial quadric for each vertex as the sum of the quadrics
      // associated with the incident faces, storing it in Vertex::quadric
			for(auto vertex = mesh.verticesBegin(); vertex != mesh.verticesEnd(); ++vertex)
			{
				//traverse all the non-boundary faces associated with the vertex
				vertex->quadric.zero();
				HalfedgeIter h = vertex->halfedge();
				do
				{
					if(!h->face()->isBoundary())
						vertex->quadric += h->face()->quadric;
					h = h->twin()->next();
				}
				while(h != vertex->halfedge());
			}

      // TODO Build a priority queue of edges according to their quadric error cost,
      // TODO i.e., by building an EdgeRecord for each edge and sticking it in the queue.
			MutablePriorityQueue<EdgeRecord> pqueue;
			
			for(auto edge = mesh.edgesBegin(); edge != mesh.edgesEnd(); ++edge)
			{
				edge->record = EdgeRecord(edge);
				pqueue.insert(edge->record);
			}
		 
      // TODO Until we reach the target edge budget, collapse the best edge.  Remember
      // TODO to remove from the queue any edge that touches the collapsing edge BEFORE
      // TODO it gets collapsed, and add back into the queue any edge touching the collapsed
      // TODO vertex AFTER it's been collapsed.  Also remember to assign a quadric to the
      // TODO collapsed vertex, and to pop the collapsed edge off the top of the queue.
			Size target_tri_num = mesh.nFaces() >> 2;
			while(mesh.nFaces() > target_tri_num && pqueue.size() > 0)
			{
				//1. Get the cheapest edge from the queue.
				EdgeRecord curr = pqueue.top();
				
				//2. Remove the cheapest edge from the queue by calling pop().
				pqueue.pop();
				
				//3. Compute the new quadric by summing the quadrics at its two endpoints.
				VertexIter v0 = curr.edge->halfedge()->vertex();
				VertexIter v1 = curr.edge->halfedge()->twin()->vertex();
				Matrix4x4 q_new = v0->quadric +	v1->quadric;
				
				//4. Remove any edge touching either of its endpoints from the queue.
				HalfedgeIter h = v0->halfedge();
				do
				{
					pqueue.remove(h->edge()->record);
					h = h->twin()->next();
				}
				while(h != v0->halfedge());
				
				h = v1->halfedge();
				do
				{
					pqueue.remove(h->edge()->record);
					h = h->twin()->next();
				}
				while(h != v1->halfedge());
				
				//5. Collapse the edge.
				VertexIter v_new = mesh.collapseEdge(curr.edge);
				if(v_new != mesh.verticesEnd())
				{
					//6. Set the quadric of the new vertex to the quadric computed in Step 2.
					v_new->position = curr.optimalPoint;
					v_new->quadric = q_new;
					
					//7. Insert any edge touching the new vertex into the queue, creating new edge records for each of them.
					h = v_new->halfedge();
					do
					{
						h->edge()->record = EdgeRecord(h->edge());
						pqueue.insert(h->edge()->record);
						h = h->twin()->next();
					}
					while(h != v_new->halfedge());
				}
			}
   }

   void Vertex::computeCentroid( void )
   {
      // TODO Compute the average position of all neighbors of this vertex, and
      // TODO store it in Vertex::centroid.  This value will be used for resampling.
			HalfedgeIter h = halfedge();
			centroid.x = 0; centroid.y = 0; centroid.z = 0;
			do
			{
				h = h->twin();
				Vector3D neighbor = h->vertex()->position;
				centroid += neighbor;
				h = h->next();
			}
			while(h != halfedge());
		 //By convention, Vertex::degree() returns the face degree,
		 //not the edge degree. The edge degree can be computed by finding the face
		 //degree, and adding 1 if the vertex is a boundary vertex.
		 int degree = this->degree();
		 if(isBoundary())
			 degree++;
			centroid /= (double)degree;
   }

   Vector3D Vertex::normal( void ) const
   // TODO Returns an approximate unit normal at this vertex, computed by
   // TODO taking the area-weighted average of the normals of neighboring
   // TODO triangles, then normalizing.
   {
      // TODO Compute and return the area-weighted unit normal.
		 
			//no boundary polygon
			HalfedgeCIter h = this->halfedge();
			Vector3D nrm(0, 0, 0);
			double totalarea = 0;
			do
			{
				h = h->twin();
				FaceCIter f = h->face();
				if(!f->isBoundary())
				{
					VertexCIter v1 = h->vertex();
					VertexCIter v2 = h->next()->twin()->vertex();
					Vector3D out = cross(v1->position - position, v2->position - position);
					nrm += out;
					totalarea += out.norm();
				}
				h = h->next();
			}
			while(h != this->halfedge());
			nrm /= totalarea;
			nrm.normalize();
			return nrm;
	 }

   void MeshResampler::resample( HalfedgeMesh& mesh )
   {
      // TODO Compute the mean edge length.
			double mean2 = 0;
			for(auto edge = mesh.edgesBegin(); edge != mesh.edgesEnd(); ++edge)
			{
				Vector3D v0 = edge->halfedge()->vertex()->position;
				Vector3D v1 = edge->halfedge()->twin()->vertex()->position;
				mean2 += (v0 - v1).norm();
			}
			mean2 /= (double)mesh.nEdges();
			mean2 *= mean2;
		 
      // TODO Repeat the four main steps for 5 or 6 iterations
			const int ITER_TIMES = 5;
			const int SMOOTH_TIMES = 20;
			const double WEIGHT_FACTOR = 0.2;
			const double LONG_EDGE_2 = 1.7777777778;
			const double SHORT_EDGE_2 = 0.64;
			std::unordered_set<EdgeIter> edgeSet;
			edgeSet.reserve(mesh.nEdges());
			
			for(int i = 0; i < ITER_TIMES; ++i)
			{
				// TODO Split edges much longer than the target length (being careful about how the loop is written!)
				EdgeIter old_end = mesh.edgesEnd();
				--old_end;
				for(auto edge = mesh.edgesBegin(); edge != mesh.edgesEnd(); ++edge)
				{
					Vector3D v0 = edge->halfedge()->vertex()->position;
					Vector3D v1 = edge->halfedge()->twin()->vertex()->position;
					if((v0 - v1).norm2() > LONG_EDGE_2 * mean2)
					{
						mesh.splitEdge(edge);
					}
					if(edge == old_end)
						break;
				}
				
				// TODO Collapse edges much shorter than the target length.  Here we need to be EXTRA careful about
				// TODO advancing the loop, because many edges may have been destroyed by a collapse (which ones?)
				edgeSet.clear();
				for(auto edge = mesh.edgesBegin(); edge != mesh.edgesEnd(); ++edge)
				{
					edgeSet.insert(edge);
				}
				while(edgeSet.size() > 0)
				{
					EdgeIter curr = *(edgeSet.begin());
					edgeSet.erase(edgeSet.begin());
					
					VertexIter v0 = curr->halfedge()->vertex();
					VertexIter v1 = curr->halfedge()->twin()->vertex();
					
					if((v0->position - v1->position).norm2() >= SHORT_EDGE_2 * mean2)
						continue;
					
					HalfedgeIter h = v0->halfedge();
					do
					{
						if(edgeSet.find(h->edge()) != edgeSet.end())
							edgeSet.erase(h->edge());
						h = h->twin()->next();
					}
					while(h != v0->halfedge());
					
					h = v1->halfedge();
					do
					{
						if(edgeSet.find(h->edge()) != edgeSet.end())
							edgeSet.erase(h->edge());
						h = h->twin()->next();
					}
					while(h != v1->halfedge());
					
					VertexIter v_new = mesh.collapseEdge(curr);
					if(v_new != mesh.verticesEnd())
					{
						h = v_new->halfedge();
						do
						{
							edgeSet.insert(h->edge());
							h = h->twin()->next();
						}
						while(h != v_new->halfedge());
					}
				}
				
				// TODO Now flip each edge if it improves vertex degree
				for(auto edge = mesh.edgesBegin(); edge != mesh.edgesEnd(); ++edge)
				{
					if(willFlipEdgeImprove(edge))
						mesh.flipEdge(edge);
				}

//				 TODO Finally, apply some tangential smoothing to the vertex positions

				for(int j = 0; j < SMOOTH_TIMES; ++j)
				{
					for(auto vertex = mesh.verticesBegin(); vertex != mesh.verticesEnd(); ++vertex)
					{
						if(vertex->isBoundary())
							continue;
						vertex->computeCentroid();
					}
					
					for(auto vertex = mesh.verticesBegin(); vertex != mesh.verticesEnd(); ++vertex)
					{
						if(vertex->isBoundary())
							continue;
						Vector3D dir = vertex->centroid - vertex->position;
						Vector3D nrm = vertex->normal();
						dir -= (dot(nrm, dir) * nrm);
						vertex->position = vertex->position + WEIGHT_FACTOR * dir;
					}
				}

			}

   }
}
