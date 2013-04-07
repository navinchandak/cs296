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
	void getArcVec(float xC,float yC,float r,float sA,float eA,b2Vec2* vs,int numP){

		for (int i=0;i<numP;i++)
		{
			float theta = (sA) + ((eA-sA)/(numP-1))*i;
			vs[i].Set(xC+r*sin(theta), yC+r*cos(theta));
		}

	}
	void drawChain(b2World* m_world,b2Vec2* vs,int numP){
		b2BodyDef bd;
		b2Body* eyePlace=m_world->CreateBody(&bd);
		b2ChainShape chain;
		chain.CreateChain(vs,numP);
		eyePlace->CreateFixture(&chain,0.0f);

	}
	b2Body* drawBox(b2World* m_world,float xC,float yC,b2FixtureDef* fixture, bool isDynamic=false){
			b2BodyDef bd;
			if(isDynamic){
				bd.type=b2_dynamicBody;
			}
			bd.position.Set(xC, yC);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(fixture);
			return ground;
	}
	b2Body* drawBox(b2World* m_world,float xC,float yC,float lby2,float bby2,bool isDynamic=false){
			b2PolygonShape shape;
			shape.SetAsBox(lby2, bby2);

			b2BodyDef bd;
			if(isDynamic){
				bd.type=b2_dynamicBody;
			}
			bd.position.Set(xC, yC);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shape, 0.0f);
			return ground;


	}
	void drawArc(b2World* m_world,float xC,float yC,float r,float sA,float eA,int numP){
		b2Vec2 vs[numP];
		getArcVec(xC,yC,r,sA,eA,vs,numP);
		drawChain(m_world,vs,numP);
	}
	b2Body* drawSphere(b2World* m_world,float xC,float yC,float r,float a,float b, float c){

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
	void drawPlatform(b2World* m_world,b2Vec2 a,b2Vec2 b)
	{		
		b2Body* platform;
		b2EdgeShape shape;
		shape.Set(a, b);
		b2BodyDef bd;
		platform = m_world->CreateBody(&bd);
		platform->CreateFixture(&shape, 0.0f);
	}

	dominos_t::dominos_t()
	{	/**The following generates the ground object. 
			It is a straight line between two points (-90,0) and (90,0)
		*/
		{
			b2Vec2 vs[2];
			vs[0].Set(-90.0f,0.0f);
			vs[1].Set(90.0,0.0);
			drawChain(m_world,vs,2);
		}
		/** This scope initializes all the object in the upper left part of the simulation */
		{
			/** Platform on which the ball initially rests and the ball itself
			*/
			drawBox(m_world,-48.5,40.0,1.6,0.15);
			b2Body* spherebody=drawSphere(m_world,-48.5,40.5,0.5,1.0f,0.0f,0.85f);		
			
			/** Some force is initially applied on this ball to start off the Rube GoldBerg machine*/
			b2Vec2 force = b2Vec2(110,0);
			spherebody->ApplyForce(force, spherebody->GetPosition());

			///The platform on which the ball falls initially after initial acceleration
			///the horizontal part of the platform
			drawBox(m_world,-43.8,35.0,3.6,0.15);
			///the vertical part of the platform 
			b2Body* body1=drawBox(m_world,-40.2,36.8,0.15,1.8);
		

			//The small vertical support to the lever 
			//drawBox(m_world,-41.4,36.7,0.15,1.45);
		

				
			////////large vertical body
			/////////the lever which hits ball number 2
			{
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
			//jjoin with large vertical bar
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = body1;
			jointDef.bodyB = body2;
			jointDef.localAnchorA.Set(0.0f,1.60f);
			jointDef.localAnchorB.Set(0.0f,-0.15f);
			//jointDef.collideConnected = false;
			m_world->CreateJoint(&jointDef);
			}
		

			/// the platform on which the second ball is lying. 
			/// The lever on the left comes and hits this ball to carry on the RubeGoldberg machine
			//drawBox(m_world,-36.8,38.1,0.4,0.15);
			//drawSphere(m_world,-36.8,38.15,0.5,8.0,0.6,0);
			drawBox(m_world,-36.6,38,0.4,0.15);
			drawSphere(m_world,-36.6,38.4,0.5,8.0,0.3,0);
		}

		{		//angles platform
			b2PolygonShape shape;
			shape.SetAsBox(3.0f, 0.15f);

			b2BodyDef bd;
			bd.position.Set(-33.5f, 35.0f);
			bd.angle = 3.14 - 0.2;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shape, 0.0f);

		}

		{
			//horizontal lever
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

			b2Body* pivot=drawBox(m_world,-21.0,31.0,0.15,0.15);
			
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = plank;
			jointDef.bodyB = pivot;
			jointDef.localAnchorA.Set(0.0f,0.0f);
			jointDef.localAnchorB.Set(0.0f,0.0f);
			//jointDef.collideConnected = false;
			m_world->CreateJoint(&jointDef);   			   	  	

		}




		//lower left part
		{	
			drawPlatform(m_world,b2Vec2(-55.0f,3.0f), b2Vec2(-30.0f, 3.0f));


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
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 0.5f;
			b2PolygonShape shape;
			shape.SetAsBox(4.70f, 0.15f);
			fd2->shape = &shape;
			b2Body* body=drawBox(m_world, -36.7,7.0,fd2,true);

			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(-36.70f, 7.0f);
			jd.Initialize(sbody, body, anchor);
			m_world->CreateJoint(&jd);

			//The light box on the right side of the see-saw

			//The light box 2 on the right side of the see-saw
			b2FixtureDef *fd4 = new b2FixtureDef;
			fd4->density = 0.7f;
			b2PolygonShape shape3;
			shape3.SetAsBox(0.5f, 0.5f);
			fd4->shape = &shape3;
			drawBox(m_world,-40.9,7.5,fd4,true);
			drawBox(m_world,-32.5,7.5,fd4,true);

		}   	   	 

		{	// right upper part
			b2Vec2 vs[3];
			vs[0].Set(-10.0f, 40.0f);
			vs[1].Set(-5.50f, 40.0f);
			vs[2].Set(42.0f, 34.0f);
			drawChain(m_world,vs,3);
			drawSphere(m_world,-6.7,40.8,0.8,0.8,0,0.5);


																								
		}


		{

			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 2.0;
			fd1->friction = 0.7;
			fd1->restitution = 0.6f;
			b2PolygonShape shape1;
			shape1.SetAsBox(0.15f, 2.0f, b2Vec2(0.0f,0.0f),0);  		
			fd1->shape = &shape1;

			b2FixtureDef *fd2 = new b2FixtureDef;
			b2PolygonShape shape2;
			shape2.SetAsBox(0.15f, 0.15f, b2Vec2(0.0f,0.0f),0);
			fd2->shape=&shape2;

			b2RevoluteJointDef jointDef;	
			// the lever	

			for(int i=0;i<5;i++)		
			{

				b2Body* plank=drawBox(m_world,42.50f - (i%2)*0.7, 33.0f - 3*i,fd1,true);
				b2Body* pivot=drawBox(m_world,42.50f - (i%2)*0.7 , 33.0f - 3*i,fd2);

				//jointDef.collideConnected = false;
				jointDef.bodyA = plank;
				jointDef.bodyB = pivot;
				jointDef.localAnchorA.Set(0.0f,0.0f);
				jointDef.localAnchorB.Set(0.0f,0.0f);
				m_world->CreateJoint(&jointDef);
			}
		}

		{
			//bottom wala chain shape
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
			drawChain(m_world,vs,10);
			drawSphere(m_world,41.4,19.4,0.4,0.4,0,0.5);
			drawSphere(m_world,39.4,19.4,0.4,0.4,0,0.5);
		}  	

		{ // initially vertical lever
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 2.35;
			fd1->friction = 0.7;
			fd1->restitution = 0.60f;
			b2PolygonShape shape1;
			shape1.SetAsBox(0.1f, 2.0f, b2Vec2(0.0f,0.0f),0);  		
			fd1->shape = &shape1;
			
			b2Body* plank=drawBox(m_world,22.50f,13.0f,fd1,true);
			b2Body* pivot=drawBox(m_world,22.5,13.0,0.1,0.1);


			//jointDef.collideConnected = false;
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = plank;
			jointDef.bodyB = pivot;
			jointDef.localAnchorA.Set(0.0f,0.0f);
			jointDef.localAnchorB.Set(0.0f,0.0f);
			m_world->CreateJoint(&jointDef);

			///////////////////////////////////

			//next chain towards le
			b2Vec2 vs[2];
			vs[0].Set(20.0f, 13.10f);
			vs[1].Set(3.75f, 13.10f);			
			drawChain(m_world,vs,2);

		}

		{//big chain
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

			//light sphere
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

		{// platform on which wedge rsst
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

		{//last chain
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

		}	
		//Smiley
		{	

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
				int xAxis=16+8*i;
				int dir;
				if(i==0){
					dir=-1;
				}
				else{
					dir=1;
				}
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(xAxis,31);
				bd.angle = pow(-1,i%2)*0.7;
				b2Body* plank = m_world->CreateBody(&bd);
				plank->CreateFixture(fd);   			

				b2BodyDef bd1;
				bd1.position.Set(xAxis,31);
				b2Body* pivot = m_world->CreateBody(&bd1);
				pivot->CreateFixture(&shape2,0.0f);			

				//jointDef.collideConnected = false;
				jointDef.bodyA = plank;
				jointDef.bodyB = pivot;
				jointDef.localAnchorA.Set(0.0f,0.0f);
				jointDef.localAnchorB.Set(0.0f,0.0f);
				m_world->CreateJoint(&jointDef);  

				drawPlatform(m_world,b2Vec2(xAxis-1,28.1f),b2Vec2(xAxis+1,28.1f));

				drawSphere(m_world,xAxis,28.4f,0.6f,0.3f,0.0f,0.0f);	

				drawArc(m_world,xAxis,23,1,PI/2,(3/2.0)*PI,30);

				{
					b2Vec2 vs[15];
					vs[0].Set(xAxis + dir*(3),29.1f);
					vs[1].Set(xAxis + dir*(2),27.1f);
					vs[2].Set(xAxis + dir*(1.85),27.0f);
					vs[3].Set(xAxis + dir*(1.70),26.9f);
					vs[4].Set(xAxis + dir*(1.55),26.8f);
					vs[5].Set(xAxis + dir*(1.40),26.7f);
					vs[6].Set(xAxis + dir*(1.40),25.5f);
					drawChain(m_world,vs,7);
					vs[0].Set(xAxis - dir*(0.7),27.0f);
					vs[1].Set(xAxis - dir*(0.7),25.5f);
					drawChain(m_world,vs,2);

				}


			}
		}




		{
			const int num=6;
			b2Vec2 vs1[num];
			getArcVec(20,29.8+(2.85/tan(PI/12.0)),2.85/sin(PI/12),11*PI/12,13*PI/12,vs1,num);
			b2Vec2 vs2[num];
			getArcVec(20,30.2+(2.85/tan(PI/12.0)),2.85/sin(PI/12),13*PI/12,11*PI/12,vs2,num);
			b2Vec2 vs[2*num];
			for(int i=0;i<num;i++)
				vs[i]=vs1[i];
			for(int i=num;i<2*num;i++)
				vs[i]=vs2[i-num];
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f,0.0f);
			b2Body* body = m_world->CreateBody(&bd);
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

		//Lips
		{	
			drawArc(m_world,20,16+(2.85/tan(PI/12)),2.85/sin(PI/12),10*PI/12,11*PI/12+0.01,10);
			drawArc(m_world,20,16+(2.85/tan(PI/12)),2.85/sin(PI/12),13*PI/12-0.01,14*PI/12+0.01,10);

		}

	}

	sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
