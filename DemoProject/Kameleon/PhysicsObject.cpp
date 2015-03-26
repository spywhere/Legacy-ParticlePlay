#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(ppPhysics* physics){
	this->physics = physics;
}

void PhysicsObject::RenderCircle(b2Vec2 center, float radius, ppColor* color){
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < k_segments; ++i){
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(this->physics->WorldToPixel(v.x), this->physics->WorldToPixel(v.y));
		theta += k_increment;
	}
	glEnd();
	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i){
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(this->physics->WorldToPixel(v.x), this->physics->WorldToPixel(v.y));
		theta += k_increment;
	}
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(this->physics->WorldToPixel(center.x), this->physics->WorldToPixel(center.y));
	glVertex2f(this->physics->WorldToPixel(center.x + radius), this->physics->WorldToPixel(center.y));
	glEnd();
}


void PhysicsObject::RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color){
	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINES);
		glVertex2f(this->physics->WorldToPixel(v1.x), this->physics->WorldToPixel(v1.y));
		glVertex2f(this->physics->WorldToPixel(v2.x), this->physics->WorldToPixel(v2.y));
	glEnd();
}

void PhysicsObject::RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color){
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for(auto vertex : vertices){
		glVertex2f(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINE_LOOP);
	for(auto vertex : vertices){
		glVertex2f(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	glEnd();
}

void PhysicsObject::RenderChain(std::vector<b2Vec2> vertices, ppColor* color){
	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINE_STRIP);
	for(auto vertex : vertices){
		glVertex2f(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	glEnd();
	for(auto vertex : vertices){
		this->RenderCircle(vertex, this->physics->PixelToWorld(3), color);
	}
}

void PhysicsObject::RenderBody(b2Body* body){
	b2Transform bdTransform = body->GetTransform();
	glPushMatrix();
	glTranslatef(this->physics->WorldToPixel(bdTransform.p.x), this->physics->WorldToPixel(bdTransform.p.y), 0);
	glRotatef(bdTransform.q.GetAngle()*180/b2_pi, 0, 0, 1);
	ppColor* color = new ppColor(0.9f, 0.7f, 0.7f);
	if(!body->IsActive()){
		color = new ppColor(0.5f, 0.5f, 0.3f);
	}else if(body->GetType()==b2_staticBody){
		color = new ppColor(0.5f, 0.9f, 0.3f);
	}else if(body->GetType()==b2_kinematicBody){
		color = new ppColor(0.5f, 0.5f, 0.9f);
	}else if(!body->IsAwake()){
		color = new ppColor(0.6f, 0.6f, 0.6f);
	}
	for(b2Fixture* ft=body->GetFixtureList();ft!=NULL;ft=ft->GetNext()){
		switch(ft->GetType()){
			case b2Shape::e_circle:
			{
				b2CircleShape* circle = (b2CircleShape*)ft->GetShape();
				this->RenderCircle(circle->m_p, circle->m_radius, color);
			}
			break;
			case b2Shape::e_edge:
			{
				b2EdgeShape* edge = (b2EdgeShape*)ft->GetShape();
				this->RenderEdge(edge->m_vertex1, edge->m_vertex2, color);
			}
			break;
			case b2Shape::e_polygon:
			{
				b2PolygonShape* poly = (b2PolygonShape*)ft->GetShape();
				std::vector<b2Vec2> vertices;
				for(int i=0;i<poly->m_count;i++){
					vertices.push_back(poly->m_vertices[i]);
				}
				this->RenderPolygon(vertices, color);
			}
			break;
			case b2Shape::e_chain:
			{
				b2ChainShape* chain = (b2ChainShape*)ft->GetShape();
				std::vector<b2Vec2> vertices;
				for(int i=0;i<chain->m_count;i++){
					vertices.push_back(chain->m_vertices[i]);
				}
				this->RenderChain(vertices, color);
			}
			break;
			default: break;
		}
	}
	glPopMatrix();
}
