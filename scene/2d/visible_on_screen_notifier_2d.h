/**************************************************************************/
/*  visible_on_screen_notifier_2d.h                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#include "scene/2d/node_2d.h"

class Viewport;
class VisibleOnScreenNotifier2D : public Node2D {
	GDCLASS(VisibleOnScreenNotifier2D, Node2D);

	HashSet<Viewport *> viewports;

	Rect2 rect;
	bool show_rect = true;

private:
	bool on_screen = false;
	void _visibility_enter();
	void _visibility_exit();

protected:
	virtual void _screen_enter() {}
	virtual void _screen_exit() {}

	void _notification(int p_what);
	static void _bind_methods();

public:
#ifdef TOOLS_ENABLED
	virtual Dictionary _edit_get_state() const override;
	virtual void _edit_set_state(const Dictionary &p_state) override;

	virtual Vector2 _edit_get_minimum_size() const override { return Vector2(); }

	virtual void _edit_set_rect(const Rect2 &p_edit_rect) override;
#endif // TOOLS_ENABLED

#ifdef DEBUG_ENABLED
	virtual Rect2 _edit_get_rect() const override;

	virtual bool _edit_use_rect() const override;
#endif // DEBUG_ENABLED

	void set_rect(const Rect2 &p_rect);
	Rect2 get_rect() const;

	void set_show_rect(bool p_show_rect);
	bool is_showing_rect() const;

	bool is_on_screen() const;

	VisibleOnScreenNotifier2D();
};

class VisibleOnScreenEnabler2D : public VisibleOnScreenNotifier2D {
	GDCLASS(VisibleOnScreenEnabler2D, VisibleOnScreenNotifier2D);

public:
	enum EnableMode {
		ENABLE_MODE_INHERIT,
		ENABLE_MODE_ALWAYS,
		ENABLE_MODE_WHEN_PAUSED,
	};

protected:
	ObjectID node_id;
	virtual void _screen_enter() override;
	virtual void _screen_exit() override;

	EnableMode enable_mode = ENABLE_MODE_INHERIT;
	NodePath enable_node_path = NodePath("..");

	void _notification(int p_what);
	static void _bind_methods();

	void _update_enable_mode(bool p_enable);

public:
	void set_enable_mode(EnableMode p_mode);
	EnableMode get_enable_mode();

	void set_enable_node_path(NodePath p_path);
	NodePath get_enable_node_path();

	VisibleOnScreenEnabler2D();
};

VARIANT_ENUM_CAST(VisibleOnScreenEnabler2D::EnableMode);
