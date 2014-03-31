/*************************************************************************/
/*  state_machine_editor_plugin.h                                             */
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
#ifndef STATE_MACHINE_EDITOR_PLUGIN_H
#define STATE_MACHINE_EDITOR_PLUGIN_H

#include "tools/editor/editor_plugin.h"
#include "tools/editor/editor_node.h"
#include "state_machine.h"
#include "tools/editor/pane_drag.h"
/**
	@author Ben Potton <ben.potton@gmail.com>
*/


class StateMachineEditor : public Control {

	OBJ_TYPE(StateMachineEditor, Control);

	static const char* _node_type_names[];

	enum ClickType {
		CLICK_NONE,
		CLICK_NAME,
		CLICK_NODE,
		CLICK_INPUT_SLOT,
		CLICK_OUTPUT_SLOT,
		CLICK_PARAMETER
	};

	enum {

		MENU_GRAPH_CLEAR = 100,
		MENU_IMPORT_ANIMATIONS = 101,
		NODE_DISCONNECT,
		NODE_RENAME,
		NODE_ERASE,
		NODE_ADD_INPUT,
		NODE_DELETE_INPUT,
		NODE_SET_AUTOADVANCE,
		NODE_CLEAR_AUTOADVANCE
	};

	bool renaming_edit;
	StringName edited_node;
	bool updating_edit;
	Popup *edit_dialog;
	HSlider *edit_scroll[2];
	LineEdit *edit_line[4];
	OptionButton *edit_option;
	Label *edit_label[4];
	Button *edit_button;
	Button *filter_button;
	CheckButton *edit_check;
	FileDialog* file_dialog;
	int file_op;

	void _popup_edit_dialog();


	void _setup_edit_dialog(const StringName& p_node);
	PopupMenu *master_anim_popup;
	PopupMenu *node_popup;
	PopupMenu *add_popup;
	HScrollBar *h_scroll;
	VScrollBar *v_scroll;
	MenuButton* add_menu;

	CustomPropertyEditor *property_editor;

	StateMachine* state_machine;
	List<StringName> order;
	Set<StringName> active_nodes;

	int last_x, last_y;

	Point2 offset;
	ClickType click_type;
	Point2 click_pos;
	StateMachineNode *click_node;
	int click_slot;
	Point2 click_motion;
	ClickType rclick_type;
	StateMachineNode *rclick_node;
	int rclick_slot;

	//Button *play_button;

	Size2 _get_maximum_size();
	Size2 get_node_size(const StateMachineNode &p_node) const;
	void _draw_node(const StateMachineNode &p_node);

	AcceptDialog *filter_dialog;
	Tree *filter;



	void _draw_cos_line(const Vector2& p_from, const Vector2& p_to, const Color& p_color);
	void _update_scrollbars();
	void _scroll_moved(float);
	//void _play_toggled();
	/*
	void _node_param_changed();
	void _node_add_callback();
	void _node_add(VisualServer::AnimationTreeNodeType p_type);
	void _node_edit_property(const StringName& p_node);
	*/

	//void _master_anim_menu_item(int p_item);
	void _node_menu_item(int p_item);
	void _add_menu_item(int p_item);


	void _filter_edited();
	void _find_paths_for_filter(const StringName& p_node, Set<String>& paths);
	void _edit_filters();
	

	//void _edit_oneshot_start();
	//void _edit_dialog_animation_changed();
	//void _edit_dialog_edit_animation();
	void _edit_dialog_changeds(String);
	void _edit_dialog_changede(String);
	void _edit_dialog_changedf(float);
	void _edit_dialog_changed();
	void _dialog_changed() const;
	ClickType _locate_click(const Point2& p_click, StateMachineNode **p_node_id, int *p_slot_index) const;
	Point2 _get_slot_pos(const StringName& p_node_id, bool p_input, int p_slot);

	StringName _add_node(int p_item);
	void _file_dialog_selected(String p_path);


protected:
	void _notification(int p_what);
	void _input_event(InputEvent p_event);
	static void _bind_methods();
	void _create_menu();
public:


	virtual Size2 get_minimum_size() const;
	void edit(StateMachine *p_statemachine);
	StateMachineEditor();
};

class StateMachineEditorPlugin : public EditorPlugin {

	OBJ_TYPE(StateMachineEditorPlugin, EditorPlugin);

	StateMachineEditor *statemachine_editor;
	EditorNode *editor;

public:

	virtual String get_name() const { return "StateMachine"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_node);
	virtual bool handles(Object *p_node) const;
	virtual void make_visible(bool p_visible);

	StateMachineEditorPlugin(EditorNode *p_node);
	~StateMachineEditorPlugin();

};


#endif // CUBE_STATE_MACHINE_EDITOR_PLUGIN_H
