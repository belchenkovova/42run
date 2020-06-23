#include "character.h"

#include "game/obstacle/obstacle.h"

using namespace						game;

									character::character()
{
	model::manager::flag_wrapper	flags = model::manager::flag::triangulate;

	common::warning::ignore = true;
	model = model::manager::make_model(sources().character, flags);
	common::warning::ignore = false;

	instance = engine::model::manager::make_instance(model);

	instance->scale(0.085f);
	instance->rotate(engine::vec3(0, 180, 0));

	animations.run = model::animation(1, 19, 1.1, true);
	animations.jump = model::animation(20, 63, 0.7, false);

	model->animate(animations.run);

	game_object::render_target(instance);
	game_object::animation_target(model);

	callback = interface::callback(interface::event::type::key_press, &character::callback_functor, this);

	engine::core::use_callback(callback);
}

void								character::update()
{
	if (not model->is_animation_playing())
		model->animate(animations.run);

	update_state();

	if (current_position != target_position)
	{
		current_position = lerp(current_position, target_position, speed);

		instance->reset_translation();
		instance->translate(current_position);
	}
}

float_range 						character::calculate_range() const
{
	return {current_position.z - this->size / 2.f, current_position.z + this->size / 2.f};
}

void								character::callback_functor()
{
	auto							key = engine::core::receive_event().read_key();

	switch (key)
	{
		case engine::interface::key::space :
			model->animate(animations.jump);
			break;

		case engine::interface::key::number_1 :
		case engine::interface::key::left :
		case engine::interface::key::letter_a :
			if (current_state == state::running and try_go_left(current_line))
				target_position = position_for_line(current_line);
			break ;

		case engine::interface::key::number_2 :
		case engine::interface::key::right :
		case engine::interface::key::letter_d :
			if (current_state == state::running and try_go_right(current_line))
				target_position = position_for_line(current_line);
			break ;

		default :
			break ;
	}
}