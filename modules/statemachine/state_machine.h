/*************************************************************************/
/*  state_machine.h                                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


#include "scene/resources/mesh_library.h"
#include "scene/3d/spatial.h"
#include "scene/resources/multimesh.h"
#include "state_machine_schema.h"

struct StateMachine_Link {
	int16_t node;
	int16_t anchor;
};

struct StateMachine_Anchor {
	Vector<StateMachine_Link> links;
};

struct StateMachineNode {

	int16_t id;
	StateMachineSchema::SM_NODETYPE type;
	Point2 pos;
	String name;


	bool CanTransition();
	void OnEnter();
	void Tick(float dt);
	void OnExit();

	String get_name() const  {return name;}
	Point2 get_position() const {return pos;}
	Point2 get_size() const  {return Point2(150,100);}

	String get_input_anchor_name(int index) const {return String("Name");}
	Point2 get_input_anchor_position(int index) const { return Point2(0.0f,50.0f + (index * 10.0f));}
	const Vector<StateMachine_Anchor *> *get_input_anchors() const {return &inputAnchors;}

	String get_output_anchor_name(int index) const {return String("Name");}
	Point2 get_output_anchor_position(int index) const { return Point2(150.0f,50.0f + (index * 10.0f));}
	const Vector<StateMachine_Anchor *> *get_output_anchors() const {return &outputAnchors;}

	Vector<StateMachine_Anchor *> inputAnchors;
	Vector<StateMachine_Anchor *> outputAnchors;


	StateMachineNode() {};
	virtual ~StateMachineNode() { }
};

class StateMachine : public Node {
public:


	OBJ_TYPE( StateMachine, Node);
	OBJ_CATEGORY("State Machines");

	bool awaiting_update;

	// void _queue_dirty_map();
	// void _update_dirty_map_callback();
public:
	StateMachineNode *add_node(StateMachineSchema::SM_NODETYPE type);
	void resource_changed(const RES& p_res);
	void get_node_list(List<uint16_t> *p_node_list) const;
	StateMachineNode *get_node(uint16_t node);
	StateMachineSchema::NodeSchema *get_node_schema(uint16_t node);
	bool connect(StateMachineNode *source,int source_anchor, StateMachineNode *dest,int dest_anchor );
	

protected:

	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name,Variant &r_ret) const;
	void _get_property_list( List<PropertyInfo> *p_list) const;

	void _notification(int p_what);
	static void _bind_methods();

public:

	
	StateMachine();
	~StateMachine();


private:
	Map<uint16_t,StateMachineNode*> node_map;
	enum {

		DISCONNECTED = -1,
	};

	StateMachineSchema *schema;
	int node_guid;

};

#endif // CUBE_STATE_MACHINE_H
