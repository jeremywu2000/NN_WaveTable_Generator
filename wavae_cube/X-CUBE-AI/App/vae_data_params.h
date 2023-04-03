/**
  ******************************************************************************
  * @file    vae_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Apr  3 14:12:36 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef VAE_DATA_PARAMS_H
#define VAE_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_VAE_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_vae_data_weights_params[1]))
*/

#define AI_VAE_DATA_CONFIG               (NULL)


#define AI_VAE_DATA_ACTIVATIONS_SIZES \
  { 24512, }
#define AI_VAE_DATA_ACTIVATIONS_SIZE     (24512)
#define AI_VAE_DATA_ACTIVATIONS_COUNT    (1)
#define AI_VAE_DATA_ACTIVATION_1_SIZE    (24512)



#define AI_VAE_DATA_WEIGHTS_SIZES \
  { 9540, }
#define AI_VAE_DATA_WEIGHTS_SIZE         (9540)
#define AI_VAE_DATA_WEIGHTS_COUNT        (1)
#define AI_VAE_DATA_WEIGHT_1_SIZE        (9540)



#define AI_VAE_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_vae_activations_table[1])

extern ai_handle g_vae_activations_table[1 + 2];



#define AI_VAE_DATA_WEIGHTS_TABLE_GET() \
  (&g_vae_weights_table[1])

extern ai_handle g_vae_weights_table[1 + 2];


#endif    /* VAE_DATA_PARAMS_H */
