/*
 * Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

#include<cmath>
#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
#include <cstdio>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
#define PI 3.14159265

///a function which helps in drawing an arc, givng it's radius , centre, and the angle made at the centre by the arc
///numP being the no of points and vs being the vector to which points on the arc are set.
/*!
\param xC x-axis of center of the arc
\param yC y-axis of the center of arc
\param r radius of arc
\param sA starting angle 
\param eA ending angle
\param vs the array in which the arc points will be returned
\param numP number of points in the arc
*/
	void dominos_t::getArcVec(float xC,float yC,float r,float sA,float eA,b2Vec2* vs,int numP){
		/// a for loop which calculates the points in an arc, using the standard formula for the points in a circle
		///finds points at angles uniformly between sA and eA
		for (int i=0;i<numP;i++)
		{
			/// finding the point at the angle theta
			float theta = (sA) + ((eA-sA)/(numP-1))*i;
			vs[i].Set(xC+r*sin(theta), yC+r*cos(theta));
		}

	}
	
	//! Function for drawing a chain passing through points specified by vs and numP being no of points
	/*!
	\param vs an array
	\param numP the number of points
	*/
	void dominos_t::drawChain(b2Vec2* vs,int numP){
		///create a b2BodyDef and initialize the body with the b2BodyDef
		b2BodyDef bd;
		b2Body* eyePlace=m_world->CreateBody(&bd);
		///initialize the chain shape with all the points given as vs
		b2ChainShape chain;
		chain.CreateChain(vs,numP);
		///create the fixture to the body
		eyePlace->CreateFixture(&chain,0.0f);

	}
	
	//! Function for creating a box (both dynamic and static at the desired position)
	/*!
	\param xC the x center of the box
	\param yC the y center of the box 
	\param fixture pointer to the fixture definition
	\param isDynamic whether the body is static or dynamic.
	\return the final body 
	*/
	b2Body* dominos_t::drawBox(float xC,float yC,b2FixtureDef* fixture, bool isDynamic=false){
			b2BodyDef bd;
			if(isDynamic){
				bd.type=b2_dynamicBody;
			}
			bd.position.Set(xC, yC);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(fixture);
			return ground;
	}
	
	//! Function which makes a revolute joint between the two given bodies a,b
	/*!
	\param a First body
	\param b Second body
	*/
	void dominos_t::makeJoint(b2Body* a, b2Body* b ){
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = a;
			jointDef.bodyB = b;
			jointDef.localAnchorA.Set(0.0f,0.0f);
			jointDef.localAnchorB.Set(0.0f,0.0f);
			m_world->CreateJoint(&jointDef);
	}
	
	
	//! Function for creating a box with the required parameters
	/*!
	\param xC the x center of the box
	\param yC the y center of the box
	\param lby2 length of the box divided by 2
	\param bby2 breadth of the box divided by 2
	\param isDynamic whether the body is dynamic or static
	\param angle the angle w.r.t the horizontal at which the object is present.
	\param density the density of the object.
	*/
	b2Body* dominos_t::drawBox(float xC,float yC,float lby2,float bby2,bool isDynamic=false,float angle=0,float density=0){
			b2PolygonShape shape;
			shape.SetAsBox(lby2, bby2);

			b2BodyDef bd;
			if(isDynamic){
				bd.type=b2_dynamicBody;
			}
			bd.angle=angle;
			bd.position.Set(xC, yC);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shape, 0.0f);
			return ground;
	}
	
	
	//! Function for drawing a circular arc
	/*!
	\param xC the x center of the circle
	\param yC the y center of the circle
	\param r the radius of the the arc 
	\param sA starting angle
	\param eA end angle
	\param numP number of points in the arc
	*/
	void dominos_t::drawArc(float xC,float yC,float r,float sA,float eA,int numP){
		b2Vec2 vs[numP];
		getArcVec(xC,yC,r,sA,eA,vs,numP);
		drawChain(vs,numP);
	}
	
	
	//! Function for drawing a rigid sphere
	/*!
	\param xC the x center of the sphere
	\param yC the y center of the sphere
	\param r the radius of the sphere
	\param a the density of the sphere
	\param b the friction of the sphere
	\param c the restitution of the sphere
	*/
	b2Body* dominos_t::drawSphere(float xC,float yC,float r,float a,float b, float c){
	
		b2Body* spherebody;			
		b2CircleShape circle;
		circle.m_radius = r;

		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = a;
		ballfd.friction = b;
		ballfd.restitution = c;

		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(xC,yC);
		spherebody = m_world->CreateBody(&ballbd);
		spherebody->CreateFixture(&ballfd);
		return spherebody;
	}
	
	//! Function for creating a straight platform by providing the two end points
	/*!
	\param a one end point of the platform
	\param b another end point of the platform
	*/
	void dominos_t::drawPlatform(b2Vec2 a,b2Vec2 b)
	{		
		b2Body* platform;
		b2EdgeShape shape;
		shape.Set(a, b);
		b2BodyDef bd;
		platform = m_world->CreateBody(&bd);
		platform->CreateFixture(&shape, 0.0f);
	}
	//! Function which defines all the objects of the simulation
	dominos_t::dominos_t()
	{	/**<B> Ground </B>
			The following generates the ground object. 
			It is a straight line between two points (-90,0) and (90,0)
		*/
		{
			b2Vec2 vs[2];
			vs[0].Set(-90.0f,0.0f);
			vs[1].Set(90.0,0.0);
			drawChain(vs,2);
		}
		/// <HR>
		///<B> UPPER LEFT PART OF THE MACHINE</B>-----------------------------
		{	///<B> Platform and the ball </B>
			/** Platform on which the ball initially rests and the ball itself
			*/
			drawBox(-48.5,40.0,1.6,0.15);
			b2Body* spherebody=drawSphere(-48.5,40.5,0.5,1.0f,0.0f,0.85f);		
			
			/** Some force is initially applied on this ball to start off the Rube GoldBerg machine*/
			b2Vec2 force = b2Vec2(110,0);
			spherebody->ApplyForce(force, spherebody->GetPosition());
			/// <B>Platform on which the ball falls</B>
			/// The platform on which the ball falls initially after initial acceleration
			///the horizontal part of the platform
			drawBox(-43.8,35.0,3.6,0.15);
			///the vertical part of the platform 
			b2Body* body1=drawBox(-40.2,36.8,0.15,1.8);
		

			//The small vertical support to the lever 
			//drawBox(b2Vec2(-41.5,38.15 ),b2Vec2(-41.3,38.15));
			drawBox(-41.4,36.7,0.15,1.45);
		

			///<B> Lever which hits ball 2</B>
			{
			///Body definition for the lever
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(-40.2f,38.65f);		
			
			///Three fixtures have been created for the body

			/// fd1 is the fixture which is the long horizontal part of the lever
			///fd1 is of box shape, 5.6 units long and 0.3 high
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 5.0;
			fd1->friction = 0.5;
			fd1->restitution = 0.f;
			fd1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(2.8,0.15, b2Vec2(-0.8f,-0.2f), 0);
			fd1->shape = &bs1;
			/// fd2 is the fixture which is the small vertical part of the lever
			///fd2 is of box shape,0.30 long and 0.8 high
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 5.0;
			fd2->friction = 0.5;
			fd2->restitution = 0.f;
			fd2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.15,0.4, b2Vec2(2.15f,0.05f), 0);
			fd2->shape = &bs2;
			/// fd3 is fixture which is small horizontal part of the lever
			/// fd3 is of box shape, 1 units long and 0.3 high
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 5.0;
			fd3->friction = 0.5;
			fd3->restitution = 0.f;
			fd3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.50,0.15, b2Vec2(2.60f,0.4f), 0);
			fd3->shape = &bs3;
			///body created for the lever, and the above fixtures attached to the body
			b2Body* body2 = m_world->CreateBody(bd);
			body2->CreateFixture(fd1);
			body2->CreateFixture(fd2);
			body2->CreateFixture(fd3);
			/// Revolute Joint created between the vertical part of the platform and the lever, so that lever can rotate about the vertical part of the platform
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = body1;
			jointDef.bodyB = body2;
			jointDef.localAnchorA.Set(0.0f,1.60f);
			jointDef.localAnchorB.Set(0.0f,-0.15f);
			//jointDef.collideConnected = false;
			m_world->CreateJoint(&jointDef);
			}
		

			///<B>Platform and the ball</B>
			/// Platform on which the second ball is lying and the second ball itself have been initialized here
			/// The lever on the left comes and hits this ball to carry on the RubeGoldberg machine
			/// the box is of length 0.8, 0.3 high and a ball of rad 0.5 has been placed on top of it
			drawBox(-36.8,38.1,0.4,0.15);
			drawSphere(-36.8,38.15,0.5,8.0,0.6,0);
			//drawBox(-36.6,38,0.4,0.15);
			//drawSphere(-36.6,38.4,0.5,8.0,0.3,0);
		
			/// tilted platform on which the ball falls for a brief peroid of time before falling on the lever. This is just a stepping platform to reach the lever
			/// it is of length 6, height 0.3 and has been kept at an angle of 2.94 radians
			drawBox(-33.5,35.0,3.0,0.15,false,3.14-0.2);

		}

		{	///<B> Lever on which the second ball falls</B>
			/// Lever on which the second ball falls before going down has been initialized here
			///Body def and body for the lever,positioned as reqd
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-21.0f, 31.0f);
			b2Body* plank = m_world->CreateBody(&bd);

			/// The fixture of the lever of len 16 and height 0.3 has been positioned appropriately in local coordinates, i.e. wrt to the body center
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 5.0;
			fd1->friction = 0.7;
			fd1->restitution = 0.f;
			b2PolygonShape shape1;
			shape1.SetAsBox(8.0f, 0.15f, b2Vec2(-3.0f,0.0f),0);  	
			fd1->shape = &shape1;
			/// fd2 is the fixture of the lever which is the box on the right part of the plank of height 1.6 and length 1.6 too
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 7.5f;
			fd2->friction = 0.0f;
			fd2->restitution = 0.85f;
			b2PolygonShape shape;
			shape.SetAsBox(0.8f, 0.8f, b2Vec2(4.2f,0.8f),0);  			
			fd2->shape = &shape;
			///Both the fixtures are then attached to the plank
			plank->CreateFixture(fd1);
			plank->CreateFixture(fd2);
			
			///The pivot is just a small static body with with the plank has been attached (i.e. the plank is attached to this body)
			b2Body* pivot=drawBox(-21.0,31.0,0.15,0.15);
			/// The pivot are plank are joined using a revoluteJoint 
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = plank;
			jointDef.bodyB = pivot;
			jointDef.localAnchorA.Set(0.0f,0.0f);
			jointDef.localAnchorB.Set(0.0f,0.0f);
			m_world->CreateJoint(&jointDef);   			   	  	

		}



		/// <HR>
		/// <B>LOWER LEFT PART OF THE MACHINE</B>---------------------------- 

		/// <B> Platform </B>
		{	/// A platform is created on which the wedge rests
			drawPlatform(b2Vec2(-55.0f,3.0f), b2Vec2(-30.0f, 3.0f));

			///<B>Wedge and the lever on top of it, with the two boxes on top of the lever</B>

			///The triangle wedge on which plank rests has been defined here. 
			/// The wedge has a polygonShape and the polygon shape has been indicated using three vertices which are the end points with respect to the local coordinates
			b2PolygonShape poly;
			b2Vec2 vertices[3];
			vertices[0].Set(-1,0);
			vertices[1].Set(1,0);
			vertices[2].Set(0,4.0);
			poly.Set(vertices, 3);
			b2FixtureDef wedgefd;
			wedgefd.shape = &poly;
			wedgefd.density = 10.0f;
			wedgefd.friction = 0.0f;
			wedgefd.restitution = 1.0f;
			b2BodyDef wedgebd;
			wedgebd.position.Set(-36.7f, 3.0f);
			b2Body* sbody = m_world->CreateBody(&wedgebd);
			sbody->CreateFixture(&wedgefd);

			/// The plank on top of the wedge has been initialized here, of length 9.4 and height 0.3
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 0.5f;
			b2PolygonShape shape;
			shape.SetAsBox(4.70f, 0.15f);
			fd2->shape = &shape;
			b2Body* body=drawBox( -36.7,7.0,fd2,true);
			/// The plank is attached to the wedge using a revoluteJoint
			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(-36.7f, 7.0f);
			jd.Initialize(sbody, body, anchor);
			m_world->CreateJoint(&jd);

			//fd4 is the fixture for the two boxes which are kept on top of the plank
			b2FixtureDef *fd4 = new b2FixtureDef;
			fd4->density = 0.7f;
			b2PolygonShape shape3;
			shape3.SetAsBox(0.5f, 0.5f);
			fd4->shape = &shape3;
			///The light box on the left side of the see-saw
			drawBox(-40.9,7.5,fd4,true);
			///The light box 2 on the right side of the see-saw
			drawBox(-32.5,7.5,fd4,true);

		}   	   	 
		/// <HR>
		///<B>UPPER RIGHT PART OF THE MACHINE</B>-------------------------
		{
			/// A big ball has been placed on top of a path .. The big ball will be hit by the block which comes from the left lower part of the machine , and it will move on to carry the rest of the task.
			///<B>Path and the ball</B>
			b2Vec2 vs[3];
			vs[0].Set(-10.0f, 40.0f);
			vs[1].Set(-5.50f, 40.0f);
			vs[2].Set(42.0f, 34.0f);
			/// The path has been initialized as a chain of three vertices positioned as required
			drawChain(vs,3);
			/// The ball has been placed on the path and is of rad 0.8
			drawSphere(-6.7,40.8,0.8,0.8,0,0.5);


																								
		}

		/// <HR>
		/// <B>RIGHT PART OF THE MACHINE </B>---------------------------------------------------------------------------------
		{
		///<B> Lever system which drives one-another </B>

		/// fd1 is the fixture for those planks
		/// It is of box shape of length 0.15 and height 4
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 2.0;
			fd1->friction = 0.7;
			fd1->restitution = 0.6f;
			b2PolygonShape shape1;
			shape1.SetAsBox(0.15f, 2.0f, b2Vec2(0.0f,0.0f),0);  		
			fd1->shape = &shape1;
		/// fd2 is the fixture definition for the small static bodies on which these levers rest
		/// has box shape, of height 0.3 and length 0.3
			b2FixtureDef *fd2 = new b2FixtureDef;
			b2PolygonShape shape2;
			shape2.SetAsBox(0.15f, 0.15f, b2Vec2(0.0f,0.0f),0);
			fd2->shape=&shape2;

		///The for loop creates 5 plank,hinge systems, attaches them to the fixture and positions them as required 
			for(int i=0;i<5;i++)		
			{
				///Plank body created at requires position using fd1
				b2Body* plank=drawBox(42.50f - (i%2)*0.7, 33.0f - 3*i,fd1,true);
				///pivot created at required position using fd2
				b2Body* pivot=drawBox(42.50f - (i%2)*0.7 , 33.0f - 3*i,fd2);

				//jointDef.collideConnected = false;
				///The pivot and the plank are joined using revolute joint
				b2RevoluteJointDef jointDef;	
				jointDef.bodyA = plank;
				jointDef.bodyB = pivot;
				jointDef.localAnchorA.Set(0.0f,0.0f);
				jointDef.localAnchorB.Set(0.0f,0.0f);
				m_world->CreateJoint(&jointDef);
			}
		}
		
		/// <HR>
		/// <B>LOWER RIGHT PART OF THE MACHINE </B> -------------------------------------------------
		{
			/// <B> The platform for the two small spheres, and their path, and the sphers</B>
			b2Vec2 vs[10];
			vs[0].Set(41.80f, 19.0f);
			vs[1].Set(36.50f, 19.0f);
			vs[2].Set(35.750f, 18.75f);
			vs[3].Set(35.50f, 18.50f);
			vs[4].Set(35.35f, 18.30f);
			vs[5].Set(31.35f, 13.50f);
			vs[6].Set(31.10f, 13.30f);
			vs[7].Set(30.85f, 13.15f);
			vs[8].Set(30.60f, 13.10f);
			vs[9].Set(24.50f, 13.10f);
			/// The path/platform has been initialized as a chain, and the chain is defined using 10 vertices, which have been alloted x,y coordinates as required
			drawChain(vs,10);
			/// The two small spheres of rad 0.4, positioned as reqd on top of the platform
			drawSphere(41.4,19.4,0.4,0.4,0,0.5);
			drawSphere(39.4,19.4,0.4,0.4,0,0.5);
		}  	
		/// <B> Lever which is closed by one ball for another ball to let through </B>
		{ /// fd1 is the fixture for the plank, of length 0.2 and 4 high 
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 2.35;
			fd1->friction = 0.7;
			fd1->restitution = 0.60f;
			b2PolygonShape shape1;
			shape1.SetAsBox(0.1f, 2.0f, b2Vec2(0.0f,0.0f),0);  		
			fd1->shape = &shape1;
			/// The plank is created, using fixture fd1 at required position
			b2Body* plank=drawBox(22.50f,13.0f,fd1,true);
			/// The pivot is created at the center of the plank of height and length 0.2
			b2Body* pivot=drawBox(22.5,13.0,0.1,0.1);


			/// A joint has been created to join the pivot and the plank
			makeJoint(plank,pivot);
		}
		/// <B> The platform towards the left of the vertical plank</B>
		{
			b2Vec2 vs[2];
			vs[0].Set(20.0f, 13.10f);
			vs[1].Set(3.75f, 13.10f);			
			/// The platform is a chain, defined using two vertices
			drawChain(vs,2);

		}
		///<B> The curved platform at the bottom</B>
		{	///vs represents the vertices of the platform
			b2Vec2 vs[46];
			//vs 0 is the long straight part towards the right 
			vs[0].Set(25.50f, 12.50f);
			//vs[1] to vs[5] represents the curve
			vs[1].Set(20.50f, 5.0f);
			vs[2].Set(20.25f, 4.75f);
			vs[3].Set(20.00f, 4.60f);
			vs[4].Set(19.80f, 4.50f);
			vs[5].Set(19.65f, 4.45f);
			//vs[5] to vs[6] is the long straight part at bottom
			vs[6].Set(-4.65f, 4.45f);
			/// The curve towards left has been initialized using circle equations
			for (int i=1; i<=30; i++)
			{
				vs[i+6].Set(0 - sqrt(abs(pow(3.75,2) - pow(4.45 + 0.25*i - 8.2,2))) - 4.65, 4.45 + 0.25*i);
			}		
			///vs[37] to vs[45] is for the crookedness at the end of the circular part, so that the incoming ball falls on the platform
			vs[37].Set(-4.35f, 11.90f);
			vs[38].Set(-4.10f, 11.85f);
			vs[39].Set(-3.90f, 11.80f);
			vs[40].Set(-3.75f, 11.75f);
			vs[41].Set(-3.85f, 11.70f);
			vs[42].Set(-3.80f, 11.65f);
			vs[43].Set(-3.76f, 11.60f);
			vs[44].Set(-3.73f, 11.55f);
			vs[45].Set(-3.71f, 11.50f);
			/// chain created using the above vertices
			drawChain(vs,46);

			/// <B> Sphere on the platform </B>
			drawSphere(0,4.85,0.4,0.3,0,1);

		}

		{/// <B>platform on which wedge rest</B>
			b2Vec2 vs[2];
			vs[0].Set(-4.65f, 6.2f);
			vs[1].Set(12.50f, 6.2f);
			/// platform initialized as a chain of vertices			
			drawChain(vs,2);
		/// <B>The triangle wedge on top of platform </B>
			/// wedge is of polygon shape (traingular), defined using three vertices
			b2PolygonShape poly;
			b2Vec2 vertices[3];
			vertices[0].Set(-1,0);
			vertices[1].Set(1,0);
			vertices[2].Set(0,2.0);
			poly.Set(vertices, 3);
			/// wedgefd is the fixture for the wedge, initialized using the polygonshape defined above
			b2FixtureDef wedgefd;
			wedgefd.shape = &poly;
			wedgefd.density = 10.0f;
			wedgefd.friction = 0.0f;
			wedgefd.restitution = 1.0f;
			b2BodyDef wedgebd;
			///wedgebd is the position of the wedge
			wedgebd.position.Set(0.0f, 6.20f);
			///wedge created and fixture attached
			b2Body* sbody = m_world->CreateBody(&wedgebd);
			sbody->CreateFixture(&wedgefd);
			/// <B>The plank on top of the wedge</B>

			/// fd2 is the fixture for the plank, having box shape of length 10 and 0.3 high, and density 0.5 
			b2PolygonShape shape;
			shape.SetAsBox(5.0f, 0.15f, b2Vec2(0.0f,0.0f), 0);
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 0.5f;
			fd2->shape = new b2PolygonShape;
			fd2->shape = &shape;
			//drawBox(0,8.2,5,0.15,true,0,0.5);
			///bs1 is the polygon shape for the trapezium on top of the plank, whose vertices are defined using vertices
			b2PolygonShape bs1;
			b2Vec2 vertices1[4];
			vertices1[0].Set(2.0f,0.0f);
			vertices1[1].Set(5.0f,0.0f);
			vertices1[2].Set(5.0f,3.15f);
			vertices1[3].Set(2.0f,4.40f);
			///fd1 is the fixture for the trapezium
			b2FixtureDef *fd1 = new b2FixtureDef;
			bs1.Set(vertices1, 4);
			fd1->shape = &bs1;
			/// body is the lever body ,positioned appropriately and attached to the two fixtures
			b2BodyDef bd2;
			bd2.position.Set(0.0f, 8.2f);
			bd2.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bd2);
			body->CreateFixture(fd1);			
			body->CreateFixture(fd2);
			/// the lever is joined to the wedge using a revoluteJoint, andchored appropriately
			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(0.0f, 8.20f);
			jd.Initialize(sbody, body, anchor);
			m_world->CreateJoint(&jd);

		}

		{/// <B> small platform on top of lever, for completing the path of the ball </B>
			
			b2Vec2 vs[2];
			vs[0].Set(0.0f, 13.10f);
			vs[1].Set(-7.0f, 13.10f);		
			/// defined using a chain of vertices	
			drawChain(vs,2);
		}
		/// <HR>
		///<B> CENTRAL PART OF THE MACHINE</B>-----------------------------
		///<B> The stick, which is pivoted, and has a handle at top</B>	
		{	
			/// fd1 is the long part of the plank,of length 0.3 and height 10, defined using a plygonShape
			b2PolygonShape shape1;
			shape1.SetAsBox(0.15f, 5.0f, b2Vec2(0.0f,0.0f),0);  		
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 0.6;
			fd1->friction = 0.7;
			fd1->restitution = 1.0f;
			fd1->shape = &shape1;
			/// fd2 is the fixture definining the handle of the plank, using a boxshape of length 2 and height 0.3
			b2PolygonShape shape2;
			shape2.SetAsBox(1.0f,0.15f, b2Vec2(0.0f,4.85f),0);  		
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 0.6;
			fd2->friction = 0.7;
			fd2->restitution = 1.0f;
			fd2->shape = &shape2;
			///bd is the body definition of the plank
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-8.0f,18.0f);
			b2Body* plank = m_world->CreateBody(&bd);
			/// plank is then attached to its two fixtures,fd1 and fd2
			plank->CreateFixture(fd1);   			
			plank->CreateFixture(fd2);   			

			/// pivot is a box of length and height 0.3
			b2Body* pivot=drawBox(-8,18,0.15,0.15);

			/// A revoluteJoint is created between the pivot and the plank
			makeJoint(plank,pivot);
		}
		/// <B> The box and its platform which the stick hits </B>
		{
			/// drawing the platform 
			drawPlatform(b2Vec2(-6.5f,21.5f), b2Vec2(-4.5f,21.5f));


			////////////////////////////

    ///the box body definition and its fixture
			b2BodyDef bd1;
			bd1.type = b2_dynamicBody;
			bd1.position.Set(-5.5f,22.2f);
			b2Body* block = m_world->CreateBody(&bd1);
			b2PolygonShape square;
			square.SetAsBox(0.7f,0.7f);  		
			b2FixtureDef *fd = new b2FixtureDef;
			fd->density = 5.80;
			fd->friction = 0.0;
			fd->restitution = 0.4f;
			fd->shape = &square;
			block->CreateFixture(fd);

		}

		///<B> The pulley system </B>
		{
		
		///<B> the open box into which a block falls from the left , which in turn activates the pulley system</B>
		
	  ///bodydef for the open box
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(-2,19);
			bd->fixedRotation = true;

		///the open box has three fixtures defined below
		
		///fd1 is the horizontal fixture of the open box
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 8.0;
			fd1->friction = 0.5;
			fd1->restitution = 0.f;
			fd1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(1.5,0.2, b2Vec2(0.f,-1.4f), 0);
			fd1->shape = &bs1;


			///fd2 is the left vertical part of the open box
			b2FixtureDef *fd2 = new b2FixtureDef;

			fd2->density = 8.0;
			fd2->friction = 0.5;
			fd2->restitution = 0.f;
			fd2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.2,1.5, b2Vec2(1.5f,0.f), 0);
			fd2->shape = &bs2;

			///fd3 is the right vertical part of the open box
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 8.0;
			fd3->friction = 0.5;
			fd3->restitution = 0.f;
			fd3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.2,1.5, b2Vec2(-1.5f,0.f), 0);
			fd3->shape = &bs3;
  ///the three fixtures are made to the body to create the open box
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(fd1);
			box1->CreateFixture(fd2);
			box1->CreateFixture(fd3);

			///The bar connected to the open box through the pulley
			
			///body definition for the bar
			b2BodyDef *heavy = new b2BodyDef;
			heavy->type = b2_dynamicBody;
			heavy->position.Set(20,33);
			heavy->fixedRotation = true;
			
			///fd4 is the fixture for the bar having a box shape of length 10 and height 0.4 with density 7.2
			b2FixtureDef *fd4 = new b2FixtureDef;
			b2PolygonShape bs4;
			bs4.SetAsBox(5.0,0.2);
			fd4->shape = &bs4;
			fd4->friction = 1.0;
			fd4->density = 7.20;	  
			b2Body* box2 = m_world->CreateBody(heavy);
			
			///creating the fixture
			box2->CreateFixture(fd4);


			/// The pulley joint
			
			///the pulley is anchored at 4 points, box1 (the open box), box2 (the bar), and two other points which are positioned appropriately
			b2PulleyJointDef* myjoint = new b2PulleyJointDef();
			b2Vec2 worldAnchorOnBody1(-2, 19); /// Anchor point on body 1 in world axis (open box)
			b2Vec2 worldAnchorOnBody2(20, 33); /// Anchor point on body 2 in world axis (the bar)
			b2Vec2 worldAnchorGround1(-2, 35); /// Anchor point for ground 1 in world axis(left anchor point)
			b2Vec2 worldAnchorGround2(20, 35); /// Anchor point for ground 2 in world axis (right anchor point)
			float32 ratio = 1.0f; // Define ratio
			///initialisation of the pulley joint defined above
			myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      ///creating the joint
			m_world->CreateJoint(myjoint);

		}	
		/// <B> Smiley </B>
		{	

/// <B> the upward part of the pulley excluding the chain (those which are in sets of two) </B>



  ///fixture for the planks which are pivoted at the centre that are in contact with the bar from the pulley system
			b2PolygonShape shape1;
			shape1.SetAsBox(0.2f, 2.6f, b2Vec2(0.0f,0.0f),0);  		
			b2FixtureDef *fd = new b2FixtureDef;
			fd->density = 2.0;
			fd->friction = 1.0;
			fd->restitution = 0.6f;
			fd->shape = &shape1;
/// defining the shape to create the platform on which the spheres stay
			b2PolygonShape shape2;
			shape2.SetAsBox(0.2f, 0.2f, b2Vec2(0.0f,0.0f),0);

			b2RevoluteJointDef jointDef;
/// <B> creating two set of bodies, one is closely a mirror image of the other </B>



///the distance between the set of bodies is set to 8 (facilitated by the statement at the starting of for loop)
			for(int i=0;i<2;i++)		
			{
				int xAxis=16+8*i;
				int dir;
				if(i==0){
					dir=-1;
				}
				else{
					dir=1;
				}
///the two planks which are pivoted at he middle and connected to the pulley system (which when moved release the chain they are holding jointly)

      /// bd is the plank
      /// fd is the fixture for the plank, it has box shape with length 0.4 and height 5.2 
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(xAxis,31);
				bd.angle = pow(-1,i%2)*0.7;
				b2Body* plank = m_world->CreateBody(&bd);
				plank->CreateFixture(fd);   			

///bd1 is the bodydef for the pivot , and it is positioned appropriately
				b2BodyDef bd1;
				bd1.position.Set(xAxis,31);
				b2Body* pivot = m_world->CreateBody(&bd1);
				pivot->CreateFixture(&shape2,0.0f);			

				//jointDef.collideConnected = false;
			///a joint is defined to connect the plank and the pivot , the local anchors are set at the corresponding centres
				jointDef.bodyA = plank;
				jointDef.bodyB = pivot;
				jointDef.localAnchorA.Set(0.0f,0.0f);
				jointDef.localAnchorB.Set(0.0f,0.0f);
				m_world->CreateJoint(&jointDef);  

				///platform on which the spheres stay (using the function drawplatform) the distance between the two platforms is 8 (xAxis is 16 and 24 in the two iterations of the for loop) 
				drawPlatform(b2Vec2(xAxis-1,28.1f),b2Vec2(xAxis+1,28.1f));
        
        
        /// the spheres of radius 0.6 which fall off the platform to complete the eyes of the pulley
        ///the distance between the spheres is 8 as xAxis is 16 and 24 in the first and second iteration
				drawSphere(xAxis,28.4f,0.6f,0.3f,0.0f,0.0f);	
        
        
        //arcs on which the spheres fall , they are positioned at a distance of 8 from each other, xAxis being 16 and 24 in the two iterations
        drawArc(xAxis,23,1,PI/2,(3/2.0)*PI,30);


///the funnel like bodies which facilitate the spheres to fall onto the arcs made above 
				{
				
				///the left part of the funnel which has an arc at the top and a straight line at the bottom is drawn as a chain using 7 points whose coordinates are defined below . the direction variable is 1 and -1 respectively in the two iterations
					b2Vec2 vs[15];
					vs[0].Set(xAxis + dir*(3),29.1f);
					vs[1].Set(xAxis + dir*(2),27.1f);
					vs[2].Set(xAxis + dir*(1.85),27.0f);
					vs[3].Set(xAxis + dir*(1.70),26.9f);
					vs[4].Set(xAxis + dir*(1.55),26.8f);
					vs[5].Set(xAxis + dir*(1.40),26.7f);
					vs[6].Set(xAxis + dir*(1.40),25.5f);
				///	the right part is a vertical line , drawn as a chain with 2 points , whose coordinates are defined below
					drawChain(vs,7);
					vs[0].Set(xAxis - dir*(0.7),27.0f);
					vs[1].Set(xAxis - dir*(0.7),25.5f);
					drawChain(vs,2); 

				}


			}
		}




		{


///<B>the dynamic type chain like body which falls off the planks to complete the lips of the smiley</B>

			const int num=6;
///the body has 6 fixtures, each being of polygon shape , with 4 vertices , the upper vertices of all fixtures lie on an arc and lower vertices all lie on a different arc

///the position of vertices for these fixtures is done below

///the arc to get points to position the upper vertices , using the getArcVec function
			b2Vec2 vs1[num];
			getArcVec(20,29.8+(2.85/tan(PI/12.0)),2.85/sin(PI/12),11*PI/12,13*PI/12,vs1,num);
			
	///the arc for the lower vertices		
			b2Vec2 vs2[num];
			getArcVec(20,30.2+(2.85/tan(PI/12.0)),2.85/sin(PI/12),13*PI/12,11*PI/12,vs2,num);
			
	///these points are all filled into a new b2vec vs with size 2*num		
			b2Vec2 vs[2*num];
			for(int i=0;i<num;i++)
				vs[i]=vs1[i];
			for(int i=num;i<2*num;i++)
				vs[i]=vs2[i-num];
			
		///	bd is the body def for the part of the lips
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f,0.0f);
			b2Body* body = m_world->CreateBody(&bd);
			
			///six fixtures are created for the body in the for loop below , each fixture is polygon shape with upper two vertices lying on one arc and the lower two vertices lying an a different arc of bigger radius
			for(int i=0;i<num-1;i++){
				b2PolygonShape shape;
				b2Vec2 a[num]={vs[2*num-i-1],vs[2*num-i-2],vs[i+1],vs[i]};
				for(int i=0;i<num;i++){
					//printf("%f %f\n",a[i].x,a[i].y);
				}

				shape.Set(a,4);
				b2FixtureDef fd;
				fd.shape = &shape;
				fd.density = 0.10f;
				fd.friction = 1.0f;
				body->CreateFixture(&fd);	
			}
			//shape.Set(vs,8);
			//shape.SetAsBox(2.85f, 0.2f);

		}

		///Lips
		
		
		///the part of the lips which are static are created using the drawArc function with radius 2.85/sin(PI/12)
		{	
			drawArc(20,16+(2.85/tan(PI/12)),2.85/sin(PI/12),9*PI/12,11*PI/12+0.01,10);
			drawArc(20,16+(2.85/tan(PI/12)),2.85/sin(PI/12),13*PI/12-0.01,15*PI/12+0.01,10);

		}

	}

	sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
