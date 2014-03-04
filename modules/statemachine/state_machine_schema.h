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


class StateMachineSchema {
public:

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
		String name;
		Vector<InputAnchorSchema*> inAnchors;
		Vector<OutputAnchorSchema*> outAnchors;

		/* script this?		
		String script;*/
		
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
		state->name="State";
		state->inAnchors.push_back(input);
		state->outAnchors.push_back(state_out);

		node_map.insert(root->name,root);
		node_map.insert(state->name,state);
		node_map.insert(transition->name,transition);
		
	};

	NodeSchema *GetNode(String name)
	{
		return node_map[name];
	};

private:
	Map<StringName,NodeSchema*> node_map;


};

#endif // STATE_MACHINE_SCHEMA_H

