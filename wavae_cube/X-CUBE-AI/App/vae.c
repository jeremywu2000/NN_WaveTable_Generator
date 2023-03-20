/**
  ******************************************************************************
  * @file    vae.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Mar 20 15:15:46 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "vae.h"
#include "vae_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_vae
 
#undef AI_VAE_MODEL_SIGNATURE
#define AI_VAE_MODEL_SIGNATURE     "9cb77466c48671851a24e493d74b60dd"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon Mar 20 15:15:46 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_VAE_N_BATCHES
#define AI_VAE_N_BATCHES         (1)

static ai_ptr g_vae_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_vae_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  decoder_dense_1_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_upsample_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4064, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2032, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_pad_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  decoder_conv2dT_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  decoder_output_conv2d_upsample_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4080, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  decoder_output_conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  decoder_output_conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 255, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  decoder_output_conv2d_pad_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  decoder_output_conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  decoder_output_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 256, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  decoder_dense_1_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  decoder_dense_1_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  decoder_input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 16, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  decoder_dense_1_dense_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 16, 1), AI_STRIDE_INIT(4, 4, 4, 512, 8192),
  1, &decoder_dense_1_dense_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  decoder_dense_1_dense_output0, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 64, 1), AI_STRIDE_INIT(4, 4, 4, 128, 8192),
  1, &decoder_dense_1_dense_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_upsample_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 127, 1), AI_STRIDE_INIT(4, 4, 4, 128, 16256),
  1, &decoder_conv2dT_1_conv2d_upsample_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_weights, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 32, 1, 4, 16), AI_STRIDE_INIT(4, 4, 128, 128, 512),
  1, &decoder_conv2dT_1_conv2d_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 127, 1), AI_STRIDE_INIT(4, 4, 4, 64, 8128),
  1, &decoder_conv2dT_1_conv2d_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_pad_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 128, 1), AI_STRIDE_INIT(4, 4, 4, 64, 8192),
  1, &decoder_conv2dT_1_conv2d_pad_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &decoder_conv2dT_1_conv2d_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  decoder_conv2dT_1_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 128, 1), AI_STRIDE_INIT(4, 4, 4, 64, 8192),
  1, &decoder_conv2dT_1_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  decoder_output_conv2d_upsample_output, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 255, 1), AI_STRIDE_INIT(4, 4, 4, 64, 16320),
  1, &decoder_output_conv2d_upsample_output_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  decoder_output_conv2d_weights, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 16, 1, 4, 1), AI_STRIDE_INIT(4, 4, 64, 64, 256),
  1, &decoder_output_conv2d_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  decoder_output_conv2d_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 255, 1), AI_STRIDE_INIT(4, 4, 4, 4, 1020),
  1, &decoder_output_conv2d_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  decoder_output_conv2d_pad_output, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 256, 1), AI_STRIDE_INIT(4, 4, 4, 4, 1024),
  1, &decoder_output_conv2d_pad_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  decoder_output_conv2d_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &decoder_output_conv2d_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  decoder_output_output, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 256, 1), AI_STRIDE_INIT(4, 4, 4, 4, 1024),
  1, &decoder_output_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  decoder_dense_1_dense_bias, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &decoder_dense_1_dense_bias_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  decoder_dense_1_dense_weights, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &decoder_dense_1_dense_weights_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  decoder_input_output, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 16, 1), AI_STRIDE_INIT(4, 4, 4, 4, 64),
  1, &decoder_input_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_output_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_conv2d_pad_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_output_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &decoder_output_chain,
  NULL, &decoder_output_layer, AI_STATIC, 
  .nl_params = NULL, 
)


AI_STATIC_CONST ai_float decoder_output_conv2d_pad_value_data[] = { 0.0 };
AI_ARRAY_OBJ_DECLARE(
    decoder_output_conv2d_pad_value, AI_ARRAY_FORMAT_FLOAT,
    decoder_output_conv2d_pad_value_data, decoder_output_conv2d_pad_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_output_conv2d_pad_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_conv2d_pad_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_output_conv2d_pad_layer, 4,
  PAD_TYPE, 0x0, NULL,
  pad, forward_pad,
  &decoder_output_conv2d_pad_chain,
  NULL, &decoder_output_layer, AI_STATIC, 
  .value = &decoder_output_conv2d_pad_value, 
  .mode = AI_PAD_CONSTANT, 
  .pads = AI_SHAPE_INIT(4, 0, 0, 0, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_output_conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_conv2d_upsample_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &decoder_output_conv2d_weights, &decoder_output_conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_output_conv2d_layer, 4,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &decoder_output_conv2d_chain,
  NULL, &decoder_output_conv2d_pad_layer, AI_STATIC, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 0, 1, 0), 
)


AI_STATIC_CONST ai_float decoder_output_conv2d_upsample_scales_data[] = { 1, 2, 1.0, 1 };
AI_ARRAY_OBJ_DECLARE(
    decoder_output_conv2d_upsample_scales, AI_ARRAY_FORMAT_FLOAT,
    decoder_output_conv2d_upsample_scales_data, decoder_output_conv2d_upsample_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_output_conv2d_upsample_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_output_conv2d_upsample_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_output_conv2d_upsample_layer, 4,
  UPSAMPLE_TYPE, 0x0, NULL,
  upsample, forward_upsample,
  &decoder_output_conv2d_upsample_chain,
  NULL, &decoder_output_conv2d_layer, AI_STATIC, 
  .scales = &decoder_output_conv2d_upsample_scales, 
  .center = false, 
  .mode = AI_UPSAMPLE_ZEROS, 
  .nearest_mode = AI_ROUND_PREFER_CEIL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_conv2dT_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_conv2d_pad_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_conv2dT_1_layer, 3,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &decoder_conv2dT_1_chain,
  NULL, &decoder_output_conv2d_upsample_layer, AI_STATIC, 
  .nl_params = NULL, 
)


AI_STATIC_CONST ai_float decoder_conv2dT_1_conv2d_pad_value_data[] = { 0.0 };
AI_ARRAY_OBJ_DECLARE(
    decoder_conv2dT_1_conv2d_pad_value, AI_ARRAY_FORMAT_FLOAT,
    decoder_conv2dT_1_conv2d_pad_value_data, decoder_conv2dT_1_conv2d_pad_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_pad_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_conv2d_pad_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_pad_layer, 3,
  PAD_TYPE, 0x0, NULL,
  pad, forward_pad,
  &decoder_conv2dT_1_conv2d_pad_chain,
  NULL, &decoder_conv2dT_1_layer, AI_STATIC, 
  .value = &decoder_conv2dT_1_conv2d_pad_value, 
  .mode = AI_PAD_CONSTANT, 
  .pads = AI_SHAPE_INIT(4, 0, 0, 0, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_conv2d_upsample_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &decoder_conv2dT_1_conv2d_weights, &decoder_conv2dT_1_conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_layer, 3,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d,
  &decoder_conv2dT_1_conv2d_chain,
  NULL, &decoder_conv2dT_1_conv2d_pad_layer, AI_STATIC, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 0, 1, 0), 
)


AI_STATIC_CONST ai_float decoder_conv2dT_1_conv2d_upsample_scales_data[] = { 1, 2, 1.0, 1 };
AI_ARRAY_OBJ_DECLARE(
    decoder_conv2dT_1_conv2d_upsample_scales, AI_ARRAY_FORMAT_FLOAT,
    decoder_conv2dT_1_conv2d_upsample_scales_data, decoder_conv2dT_1_conv2d_upsample_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_upsample_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_dense_1_dense_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_conv2dT_1_conv2d_upsample_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_conv2dT_1_conv2d_upsample_layer, 3,
  UPSAMPLE_TYPE, 0x0, NULL,
  upsample, forward_upsample,
  &decoder_conv2dT_1_conv2d_upsample_chain,
  NULL, &decoder_conv2dT_1_conv2d_layer, AI_STATIC, 
  .scales = &decoder_conv2dT_1_conv2d_upsample_scales, 
  .center = false, 
  .mode = AI_UPSAMPLE_ZEROS, 
  .nearest_mode = AI_ROUND_PREFER_CEIL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  decoder_dense_1_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &decoder_dense_1_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &decoder_dense_1_dense_weights, &decoder_dense_1_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  decoder_dense_1_dense_layer, 1,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &decoder_dense_1_dense_chain,
  NULL, &decoder_conv2dT_1_conv2d_upsample_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 9540, 1, 1),
    9540, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 24512, 1, 1),
    24512, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VAE_IN_NUM, &decoder_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VAE_OUT_NUM, &decoder_output_output),
  &decoder_dense_1_dense_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 9540, 1, 1),
      9540, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 24512, 1, 1),
      24512, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VAE_IN_NUM, &decoder_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VAE_OUT_NUM, &decoder_output_output),
  &decoder_dense_1_dense_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool vae_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_vae_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    decoder_input_output_array.data = AI_PTR(g_vae_activations_map[0] + 16256);
    decoder_input_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 16256);
    
    decoder_dense_1_dense_output_array.data = AI_PTR(g_vae_activations_map[0] + 16320);
    decoder_dense_1_dense_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 16320);
    
    decoder_conv2dT_1_conv2d_upsample_output_array.data = AI_PTR(g_vae_activations_map[0] + 64);
    decoder_conv2dT_1_conv2d_upsample_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 64);
    
    decoder_conv2dT_1_conv2d_output_array.data = AI_PTR(g_vae_activations_map[0] + 16320);
    decoder_conv2dT_1_conv2d_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 16320);
    
    decoder_conv2dT_1_conv2d_pad_output_array.data = AI_PTR(g_vae_activations_map[0] + 64);
    decoder_conv2dT_1_conv2d_pad_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 64);
    
    decoder_conv2dT_1_output_array.data = AI_PTR(g_vae_activations_map[0] + 16320);
    decoder_conv2dT_1_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 16320);
    
    decoder_output_conv2d_upsample_output_array.data = AI_PTR(g_vae_activations_map[0] + 0);
    decoder_output_conv2d_upsample_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 0);
    
    decoder_output_conv2d_output_array.data = AI_PTR(g_vae_activations_map[0] + 16320);
    decoder_output_conv2d_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 16320);
    
    decoder_output_conv2d_pad_output_array.data = AI_PTR(g_vae_activations_map[0] + 0);
    decoder_output_conv2d_pad_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 0);
    
    decoder_output_output_array.data = AI_PTR(g_vae_activations_map[0] + 1024);
    decoder_output_output_array.data_start = AI_PTR(g_vae_activations_map[0] + 1024);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool vae_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_vae_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    decoder_conv2dT_1_conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    decoder_conv2dT_1_conv2d_weights_array.data = AI_PTR(g_vae_weights_map[0] + 0);
    decoder_conv2dT_1_conv2d_weights_array.data_start = AI_PTR(g_vae_weights_map[0] + 0);
    
    decoder_conv2dT_1_conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    decoder_conv2dT_1_conv2d_bias_array.data = AI_PTR(g_vae_weights_map[0] + 8192);
    decoder_conv2dT_1_conv2d_bias_array.data_start = AI_PTR(g_vae_weights_map[0] + 8192);
    
    decoder_output_conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    decoder_output_conv2d_weights_array.data = AI_PTR(g_vae_weights_map[0] + 8256);
    decoder_output_conv2d_weights_array.data_start = AI_PTR(g_vae_weights_map[0] + 8256);
    
    decoder_output_conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    decoder_output_conv2d_bias_array.data = AI_PTR(g_vae_weights_map[0] + 8512);
    decoder_output_conv2d_bias_array.data_start = AI_PTR(g_vae_weights_map[0] + 8512);
    
    decoder_dense_1_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    decoder_dense_1_dense_bias_array.data = AI_PTR(g_vae_weights_map[0] + 8516);
    decoder_dense_1_dense_bias_array.data_start = AI_PTR(g_vae_weights_map[0] + 8516);
    
    decoder_dense_1_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    decoder_dense_1_dense_weights_array.data = AI_PTR(g_vae_weights_map[0] + 9028);
    decoder_dense_1_dense_weights_array.data_start = AI_PTR(g_vae_weights_map[0] + 9028);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_vae_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_VAE_MODEL_NAME,
      .model_signature   = AI_VAE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 285137,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_vae_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_VAE_MODEL_NAME,
      .model_signature   = AI_VAE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 285137,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_vae_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_vae_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_vae_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_vae_create(network, AI_VAE_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_vae_data_params_get(&params) != true) {
        err = ai_vae_get_error(*network);
        return err;
    }
#if defined(AI_VAE_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_VAE_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_vae_init(*network, &params) != true) {
        err = ai_vae_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_vae_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_vae_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_vae_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_vae_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= vae_configure_weights(net_ctx, params);
  ok &= vae_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_vae_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_vae_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_VAE_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

