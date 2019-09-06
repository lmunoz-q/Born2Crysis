include Makefiles/default_var.mk

NAME := doom-nukem
TEST_ARG += test.b2cm

BLACK_LIST_SRCS += libui mflib

CFLAGS += -D_REENTRANT -g #-flto -O3

INC_DIR += libui/inc mflib mflib/include

SRCS = src/bmml/compile/eval_param.c \
	   src/bmml/compile/eval_params.c \
	   src/bmml/compile/find_name.c \
	   src/bmml/compile/finish_compilation.c \
	   src/bmml/compile/line.c \
	   src/bmml/compile/new_alias.c \
	   src/bmml/compile/ops/alias.c \
	   src/bmml/compile/ops/alloc.c \
	   src/bmml/compile/ops/call.c \
	   src/bmml/compile/ops/call_if.c \
	   src/bmml/compile/ops/common_2.c \
	   src/bmml/compile/ops/common_3.c \
	   src/bmml/compile/ops/ptr_move.c \
	   src/bmml/compile/ops/release.c \
	   src/bmml/compile/write_op.c \
	   src/bmml/debug/error.c \
	   src/bmml/debug/set_error.c \
	   src/bmml/get_op.c \
	   src/bmml/interface/add_extern_function_to_library.c \
	   src/bmml/interface/add_function_to_library.c \
	   src/bmml/interface/add_function_to_library_direct.c \
	   src/bmml/interface/add_symbol_to_library.c \
	   src/bmml/interface/compile_function.c \
	   src/bmml/interface/destroy_function.c \
	   src/bmml/interface/destroy_library.c \
	   src/bmml/interface/execute_function.c \
	   src/bmml/interface/get_function.c \
	   src/bmml/interface/init_function.c \
	   src/bmml/interface/init_library.c \
	   src/bmml/interface/link_library.c \
	   src/bmml/realloc_f.c \
	   src/bmml/run/getters/get_casted_parameter.c \
	   src/bmml/run/getters/get_float64.c \
	   src/bmml/run/getters/get_int64.c \
	   src/bmml/run/getters/get_param_type.c \
	   src/bmml/run/getters/get_ptr.c \
	   src/bmml/run/getters/get_type.c \
	   src/bmml/run/ops/add.c \
	   src/bmml/run/ops/alias.c \
	   src/bmml/run/ops/alloc.c \
	   src/bmml/run/ops/and.c \
	   src/bmml/run/ops/call.c \
	   src/bmml/run/ops/call_if.c \
	   src/bmml/run/ops/delta.c \
	   src/bmml/run/ops/div.c \
	   src/bmml/run/ops/less.c \
	   src/bmml/run/ops/mod.c \
	   src/bmml/run/ops/more.c \
	   src/bmml/run/ops/mul.c \
	   src/bmml/run/ops/not.c \
	   src/bmml/run/ops/or.c \
	   src/bmml/run/ops/point.c \
	   src/bmml/run/ops/release.c \
	   src/bmml/run/ops/set.c \
	   src/bmml/run/ops/shift_down.c \
	   src/bmml/run/ops/shift_up.c \
	   src/bmml/run/ops/sub.c \
	   src/bmml/run/ops/xor.c \
	   src/camera/camera_update.c \
	   src/camera/init_camera.c \
	   src/camera/look_at.c \
	   src/camera/projection_matrix.c \
	   src/editor/add_editor_elements/add_delete_button.c \
	   src/editor/add_editor_elements/add_editor_elements_1.c \
	   src/editor/add_editor_elements/add_editor_elements_2.c \
	   src/editor/add_editor_elements/add_editor_elements_3.c \
	   src/editor/add_editor_elements/add_editor_elements_4.c \
	   src/editor/add_editor_elements/add_editor_elements_5.c \
	   src/editor/add_editor_elements/add_editor_elements_6.c \
	   src/editor/add_editor_elements/add_editor_elements_7.c \
	   src/editor/add_editor_elements/add_lux_fallof_selector.c \
	   src/editor/add_editor_elements/add_lux_inten_selector.c \
	   src/editor/add_editor_elements/add_precision_slider_physics_drag.c \
	   src/editor/add_editor_elements/add_precision_slider_physics_drag_down.c \
	   src/editor/add_editor_elements/add_precision_slider_physics_friction_down.c \
	   src/editor/add_editor_elements/add_precision_slider_physics_friction_up.c \
	   src/editor/add_editor_elements/add_precision_slider_physics_gravity_down.c \
	   src/editor/add_editor_elements/add_precision_slider_physics_gravity_up_up.c \
	   src/editor/add_editor_elements/add_precision_wall_friction.c \
	   src/editor/add_editor_elements/add_script_area.c \
	   src/editor/add_editor_elements/add_slider_alpha.c \
	   src/editor/add_editor_elements/add_sliders_physics_drag.c \
	   src/editor/add_editor_elements/add_sliders_physics_gbl_fric.c \
	   src/editor/add_editor_elements/add_sliders_physics_gravity.c \
	   src/editor/add_editor_elements/add_wall_friction.c \
	   src/editor/add_editor_elements/create_script_obj_area.c \
	   src/editor/add_editor_elements/slider_on_press_label_update2.c \
	   src/editor/button_funcs/bf_set_skybox.c \
	   src/editor/button_funcs/bf_switch_goal.c \
	   src/editor/button_funcs/bf_switch_light.c \
	   src/editor/button_funcs/bf_switch_physics.c \
	   src/editor/button_funcs/change_lux_type.c \
	   src/editor/button_funcs/decrease_secteur_number.c \
	   src/editor/button_funcs/increase_secteur_number.c \
	   src/editor/button_funcs/modify_lux_fallof_number.c \
	   src/editor/button_funcs/modify_lux_inten_number.c \
	   src/editor/button_funcs/portail_pressed.c \
	   src/editor/button_funcs/update_sector_physics.c \
	   src/editor/editor_event.c \
	   src/editor/editor_init_value.c \
	   src/editor/editor_render.c \
	   src/editor/editor_update.c \
	   src/editor/free_editor_interface.c \
	   src/editor/init_editor.c \
	   src/editor/launch_editor_interface.c \
	   src/editor/modifier_update_editor.c \
	   src/editor/remplir_view.c \
	   src/editor/render_editor_view.c \
	   src/editor/render_mesh_preview.c \
	   src/editor/toggle_capture_mouse.c \
	   src/editor/update_alpha.c \
	   src/editor/update_double_slider_data.c \
	   src/editor/update_editor_interface_secteur.c \
	   src/editor/update_is_goal.c \
	   src/editor/update_is_light.c \
	   src/editor/update_is_making_portal.c \
	   src/editor/update_is_physics.c \
	   src/editor/update_lux_intensity_text.c \
	   src/editor/update_secteur_courant_text.c \
	   src/editor/update_sector_drag.c \
	   src/editor/update_sector_friction.c \
	   src/editor/update_sector_gravity.c \
	   src/editor/update_wall_friction.c \
	   src/env/env_destroy.c \
	   src/env/env_get.c \
	   src/env/env_init.c \
	   src/event_handler/gen_key.c \
	   src/event_handler/handle_events.c \
	   src/event_handler/handle_states.c \
	   src/event_handler/init_input_map.c \
	   src/event_handler/mouse_motion_handler.c \
	   src/graphics/calculate_light.c \
	   src/graphics/clipping/edge_to_polygon.c \
	   src/graphics/clipping/init_clipper.c \
	   src/graphics/clipping/init_edge.c \
	   src/graphics/clipping/portalclip/clip_1o2i.c \
	   src/graphics/clipping/portalclip/clip_2to1i.c \
	   src/graphics/clipping/portalclip/clip_portal.c \
	   src/graphics/clipping/portalclip/get_insec_r.c \
	   src/graphics/clipping/portalclip/line_intsect_2d.c \
	   src/graphics/clipping/zclip/clip_2out1in.c \
	   src/graphics/clipping/zclip/clip_znear.c \
	   src/graphics/gthreads/gthread_destroy.c \
	   src/graphics/gthreads/gthread_init.c \
	   src/graphics/gthreads/gthread_launch.c \
	   src/graphics/gthreads/gthread_wait.c \
	   src/graphics/gthreads/gthread_work.c \
	   src/graphics/light_to_world.c \
	   src/graphics/model_to_world.c \
	   src/graphics/openworld_renderer.c \
	   src/graphics/polygons_set_trans.c \
	   src/graphics/portal_cull.c \
	   src/graphics/raster/draw_alpha_line.c \
	   src/graphics/raster/draw_line.c \
	   src/graphics/raster/init_raster.c \
	   src/graphics/raster/raster_bot.c \
	   src/graphics/raster/raster_line.c \
	   src/graphics/raster/raster_top.c \
	   src/graphics/raster/rasterize.c \
	   src/graphics/raster/rasterize_wireframe.c \
	   src/graphics/render_mesh.c \
	   src/graphics/render_sector.c \
	   src/graphics/sector_queue/sector_queue_pop.c \
	   src/graphics/sector_queue/sector_queue_push.c \
	   src/graphics/transparency/draw_transparent.c \
	   src/graphics/transparency/transbuff/get_transbuff.c \
	   src/graphics/transparency/transbuff/transbuff_destroy.c \
	   src/graphics/transparency/transbuff/transbuff_pop.c \
	   src/graphics/transparency/transbuff/transbuff_push.c \
	   src/graphics/view_to_projection.c \
	   src/graphics/world_to_view.c \
	   src/graphics/zbuff/destroy_zbuff.c \
	   src/graphics/zbuff/get_zbuff.c \
	   src/graphics/zbuff/init_zbuff.c \
	   src/graphics/zbuff/reset_zbuff.c \
	   src/key_funcs/init_default_controls.c \
	   src/key_funcs/init_default_editor_controls.c \
	   src/key_funcs/kf_crouch.c \
	   src/key_funcs/kf_eidos_rewind.c \
	   src/key_funcs/kf_fly_backwards.c \
	   src/key_funcs/kf_fly_down.c \
	   src/key_funcs/kf_fly_forward.c \
	   src/key_funcs/kf_fly_left.c \
	   src/key_funcs/kf_fly_right.c \
	   src/key_funcs/kf_fly_up.c \
	   src/key_funcs/kf_hanle_drop/is_drop_catched.c \
	   src/key_funcs/kf_hanle_drop/kf_handle_drop.c \
	   src/key_funcs/kf_item_copy.c \
	   src/key_funcs/kf_item_delete.c \
	   src/key_funcs/kf_item_place.c \
	   src/key_funcs/kf_jump.c \
	   src/key_funcs/kf_preview_rotate_pitch.c \
	   src/key_funcs/kf_preview_rotate_roll.c \
	   src/key_funcs/kf_preview_rotate_yaw.c \
	   src/key_funcs/kf_quit_editor.c \
	   src/key_funcs/kf_quit_game.c \
	   src/key_funcs/kf_run.c \
	   src/key_funcs/kf_scale_item.c \
	   src/key_funcs/kf_toggle_editor_view.c \
	   src/key_funcs/kf_toggle_modify.c \
	   src/key_funcs/kf_walk_backward.c \
	   src/key_funcs/kf_walk_forward.c \
	   src/key_funcs/kf_walk_left.c \
	   src/key_funcs/kf_walk_right.c \
	   src/logic/update.c \
	   src/logic/win_condition.c \
	   src/main.c \
	   src/map_file/count_world.c \
	   src/map_file/load_lib.c \
	   src/map_file/load_map_file.c \
	   src/map_file/save_map_file.c \
	   src/menu/add_editorbutton.c \
	   src/menu/add_playbutton.c \
	   src/menu/add_quitbutton.c \
	   src/menu/change_color.c \
	   src/menu/launch_main_menu.c \
	   src/menu/switch_bool.c \
	   src/object_manager/get_object_list.c \
	   src/object_manager/object_manager_add.c \
	   src/object_manager/object_manager_get_obj.c \
	   src/objparser/destroy_obj.c \
	   src/objparser/get_mtl_name.c \
	   src/objparser/get_mtl_tex.c \
	   src/objparser/get_vertices.c \
	   src/objparser/load_obj.c \
	   src/objparser/obj_to_mesh.c \
	   src/objparser/read_line.c \
	   src/objparser/utils/get_ints.c \
	   src/perlin/gen_perlin.c \
	   src/physic/apply_effect.c \
	   src/physic/collision_capsule_trianle.c \
	   src/physic/collision_raysphere.c \
	   src/physic/eidos_rewind.c \
	   src/physic/entity_accelerate.c \
	   src/physic/polygon_to_wall.c \
	   src/physic/prepare_walls.c \
	   src/physic/ssv_seg_seg.c \
	   src/physic/update_entity.c \
	   src/physic/wall_from_triangle.c \
	   src/player/init_player.c \
	   src/player/player_update.c \
	   src/player/render_player.c \
	   src/player/update_player_sector.c \
	   src/renderer/hud.c \
	   src/renderer/render.c \
	   src/renderer/render_endscreen.c \
	   src/screen_states/endscreen.c \
	   src/screen_states/game.c \
	   src/screen_states/init_game.c \
	   src/sound/start_sound.c \
	   src/texture_manager/destroy_texture.c \
	   src/texture_manager/get_texture_from_id.c \
	   src/texture_manager/get_texture_list.c \
	   src/texture_manager/load_new_texture.c \
	   src/texture_manager/load_texture.c \
	   src/texture_manager/texture_get_pixel.c \
	   src/utilities/doom_fill_text.c \
	   src/utilities/doom_str_clean.c \
	   src/utilities/fps_counter.c \
	   src/world/buffer_destroy.c \
	   src/world/buffer_increase.c \
	   src/world/delete_mesh.c \
	   src/world/get_mesh_radius.c \
	   src/world/get_polygon_buffer.c \
	   src/world/get_sector.c \
	   src/world/get_world.c \
	   src/world/init_world.c \
	   src/world/light/light_add.c \
	   src/world/light/light_delete.c \
	   src/world/load_buffer.c \
	   src/world/mesh_add_physics.c \
	   src/world/mesh_change_texture.c \
	   src/world/mesh_copy.c \
	   src/world/mesh_create.c \
	   src/world/mesh_delete_physics.c \
	   src/world/polygon_copy.c \
	   src/world/portals/init_portals.c \
	   src/world/sector_create.c \
	   src/world/set_polygon_buffer.c \
	   src/world/skybox/skybox_load.c \
	   src/world/skybox/skybox_set_pos.c \
	   src/world/world_add_mesh.c \
	   src/world/world_destroy.c

Darwin_LDFLAGS += -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
#note: on linux, if sdl2-config is not present, expect pulseaudio + alsa + x11 + wayland
#to get sdl2-config, install the package libsdl2-dev
#ifneq ($(shell command -v sdl2-config), )
#Linux_LDFLAGS += `$(shell command -v sdl2-config) --static-libs | sed -e "s/-lSDL2 //g"`
#else
Linux_LDFLAGS += -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt
#endif

Darwin_LDLIBS += $(PACKAGE_MANAGER_LIB)/libSDL2.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib
Linux_LDLIBS += $(PACKAGE_MANAGER_LIB)/libSDL2.so $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.so $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.so $(PACKAGE_MANAGER_LIB)/libSDL2_image.so $(PACKAGE_MANAGER_LIB)/libSDL2_net.so
LDLIBS += mflib/mflib.a
CLIB += libui/libui.a

include Makefiles/bin.mk

mflib/mflib.a:
	$(MAKE) -C mflib

ifeq ($(UNAME), Darwin)

$(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib:
	$(PACKAGE_MANAGER) install SDL2_net
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2.dylib:
	$(PACKAGE_MANAGER) install SDL2
	touch $(PACKAGE_MANAGER_LIB)/libSDL2.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib:
	$(PACKAGE_MANAGER) install SDL2_ttf
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib:
	$(PACKAGE_MANAGER) install SDL2_mixer
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib:
	$(PACKAGE_MANAGER) install SDL2_image
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib

else ifeq ($(UNAME), Linux)

$(PACKAGE_MANAGER_LIB)/libSDL2.so:
	$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_ttf.so:
	$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_TTF_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_mixer.so:
	$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_MIXER_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_image.so:
	$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_IMAGE_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_net.so:
	$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_NET_NAME)

else

SDL2-2.0.9/build/libSDL2.dylib:
	echo "non OSX is not supported for now"

endif
