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


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
	/// The following operations are done in this method :
  dominos_t::dominos_t()
  {
    //Ground
    b2Body* b1;
				/** Ground object is created, its shape is defined, and the shape is attached to the body */
    {
					 /*! - Var: shape<BR>
												DataType: b2EdgeShape<BR>
												value: EdgeShape on length 180<BR>
						*/
      b2EdgeShape shape;
						shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
						/** - Var: bd<BR>
												DataType: b2BodyDef<BR>
												value: body definition of ground as a static object
						*/
      b2BodyDef bd;
						/** - Var: b1<BR>
												DataType: b2Body* <BR>
												value: pointer to the new body in the world
						*/
      b1 = m_world->CreateBody(&bd);
						/// - the shape is attached to thw ground body
      b1->CreateFixture(&shape, 0.0f);
    }
      
    //Top horizontal shelf
				/** Polygon shelf is created on which the dominos are resting initially */ 
    {
					 /*! - Var: shape<BR>
												DataType: b2PolygonShape<BR>
												value: PolyGonShape on length 12 and height 0.5<BR>
						*/
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
						/** - Var: bd<BR>
												DataType: b2BodyDef<BR>
												value: body definition of shelf with required position coordinates
						*/
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
						/** - Var: ground<BR>
												DataType: b2Body* <BR>
												value: pointer to the new body in the world
						*/
      b2Body* ground = m_world->CreateBody(&bd);
						/// - the shape is attached to the polygon shelf
      ground->CreateFixture(&shape, 0.0f);
    }

    //Dominos
				/** 10 dominos are created  */ 
    {
					 /*! - Var: shape<BR>
												DataType: b2PolygonShape <BR>
												value: Box on length 0.2 and height 2<BR>
						*/
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
						
					 /*! - Var: fd<BR>
												DataType: b2FixtureDef <BR>
												value: shape is box shape defined earlier, density is 20 and friction coeff is 0.1 <BR>
						*/
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
						/** - Inside the loop of creation of dominos
							   		- Var: bd<BR>
														DataType: b2BodyDef<BR>
														value: Dynamic body definition at required position
						    		- Var: body<BR>
														DataType: b2Body*<BR>
														value: pointer to the body in the world
						    		- the fixture created earlier with shape, density and friction is attached to each of the bodies*/
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
      
    //Another horizontal shelf
				/**The shelf on which the balls are initially resting, its shape and fixture is defined here */
    {
					 /*! - Var: shape<BR>
												DataType: b2PolygonShape<BR>
												value: box of length 14, height 0.5
						*/
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
						/** - Var: bd<BR>
												DataType: b2BodyDef<BR>
												value: body definition with the required position
						*/
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
						/** - Var: ground<BR>
												DataType: b2Body* <BR>
												value: pointer to the new body in the world
						*/
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
				/** the vertical shelf which supports the pendulum (below the horizontal shelf which holds the domino*/
      {
					 /*! - Var: shape<BR>
												DataType: b2PolygonShape <BR>
												value: Box on length 0.5 and height 3.0<BR>
						*/
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
						/** - Var: bd<BR>
												DataType: b2BodyDef<BR>
												value: body definition of the shelf, at reqd position
						*/
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
						/** - Var: b2<BR>
												DataType: b2Body* <BR>
												value: pointer to the new body in the world
						*/
	b2 = m_world->CreateBody(&bd);
						/// - the shape is attached to the polygon vert shelf
	b2->CreateFixture(&shape, 10.0f);
      }

				/** the bob in the pendulum which strikes the dominos */
      b2Body* b4;
      {
					 /*! - Var: shape<BR>
												DataType: b2PolygonShape <BR>
												value: Box on length 0.25 and height 0.25<BR>
						*/
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	   
						/** - Var: bd<BR>
												DataType: b2BodyDef<BR>
												value: dynamic body definition of the bob, at reqd position
						*/
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
						/** - Var: b4<BR>
												DataType: b2Body* <BR>
												value: pointer to the bob in the world
						*/
	b4 = m_world->CreateBody(&bd);
						/// - the shape is attached to the bob
	b4->CreateFixture(&shape, 2.0f);
      }
				/** Connecting the vertical shelf with the bob,(joint definition) using an anchor at the necessary position*/
						/** - Var: jd <BR>
												DataType: b2RevoluteJointDef <BR>
												value: it contains the initialize() function which will be called to initialize the joint
						*/
      b2RevoluteJointDef jd;
						/** - Var: anchor <BR>
												DataType: b2Vec2 <BR>
												value: position of the anchor
						*/
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
						/// - the joint is initialized with the two bodies and the anchor, where the bodies have to be joined
      jd.Initialize(b2, b4, anchor);
						/// - the joint is created in the world
      m_world->CreateJoint(&jd);
    }
      
    //The train of small spheres
				/** The small spheres are defined here, its shape and position */
    {
      b2Body* spherebody;
	
					 /*! - Var: circle<BR>
												DataType: b2CircleShape<BR>
												value: CircleShape of radius 0.5 <BR>
						*/
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
					 /*! - Var: ballfd<BR>
												DataType: b2FixtureDef <BR>
												value: shape is circle shape defined earlier, density is 1 and friction coeff is 0.0 <BR>
						*/
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
						/** - Inside the loop of creation of spheres
							   		- Var: ballbd<BR>
														DataType: b2BodyDef<BR>
														value: Dynamic body definition at required position
						    		- Var: spherebody<BR>
														DataType: b2Body*<BR>
														value: pointer to the sphere in the world
						    		- the fixture created earlier with shape, density and friction is attached to each of the bodies*/
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }

    //The pulley system
    /** The entire pulley system (i.e the open box, the bar and the pulley joints with their shapes and position) is defined here*/
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      //The open box
      /** The open box in which the balls fall is created here*/ 
      /** The open box is created by applying fixture to 2 vertical and 1 horizontal box shaped polygons*/
      /*! - Var: fd1<BR>
            DataType: b2FixtureDef*<BR>
            value: box shaped polygon defined below, density is 10, friction coeff is 0.5 and restitution is 0<BR>
      */
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      
      /*! - Var: bs1<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 4 and height 0.4<BR>
      */
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      
      /*! - Var: fd2<BR>
            DataType: b2FixtureDef*<BR>
            value: box shaped polygon defined below, density is 10, friction coeff is 0.5 and restitution is 0<BR>
      */
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      
      /*! - Var: bs2<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 0.4 and height 4<BR>
      */
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      
      /*! - Var: fd2<BR>
            DataType: b2FixtureDef*<BR>
            value: box shaped polygon defined below, density is 10, friction coeff is 0.5 and restitution is 0<BR>
      */
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      
      /*! - Var: bs3<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 0.4 and height 4<BR>
      */
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
      
      /*! - Var: box1<BR>
            DataType: b2Body*<BR>
            value: pointer to the open box formed from three fixtures i.e. fd1, fd2 and fd3<BR>
      */ 
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      /** The bar that is tied on the other side of pulley is defined here*/
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      
      /*! - Var: box2<BR>
            DataType: b2Body*<BR>
            value: pointer to the bar in the world with density and position specified<BR>
      */
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      /** The pulley joints are defined here*/
      /*! - Var: myjoint<BR>
            DataType: b2PulleyJointDef*<BR>
            value: Pulley Joint defined by 4 anchors i.e 2 on bodies(one on each body) and 2 on ground; rope length ratio is 1<BR>
      */
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    //The revolving horizontal platform
    /** The horizontal revolving platform on which the heavy sphere is kept*/
    {
      /*! - Var: shape<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 4.4 and height 0.4<BR>
      */
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);

	     /*! - Var: bd<BR>
            DataType: b2BodyDef<BR>
            value: Dynamic body definition and position specified<BR>
      */
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      
      /*! - Var: body<BR>
            DataType: b2Body*<BR>
            value: the horizontal revolving platform<BR>
      */
      b2Body* body = m_world->CreateBody(&bd);
      
      /*! - Var: fd<BR>
            DataType: b2FixtureDef<BR>
            value: box shaped polygon as defined above, density is 1.0<BR>
      */
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      /*! - Var: shape2<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 0.4 and height4.0<BR>
      */
      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      
      /*! - Var: bd2<BR>
            DataType: b2BodyDef<BR>
            value: Static body definition and position specified<BR>
      */
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      
      /*! - Var: body2<BR>
            DataType: b2Body*<BR>
            value: pointer to a static box that acts as a hinge for the revolving platform<BR>
      */
      b2Body* body2 = m_world->CreateBody(&bd2);

      /*! - Var: jointDef<BR>
            DataType: b2RevoluteJointDef<BR>
            value: revolute joint with revolving platform and static hinge anchored at required position<BR>
      */
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //The heavy sphere on the platform
    /** The heavy sphere which falls down on the see-saw system*/
    {
      /*! - Var: sbody<BR>
            DataType: b2Body*<BR>
            value: pointer to the heavy sphere on the platform<BR>
      */
      b2Body* sbody;
      
      /*! - Var: circle<BR>
            DataType: b2CircleShape<BR>
            value: Circle shape of radius 1.0<BR>
      */
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
	     /*! - Var: ballfd<BR>
            DataType: b2FixtureDef<BR>
            value: shape is circle, density is 50, friction is 0 and restitution is also 0<BR>
      */
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      
      /*! - Var: ballbd<BR>
            DataType: b2BodyDef<BR>
            value: Dynamic body definition and position specified<BR>
      */
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    //The see-saw system at the bottom
    /** The see-saw system that is triggered by the falling sphere*/
    {
      //The triangle wedge
      /** The shape, size and position of the wedge of the see-saw system are defined here*/
      /*! - Var: sbody<BR>
            DataType: b2Body*<BR>
            value: pointer to the triangular wedge of the see-saw system<BR>
      */
      b2Body* sbody;
      
      /*! - Var: poly<BR>
            DataType: b2PolygonShape<BR>
            value: shape is triangle with defined coordinates<BR>
      */
      b2PolygonShape poly;
      
      /*! - Var: vertices<BR>
            DataType: b2Vec2<BR>
            value: array of vectors storing the coordinates of three vertices of the triangle<BR>
      */
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      
      /*! - Var: wedgefd<BR>
            DataType: b2FixtureDef<BR>
            value: shape is triangle, density is 10, friction coeff is 0 and restitution is 0<BR>
      */
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      
      /*! - Var: wedgebd<BR>
            DataType: b2BodyDef<BR>
            value: Static body definition at required position<BR>
      */
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      /** The plank kept on the top of the wedge is created here*/
      /*! - Var: shape<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 30 and height 0.4<BR>
      */
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      
      /*! - Var: bd2<BR>
            DataType: b2BodyDef<BR>
            value: Dynamic body with position coordinates set<BR>
      */
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      
      /*! - Var: body<BR>
            DataType: b2Body*<BR>
            value: the plank on the wedge<BR>
      */
      b2Body* body = m_world->CreateBody(&bd2);
      
      /*! - Var: fd2<BR>
            DataType: b2FixtureDef*<BR>
            value: box shaped polygon as defined above, density is 1.0<BR>
      */
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      /*! - Var: jd<BR>
            DataType: b2RevoluteJointDef<BR>
            value: revolute joint with the wedge and the plank anchored at coordinates(30, 1.5)<BR>
      */
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      /** The shape, size and position of the light box kept on the plank are defined here*/
      /*! - Var: shape2<BR>
            DataType: b2PolygonShape<BR>
            value: box of length 4.0 and height 4.0<BR>
      */
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      
      /*! - Var: bd3<BR>
            DataType: b2BodyDef<BR>
            value: Dynamic body definition at required position<BR>
      */
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      
      /*! - Var: body3<BR>
            DataType: b2Body*<BR>
            value: the light box on the plank<BR>
      */
      b2Body* body3 = m_world->CreateBody(&bd3);
      
      /*! - Var: fd3<BR>
            DataType: b2FixtureDef<BR>
            value: box shaped polygon as defined above, density is 0.01<BR>
      */
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
