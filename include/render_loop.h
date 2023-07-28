#ifndef RENDER_LOOP_H
#define RENDER_LOOP_H

#include "global_include.h"
#include "scene.h"
#include "camera.h"

void multi_rotating_cube_demo_loop(Scene scene);

void scene_light_demo_loop(Scene scene);

void scene_load_model_demo_loop(Scene scene);

void framebuffer_test_loop(Scene scene);

void scene_skybox_demo_loop(Scene scene);

void scene_geometry_shader_demo_loop(Scene scene);

void scene_explode_model_demo_loop(Scene scene);

void scene_visualize_model_normal_loop(Scene scene);

void rendering_instance_demo_loop(Scene scene);

void rendering_instance_demo_loop_opt(Scene scene);

void planet_demo_loop(Scene scene);

void MSAA_demo_loop(Scene scene);

void offscreen_MSAA_loop(Scene scene);

void offscreen_MSAA_loop_ano(Scene scene);

void blinn_phong_demo_loop(Scene scene);

void shadow_mapping_demo_loop(Scene scene);

void renderScene(Shader &shader, unsigned int VAO);
void renderCube();
void renderQuad();

void switch_shadow_mapping_demo_loop(Scene scene);

void switch_shadow_mapping_demo_loop_p2(Scene scene);

void renderScene_point_light(Shader &shader);
void renderCube_point_light();

void point_light_source_shadow_mapping_demo_loop(Scene scene);

void simple_normal_mapping_demo_loop(Scene scene);
void simple_height_mapping_demo_loop(Scene scene);
void renderQuad_Normal();

void deferred_shading_demo_loop(Scene scene);

void PBR_light_base_demo_loop(Scene scene);
void PBR_light_textured_demo_loop(Scene scene);
void renderSphere();

void PBR_IBL_diffuse_demo_loop(Scene scene);

void PBR_IBL_diffuse_demo_loop_p2(Scene scene);

void PBR_IBL_diffuse_demo_loop_ano(Scene scene);

void PBR_IBL_specular_demo_loop(Scene scene);

void PBR_IBL_textured_demo_loop(Scene scene);

void PBR_IBL_model_demo_loop(Scene scene);

#endif