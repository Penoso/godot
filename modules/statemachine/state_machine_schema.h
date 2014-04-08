/*************************************************************************/
/*  state_machine_schema.h                                                           */
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
#ifndef STATE_MACHINE_SCHEMA_H
#define STATE_MACHINE_SCHEMA_H
#include "modules/gdscript/gd_script.h"

class StateMachineSchema {
public:

	typedef uint16_t SM_NODETYPE ;

	struct InputAnchorSchema
	{
		String name;
		Vector<String> allowedTypes;		
	};

	struct OutputAnchorSchema
	{
		String name;
		String outputType;
	};

	struct NodeSchema
	{
		NodeSchema()
		{
			size.x = 100;
			size.y = 70;
			color = Color(0.7f,0.8f,0.67f);

		}
		SM_NODETYPE type;
		String name;
		Vector<InputAnchorSchema*> inAnchors;
		Vector<OutputAnchorSchema*> outAnchors;

		Point2 size;
		Color color;

	private:		
		String scriptcode;
		GDScript script;
		
	};

	StateMachineSchema()
	{
		InputAnchorSchema *input = new InputAnchorSchema();
		input->name = "Input";
		input->allowedTypes.push_back("State");
		input->allowedTypes.push_back("Transition");

		OutputAnchorSchema *trans_out = new OutputAnchorSchema();
		trans_out->name = "Output";
		trans_out->outputType = "Transition";
		
		OutputAnchorSchema *state_out = new OutputAnchorSchema();
		state_out->name = "Output";
		state_out->outputType = "State";


		// Hard code this for now...
		NodeSchema *state = new NodeSchema();
		state->name="State";
		state->inAnchors.push_back(input);
		state->outAnchors.push_back(state_out);



		NodeSchema *transition = new NodeSchema();
		transition->name="Transition";
		transition->inAnchors.push_back(input);
		transition->outAnchors.push_back(trans_out);


		NodeSchema *root = new NodeSchema();
		root->name="Root";
		//root->inAnchors.push_back(input);
		root->outAnchors.push_back(state_out);

		node_map.insert(1,root);
		node_map.insert(0,state);
		node_map.insert(2,transition);
		
	};

	NodeSchema *get_node(SM_NODETYPE id)
	{
		return node_map[id];
	};

	void get_node_list(List<NodeSchema *> *p_node_list) const
	{
	
		for (Map<SM_NODETYPE,NodeSchema*>::Element *E = node_map.front(); E; E = E->next()) {

			p_node_list->push_back(E->value());
		}

	}

private:
	Map<SM_NODETYPE,NodeSchema*> node_map;


};

#endif // STATE_MACHINE_SCHEMA_H

