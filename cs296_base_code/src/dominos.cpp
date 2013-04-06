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
using namespace std;

#include "dominos.hpp"

namespace cs296
{
 	dominos_t::dominos_t()
  	{
    	//Ground
    	{
    		b2Body* b1;
   	   		b2EdgeShape shape;
     		shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      		b2BodyDef bd;
      		b1 = m_world->CreateBody(&bd);
      		b1->CreateFixture(&shape, 0.0f);
    	}
		
		{
      		b2PolygonShape shape;
      		shape.SetAsBox(1.6f, 0.15f);
		
     		b2BodyDef bd;
      		bd.position.Set(-48.5f, 40.0f);
      		b2Body* ground = m_world->CreateBody(&bd);
      		ground->CreateFixture(&shape, 0.0f);
      		
      		b2Body* spherebody;
	
		    b2CircleShape circle;
      		circle.m_radius = 0.5;
	
      		b2FixtureDef ballfd;
      		ballfd.shape = &circle;
      		ballfd.density = 1.0f;
      		ballfd.friction = 0.0f;
      		ballfd.restitution = 0.85f;
	
	  		b2BodyDef ballbd;
	  		ballbd.type = b2_dynamicBody;
	  		ballbd.position.Set(-48.5f,40.5f);
	  		spherebody = m_world->CreateBody(&ballbd);
	  		spherebody->CreateFixture(&ballfd);
	  		
	  		b2Vec2 force = b2Vec2(110,0);
			spherebody->ApplyForce(force, spherebody->GetPosition());
    	}
		
		{
      		b2PolygonShape shape;
      		shape.SetAsBox(3.6f, 0.15f);
		
     		b2BodyDef bd;
      		bd.position.Set(-43.8f, 35.0f);
      		b2Body* ground = m_world->CreateBody(&bd);
      		ground->CreateFixture(&shape, 0.0f);
      		
    	}
		
		{
      		b2PolygonShape shape;
      		shape.SetAsBox(0.15f,1.45f);
		
     		b2BodyDef bd;
      		bd.position.Set(-41.4f, 36.70f);
      		b2Body* ground = m_world->CreateBody(&bd);
      		ground->CreateFixture(&shape, 0.0f);
    	}
		
		{		
			////////
			b2PolygonShape shape;
    	  	shape.SetAsBox(0.15f,1.8f);
		
    		b2BodyDef bd1;
    	  	bd1.position.Set(-40.2f, 36.80f);
    	  	b2Body* body1 = m_world->CreateBody(&bd1);
    	  	body1->CreateFixture(&shape, 0.0f);
    		/////////
			
			b2BodyDef *bd = new b2BodyDef;
    	  	bd->type = b2_dynamicBody;
    	  	bd->position.Set(-40.2f,38.65f);		
			
			b2FixtureDef *fd1 = new b2FixtureDef;
    	  	fd1->density = 5.0;
    	  	fd1->friction = 0.5;
    	  	fd1->restitution = 0.f;
    		fd1->shape = new b2PolygonShape;
    	  	b2PolygonShape bs1;
    	  	bs1.SetAsBox(2.8,0.15, b2Vec2(-0.8f,-0.2f), 0);
    	  	fd1->shape = &bs1;
    	  	b2FixtureDef *fd2 = new b2FixtureDef;
    	 	fd2->density = 5.0;
    	  	fd2->friction = 0.5;
    	  	fd2->restitution = 0.f;
    	  	fd2->shape = new b2PolygonShape;
    	  	b2PolygonShape bs2;
    	  	bs2.SetAsBox(0.15,0.4, b2Vec2(2.15f,0.05f), 0);
    	  	fd2->shape = &bs2;
    	  	b2FixtureDef *fd3 = new b2FixtureDef;
    	  	fd3->density = 5.0;
    	  	fd3->friction = 0.5;
    	  	fd3->restitution = 0.f;
    	  	fd3->shape = new b2PolygonShape;
    	 	b2PolygonShape bs3;
    	  	bs3.SetAsBox(0.50,0.15, b2Vec2(2.60f,0.4f), 0);
    	  	fd3->shape = &bs3;
    	   
    	  	b2Body* body2 = m_world->CreateBody(bd);
    	  	body2->CreateFixture(fd1);
    	  	body2->CreateFixture(fd2);
    	  	body2->CreateFixture(fd3);
	
			b2RevoluteJointDef jointDef;
    	  	jointDef.bodyA = body1;
    	  	jointDef.bodyB = body2;
    	  	jointDef.localAnchorA.Set(0.0f,1.60f);
    	  	jointDef.localAnchorB.Set(0.0f,-0.15f);
    	  	//jointDef.collideConnected = false;
    	  	m_world->CreateJoint(&jointDef);
		}
		
		{
      		b2PolygonShape shape;
      		shape.SetAsBox(0.4f, 0.15f);
		
     		b2BodyDef bd;
      		bd.position.Set(-36.8f, 38.10f);
      		b2Body* ground = m_world->CreateBody(&bd);
      		ground->CreateFixture(&shape, 0.0f);
      		
      		b2Body* spherebody;
	
      		b2CircleShape circle;
      		circle.m_radius = 0.5;
	
      		b2FixtureDef ballfd;
      		ballfd.shape = &circle;
      		ballfd.density = 8.0f;
      		ballfd.friction = .6f;
      		ballfd.restitution = 0.0f;
	
      
	  		b2BodyDef ballbd;
	 	 	ballbd.type = b2_dynamicBody;
	  		ballbd.position.Set(-36.8f, 38.15f);
	  		spherebody = m_world->CreateBody(&ballbd);
	  		spherebody->CreateFixture(&ballfd);
    	}
    	
    	{
      		b2PolygonShape shape;
      		shape.SetAsBox(3.0f, 0.15f);
		
     		b2BodyDef bd;
      		bd.position.Set(-33.5f, 35.0f);
      		bd.angle = 3.14 - 0.2;
      		b2Body* ground = m_world->CreateBody(&bd);
      		ground->CreateFixture(&shape, 0.0f);
      		
    	}
    	
    	{
      		
      		b2BodyDef bd;
     		bd.type = b2_dynamicBody;
      		bd.position.Set(-21.0f, 31.0f);
      		
      		b2PolygonShape shape1;
      		shape1.SetAsBox(8.0f, 0.15f, b2Vec2(-3.0f,0.0f),0);  			
      		//bd.angle = 3.14 - 0.3;
      		b2Body* plank = m_world->CreateBody(&bd);
      		//plank->CreateFixture(&shape, 0.0f);
      		b2FixtureDef *fd1 = new b2FixtureDef;
    	  	fd1->density = 5.0;
    	  	fd1->friction = 0.7;
    	  	fd1->restitution = 0.f;
    		fd1->shape = &shape1;
    		
    		b2PolygonShape shape;
      		shape.SetAsBox(0.8f, 0.8f, b2Vec2(4.2f,0.8f),0);  			
      		//bd.angle = 3.14 - 0.3;
      		//plank->CreateFixture(&shape, 0.0f);
      		b2FixtureDef *fd2 = new b2FixtureDef;
    	  	fd2->density = 7.5f;
    	  	fd2->friction = 0.0f;
    	  	fd2->restitution = 0.85f;
    		fd2->shape = &shape;
    		
    		plank->CreateFixture(fd1);
    		plank->CreateFixture(fd2);
    		
    		b2PolygonShape shape2;
    		shape2.SetAsBox(0.15f,0.15f);
    		
    		b2BodyDef bd1;
    		bd1.position.Set(-21.0f,31.0f);
    		b2Body* pivot = m_world->CreateBody(&bd1);
			pivot->CreateFixture(&shape2,0.0f);
    		
 			b2RevoluteJointDef jointDef;
    	  	jointDef.bodyA = plank;
    	  	jointDef.bodyB = pivot;
    	  	jointDef.localAnchorA.Set(0.0f,0.0f);
    	  	jointDef.localAnchorB.Set(0.0f,0.0f);
    	  	//jointDef.collideConnected = false;
    	  	m_world->CreateJoint(&jointDef);   			   	  	
      		
    	}
    	/*
    	{
    		b2Body* b1;
   	   		b2EdgeShape shape1;
     		shape1.Set(b2Vec2(-55.0f,7.0f), b2Vec2(-30.0f, 7.0f));
      		b2BodyDef bd1;
      		b1 = m_world->CreateBody(&bd1);
      		b1->CreateFixture(&shape1, 0.0f);
      		
      		b2PolygonShape shape;
      		shape.SetAsBox(0.40f, 0.15f);
     		b2BodyDef bd;
      		bd.position.Set(-41.0f, 9.0f);
      		b2Body* ground = m_world->CreateBody(&bd);
      		ground->CreateFixture(&shape, 0.0f);
      		
      		b2BodyDef *bd2 = new b2BodyDef;
    	  	bd2->type = b2_dynamicBody;
    	  	bd2->position.Set(-41.0f,9.1f);		
			
			b2FixtureDef *fd1 = new b2FixtureDef;
    	  	fd1->density = 0.01f;
    	  	fd1->friction = 0.8;
    	  	fd1->restitution = 0.0f;
    		fd1->shape = new b2PolygonShape;
    	  	b2PolygonShape bs1;
    	  	bs1.SetAsBox(6.0f,0.10f, b2Vec2(2.0f,0.0f), 0);
    	  	fd1->shape = &bs1;
    	  	b2FixtureDef *fd2 = new b2FixtureDef;
    	 	fd2->density = 0.01f;
    	  	fd2->friction = 0.8;
    	  	fd2->restitution = 0.0f;
    	  	fd2->shape = new b2PolygonShape;
    	  	b2PolygonShape bs2;
    	  	bs2.SetAsBox(0.1f,0.4f, b2Vec2(-3.9f,0.2f), 0);
    	  	fd2->shape = &bs2;
      	   
    	  	b2Body* body2 = m_world->CreateBody(bd2);
    	  	body2->CreateFixture(fd1);
    	  	body2->CreateFixture(fd2);     		
      		
      		b2Body* spherebody;
		    b2CircleShape circle;
      		circle.m_radius = 0.5;
	
      		b2FixtureDef ballfd;
      		ballfd.shape = &circle;
      		ballfd.density = 0.016f;
      		ballfd.friction = 0.0f;
      		ballfd.restitution = 0.85f;
	
	  		b2BodyDef ballbd;
	  		ballbd.type = b2_dynamicBody;
	  		ballbd.position.Set(-44.85f,9.15f);
	  		spherebody = m_world->CreateBody(&ballbd);
	  		spherebody->CreateFixture(&ballfd);
      		
    	}
    	
 		*/
 		{
    		b2Body* b1;
   	   		b2EdgeShape shape1;
     		shape1.Set(b2Vec2(-55.0f,3.0f), b2Vec2(-30.0f, 3.0f));
      		b2BodyDef bd;
      		b1 = m_world->CreateBody(&bd);
      		b1->CreateFixture(&shape1, 0.0f);
      		
      		
      		//The triangle wedge
      		b2Body* sbody;
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
      		wedgebd.position.Set(-36.70f, 3.0f);
      		sbody = m_world->CreateBody(&wedgebd);
      		sbody->CreateFixture(&wedgefd);
		
      		//The plank on top of the wedge
      		b2PolygonShape shape;
      		shape.SetAsBox(4.70f, 0.15f);
      		b2BodyDef bd2;
      		bd2.position.Set(-36.7f, 7.0f);
      		bd2.type = b2_dynamicBody;
      		b2Body* body = m_world->CreateBody(&bd2);
      		b2FixtureDef *fd2 = new b2FixtureDef;
      		fd2->density = 0.5f;
      		fd2->shape = new b2PolygonShape;
      		fd2->shape = &shape;
      		body->CreateFixture(fd2);
			
      		b2RevoluteJointDef jd;
      		b2Vec2 anchor;
      		anchor.Set(-36.70f, 7.0f);
      		jd.Initialize(sbody, body, anchor);
      		m_world->CreateJoint(&jd);
		
      		//The light box on the right side of the see-saw
      		b2PolygonShape shape2;
      		shape2.SetAsBox(0.5f, 0.5f);
      		b2BodyDef bd3;
      		bd3.position.Set(-40.90f, 7.50f);
      		bd3.type = b2_dynamicBody;
      		b2Body* body3 = m_world->CreateBody(&bd3);
      		b2FixtureDef *fd3 = new b2FixtureDef;
      		fd3->density = 0.7f;
      		fd3->shape = new b2PolygonShape;
      		fd3->shape = &shape2;
      		body3->CreateFixture(fd3);
      		
      		//The light box 2 on the right side of the see-saw
      		b2PolygonShape shape3;
      		shape3.SetAsBox(0.5f, 0.5f);
      		b2BodyDef bd4;
      		bd4.position.Set(-32.50f, 7.50f);
      		bd4.type = b2_dynamicBody;
      		b2Body* body4 = m_world->CreateBody(&bd4);
      		b2FixtureDef *fd4 = new b2FixtureDef;
      		fd4->density = 0.7f;
      		fd4->shape = new b2PolygonShape;
      		fd4->shape = &shape3;
      		body4->CreateFixture(fd4);
   
    	}   	   	 
    	
    	{
    		b2BodyDef bd;
    		b2Body* platform = m_world->CreateBody(&bd);
    		b2Vec2 vs[3];
			vs[0].Set(-10.0f, 40.0f);
			vs[1].Set(-5.50f, 40.0f);
			vs[2].Set(42.0f, 34.0f);
			b2ChainShape chain;
			chain.CreateChain(vs, 3);
			platform->CreateFixture(&chain, 0.0f);
    		
    		/*
    		b2Body* b1;
   	   		b2EdgeShape shape1;
     		shape1.Set(b2Vec2(-10.0f,40.0f), b2Vec2(42.0f, 34.0f));
      		b2BodyDef bd;
      		//bd.angle = 3.14 - 0.1;
      		b1 = m_world->CreateBody(&bd);
      		b1->CreateFixture(&shape1, 0.0f);*/
      		
      		b2Body* spherebody;
		    b2CircleShape circle;
      		circle.m_radius = 0.8;
	
      		b2FixtureDef ballfd;
      		ballfd.shape = &circle;
      		ballfd.density = 0.8f;
      		ballfd.friction = 0.0f;
      		ballfd.restitution = 0.5f;
	
	  		b2BodyDef ballbd;
	  		ballbd.type = b2_dynamicBody;
	  		ballbd.position.Set(-6.70f,40.0f);
	  		spherebody = m_world->CreateBody(&ballbd);
	  		spherebody->CreateFixture(&ballfd);
      		
    	}
    	 
    	  	
    	{
    		
    		b2PolygonShape shape1;
    	  	shape1.SetAsBox(0.15f, 2.0f, b2Vec2(0.0f,0.0f),0);  		
    	  	b2FixtureDef *fd1 = new b2FixtureDef;
    		fd1->density = 2.0;
    		fd1->friction = 0.7;
    		fd1->restitution = 0.6f;
    		fd1->shape = &shape1;

			b2PolygonShape shape2;
    		shape2.SetAsBox(0.15f, 0.15f, b2Vec2(0.0f,0.0f),0);
    		
    		b2RevoluteJointDef jointDef;
    		
    		  	
    		for(int i=0;i<5;i++)		
    		{
    	  		
    			b2BodyDef bd;
	     		bd.type = b2_dynamicBody;
    	  		bd.position.Set(42.50f - (i%2)*0.7, 33.0f - 3*i);
    	  		b2Body* plank = m_world->CreateBody(&bd);
    	  		plank->CreateFixture(fd1);   			
    	  		
    	  		b2BodyDef bd1;
    			bd1.position.Set(42.50f - (i%2)*0.7 , 33.0f - 3*i);
    	  		b2Body* pivot = m_world->CreateBody(&bd1);
    			pivot->CreateFixture(&shape2,0.0f);			
    			
 				//jointDef.collideConnected = false;
 				jointDef.bodyA = plank;
    			jointDef.bodyB = pivot;
    			jointDef.localAnchorA.Set(0.0f,0.0f);
    			jointDef.localAnchorB.Set(0.0f,0.0f);
    		  	m_world->CreateJoint(&jointDef);
    		}
    	}
    	
    	{
    		b2BodyDef bd;
    		b2Body* platform = m_world->CreateBody(&bd);
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
			b2ChainShape chain;
			chain.CreateChain(vs, 10);
			platform->CreateFixture(&chain, 0.0f);
			
			b2Body* spherebody;
			b2Body* spherebody1;			
		    b2CircleShape circle;
      		circle.m_radius = 0.4;
		     		
      		b2FixtureDef ballfd;
      		ballfd.shape = &circle;
      		ballfd.density = 0.4f;
      		ballfd.friction = 0.0f;
      		ballfd.restitution = 0.5f;
	
	  		b2BodyDef ballbd;
	  		ballbd.type = b2_dynamicBody;
	  		ballbd.position.Set(41.40f,19.40f);
	  		spherebody = m_world->CreateBody(&ballbd);
	  		spherebody->CreateFixture(&ballfd);
			
			b2BodyDef ballbd1;
	  		ballbd1.type = b2_dynamicBody;
	  		ballbd1.position.Set(39.40f,19.40f);
	  		spherebody1 = m_world->CreateBody(&ballbd1);
	  		spherebody1->CreateFixture(&ballfd);
	  	

    	}  	
    	
    	{
    		b2PolygonShape shape1;
    	  	shape1.SetAsBox(0.1f, 2.0f, b2Vec2(0.0f,0.0f),0);  		
    	  	b2FixtureDef *fd1 = new b2FixtureDef;
    		fd1->density = 2.35;
    		fd1->friction = 0.7;
    		fd1->restitution = 0.60f;
    		fd1->shape = &shape1;

			b2PolygonShape shape2;
    		shape2.SetAsBox(0.1f, 0.1f, b2Vec2(0.0f,0.0f),0);
    		
    		b2RevoluteJointDef jointDef;
    		b2BodyDef bd;
	     	bd.type = b2_dynamicBody;
    	  	bd.position.Set(22.50f,13.0f);
    	  	b2Body* plank = m_world->CreateBody(&bd);
    	  	plank->CreateFixture(fd1);   			
    	  		
    	  	b2BodyDef bd1;
    		bd1.position.Set(22.50f,13.0f);
    	  	b2Body* pivot = m_world->CreateBody(&bd1);
    		pivot->CreateFixture(&shape2,0.0f);			
    		
 			//jointDef.collideConnected = false;
 			jointDef.bodyA = plank;
    		jointDef.bodyB = pivot;
    		jointDef.localAnchorA.Set(0.0f,0.0f);
    		jointDef.localAnchorB.Set(0.0f,0.0f);
    		m_world->CreateJoint(&jointDef);
    		
    		///////////////////////////////////
    		
    		
    		b2BodyDef bd2;
    		b2Body* platform = m_world->CreateBody(&bd2);
    		b2Vec2 vs[2];
			vs[0].Set(20.0f, 13.10f);
			vs[1].Set(3.75f, 13.10f);			
			b2ChainShape chain;
			chain.CreateChain(vs, 2);
			platform->CreateFixture(&chain, 0.0f);
    		
    	}
    	
    	{
    		b2BodyDef bd;
    		b2Body* platform = m_world->CreateBody(&bd);
    		b2Vec2 vs[46];
			vs[0].Set(25.50f, 12.50f);
			vs[1].Set(20.50f, 5.0f);
			vs[2].Set(20.25f, 4.75f);
			vs[3].Set(20.00f, 4.60f);
			vs[4].Set(19.80f, 4.50f);
			vs[5].Set(19.65f, 4.45f);
			vs[6].Set(-4.65f, 4.45f);
			
			for (int i=1; i<=30; i++)
			{
				vs[i+6].Set(0 - sqrt(abs(pow(3.75,2) - pow(4.45 + 0.25*i - 8.2,2))) - 4.65, 4.45 + 0.25*i);
			}		
			
			vs[37].Set(-4.35f, 11.90f);
			vs[38].Set(-4.10f, 11.85f);
			vs[39].Set(-3.90f, 11.80f);
			vs[40].Set(-3.75f, 11.75f);
			vs[41].Set(-3.85f, 11.70f);
			vs[42].Set(-3.80f, 11.65f);
			vs[43].Set(-3.76f, 11.60f);
			vs[44].Set(-3.73f, 11.55f);
			vs[45].Set(-3.71f, 11.50f);
						
			b2ChainShape chain;
			chain.CreateChain(vs, 46);
			platform->CreateFixture(&chain, 0.0f);
			
			
			b2Body* spherebody;			
		    b2CircleShape circle;
      		circle.m_radius = 0.4;
		     		
      		b2FixtureDef ballfd;
      		ballfd.shape = &circle;
      		ballfd.density = 0.3f;
      		ballfd.friction = 0.0f;
      		ballfd.restitution = 1.0f;
	
	  		b2BodyDef ballbd;
	  		ballbd.type = b2_dynamicBody;
	  		ballbd.position.Set(0.0f,4.85f);
	  		spherebody = m_world->CreateBody(&ballbd);
	  		spherebody->CreateFixture(&ballfd);
	  	
    	}
    	
    	{
    		b2BodyDef bd1;
    		b2Body* platform = m_world->CreateBody(&bd1);
    		b2Vec2 vs[2];
			vs[0].Set(-4.65f, 6.2f);
			vs[1].Set(12.50f, 6.2f);			
			b2ChainShape chain;
			chain.CreateChain(vs, 2);
			platform->CreateFixture(&chain, 0.0f);
			
			//The triangle wedge
      		b2Body* sbody;
      		b2PolygonShape poly;
      		b2Vec2 vertices[3];
      		vertices[0].Set(-1,0);
      		vertices[1].Set(1,0);
      		vertices[2].Set(0,2.0);
      		poly.Set(vertices, 3);
      		b2FixtureDef wedgefd;
      		wedgefd.shape = &poly;
      		wedgefd.density = 10.0f;
      		wedgefd.friction = 0.0f;
      		wedgefd.restitution = 1.0f;
      		b2BodyDef wedgebd;
      		wedgebd.position.Set(0.0f, 6.20f);
      		sbody = m_world->CreateBody(&wedgebd);
      		sbody->CreateFixture(&wedgefd);
      		
      		//The plank on top of the wedge
      		b2PolygonShape shape;
      		shape.SetAsBox(5.0f, 0.15f, b2Vec2(0.0f,0.0f), 0);
      		b2BodyDef bd2;
      		bd2.position.Set(0.0f, 8.2f);
      		bd2.type = b2_dynamicBody;
      		b2Body* body = m_world->CreateBody(&bd2);
      		b2FixtureDef *fd2 = new b2FixtureDef;
      		fd2->density = 0.5f;
      		fd2->shape = new b2PolygonShape;
      		fd2->shape = &shape;
      		
      		b2PolygonShape bs1;
    	  	b2Vec2 vertices1[4];
      		vertices1[0].Set(2.0f,0.0f);
      		vertices1[1].Set(5.0f,0.0f);
      		vertices1[2].Set(5.0f,3.15f);
      		vertices1[3].Set(2.0f,4.40f);
      		b2FixtureDef *fd1 = new b2FixtureDef;
      		bs1.Set(vertices1, 4);
    	  	fd1->shape = &bs1;
    	  	   	  	
    	  	body->CreateFixture(fd1);			
    	  	body->CreateFixture(fd2);
    	  	      		
      		b2RevoluteJointDef jd;
      		b2Vec2 anchor;
      		anchor.Set(0.0f, 8.20f);
      		jd.Initialize(sbody, body, anchor);
      		m_world->CreateJoint(&jd);
      		
		}
		
		{
			b2BodyDef bd2;
    		b2Body* platform = m_world->CreateBody(&bd2);
    		b2Vec2 vs[2];
			vs[0].Set(0.0f, 13.10f);
			vs[1].Set(-7.0f, 13.10f);			
			b2ChainShape chain;
			chain.CreateChain(vs, 2);
			platform->CreateFixture(&chain, 0.0f);
		}
		
		{
			b2PolygonShape shape1;
    	  	shape1.SetAsBox(0.15f, 5.0f, b2Vec2(0.0f,0.0f),0);  		
    	  	b2FixtureDef *fd1 = new b2FixtureDef;
    		fd1->density = 0.6;
    		fd1->friction = 0.7;
    		fd1->restitution = 1.0f;
    		fd1->shape = &shape1;
			
			b2PolygonShape shape2;
    	  	shape2.SetAsBox(1.0f,0.15f, b2Vec2(0.0f,4.85f),0);  		
    	  	b2FixtureDef *fd2 = new b2FixtureDef;
    		fd2->density = 0.6;
    		fd2->friction = 0.7;
    		fd2->restitution = 1.0f;
    		fd2->shape = &shape2;

			b2PolygonShape shape3;
    		shape3.SetAsBox(0.15f, 0.15f, b2Vec2(0.0f,0.0f),0);
    		
    		b2RevoluteJointDef jointDef;
			
			b2BodyDef bd;
	     	bd.type = b2_dynamicBody;
    	 	bd.position.Set(-8.0f,18.0f);
    	 	b2Body* plank = m_world->CreateBody(&bd);
    	 	plank->CreateFixture(fd1);   			
    	 	plank->CreateFixture(fd2);   			
    	 	
    	 	b2BodyDef bd1;
    		bd1.position.Set(-8.0f,18.0f);
    	  	b2Body* pivot = m_world->CreateBody(&bd1);
    		pivot->CreateFixture(&shape3,0.0f);			
    			
 			//jointDef.collideConnected = false;
 			jointDef.bodyA = plank;
    		jointDef.bodyB = pivot;
    		jointDef.localAnchorA.Set(0.0f,0.0f);
    		jointDef.localAnchorB.Set(0.0f,0.0f);
    		m_world->CreateJoint(&jointDef);
		}
		
		{
			b2Body* platform;
   	   		b2EdgeShape shape;
     		shape.Set(b2Vec2(-6.5f,21.5f), b2Vec2(-4.5f,21.5f));
      		b2BodyDef bd;
      		platform = m_world->CreateBody(&bd);
      		platform->CreateFixture(&shape, 0.0f);
      		
      		////////////////////////////
      		
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
		
		//The pulley system
    	{
    	  	b2BodyDef *bd = new b2BodyDef;
      		bd->type = b2_dynamicBody;
      		bd->position.Set(-2,19);
      		bd->fixedRotation = true;
      
      		//The open box
      		b2FixtureDef *fd1 = new b2FixtureDef;
      		fd1->density = 8.0;
      		fd1->friction = 0.5;
      		fd1->restitution = 0.f;
      		fd1->shape = new b2PolygonShape;
      		b2PolygonShape bs1;
      		bs1.SetAsBox(1.5,0.2, b2Vec2(0.f,-1.4f), 0);
      		fd1->shape = &bs1;
      		b2FixtureDef *fd2 = new b2FixtureDef;
      		fd2->density = 8.0;
      		fd2->friction = 0.5;
      		fd2->restitution = 0.f;
      		fd2->shape = new b2PolygonShape;
      		b2PolygonShape bs2;
      		bs2.SetAsBox(0.2,1.5, b2Vec2(1.5f,0.f), 0);
      		fd2->shape = &bs2;
     		b2FixtureDef *fd3 = new b2FixtureDef;
      		fd3->density = 8.0;
      		fd3->friction = 0.5;
      		fd3->restitution = 0.f;
      		fd3->shape = new b2PolygonShape;
      		b2PolygonShape bs3;
      		bs3.SetAsBox(0.2,1.5, b2Vec2(-1.5f,0.f), 0);
      		fd3->shape = &bs3;
      		 
      		b2Body* box1 = m_world->CreateBody(bd);
      		box1->CreateFixture(fd1);
      		box1->CreateFixture(fd2);
      		box1->CreateFixture(fd3);
		
      		//The bar
      		b2BodyDef *heavy = new b2BodyDef;
      		heavy->type = b2_dynamicBody;
      		heavy->position.Set(20,33);
      		heavy->fixedRotation = true;
      		b2FixtureDef *fd4 = new b2FixtureDef;
      		b2PolygonShape bs4;
      		bs4.SetAsBox(5.0,0.2);
      		fd4->shape = &bs4;
      		fd4->friction = 1.0;
      		fd4->density = 7.20;	  
      		b2Body* box2 = m_world->CreateBody(heavy);
      		box2->CreateFixture(fd4);
      		
      		/*//support
      		b2BodyDef sp;
    		b2Body* platform = m_world->CreateBody(&sp);
    		b2Vec2 vs[2];
			vs[0].Set(20.2f, 32.60f);
			vs[1].Set(19.8f, 32.60f);			
			b2ChainShape chain;
			chain.CreateChain(vs, 2);
			platform->CreateFixture(&chain, 0.0f);
      		*/

      		// The pulley joint
      		b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      		b2Vec2 worldAnchorOnBody1(-2, 19); // Anchor point on body 1 in world axis
      		b2Vec2 worldAnchorOnBody2(20, 33); // Anchor point on body 2 in world axis
      		b2Vec2 worldAnchorGround1(-2, 35); // Anchor point for ground 1 in world axis
      		b2Vec2 worldAnchorGround2(20, 35); // Anchor point for ground 2 in world axis
      		float32 ratio = 1.0f; // Define ratio
      		myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      		m_world->CreateJoint(myjoint);
    			
    	
    		//Smiley
    	
    		
    		b2PolygonShape shape1;
    	  	shape1.SetAsBox(0.2f, 2.6f, b2Vec2(0.0f,0.0f),0);  		
    	  	b2FixtureDef *fd = new b2FixtureDef;
    		fd->density = 2.0;
    		fd->friction = 1.0;
    		fd->restitution = 0.6f;
    		fd->shape = &shape1;

			b2PolygonShape shape2;
    		shape2.SetAsBox(0.2f, 0.2f, b2Vec2(0.0f,0.0f),0);
    		
    		b2RevoluteJointDef jointDef;
    		
    		  	
    		for(int i=0;i<2;i++)		
    		{
    	  		
    			b2BodyDef bd;
	     		bd.type = b2_dynamicBody;
    	  		bd.position.Set(16.0 + 8*i,31);
    	  		bd.angle = pow(-1,i%2)*0.7;
    	  		b2Body* plank = m_world->CreateBody(&bd);
    	  		plank->CreateFixture(fd);   			
    	  		
    	  		b2BodyDef bd1;
    			bd1.position.Set(16.0 + 8*i,31);
    	  		b2Body* pivot = m_world->CreateBody(&bd1);
    			pivot->CreateFixture(&shape2,0.0f);			
    			
 				//jointDef.collideConnected = false;
 				jointDef.bodyA = plank;
    			jointDef.bodyB = pivot;
    			jointDef.localAnchorA.Set(0.0f,0.0f);
    			jointDef.localAnchorB.Set(0.0f,0.0f);
    		  	m_world->CreateJoint(&jointDef);  
    		}
    	}
    		
    	{
    		b2PolygonShape shape;
      		shape.SetAsBox(2.85f, 0.2f);
	
      		b2FixtureDef fd;
      		fd.shape = &shape;
      		fd.density = 0.10f;
      		fd.friction = 1.0f;
		
      		b2BodyDef bd;
	  		bd.type = b2_dynamicBody;
	  		bd.position.Set(20,30);
	  		b2Body* body = m_world->CreateBody(&bd);
	  		body->CreateFixture(&fd);   		  	
    	
		}
		
		//Lips
		{	
			b2BodyDef bd;
    		b2Body* platform = m_world->CreateBody(&bd);
    		b2Vec2 vs[2];
			vs[0].Set(22.7f, 16.0f);
			vs[1].Set(28.0f, 18.0f);
			
			b2ChainShape chain;
			chain.CreateChain(vs, 2);
			platform->CreateFixture(&chain, 0.0f);		
			
		}
		
		{	
			b2BodyDef bd;
    		b2Body* platform = m_world->CreateBody(&bd);
    		b2Vec2 vs[2];
			vs[0].Set(17.3f, 16.0f);
			vs[1].Set(12.0f, 18.0f);
			
			b2ChainShape chain;
			chain.CreateChain(vs, 2);
			platform->CreateFixture(&chain, 0.0f);		
			
		}
		
		//Eyes
		{
			
		}
	}

  	sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
